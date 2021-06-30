.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _chart_panel:

############
Charts Panel
############

In the central panel or *chart panel*, is where the data of the entities will be displayed.
The main feature of the *Fast DDS Monitor* application is to graphically display the data that is being monitored.
DDS entities have associated different types of data (so-called *DataKind*) that could be visualize by configuring
a chart.
For example, it can be displayed the mean, median and standard deviation latency between two machines (*Hosts*) running
*Fast DDS* applications for the period of two hours in intervals of ten minutes.

Chart series
============
A *DataPoint* in a chart series in the *Fast DDS Monitor* refers to a specific data type of the DDS network monitoring.
Each *DataPoint* consists in a timestamp and a real value.
The *timestamp* is the moment the data has been created, reported, received, etc. depending on the *DataKind*.
The *value* refers to the real value of this *DataPoint* for this *DataKind* at the moment of the *timestamp* value.

For example, each *DataPoint* of the *DataKind* ``DATA_COUNT`` has a timestamp and an integer value.
This value is the number of ``Data packets`` a *DataWriter* sent since the last time that same data was reported.

.. todo::

    For a complete description of each *DataKind*, please refer to ...
    Add link to backend documentation once there is a first version.

Chart view
==========
Every *DataKind* is represented similarly inside a *Chartbox*.
None, one or multiple lines of different colors will represent the different data series that are being displayed
in the chart with the following format:

- The X axis is the time value of the data.
- The Y axis is the value that is store in the data.

This could be integers, doubles or times, but for the same *DataKind* will always be the same value type.
Every point represents an accumulated value of *DataPoints* of a data kind in a time range.

.. _create_serie:

Create Series Dialog
====================
This Dialog (:ref:`create_new_series_layout`) allows to create a new data series in a Chartbox.
The fields in the dialog configure the data that will be displayed
When all the data has been set in the :ref:`create_serie`, press *Apply* to create the series and continue with
the same parameters set in order to create a new series.
Pressing *OK* the actual parameters are used to create a new *series* unless it has not been any changed since
*Apply* has been pressed.
Press *Cancel* close the window without creating any series.

Series label
------------
Name the new series in the Chartbox.
If not set, the default series name is formed according to the following rule:
``<cumulative_function>_<source_entity_kind>_<target_entity_kind>-<target_entity_id>``.

.. _source_entity_id:

Source Entity Id
----------------
This is the name and *entity Id* of the entity from which the data will be collected in the format ``<name>:\<<id>\>``.
This field has an entity kind to encapsulate the ids of the entities with the same kind,
and make it easier for the user to search for the id required.

Each *DataKind* is related with one entity kind, normally a *DataWriter* or a *DataReader*,
which are the producers of that *DataKind*.
However, every entity kind is available to choose the data to represent.
When an entity without this type of data is selected, the monitor will look for the entities contained
in the specified entity that do report this specific *DataKind*.
For example, in case the user wants to represent the number of packets (``DATA_COUNT``) transmitted by a *Host*,
the monitor will look for all the *DataWriters* contained in that *Host* and report the total number of packets.

Continuing with the ``DATA_COUNT`` *DataKind* example, the monitor will find every *DataWriter* in this *Host*
by finding every *User* in this *Host*, then finding every *Process* in these *Users*, finding every
*DomainParticipant* in these *Processes* and finding every *DataWriter* in these *DomainParticipants*.
Hence, the data displayed will be all the data that all those *DataWriters* have stored, accumulated by the
cumulative function.
Please refer to :ref:`entities` section for more information on the monitor entities connections.

It is recommended to check some examples (see :ref:`start_tutorial`) in order to better understand this functionality.

Target Entity Id
----------------

.. note::

    Not every *DataKind* has a target entity, so the dialog will only show this field when the *DataKind* selected
    requires it.

This is the entity Id of the entity to which the data refers.
This field works similar to the :ref:`source_entity_id`.
Some *DataKind* has a target entity to which the data refers, and this target must be of an specific entity kind.
Choosing an entity of a different kind than the one this data requires will be solved by using the same
mechanism explained in :ref:`source_entity_id`.
That is, searching for the correct entity kind by following the connections between entities.

i.e. To show the *DataKind* ``FASTDDS_LATENCY``, that is reported by a *DataWriter*, and targeted to a *DataReader*,
from an entity ``Host_1`` to an entity ``Host_2``, both of kind *Host*, the data displayed would be collected
following the steps described below:

- Get all the *DataWriters* of ``Host_1`` by searching for its *Users*, their *Processes*, their
  *DomainParticipants* and their respective *DataWriters*.
- Get all the *DataReaders* of ``Host_2`` by searching for its *Users*, their *Processes*, their
  *DomainParticipants* and their respective *DataReaders*.
- Get all the data from the *DataWriters* found that refer to the *DataReaders* found inside the interval set.
- Accumulate the data using the *cumulative function*.

It is recommended to check some examples (:ref:`start_tutorial`) in order to better understand this functionality.

.. todo::

    Add link to backend documentation once there is a first version.

.. _number_of_bins:

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

.. _start_time:

Start time
----------
The time that represents the minimum limit for the data points that will be displayed.
That is, every data that refers to a time before this value will not be displayed.
*Default initial timestamp* means the time when the monitor has been initialized.

.. _end_time:

