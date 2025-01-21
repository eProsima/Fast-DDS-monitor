.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _historic_series:

#############
Historic Data
#############

.. _create_historic_series:

Create Historic Series Chartbox
===============================

In order to create a new static Chartbox in the central panel, use the button :ref:`display_historic_data_button`
in the :ref:`edit_menu` or in :ref:`shortcuts_bar_layout`. A static Chartbox can only contain series referring
the same *DataKind*.

Data Kind
---------
Select a *Datakind* to be represented. Check the common parameters explanation in :ref:`data_kind_parameter`.
Clicking `OK` will create a new Chartbox referring the *DataKind* chosen that will hold historic series.

.. _create_historic_series_dialog:

Create Historic Series Dialog
=============================
The :ref:`create_new_series_layout` allows users to create a new data series within a Chartbox.
The fields in the dialog configure the data that will be displayed.
When all the data has been set in the :ref:`create_historic_series_dialog`, press *Add* to create the series and
continue with the same parameter set in order to create a new series.
Press *Add & Close* to create the series and close the dialog.
Press *Close* to close the window without creating any series.

Series label
------------
Check the common parameters explanation in :ref:`series_label_parameter`.

Source Entity Id
----------------
Check the common parameters explanation in :ref:`source_entity_id_parameter`.

Target Entity Id
----------------
Check the common parameters explanation in :ref:`target_entity_id_parameter`.

.. _number_of_bins_parameter:

Number of bins
--------------
Number of *DataPoints* that will be displayed for this *Chart Series*.
The data is collected in individual points in every entity, without a regular time interval or pattern.
Therefore, to show the data in a more understandable manner, each of these points will be merged in a single point
inside a fraction of the time interval, following the *cummulative function* (see  :ref:`statistics_kind_parameter`).
The *Number of bins* determines how many fractions this time interval will be split in, and thus, how many points
will be displayed in the chart.
To see all the individual data points without accumulating them, set the *Number of bins* to 0.

.. note::

    When selecting *RAW_DATA* as the statistics kind, each bin will show the first data value received after
    the previous data point.

.. warning::

    Some of the data queried could not exist.
    In these cases the point will not be plotted, and the number of points in the
    series will not match with the number of bins.

.. _start_time_parameter:

Start time
----------
The time that represents the minimum limit for the data points that will be displayed.
That is, every data that refers to a time before this value will not be displayed.
*Default initial timestamp* refers to the time when the monitor was initialized.

.. _end_time_parameter:

End time
--------
The time that represents the maximum limit for the data points that will be displayed.
That is, every data that refers to a time after this value will not be displayed.
*Now* means the current time.
Be aware that the current time is not the maximum time that could be set up to see the data, but setting
a time later than *Now* would (obviously) not show any data points in the later time frames.

Statistics kind
---------------
Check the common parameters explanation :ref:`statistics_kind_parameter`.

Quick explanation of the data displayed
---------------------------------------
First, the application will create a complete list of data points by merging the data of all entities referred
to in this query.
(see the example in :ref:`source_entity_id_parameter`).

The current represented chart consists in a number of frames or bins, set by the :ref:`number_of_bins_parameter`
variable from the value :ref:`start_time_parameter` to the value :ref:`end_time_parameter`.
Inside one of this fractions of time, referred to as frames, there could be none, one or several data points.
If there are no data points in this frame, the value will be ``0`` or will not be displayed in the chart.
If there are data points in the frame, only one point will be displayed in the chart for this time frame.
This point will be calculated by accumulating all these points inside the frame by a *cumulative funcion*,
specified by the value :ref:`statistics_kind_parameter`.

In case the *Number of bins* is set to 0, there is no accumulation or time frame, and so the data displayed will be
all the data points for this configuration, each in its time value.

.. warning::

    Some of the data queried could not exist in the database for many reasons, i.e. the entity did not exist in
    the time where the query requires data, the entity does not report such data, or simply some data is reported
    with lower frequency than the one asked.
    In these cases, the graph would not be connected and the points where the data is not retrieved
    will not be shown.
