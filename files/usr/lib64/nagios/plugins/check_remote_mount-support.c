/*
 * This program is meant to check for shared folder mounted on the system.
 *
 * With shared folders (especialli Samba ones) it can happen that the server
 * becomes unresponsive without closing the connection. In this situation any
 * low-level operation on that tree will get stuck, with no timeout and it's not
 * possible to check the mount point with a simple "does a file exist".
 * This programs creates a child process that checks a file while, at the same
 * time, the main process checks if the child gets stuck with a timeout.
 *
 * Compile with:
 *   gcc -O3 -o check_remote_mount-support check_remote_mount-support.c
 *
 * Debug compile with:
 *   gcc -Wall -D__DEBUG__ -DDEFAULT_TIMEOUT=15 -std=c99 -o check_remote_mount-support check_remote_mount-support.c
 *   gcc -Wall -D__DEBUG__ -std=c99 -o check_remote_mount-support check_remote_mount-support.c
 *
 * Fabrizio Colonna - <colofabrix@tin.it> - 12/06/2015
 */

#define _POSIX_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>


// Default timeout for the child process
#define DEFAULT_TIMEOUT 6

// PID of the child process
pid_t child_pid;


/**
 * Check that can open a specific file or directory
 *
 * @param filepath Full path to the file to check. The file must exist
 * @return EXIT_SUCCESS if the file is present and readable, EXIT_FAILURE otherwise 
 */
int check_file( const char* filepath )
{
    FILE* file_ptr;

    // Open a file and check if I can do it
    //
#ifdef __DEBUG__
    printf( "CHILD: Trying to open the file %s\n", filepath );
#endif
    file_ptr = fopen( filepath, "r" );
    if( file_ptr == NULL )
    {
#ifdef __DEBUG__
        printf( "CHILD: Error opening file - %s\n", strerror(errno) );
#endif
        return EXIT_FAILURE;
    }

    // All good. Close and exit
#ifdef __DEBUG__
    printf( "CHILD: File opened, close it and return success\n" );
#endif
    fclose( file_ptr );
    return EXIT_SUCCESS;
}


/**
 * Alarm handler, to kill the child process
 *
 * @see Check the manpage: man 2 signal
 */
void alrm_handler( int signo )
{
    int tmp;

    // Kill the process and acknowledge its termination instead of letting the main
    // procedure do it. In this way the main procedures returns with an error.
#ifdef __DEBUG__
    printf( "PARENT: Timeout, killing the child and waiting\n" );
#endif
    kill( child_pid, SIGKILL ); 
    waitpid( child_pid, &tmp, 0 );
#ifdef __DEBUG__
    printf( "PARENT: Exit with status 1\n" );
#endif
    exit( EXIT_FAILURE );
}


/**
 * Main program
 *
 * @param argv[1] Full path to the file to check. The file must exist
 * @return EXIT_SUCCESS if the file is present and readable, EXIT_FAILURE otherwise 
 */
int main( int args, char* argv[] )
{
    int child_status;

    // Checking input arguments (Don't care if there are excess arguments)
    if( args < 2 )
    {
        exit( EXIT_FAILURE );
    }

    // Fork!
    child_pid = fork();
 
    if( child_pid == -1 )
    {
        // Error in fork, exit with failure
        perror( "Fork failed: " );
        exit( EXIT_FAILURE );
    }
    else if( child_pid == 0 )
    {
        // Child checks the file and return its status
        _exit( check_file( argv[1] ) );
    }
    else
    {
        // Parent checks for children's task

        // Setup an alarm to kill the child in case of problems
        signal( SIGALRM, alrm_handler );
        alarm( DEFAULT_TIMEOUT );

        // Wait for child
#ifdef __DEBUG__
        printf( "PARENT: Waiting for child termination\n" );
#endif
        waitpid( child_pid, &child_status, 0 );

        if( WIFEXITED( child_status ) )
        {
            // Child exited of its own. Return its status
#ifdef __DEBUG__
            printf( "PARENT: Child terminated normally with return status %d\n", WEXITSTATUS( child_status ) );
#endif
            exit( WEXITSTATUS( child_status ) );
        }
        else
        {
            // Child exited forcefully. Return failure
#ifdef __DEBUG__
            printf( "PARENT: Problem with child termination\n" );
#endif
            exit( EXIT_FAILURE );
        }
    }
}
