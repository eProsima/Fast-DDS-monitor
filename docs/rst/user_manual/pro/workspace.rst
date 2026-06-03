.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _workspace:
.. _workspace_saving:
.. _workspace_restoring:
.. _workspace_what_is_saved:

################################
Workspace Save and Restore |Pro|
################################

*Fast DDS Monitor Pro* can save the complete visual state of a monitoring session to a file and
reload it in a later session, so you can resume exactly where you left off without reconfiguring
monitors, layouts, charts, and alerts from scratch.

Saving a Workspace
==================

There are three ways to save the current workspace:

- Click the |save| button in the top-right toolbar of the application window.
- Press **Ctrl+S**.
- Go to **File -> Save Workspace**.

A file dialog opens to choose the destination folder and file name.
An existing file at the selected path is overwritten.
The workspace is saved as a JSON file with the ``.fdmw`` (*Fast DDS Monitor Workspace*) extension.
The statistics backend is always reset on load. Entity IDs are not used to identify entities in the file
because they are volatile and change between runs. Instead, entities are resolved by type and name when
the workspace is loaded.

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

    If a saved workspace references a DDS domain or Discovery Server that is not reachable at load time, that monitor opens in a waiting state and its panes populate as entities are discovered.

The statistics backend is always reset on load.
Entities are resolved by type and name - not by volatile entity IDs - so workspaces are portable
across runs even when entity identifiers change.

What Gets Saved
===============

The workspace file captures the complete visual state of the application. The following is a full account
of what is included.

**Application settings**

* Theme selection (dark, light, or follow system).
* Show or hide proxy entities, inactive entities, and metatraffic.
* :ref:`ROS 2 Demangling <ros2_demangling>` state (reverted or applied).
* Toolbar visibility and which buttons are shown in the shortcuts toolbar.
* Left sidebar visibility and which buttons are shown in it.
* Alerts polling time and scheduler configuration.

**Left sidebar**

* The selected icon and the active sub-category within it (for example, the Log tab inside
  :ref:`Monitor Status <pro_status_panel>`).
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
* Created entity aliases within each :ref:`domain view <pro_domain_view>`.
* Active topic filter applied to each :ref:`domain graph view <pro_domain_graph>`.
* Entity visibility settings (shown/hidden per alias) for each :ref:`domain graph view <pro_domain_graph>`.

:ref:`Statistics Charts <pro_chart_view>`

For each statistics chart pane:

* Data kind, time window, update period, and maximum data points.
* For each series: source and target entity (resolved by type and name), statistics kind, label, color,
  visibility, max data points, and whether cumulative mode was active.
* Chart name, legend visibility, pause state, expand state, and whether data points are shown.
* Y-axis settings (and X-axis settings for historic charts).

:ref:`Image Panes <image_pane>`

* The subscribed topic name and domain number.
* Whether the pane was active (streaming) or paused when saved. The topic entity ID is not used for
  restoration since it is volatile; the pane is reconnected by topic name and domain on load.

:ref:`Spy Panes <dockable_spy_pane>`

* The subscribed topic and domain.
* Whether the pane was paused or running.

:ref:`Topic Charts <topic_charts>`

For each topic chart pane:

* Domain, time window, and maximum data points.
* For each series: topic name, field path, max data points, label, color, and visibility.
* Chart name, legend visibility, pause state, expand state, and whether data points are shown.
* Y-axis lock and range (X-axis lock and range are not saved).

:ref:`Publisher Panes <publisher_pane>`

* The target topic name and domain number. The pane re-resolves the topic from this stable pair on load,
  not from the volatile entity identifier.
* The complete map of form values entered by the user, keyed by field path. Values are snapshotted at
  save time, so unpublished edits are preserved. The element count of every variable-length sequence and
  map, and the active branch of every union, are captured so the form opens in the same shape it was
  last saved with.
* The per-field slider minimum and maximum bounds for every numeric scalar field.
* The continuous-mode toggle state and the configured interval in milliseconds.

:ref:`IDL Panes <dockable_idl_pane>`

* The topic name and domain being viewed, so the pane reopens showing the same
  type definition on load.

:ref:`Pane layouts <dockable_panes>`

* The full split tree for each monitor tab, including the type of every pane, its position, and the
  width and height ratios of all dividers.
