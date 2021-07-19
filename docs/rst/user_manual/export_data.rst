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

The monitor offers the possibility to export to a CSV file all the data that have been or are being represented in
each of the charts boxes, both historical and real-time charts.

Thus the monitor offers the user three possibilities:

 * Export the data of a single series.
   This can be done from the series menu explained in section :ref:`chartbox_chart_menu`.
 * Export the data of all the series belonging to a chart box.
   This can be done from the *Chart* menu available in each chart box. This menu is explained in section
   :ref:`chartbox_series_configuration`.
 * Export all the data of all the series of all the chart boxes.
   This is done from the application *File* menu, explained in section :ref:`application_menu_file`.

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
