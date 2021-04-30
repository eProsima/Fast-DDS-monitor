.. include:: ../exports/alias.include

.. _chart_panel:

###########
Chart Panel
###########

Functionality related with :ref:`main_panel_layout`.

Data Types
==========
A Data or *Data Point* in the Monitor refers to a specific data type of the DDS network monitoring.
Each data point consists in a time and a value.
The time is the moment the data has been created, reported, received, etc. depending on the *DataKind*.
The value refers to the value of this *DataKind* in the particular moment that represents the time of the data.

i.e. each data point of the *DataKind* ``DATA_COUNT`` has a time and an integer value, and it is stored in a
*DataWriter*.
This data point value refers to the number of *Data* this *DataWriter* sent since the last time this data was reported
to the time this data has.

Hence, the representation of all the *DataKinds* will be similar. \
The Y axis is the time value of the data. \
The X axis is the value that is store in the data.
This could be integers, doubles or times, but for the same *DataKind* will be always the same value type.

For a complete description of each *DataKind*, please refer to.

.. todo::

    Add link to backend documentation once there is a first version.

.. _create_serie:

Create Serie Dialog
===================
This Dialog (:ref:`create_new_series_layout`) allows to create a new *Serie* or data representation in a Chartbox.
The fields in the dialog configure the data that will be displayed

Series label
------------
Name that this new serie will have in the Chartbox. \
If not set, the default name of a serie is ``<cumulative_function>_<entity_kind>-<number_of_binds>``.

.. _source_entity_id:

Source Entity Id
----------------
This is the entity Id of the entity that the data will be collected from.
This field has an entity kind to encapsulate the ids of the entities with the same kind, and make it easier to
search for the id required.

Each *DataKind* is related with one entity kind, normally a *DataWriter* or a *DataReader*, where this data is stored.
However, every entity kind is available to choose the data to represent.
This is because choosing an entity that has not this data associated, it is possible to find all the connected entities
to this one by the entity connections (visit section :ref:`entities` for more information).

i.e. To show the *DataKind* ``HEARTBEAT_COUNT``, that is stored in a *DataWriter*, for an entity of kind *Host*, the
application will find every *DataWriter* in this *Host* by finding every *User* in this *Host*, then finding every
*Process* in these *Users*, finding every *Participant* in these *Processes* and finding every *DataWriter* in these
*Participants*.
Hence, the data displayed will be all the data that all those *DataWriters* have stored, accumulated by the
cumulative function.

It is recommended to check some examples (:ref:`start_tutorial`) in order to better understand this functionality.

Target Entity Id
----------------

.. note::

    Not every *DataKind* has a target, so the dialog will only show this field when the *DataKind* selected
    requires it.

This is the entity Id of the entity that the data refers to. \
This field works similar to the :ref:`source_entity_id`.
Some *DataKind* has a target entity that the data refers to, and this target must be of an specific entity kind.
Choosing an entity of a different kind than the one this data requires, will be solved by using the same
mechanism explained in :ref:`source_entity_id`.
That is, searching for the correct entity kind by following the connections between entities.

i.e. To show the *DataKind* ``FASTDDS_LATENCY``, that is stored in a *DataWriter*, and targeted to a *DataReader*,
from an entity ``Host_1`` to an entity ``Host_2``, both of kind *Host*, the data displayed would be collected
like this:

- Get all the *DataWriters* of ``Host_1`` by searching for its *Users*, their *Process*, their *Participants* and
  their respective *DataWriters*.
- Get all the *DataReaders* of ``Host_2`` by searching for its *Users*, their *Process*, their *Participants* and
  their respective *DataReaders*.
- Get all the data from the *DataWriters* found that refer to the *DataReaders* found inside the interval set.
- Accumulate the data by the *cumulative function*.

It is recommended to check some examples (:ref:`start_tutorial`) in order to better understand this functionality.

.. todo::

    Add link to backend documentation once there is a first version.

.. _number_of_bins:

Number of bins
--------------
Number of points that will be displayed for this data.

The data is collected in individual points in every entity, without a regular time interval or pattern.
Therefore, to show the data in a better understandable manner, each of these points will be merged in a single point
inside a fraction of the time interval.
The *Number of bins* determines how many fractions this time interval will be split on, and thus, how many points
will be displayed in the chart.

To see all the individual without accumulate them and divide them in regular time frames, set the *Number of bins* to 0.

.. _start_time:

Start time
----------
The time that represents the minimum limit for the data points that will be displayed.
That is, every data that refers to a time before this value will not be displayed. \
*Default initial timestamp* means the lower time that the data stored with this data configuration has.

