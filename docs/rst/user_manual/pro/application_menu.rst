.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _pro_application_menu:

################
Application Menu
################

The application menu bar provides access to all operations in *Fast DDS Monitor Pro*.
It is divided into five groups: **File**, **Add**, **Edit**, **View**, and **Help**.

.. figure:: /rst/figures/screenshots/application_menu_pro.png
    :align: center

.. _pro_application_menu_file:

File
====

The **File** menu contains actions for starting and stopping monitors, exporting data, saving and
restoring workspaces, and closing the application.

.. _pro_init_monitor_button:

**Initialize DDS Monitor**
    Opens a dialog to start monitoring a DDS Domain by number (0–232).
    Once started, the monitor discovers all DDS entities in that domain and collects their connections,
    configuration, and statistical data in real time.
    See :ref:`monitor_domain` for a full explanation.
    Attempting to initialize a domain that is already being monitored shows an error and adds an entry
    to the :ref:`pro_issues_panel`; select **Retry** to choose a different domain.

**Initialize Discovery Server Monitor**
    Opens a dialog to start monitoring a DDS network via one or more *Fast DDS Discovery Servers*.
    Enter the server addresses as a semicolon-separated list of ``ip:port`` pairs.
    The monitor connects to the servers and collects all discovery information for the entities
    communicating through them.
    See :ref:`monitor_domain` for full details.
    Starting a monitor on an already-initialized Discovery Server shows an error and an entry in the
    :ref:`pro_issues_panel`.

**Initialize DDS Monitor with Profile**
    Opens a dialog to start monitoring using a DDS XML profiles file.
    Select the XML file and then choose the profile that defines the DDS configuration to use.
    See :ref:`add_monitor_using_dds_xml_profiles` for step-by-step instructions.

.. _pro_stop_monitor:

**Stop Monitor** |Pro|
    Opens a submenu listing every domain currently being monitored.
    Selecting a domain stops monitoring it: its panes and charts remain open but become inactive,
    and the domain is no longer tracked.
    This is the reverse operation of *Initialize DDS Monitor* and is useful when switching between
    domains or freeing resources from a domain that is no longer of interest.

**Save Workspace** |Pro|
    Save the current session using the |save| button, **Ctrl+S**, or **File -> Save Workspace**.
    See :ref:`workspace` for the full workspace documentation including what gets saved.

**Load Workspace** |Pro|
    Restore a previously saved session.
    Go to **File -> Load Workspace** and select a ``.fdmw`` file.
    See :ref:`workspace` for details on the restore behavior.

.. _pro_export_data:

**Export Charts to CSV**
    Exports chart data from the current session to a CSV file.
    Three export scopes are available:

    * **Single series** - export from the series context menu inside the Chartbox.
    * **All series in a Chartbox** - export from the Chart menu of the Chartbox.
    * **All series in all Chartboxes** - export via this menu item (exports everything at once).

    The exported CSV file uses the following structure:

    .. list-table::
        :header-rows: 4

        *   -
            - <DataKind>
        *   -
            - <Chartbox name>
        *   - ms
            - <DataKind units>
        *   - UnixTime
            - <Series name>
        *   - <unix_time>
            - <data_value>

.. _pro_dump_button:

**Dump**
    Dumps the full contents of the statistics database to a JSON file without modifying the stored
    data.
    Useful for taking a snapshot of the session for offline analysis or archiving.
    The JSON file preserves all entity statistics collected since the session started.

.. _pro_dump_clear_button:

**Dump and Clear**
    Same as **Dump**, but also clears all accumulated statistics data for every entity after saving.
    Use this to reset statistics while preserving a record of the session - useful for long-running
    sessions where periodic snapshots are needed without growing the in-memory database indefinitely.

**Quit**
    Closes the application.

.. _pro_edit_menu:

Edit
====

The **Edit** menu contains actions for managing the data in the current session - cleaning up
entities, clearing statistics, configuring alerts, scheduling maintenance tasks, and resetting the
display.

.. _pro_clear_inactive_entities:

**Delete Inactive Entities**
    Removes all entities that are no longer active from the database.
    Inactive entities are those that have stopped publishing or have been undiscovered.
    This frees memory and cleans up the entity lists.

.. _pro_delete_statistics_data:

**Delete Statistics Data**
    Clears all accumulated statistics data for every entity without removing the entities themselves.
    The entities remain visible but all their historical statistics are reset.

.. _pro_schedule_delete:

**Scheduler Configuration**
    Opens a dialog to configure a recurring schedule for automatic database dumps, statistics data
    removal, and/or inactive-entity cleanup.
    Useful for long-running monitoring sessions where periodic housekeeping is needed.

.. _pro_alerts_configuration:

**Alerts Configuration**
    Switches to the **Configuration** tab of the :ref:`pro_alert_configuration_panel` in the left
    sidebar. Alert rules are created and edited there, and the polling time is also configured
    inline — no separate dialog is opened.

.. _pro_refresh_button:

**Refresh**
    Resets the currently selected entity and rebuilds the entity models from the current database
    state.
    Use this if entities appear to be missing from the Explorer Panel or the display seems out of sync.

.. _pro_clear_log:

**Clear Log**
    Clears all entries from the callbacks log in the :ref:`pro_log_panel`.
    This does not affect the underlying data, only the log display.

.. _pro_clear_issues:

**Clear Issues**
    Clears all entries from the :ref:`pro_issues_panel`.
    This does not resolve the underlying issues, only removes them from the panel.

.. _pro_add_menu:

Add |Pro|
=========

The **Add** menu contains all actions that open new panes or views in the workspace.
Every item here creates a panel that can be docked, split, or floated anywhere in the layout.

.. _pro_display_historic_data_button:
.. _pro_display_dynamic_data_button:

