.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _chart_panel:

############
Charts Panel
############

In this panel will be displayed the different chartbox with the different series the user creates.

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

Chartbox kinds
==============

There are two kinds of Chartbox that could be created, historic and dynamic.

- The **historic**  chartbox represents static data that has been accumulated along the monitor execution.
  This data is not updated with new data or refreshed in case somethings has changed.
  See the details of this chartbox kind in section :ref:`historic_series`.
- The **dynamic** or **real-time** chartbox represents the new data that is being collected in real time by the monitor.
  These series will update over time with the new data received from a DDS network, and so the new data will be
  displayed in pseudo-real-time.
  See the details of this chartbox kind in section :ref:`dynamic_series`.

Common Series parameters
==========================

Some of the parameters of the chartbox creations remains on the kind of chartbox to create.
The ones mentioned here are the common parameters used by the two kinds of chartbox.

.. _data_kind_parameter:

Data kind
---------

The *DataKind* refers to the data that this chartbox will refer to.
There are several *DataKinds* that represent each of the data kinds that a Fast DDS network can report.
(Be aware that by default a DDS network will not report most of this data, and in case of Fast DDS it must be
configured beforehand in order to report it periodically).

.. todo::

    For a complete description of each *DataKind*, please refer to ...
    Add link to backend documentation once there is a first version.

.. _series_label_parameter:

Series label
------------
Name the new series in the Chartbox.
If not set, the default series name is formed according to the following rule:
``<cumulative_function>_<source_entity_kind>-<target_entity_id>_<target_entity_kind>-<target_entity_id>``.

.. _source_entity_id_parameter:

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

.. _target_entity_id_parameter:

Target Entity Id
----------------

.. note::

    Not every *DataKind* has a target entity, so the dialog will only show this field when the *DataKind* selected
    requires it.

This is the entity Id of the entity to which the data refers.
This field works similar to the :ref:`source_entity_id_parameter`.
Some *DataKind* has a target entity to which the data refers, and this target must be of an specific entity kind.
Choosing an entity of a different kind than the one this data requires will be solved by using the same
mechanism explained in :ref:`source_entity_id_parameter`.
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

.. _statistics_kind_parameter:

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