.. _end_time:

End time
--------
The time that represents the maximum limit for the data points that will be displayed.
That is, every data that refers to a time after this value will not be displayed. \
*Now* means the current time.
Be aware that the current time is not the maximum time that could be set up to see the data, but setting
a time biggest than *Now* will (obviously) not have data points.

.. _statistics_kind:

Statistics kind
---------------
The cumulative function use to accumulate the data points that fulfilled the conditions set in this configuration. \
When in a single time frame there are several data points to show, these data points are transformed into one by
a *cumulative function*.
This function is the one that *Statistics kind* is set to.

The available methods to accumulate some data points into one are:

- *NONE*: returns the data point with the lower time.
- *MEAN*: calculate the mean value of all the data points.
- *STANDARD_DEVIATION*: calculate the standard deviation of all the data points.
- *MAX*: returns the data point with the maximum value.
- *MIN*: returns the data point with the minimum value.
- *MEDIAN*: calculate the median of all the data points.
- *COUNT*: returns the number of data point in this time frame.
- *SUM*: calculate the sum of all the data points.

In case the *Number of bins* is ``0`` the *Statistics kind* is not used as the data are not going to be accumulated.

Quick explanation of the data displayed
---------------------------------------
First, the application will create a whole list of data points by merging the data from all the entities this query
makes reference to (visit example in :ref:`source_entity_id`).

The actual chart that will be represented consists in a number of frames, set by variable :ref:`number_of_bins`,
each of them with same time lengths from the value :ref:`start_time` to the value :ref:`end_time`.
Inside one of this fractions of time, that we will call time frames, there could be none, one or several data points. \
If there are no data points in this frame, the value will be ``0`` or will not be displayed in the chart. \
If there are data points in the frame, only one point will be displayed in the chart for this time frame.
This point will be calculated by accumulating all these points inside the frame by a *cumulative funcion*,
specified by the value :ref:`statistics_kind`. \

In case the *Number of bins* is set to 0, there is no accumulation or time frame, and so the data displayed will be
all the data points for this configuration, each in its time value.

.. _chartbox:

Chartbox
========

In this section it is explained the main functionalities and interactions available with a :ref:`chartbox_layout`,
an inside window in :ref:`main_panel_layout` that displays entities data with different configurations.

To start a new Chartbox, press :ref:`display_data_button` in :ref:`edit_menu` or in :ref:`shortcuts_bar`.

Clicking :ref:`display_data_button`, a new Dialog will appear asking to choose one of the data types that are
being collected in the application. \
Once a chart has been set with a data type (aka *DataKind*) it could not be changed.
Nevertheless, new charts could be started with the same or different *DataKind* without limits.

These charts will be displayed in the central panel with the title of the *DataKind* they refer to.
In these charts it will be displayed the Series of data that the user initialize.
For how to set a new serie please refer to :ref:`create_serie`.

Chart Menu
----------
In the top bar of each Chartbox there is a Menu tab *Chart* with these buttons.

Reset zoom
^^^^^^^^^^
Reset the zoom of the Chartbox to the standard one.
The standard zoom is calculated to fit all the data that is being currently displayed.

Clear chart
^^^^^^^^^^^
Eliminate every data configuration displayed in the Chartbox

Remove chart
^^^^^^^^^^^^
Eliminate the Chartbox and every configuration in it.

Series Menu
-----------
In the top bar of each Chartbox there is a Menu tab *Series* with these buttons.

Add series
^^^^^^^^^^
Add a new serie in this Chartbox.
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
Left click in any point in a data displayed will show an info box with the x and y label values of the point.

Moving the view
^^^^^^^^^^^^^^^
Press and hold ``Ctrl`` key and left click in one point of the Chartbox.
Move the mouse to move the all data and the labels at once.

Zoom in/out
^^^^^^^^^^^
Press and hold ``Ctrl`` key and scroll up to zoom in to the center of the Chartbox.
Press and hold ``Ctrl`` key and scroll down to zoom out from the center of the Chartbox.

Series Configuration
--------------------
Right click in the name of the serie in the *Legend* will open a dialog with the available configurations for a serie.

Remove serie
^^^^^^^^^^^^
Remove this serie.

Rename serie
^^^^^^^^^^^^
Change the name of this serie.

Change color
^^^^^^^^^^^^
A Dialog will open to choose a new color for the e and the points displayed.
Also available with left click on the color of the serie in the *Legend*.

Hide/Show serie
^^^^^^^^^^^^^^^
Hide a serie if it is displayed, or it reveal it if it is hide.
Also available with left click on the name of the serie in the *Legend*.
