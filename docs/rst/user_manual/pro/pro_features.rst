.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _pro_features:

######################
Fast DDS Monitor |Pro|
######################

*Fast DDS Monitor Pro* is the commercial edition of *eProsima Fast DDS Monitor*.
It builds on the open-source version with more advanced monitoring capabilities, a richer interface, and
tooling designed for real production deployments.

.. note::

    All features described in this section are exclusive to *Fast DDS Monitor Pro*.

The following Pro features are covered in this section:

* :ref:`Multiple Monitor Support <multiple_monitors>` |Pro| to observe several DDS Domains, Discovery
  Servers, or XML-configured environments side by side in the same workspace.

* :ref:`Dockable Panes <dockable_panes>` |Pro| so that Charts, Spy Topic and IDL views open as freely
  positionable and splittable panes rather than fixed tab views.

* :ref:`Topic Charts <topic_charts>` |Pro| for plotting live numeric values from any DDS topic as a
  time-series chart, with support for multiple series, field selection, and pause/resume controls.

* :ref:`XY Charts <xy_charts>` |Pro| for plotting two numeric DDS topic fields against each other as a
  real-time scatter chart, enabling phase-space or correlation analysis between any pair of numeric fields
  within the same DDS domain.

* :ref:`Image Pane <image_pane>` |Pro| for rendering live image and video data from DDS topics inside the
  monitor, with automatic detection of ROS 2 sensor_msgs types and generic OMG IDL image types.

* :ref:`Topics Explorer <topics_panel>` |Pro| as a dedicated topic navigation panel in the left sidebar
  with text filtering, expandable field trees, and context actions for opening Spy or Topic Chart panes.

* :ref:`Workspace Save and Restore <workspace>` |Pro| to save the full workspace state to a file and
  reload it in a future session, preserving tab layouts, pane configurations, chart settings, alert rules,
  and tab order.

* :ref:`Right-Side Pane Configuration <right_pane_config>` |Pro| for creating and editing all pane types
  from an inline configuration sidebar, including statistics charts, topic charts, spy panes, IDL panes, and
  image panes, without opening separate dialogs.

* :ref:`Entity Summary Bar <entity_summary_bar>` |Pro| showing live counters for every type of monitored
  DDS entity at the bottom of the window, so the overall network size is always in view.

* :ref:`Dark Mode and Theming <theming>` |Pro| with a full theming system offering light and dark palettes
  applied consistently across the entire application including panels, charts, icons, and dialogs.
