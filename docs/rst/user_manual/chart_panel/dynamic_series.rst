.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _dynamic_series:

##############
Real-Time Data
##############

A **Dynamic** or **Real-Time** series displays the data that is being receiving by the monitor in the current moment.
This is a pseud-real-time display of a running DDS network.
Pseudo because it is not an exact representation of the DDS network activity in the exact moment it is represented,
but it represents a periodical update of the last seconds of the network.

Every data displayed is delayed by 5 seconds in order to accurately represent all the data reported by the network.
This is because the data is not instantly reported by Fast DDS, an thus it could be that the data used to update the
chart is not complete.

.. _create_dynamic_series:

Create Dynamic Series Chartbox
==============================
An static chartbox could only contain series referring the same *DataKind*.
In order to create a new chartbox in the central panel, use the button :ref:`display_data_button` in the
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