End time
--------
The time that represents the maximum limit for the data points that will be displayed.
That is, every data that refers to a time after this value will not be displayed.
*Now* means the current time.
Be aware that the current time is not the maximum time that could be set up to see the data, but setting
a time bigger than *Now* could (obviously) not have data points in the higher time frames.

.. _statistics_kind:

Statistics kind
---------------
The cumulative function is used to accumulate the data points that fulfilled the conditions set in this configuration.
When there are several data points to show in a single time frame these data points are transformed into one by
a *cumulative function*.
This function is the one set in *Statistics kind*.

The available methods to accumulate some data points into one are:

- *NONE*: returns the *DataPoint* with the lower time.
- *MEAN*: calculate the mean value of all the data points.
- *STANDARD_DEVIATION*: calculate the standard deviation of all the data points.
- *MAX*: returns the *DataPoint* with the maximum value.
- *MIN*: returns the *DataPoint* with the minimum value.
- *MEDIAN*: calculate the median of all the data points.
- *COUNT*: returns the number of *DataPoint* in this time frame.
- *SUM*: calculate the sum of all the data points.

In case the *Number of bins* is ``0`` the *Statistics kind* is not used as the data is not going to be accumulated.

Quick explanation of the data displayed
---------------------------------------
First, the application will create a complete list of data points by merging the data of all entities referred
to in this query.
(see the example in :ref:`source_entity_id`).

The current represented chart consists in a number of frames or bins, set by the :ref:`number_of_bins` variable
from the value :ref:`start_time` to the value :ref:`end_time`.
Inside one of this fractions of time, referred to as frames, there could be none, one or several data points.
If there are no data points in this frame, the value will be ``0`` or will not be displayed in the chart.
If there are data points in the frame, only one point will be displayed in the chart for this time frame.
This point will be calculated by accumulating all these points inside the frame by a *cumulative funcion*,
specified by the value :ref:`statistics_kind`.

In case the *Number of bins* is set to 0, there is no accumulation or time frame, and so the data displayed will be
all the data points for this configuration, each in its time value.

.. warning::

    Some of the data queried could not exist in the database for many reasons, i.e. the entity did not exist in
    the time where the query requires data, the entity does not report such data, or simply some data is reported
    with lower frequency than the one asked.
    In these cases, the graph could not be connected and the points where the data is not retrieved
    will not be shown.

.. _chartbox:

Chartbox
========

In this section it is explained the main functionalities and interactions available within a :ref:`chartbox_layout`,
a window contained in the :ref:`main_panel_layout` that displays entities data with different configurations.

To start a new Chartbox, press :ref:`display_historical_data_button` in :ref:`edit_menu` or in :ref:`shortcuts_bar`.

Clicking :ref:`display_historical_data_button`, a new Dialog will appear requesting to choose one of the data types
that are being collected in the application.
Once a chart has been set with a *DataKind* it could not be changed.
Nevertheless, new charts could be started with the same or different *DataKind*.

These charts will be displayed in the central panel with the title of the *DataKind* they refer to.
In these charts it will be displayed the Series of data that the user initialize.
For how to set a new series please refer to :ref:`create_serie`.

Chart Menu
----------
In the top bar of each Chartbox there is a Menu tab *Chart* with the following buttons.

Reset zoom
^^^^^^^^^^
Reset the zoom of the Chartbox to the standard one.
The standard zoom is calculated to fit all the data that is being currently displayed.

Clear chart
^^^^^^^^^^^
Eliminate every data configuration displayed in the Chartbox

Close chart box
^^^^^^^^^^^^^^^
Eliminate the Chartbox and every configuration in it.
It could be removed as well pressing the ``x`` button in the top of the chart.

Series Menu
-----------
In the top bar of each Chartbox there is a Menu tab *Series* with these buttons.

Add series
^^^^^^^^^^
Add a new series in this Chartbox.
This will open a new :ref:`create_serie`.

Hide all series
^^^^^^^^^^^^^^^
Hide all series in this Chartbox.

Display all series
^^^^^^^^^^^^^^^^^^
Reveal all series in this Chartbox.

Chart Interaction
-----------------
The user could interact with the Chartbox and the data in it by resizing and moving the view.

Point description
^^^^^^^^^^^^^^^^^
Clicking in any point of a displayed series, an info box will be prompt with the ``x`` and ``y``
label values of the data point.

Moving the view
^^^^^^^^^^^^^^^
Press and hold ``Ctrl`` key and left click in one point of the Chartbox.
Move the mouse to scroll over the data.

Zoom in/out
^^^^^^^^^^^
Press and hold ``Ctrl`` key and scroll up to zoom in to the center of the Chartbox.
Press and hold ``Ctrl`` key and scroll down to zoom out from the center of the Chartbox.

Series Configuration
--------------------
Right clicking in the name of a series in the *Legend* will open a dialog with the available configurations for
a series.

Remove series
^^^^^^^^^^^^^
Remove this series.

Rename series
^^^^^^^^^^^^^
Change the name of this series.

Change color
^^^^^^^^^^^^
A Dialog will open to choose a new color for the series and the points displayed.
Also available with left click on the color of the series in the *Legend*.

Hide/Show series
^^^^^^^^^^^^^^^^
Hide a series if it is displayed, or it reveal it if it is hide.
Also available with left click on the name of the series in the *Legend*.
