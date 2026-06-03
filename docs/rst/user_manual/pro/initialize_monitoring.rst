.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _pro_initialize_monitoring:

###########################
Initialize Monitoring |Pro|
###########################

When *Fast DDS Monitor Pro* is launched, the following start screen is displayed.
Click the **Start monitoring!** button to begin monitoring a Fast DDS application.

.. thumbnail:: /rst/figures/screenshots/main_pro.png
    :align: center

Next, select the type of monitoring to perform, as explained in section :ref:`monitor_domain`.
The screenshot below shows the full monitor interface and the dialog box used to start monitoring
a DDS Domain or a Discovery Server network.

.. thumbnail:: /rst/figures/screenshots/init-monitor_pro.png
    :align: center

*Fast DDS Monitor Pro* supports multiple active monitors simultaneously.
Each monitor operates independently on its own DDS domain or Discovery Server network.
See :ref:`multiple_monitors` for details on opening and managing several monitors side by side.

.. _dockable_panes:
.. _dockable_panes_layout:
.. _dockable_panes_splitting:

Dockable Pane Workspace
=======================

In *Fast DDS Monitor Pro*, every visualization and inspection view lives in a dockable pane.
Statistics charts, topic charts, spy panes, IDL panes, image panes, and publisher panes can all be
arranged side by side in a freely configurable split layout.
You can resize, split, and close panes at any time to organize the workspace to suit your session.

The main content area of each monitor tab is a grid where each cell holds one pane.
A single monitor tab supports up to **six panes** open at the same time.

To add a pane next to an existing one, click the three-dots button in any pane header, choose
**Split right** or **Split down**, and select the view type to open.
To resize, drag the divider between any two adjacent panes.
The layout adjusts automatically whenever a pane is added or closed.

.. thumbnail:: /rst/figures/screenshots/tab_reordering_pro.png
    :align: center

.. _theming:
.. _theming_switching:
.. _theming_coverage:

Dark Mode
=========

*Fast DDS Monitor Pro* also provides two themes: **Light** and **Dark**.
When you switch themes, every part of the application updates instantly — panels, charts, dialogs,
icons, controls, and the menu bar — without requiring a restart.

To switch themes, open **View → Theme** and choose **Light** or **Dark**.
Both entries are mutually exclusive checkable actions; the active theme shows a checkmark.

.. thumbnail:: /rst/figures/screenshots/main_dark_pro.png
    :align: center

The selected theme is persisted in the workspace file and restored when the workspace is loaded.
If no workspace has been saved yet, the application follows the operating system color scheme:
it starts in Dark mode on systems that report a dark scheme, and in Light mode otherwise.

The theme is applied across all components:

- **Panels and sidebars** - backgrounds, text, row hover states, scrollbars, and dividers.
- **Charts** - backgrounds, axis labels, grid lines, and legend text.
  Chart series colors are a fixed ten-color palette that is the same in both themes.
- **Domain graph** - node and edge colors adapt; entity status colors (green/yellow/red) are fixed.
- **Dialogs** - all dialogs, wizards, and alert/alias forms use the active palette.
- **Controls** - buttons, inputs, toggles, sliders, and scroll bars are consistently themed.
- **Icons** - automatically switch between dark and light stroke variants.
- **Title bar and menu bar** - the custom title bar and window controls follow the active palette.

.. _multiple_monitors:
.. _multiple_monitors_types:

Multiple Monitor Support
========================

*Fast DDS Monitor Pro* lets you run several monitors at the same time within a single workspace.
Each monitor connects to its own DDS environment.
You can freely switch between monitors, open panes from different monitors simultaneously, or add
new ones at any time during a session.

The open-source edition only supports one active monitor at a time; the Pro edition removes that
restriction, making it practical for deployments where more than one DDS environment must be
observed simultaneously.

When creating a new monitor, choose one of three initialization modes:

* **DDS Domain** - the monitor joins a DDS Domain identified by its domain ID.
  Every DDS entity in that domain becomes visible in the Explorer panels.

* **Discovery Server** - the monitor connects to a Discovery Server using a locator (address and
  port). Use this mode when the DDS network relies on the Discovery Server paradigm rather than
  Simple Discovery.

* **XML Profile** - the monitor reads its configuration from an XML profile file. Useful when the
  DDS environment requires specific QoS policies or transport settings defined outside the
  application.

See :ref:`pro_initialize_monitoring` for the full initialization procedure and
:ref:`monitor_domain` for further details on each mode.

Left Sidebar
============

The left sidebar contains five panels:

- :ref:`Explorer Panel <pro_left_panel>` — shows all entities discovered by the monitor in collapsible,
  interactive lists.
- :ref:`Topics Panel <topics_panel>` |Pro| — topic-centered view with filtering, field trees, and
  direct actions on any topic.
- :ref:`Alerts Panel <pro_alerts_panel>` — lists the alerts configured by the user and shows alert
  details.
- :ref:`Monitor Status Panel <pro_status_panel>` — shows entity counts, active domains, and the event
  log.
- :ref:`Issues Panel <pro_issues_panel>` — lists error events reported by the application.

Bottom Panels
=============

Three additional panels sit at the bottom of the application window:

- :ref:`Alert Messages Panel <pro_alert_messages_panel>` — lists the alerts triggered by the
  application, grouped by alert rule name with timestamps.
- :ref:`Problem Summary <pro_problem_summary>` — collapsible section at the bottom of the main panel
  listing detected DDS entity problems such as samples lost or incompatible QoS.
- :ref:`Entity Summary Bar <entity_summary_bar>` |Pro| — compact counter strip showing the live total
  of Participants, DataWriters, DataReaders, and Topics across all active monitors.

Main Panel Views
================

The central panel hosts multiple tabs with different views.

.. figure:: /rst/figures/screenshots/main_panel_pro.png
    :align: center

The central panel can display several types of views.
Use the :ref:`Add menu <pro_add_menu>` to open any of them in the workspace.

- :ref:`Statistics Chart <pro_chart_view>` — plots pre-computed DDS metrics (latency, throughput,
  packet counts) over a configurable time range, historical or real-time.
- :ref:`Domain View <pro_domain_graph>` — interactive graph showing all DDS entities in a domain and
  the connections between DataWriters and DataReaders through their shared topics.
- :ref:`Image View <image_pane>` |Pro| — renders live image or video data from a DDS topic directly
  inside the monitor.
- :ref:`Spy Topic View <dockable_spy_pane>` — shows each incoming DDS topic sample as an
  expandable field tree in real time.
- :ref:`Topic Live Chart <time_series>` |Pro| — plots raw numeric values from any DDS topic against
  time or other topic field, updated live; supports multiple series and XY scatter mode.
- :ref:`Publisher View <publisher_pane>` |Pro| — compose and publish DDS samples on any discovered
  topic using a form generated from the topic's dynamic type.
