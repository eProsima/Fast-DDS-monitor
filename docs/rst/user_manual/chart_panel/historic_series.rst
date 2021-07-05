.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _historic_series:

#############
Historic Data
#############

Create Historic Series Chartbox
===============================

An static chartbox could only contain series referring the same *DataKind*.
In order to create a new chartbox in the central panel, use the button :ref:`display_historic_data_button` in the
:ref:`edit_menu` or in :ref:`shortcuts_bar_layout`.

Data Kind
---------
Check common parameters explanation :ref:`data_kind_parameter`.

Clicking `OK` will create a new chartbox referring the *DataKind* chosen that will hold historic series.

.. _create_historic_series:

Create Historic Series Dialog
=============================
The Dialog (:ref:`create_new_series_layout`) allows to create a new data series in a Chartbox.
The fields in the dialog configure the data that will be displayed
When all the data has been set in the :ref:`create_historic_series`, press *Apply* to create the series and continue
with the same parameters set in order to create a new series.
Pressing *OK* the actual parameters are used to create a new *series* unless it has not been any changed since
*Apply* has been pressed.
Press *Cancel* close the window without creating any series.

Series label
------------
Check common parameters explanation :ref:`series_label_parameter`.

Source Entity Id
----------------
Check common parameters explanation :ref:`source_entity_id_parameter`.

Target Entity Id
----------------
Check common parameters explanation :ref:`target_entity_id_parameter`.

.. _number_of_bins_parameter:

Number of bins
--------------
Number of *DataPoints* that will be displayed for this chart series.
The data is collected in individual points in every entity, without a regular time interval or pattern.
Therefore, to show the data in a better understandable manner, each of these points will be merged in a single point
inside a fraction of the time interval.
The *Number of bins* determines how many fractions on which this time interval will be split, and thus, how many points
will be displayed in the chart.
To see all the individual data points without accumulate them, set the *Number of bins* to 0.

.. warning::

    Some of the data queried could not exist.
    In these cases the point will not be plotted, and the number of points in the
    series will not match with the number of bins.

.. _start_time_parameter:

Start time
----------
The time that represents the minimum limit for the data points that will be displayed.
That is, every data that refers to a time before this value will not be displayed.
*Default initial timestamp* means the time when the monitor has been initialized.

.. _end_time_parameter:

End time
--------
The time that represents the maximum limit for the data points that will be displayed.
That is, every data that refers to a time after this value will not be displayed.
*Now* means the current time.
Be aware that the current time is not the maximum time that could be set up to see the data, but setting
a time bigger than *Now* could (obviously) not have data points in the higher time frames.

Statistics kind
---------------
Check common parameters explanation :ref:`statistics_kind_parameter`.

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
    In these cases, the graph could not be connected and the points where the data is not retrieved
    will not be shown.
