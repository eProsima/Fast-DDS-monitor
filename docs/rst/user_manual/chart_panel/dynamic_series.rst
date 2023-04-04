.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _dynamic_series:

##############
Real-Time Data
##############

A **Dynamic** or **Real-Time** series displays the data that is being receiving by the monitor in the current moment.
This is a pseudo-real-time display of a running DDS network.
Pseudo because it is not an exact representation of the DDS network activity in the exact moment it is represented,
but it represents a periodical update of the last seconds of the network.

Every data displayed is delayed by 5 seconds in order to accurately represent all the data reported by the network.
This is because the data is not instantly reported by Fast DDS, an thus it could be that the data used to update the
chart is not complete.

.. _create_dynamic_series:

Create Dynamic Series Chartbox
==============================
An static chartbox could only contain series referring the same *DataKind*.
In order to create a new chartbox in the central panel, use the button :ref:`display_dynamic_data_button` in the
:ref:`edit_menu` or in :ref:`shortcuts_bar_layout`.

A new dialog will appear asking to choose some parameters that will be share for all the new series created in this
new chartbox.

Data Kind
---------
Check common parameters explanation :ref:`data_kind_parameter`.

.. _time_window_parameter:

Time window
-----------
This parameter is the default size and value of the X axis.
The X axis will be set by default to have the current moment to the rightmost point.
The X axis leftmost point will be the current time minus the size of the `Time window`.

.. _update_period_parameter:

Update period
-------------
This parameter refers to the time elapsed between two updates of the chartbox series.
Each of the series inside the chartbox will be updated with the new data collected every `Update period` seconds.

.. _chart_panel_maximum_data_points:

Maximum data points
-------------------
This parameter set the default for the maximum amount of data points that the series in this charbox will have.
Check series :ref:`series_maximum_data_points` section for more information.

Clicking `OK` will create a new chartbox referring the *DataKind* chosen that will hold dynamic series.

Create Dynamic Series Dialog
============================
This Dialog (:ref:`create_new_series_layout`) allows to create a new data series in a Chartbox.
The fields in the dialog configure the data that will be displayed
When all the data has been set in the :ref:`create_dynamic_series`, press *Apply* to create the series and continue with
the same parameters set in order to create a new series.
Pressing *OK* the actual parameters are used to create a new *series* unless it has not been any changed since
*Apply* has been pressed.
Press *Cancel* close the window without creating a new series with the current parameters.

Series label
------------
Check common parameters explanation :ref:`series_label_parameter`.

Source Entity Id
----------------
Check common parameters explanation :ref:`source_entity_id_parameter`.

Target Entity Id
----------------
Check common parameters explanation :ref:`target_entity_id_parameter`.

Statistics kind
---------------
This parameter behaves as it is explained in :ref:`statistics_kind_parameter` except for *NONE* kind.
Selecting *NONE* as Statistics kind will display every data available in the interval of time given by
:ref:`update_period_parameter` with no accumulation.

.. note::

    The data will not be displayed at the time it arrives in any case.
    It will always appear displayed after each :ref:`update_period_parameter`.

.. _series_maximum_data_points:

Maximum data points
-------------------
This parameter limits the number of data points that will be showed for this specific series.
Data points will be added dynamically to the series.
This can, at some point, generate an efficiency problem due to memory exhaustion.
In order to avoid this, this parameter will limit the number of data points,
removing the old data as new ones are being added.
Use value ``0`` for not limited series.

This value can be changed by series at any time in the series menu.


Cumulative data
---------------

This option allows the user to define the time interval for which the statistic selected in "Statistic kind" is to be
calculated.
That is, in case the user selects a time interval to obtain accumulated statistics data, the statistics will be applied
to all the data collected by the monitor in that defined time interval.
This allows the update interval of the chart and the time interval for calculating the statistics to be independent.

Let's look into a simple example of monitoring the latency of a publisher and a subscriber in the Shapes Demo
application launched with statistics enabled (a detailed example of Fast DDS Monitor monitoring a Shapes Demo
application is shown in the following `video tutorial <https://www.youtube.com/watch?v=6ZEb0a7Ei4Y>`_).
First, a chart is created to monitor the application latency with a time window of 5 minutes and an update period of
5 seconds.
Then the dialog box for creating series in the graph is opened.
Select your host as source and target entities and the DataWriters and DataReaders running on your machine will be
automatically detected.
Select the mean as the type of statistical measurement to be applied.
Finally, create three series with three different types of accumulation:

- **No accumulation**.
  The average latency between publisher and subscriber in the last update period, 5 seconds in this particular case,
  is calculated.
- **With accumulation from the first available data point**.
  This calculates the average latency between publisher and subscriber from the time the monitor has the first
  available data until the current time.
  This current instant is updated every update period, adding new points to the calculated statistic.
- **With accumulation by setting a time interval**.
  The average latency between publisher and subscriber is calculated from the current time minus the cumulative time
  interval set until the current time.

Below is an image of the three series created. It can be seen that the series with a longer accumulation period tends
to have a steady latency value, being less susceptible to strong but momentary latency variations.
On the contrary, the series that calculates the average latency with the available data of the last 5 seconds shows a
large variation due to the smaller number of data points available for the calculation of the statistic.

.. figure:: /rst/figures/screenshots/cumulative_chart.png
    :align: center

Quick explanation of the data displayed
---------------------------------------
First, the application will create an empty chart where X axis represents the time between the current moment and
that time minus the :ref:`time_window_parameter` size.
This window is permanently moving in order to always represent the current time.
This X axis movement could be paused in order to move and resize the chart at any moment,
and new data will still appear.

Every :ref:`update_period_parameter` new data will be displayed in the right side of the chart.
The new data displayed references the accumulative value of the data that has been stored in that amount of time.

.. warning::

    Some of the data queried could not exist in the database for many reasons, i.e. the entity did not report anything
    in the time where the query requires data.
    In these cases, after an :ref:`update_period_parameter` there will not appear any point and the chart will be
    connected with the next interval with data.
