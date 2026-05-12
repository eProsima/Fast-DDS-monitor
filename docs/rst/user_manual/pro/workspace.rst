.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _workspace:

################################
Workspace Save and Restore |Pro|
################################

*Fast DDS Monitor Pro* lets you save the full visual state of your monitoring session to a file and reload
it in a later session. When you restore a workspace the application rebuilds everything exactly as you left
it, so you can continue where you stopped without having to reconfigure monitors, layouts, charts, and
alerts from scratch.

The workspace is saved as a JSON file with the ``.fdmw`` (Fast DDS Monitor Workspace) extension. The
statistics backend is always reset on load. Entity IDs are not used to identify entities in the file
because they are volatile and change between runs. Instead, entities are resolved by type and name when
the workspace is loaded.

.. _workspace_saving:

Saving the Workspace
====================

To save the current workspace:

* Click **File** in the menu bar and choose **Save Workspace As...**

A file dialog opens where you can choose the destination folder and file name. If you select an existing
file it will be overwritten.

.. _workspace_restoring:

Restoring a Workspace
=====================

To load a previously saved workspace:

* Click **File** in the menu bar and choose **Load Workspace...**

A file dialog opens. Select the ``.fdmw`` file you want to load. The application validates the file before
applying it. Malformed files show an error. Unknown properties in the file are ignored, which allows
workspace files from newer versions to be opened in older builds without failing. Values that fall outside
valid ranges are clamped or ignored rather than stopping the load.

When loading, the following data is cleared before the workspace is applied: DDS entity lists, alert
status information, status logs, issues, problems found, and alert messages. Monitors are then started
fresh and the rest of the workspace state is reconstructed on top.

.. note::

    If a saved workspace references a DDS domain or Discovery Server that is not reachable at load time,
    that monitor opens in a waiting state and its panes populate as entities are discovered.

.. _workspace_what_is_saved:

What Gets Saved
===============

The workspace file captures the complete visual state of the application. The following is a full account
of what is included.

**Application settings**

* Theme selection (dark, light, or follow system).
* Show or hide proxy entities, inactive entities, and metatraffic.
* ROS 2 Demangling state (reverted or applied).
* Toolbar visibility and which buttons are shown in the shortcuts toolbar.
* Left sidebar visibility and which buttons are shown in it.
* Alerts polling time and scheduler configuration.

**Left sidebar**

* The selected icon and the active sub-category within it (for example, the Log tab inside Monitor
  Status).
* Width ratio of the left sidebar.
* All configured alert rules.

**Bottom bar**

* Whether the bottom bar is open, collapsed, or fully closed.
* Its height ratio.
* The selected sub-tab (Problems or Alerts).
* The problem that is currently being filtered.

**Main panel**

* All open monitor tabs, the selected tab, and the tab order.
* Each monitor is identified by its type and connection parameters: domain number for regular monitors,
  Discovery Server locator for DS monitors, and the XML profile file path for XML-configured monitors. All
  three monitor types are restored on load.
* Created entity aliases within each domain view.
* Active topic filter applied to each domain graph view.

**Statistics Charts**

For each statistics chart pane:

* Data kind, time window, update period, and maximum data points.
* For each series: source and target entity (resolved by type and name), statistics kind, label, color,
  visibility, max data points, and whether cumulative mode was active.
* Chart name, legend visibility, pause state, expand state, and whether data points are shown.
* Y-axis settings (and X-axis settings for historic charts).

**Topic Charts**

For each topic chart pane:

* Domain, time window, and maximum data points.
* For each series: topic name, field path, max data points, label, color, and visibility.
* Chart name, legend visibility, pause state, expand state, and whether data points are shown.
* Y-axis lock and range (X-axis lock and range are not saved).

**Spy Panes**

* The subscribed topic and domain.
* Whether the pane was paused or running.

**Image Panes**

* The subscribed topic name and domain number.
* Whether the pane was active (streaming) or paused when saved. The topic entity ID is not used for
  restoration since it is volatile; the pane is reconnected by topic name and domain on load.

**Pane layouts**

* The full split tree for each monitor tab, including the type of every pane, its position, and the
  width and height ratios of all dividers.
