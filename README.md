# nrpe-client

This role installs the NRPE client on a monitoring server.

## Requirements

None.

## Role Variables

### Default usage

For default usage of this role you only need to define the following, for more advanced usage look at the [Advanced usage](#advanced-usage) section:
```yaml
# Sets the hosts allowed to connect to NRPE
nrpe_allowed_hosts:
  - 127.0.0.1
```

### Advanced usage

For more advanced usage the following variables are available:
```yaml
# The directory where the downloaded files will be placed and extracted.
download_dir: "{{ ansible_env.HOME }}/nrpe"

# The version of NRPE to be installed
nrpe_version: 4.0.2

# The NRPE download url
nrpeurl: "https://github.com/NagiosEnterprises/nrpe/archive/nrpe-{{ nrpe_version }}.tar.gz"

# The name of the untarred NRPE directory
nrpesrc: "nrpe-nrpe-{{ nrpe_version }}"

# The user which the NRPE daemon runs as
nrpe_user: nagios

# The group which the NRPE daemon runs as
nrpe_group: nagios

# Determines if the NRPE daemon will allow clients to specify arguments to commands that are executed. Change to 1 to enable
nrpe_dont_blame_nrpe: 0
```

## Dependencies

This role doesn't have any strict dependencies but can be used with [wilmardo/nagios](https://galaxy.ansible.com/wilmardo/nagios/).

## Example Playbook

Install NRPE and setup the allowed_hosts.
It is better to move the `nrpe_allowed_hosts` to host_vars of your project but this will work.
```yaml
- hosts: monitoring-servers
  roles:
     - { role: nrpe-client, nrpe_allowed_hosts [ 127.0.0.1, 192.168.1.100 ] }
```

## License

BSD-3-Clause-Clear

## Author Information

