.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _pro_export_data:

###########
Export Data
###########

*Fast DDS Monitor Pro* can export the data collected during a monitoring session in two formats:
CSV for chart data and JSON for the full statistics database.

Export Charts to CSV
====================

All data currently displayed in Chartboxes — both historical and real-time — can be exported to a
CSV file.
Three export scopes are available:

* **Single series**: export from the series context menu, as described in :ref:`chartbox_chart_menu`.
* **All series in a Chartbox**: export from the Chart menu of the Chartbox, as described in
  :ref:`chartbox_series_configuration`.
* **All series in all Chartboxes**: export from **File → Export Charts to CSV**, as described in
  :ref:`pro_application_menu_file`.

CSV File Format
---------------

The exported CSV file uses the following structure:

.. list-table::
    :header-rows: 4

    *   -
        - <DataKind>
    *   -
        - <Chartbox name>
    *   - ms
        - <DataKind units>
    *   - UnixTime
        - <Series name>
    *   - <unix_time>
        - <data_value>

Export Database to JSON
=======================

The full statistics database can be dumped to a JSON file using one of two options:

* **Dump**: exports the database without clearing it.
  See :ref:`pro_dump_button`.
* **Dump and Clear**: exports the database and clears all statistics data for all entities.
  See :ref:`pro_dump_clear_button`.