**Add Topic Live Chart** |Pro|
    Opens a new :ref:`Time Series Chart <time_series>` pane that plots raw numeric values from any
    user-defined DDS topic directly against time, updated live as samples arrive.
    Multiple series from different topics can be overlaid on the same chart.
    XY (scatter) mode is available from within the chart configuration.
    See :ref:`topic_charts` for full documentation.

**Add Statistics Chart**
    Opens a new statistics *Chartbox* for plotting pre-computed DDS metrics such as latency,
    throughput, and packet counts.
    After opening, choose between a historical chart (past time range) or a real-time chart
    (live updates as samples arrive).
    See :ref:`historic_series` for historical configuration and :ref:`dynamic_series` for real-time.

**Add Spy Topic View**
    Opens a new :ref:`Dockable Spy Pane <dockable_spy_pane>` that subscribes to a selected DDS topic
    and shows each incoming sample as an expandable field tree in real time.
    Useful for verifying message content and inspecting raw field values as they are published.
    See :ref:`Dockable Pane Workspace <dockable_panes>` for details.

**Add Topic Type View (IDL)**
    Opens a pane showing the full IDL type definition of a selected DDS topic, including the complete
    struct hierarchy, field names, and type annotations.
    The IDL text can be copied to the clipboard.
    ROS 2 types are shown demangled by default (toggle with **View → Revert ROS 2 Demangling**).

**Add Image View** |Pro|
    Opens a new :ref:`Image Pane <image_pane>` that renders live image or video data streamed over a
    DDS topic directly inside the monitor.
    Supports ROS 2 ``sensor_msgs/Image`` and generic OMG IDL image types.
    See :ref:`image_pane` for details.

**Add Publisher View** |Pro|
    Opens a new :ref:`Publisher Pane <publisher_pane>` for composing and publishing DDS samples on any
    discovered topic.
    The form is generated automatically from the topic's dynamic type and supports both one-shot and
    continuous publishing modes.
    See :ref:`publisher_pane` for details.

**Create Alert**
    Opens the alert creation dialog to define a new alert rule based on a DDS statistic threshold.
    Once created, the alert appears in the :ref:`pro_alerts_panel` and triggers notifications when the
    configured condition is met.

.. _pro_view_menu:

View
====

The **View** menu controls the visibility and appearance of entities and panels in the application,
including entity filters, sidebar layout, theming, and the shortcuts toolbar.

**Hide/Show Proxy Entities**
    Toggles the display of proxy entities - entities from other DDS domains whose statistics messages
    are reaching the monitor's domain.
    When hidden, proxy entities are completely unavailable in the application, including in charts.
    Proxy entities are hidden by default.

**Hide/Show Inactive Entities**
    Toggles the display of inactive entities - entities that have been discovered but are no longer
    active in the DDS network.
    When hidden, inactive entities are unavailable in the application, including in charts.

.. _pro_hide_show_metatraffic:

**Hide/Show Metatraffic**
    Toggles the display of metatraffic entities.
    Metatraffic entities include *Fast DDS* Statistics module topics, ROS discovery topics, and all
    endpoints bound to them.
    They are hidden by default.
    When hidden, metatraffic entities are completely unavailable in the application.

**Revert/Perform ROS 2 Demangling**
    By default, ROS 2 type names and IDL representations are demangled to match the original ROS 2
    type definitions and improve compatibility with *Fast DDS Gen*.
    Demangled IDL views are marked with a badge in the corner.
    This option toggles the demangling on or off for all IDL views.

**Theme** |Pro|
    Opens the theme settings to switch between light and dark palettes or configure a custom theme.
    The selected theme is applied consistently across all panels, charts, icons, and dialogs.
    See :ref:`theming` for details.

**Hide/Show Shortcuts Toolbar**
    Hides or reveals the shortcuts toolbar at the top of the window.

**Customize Shortcuts Toolbar**
    Opens a dialog to independently show or hide each button in the shortcuts toolbar.
    This toolbar exposes shortcuts to buttons with the main functionality to interact with the
    *Fast DDS Monitor Pro* application.

    The meaning of each of the icons available in the shortcut bar is explained below:

    * |historical_chart| - Display historical data.
    * |dynamic_chart| - Display real-time data.
    * |create_alert| - Open the create alerts panel.
    * |refresh| - Refresh Fast DDS Monitor.
    * |clear_log| - Clear the list of logs.
    * |clear_issues| - Clear the issues panel.

**Hide/Show Left Sidebar**
    Hides or reveals the entire left sidebar.

**Customize Left Sidebar**
    Opens a dialog to independently show or hide each panel within the :ref:`pro_left_panel`.

Help
====

The **Help** menu provides links to documentation, release notes, community resources, and
application information.

**Documentation**
    Opens this documentation in the default browser.

**Release Notes**
    Opens the `Releases <https://github.com/eProsima/Fast-DDS-monitor/releases>`_ page of the
    `GitHub Fast DDS Monitor repository`_ in the default browser.

**Join Us on LinkedIn**
    Opens the `eProsima LinkedIn page <https://www.linkedin.com/company/eprosima>`_ in the default
    browser.

**Search Feature Requests**
    Opens the `Issues`_ section of the `GitHub Fast DDS Monitor repository`_ to search for or browse
    existing feature requests and bug reports.

**Report Issue**
    Opens a new issue form in the `Issues`_ section of the `GitHub Fast DDS Monitor repository`_
    to report a bug or request a feature.

**About**
    Displays a dialog with general information about the currently running *Fast DDS Monitor Pro*
    application, including the version number and license information.

.. _GitHub Fast DDS Monitor repository: https://github.com/eProsima/Fast-DDS-Monitor
.. _Issues: https://github.com/eProsima/Fast-DDS-Monitor/issues
