Role Name
=========

Configures a specific client to be checked by Nagios.

The roles installs and configure NRPE on the local hosts and the relevant configuration on the Nagios servers


Defined Variables
-----------------

Variables that are defined in this role

| Variable                   | Default   | Description                                                    |
| :---                       | :---      | :---                                                           |
| `nagios_nrpe_enabled`      | false     | Enable NRPE to accept incoming requests.                       |
| `nagios_sms_alerts`        | false     | If true will set Nagios to send alerts via SMS.                |
| `nagios_critical_host`     | false     | If true Nagio will setup the host as Critical.                 |


Managed Variables
-----------------

Variables that are created manipulating existing values. This variables should not be
modified unsless you know what you are doing.

| Variable                   | Default                                    | Description                                                  |
| :---                       | :---                                       | :---                                                         |


Encrypted Variables
-------------------

Variables that must be kept encrypted

| Variable                    | Description                                          |
| :---                        | :---                                                 |


Used Variables
--------------

Variables that are defined outside the role and used by it

| Variable          | Description                                        |
| :---              | :---                                               |


Target Groups
-------------

Groups that the role will use to configure the system. These are defined in the inventories.

| Group          | Description                                                  |
| :---           | :---                                                         |
| `nagios`       | The Nagios servers that will check the machine.              |


Role Tags
--------------

| Tag          | Description                                  |
| :---         | :---                                         |


Dependencies
------------

No dependencies.


Example Playbook
----------------


TODO
------------

List of things to be done.


Known Bugs
------------

List of known bugs.
