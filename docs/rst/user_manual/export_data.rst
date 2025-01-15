.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _export_data:

###########
Export data
###########

One of the main functionalities of the *Fast DDS Monitor* is the possibility of exporting the data generated in each
monitoring session. The different monitor capabilities for exporting user data are explained below.

Export charts in a CSV file
===========================

The monitor offers the possibility to export to a CSV file all the data that has been or is being represented in
each of the *Chartboxes*, for both historical and real-time charts.

Thus, the monitor offers the user three possibilities:

 * Export the data of a single series.
   This can be done from the series menu as explained in section :ref:`chartbox_chart_menu`.
 * Export the data of all the series belonging to a *Chartbox*.
   This can be done from the *Chart* menu available in each *Chartbox*. This menu is explained in section
   :ref:`chartbox_series_configuration`.
 * Export all the data of all the series of all the *Chartboxes*.
   This is done from the application *File* menu, as explained in section :ref:`application_menu_file`.

Format of the CSV file
----------------------

This section presents a table with the format of the CSV file containing the exported data.

.. list-table::
    :header-rows: 4

    *   -
        - <DataKind>
    *   -
        - <Chart box name>
    *   - ms
        - <DataKind units>
    *   - UnixTime
        - <Series name>
    *   - <unix_time>
        - <data_value>

Export database in a JSON file
==============================

The monitor gives you the option to dump the data from the database to a JSON file.

Thus the monitor provides the user two options:

  * Dump.
    Explained in section :ref:`dump_button`.
  * Dump and clear.
    Explained in section :ref:`dump_clear_button`.

Format of the JSON file
-----------------------

This section presents a JSON with the format of the JSON file containing the exported data.

.. code-block:: json

    {
        "datareaders":{},
        "datawriters":{},
        "domains": {
            "0": {
                "alias":"0",
                "alive":true,
                "metatraffic":false
                "name":"0",
                "participants":[],
                "topics":[]
            }
        },
        "hosts":{},
        "locators":{},
        "participants":{},
        "processes":{},
        "topics":{},
        "users":{},
        "users":{},
    }
