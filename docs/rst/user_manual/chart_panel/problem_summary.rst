.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _problem_summary_panel:

#####################
Problem Summary Panel
#####################

This section that can be expanded and collapsed displays all the collected problems per entity.
Those problems are related to DataReader samples lost, incompatible QoS between endpoints, or DataWriter deadline
missed counter, for instance. The entities that have reported a problem would display a warning or an error icon
close to the entity name, based on the severity of the problem. The entity representation in the domain graph may
also display that icon.

.. thumbnail:: /rst/figures/screenshots/problem.png
    :align: center

Error Messages
==============

Error messages correspond to serious issues in the communication between DDS entities, preventing them from
communicating. The entities that present these issues display an error icon close to their entity name.
There is only one type of error that can be reported,  :code:`INCOMPATIBLE_QOS`.

- :code:`INCOMPATIBLE_QOS`: This error is reported when the QoS of the DataWriter and DataReader are incompatible.
  This means that the DataWriter and DataReader have different QoS policies, and present a combination that prevents
  them from communicating. The error message informs the user about the entities that present the issue, and lists
  which specific QoS policies are incompatible. Finally, it also presents applicable links to the documentation.

Warning Messages
================

Warning messages correspond to less severe issues in the communication between DDS entities than error messages, but
still require attention. The entities that present these issues display a warning icon close to their entity name.
The warning messages that can be reported are as following:

- :code:`LIVELINESS_LOST`: This warning is reported when a DataWriter has lost liveliness. This warning also informs
  the user about the number of times the liveliness has been lost.

- :code:`DEADLINE_MISSED`: This warning is reported when an entity misses a deadline, and informs the user about the
  number of times a deadline has been missed.

- :code:`SAMPLE_LOST`: This warning is reported when an entity has lost samples, informing the user about the number of
  samples lost.
