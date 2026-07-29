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

Except for the basic functionalities inherited from the *Fast DDS Monitor Basic*, it includes the following Pro features:

* :ref:`Dockable Panes <dockable_panes>` |Pro| so that Charts, Spy Topic and IDL views open as freely
  positionable and splittable panes rather than fixed tab views.

* :ref:`Dark Mode and Theming <theming>` |Pro| with a full theming system offering light and dark palettes
  applied consistently across the entire application including panels, charts, icons, and dialogs.

* :ref:`Multiple Monitor Support <multiple_monitors>` |Pro| to observe several DDS Domains, Discovery
  Servers, or XML-configured environments side by side in the same workspace.

* :ref:`Offline Mode <offline_mode>` |Pro| for opening a captured DDS recording (MCAP or SQLite) and
  inspecting it with full playback control - scrub, play, pause, loop, and change speed through the
  recorded timeline.

* :ref:`Domain Removal <pro_stop_monitor>` |Pro| to stop monitoring a specific domain at any time, keeping all existing panes and charts open in an inactive state.

* :ref:`Workspace Save and Restore <workspace>` |Pro| to save the full workspace state to a file and
  reload it in a future session, preserving tab layouts, pane configurations, chart settings, alert rules,
  and tab order.

* :ref:`Topics Panel <topics_panel>` |Pro| as a dedicated topic navigation panel in the left sidebar
  with text filtering, expandable field trees, and context actions for opening Spy or Topic Chart panes.

* :ref:`Custom Series <custom_series_panel>` |Pro| for defining data series computed from a JavaScript
  formula that binds one or more topic fields to variables, then plotting the result on a topic chart.

* :ref:`On-Demand Statistics Readers <statistics_readers_panel>` |Pro| for controlling which
  statistics DataReaders are active, so only the statistics you ask for are collected.

* :ref:`Alert Configuration Pane <pro_alert_configuration_panel>` |Pro| as an integrated form in
  the left sidebar for creating and editing alert rules inline, replacing the previous dialog-based
  workflow.

* :ref:`Entity Summary Bar <entity_summary_bar>` |Pro| showing live counters for every type of monitored
  DDS entity at the bottom of the window, so the overall network size is always in view.

* :ref:`Image Pane <image_pane>` |Pro| for rendering live image data from DDS topics inside the
  monitor, with automatic detection of ROS 2 ``sensor_msgs`` and *eProsima Fast DDS* image types, plus
  manual field mapping for arbitrary topics.

* :ref:`Topic Time Series Charts <topic_charts>` |Pro| for plotting live numeric values from any DDS topic as a
  time-series chart, with support for multiple series, field selection, and pause/resume controls.

* :ref:`XY Topic Charts <xy_charts>` |Pro| for plotting two numeric DDS topic fields against each other as a
  real-time scatter chart, enabling phase-space or correlation analysis between any pair of numeric fields
  within the same DDS domain.

* :ref:`Publisher Pane <publisher_pane>` |Pro| for publishing user-defined samples on any discovered DDS
  topic, with a form built automatically from the topic's dynamic type and support for one-shot and
  continuous publishing.

* :ref:`Register Type <register_type>` |Pro| for registering a user-supplied data type from its IDL,
  optionally under a custom name, so it can be used for spying, publishing, and charting on topics
  whose type was never discovered on the network.

* :ref:`Right-Side Pane Configuration <right_pane_config>` |Pro| for creating and editing all pane types
  from an inline configuration sidebar, including statistics charts, topic charts, spy panes, IDL panes, and
  image panes, without opening separate dialogs.
