#######################################
eProsima DDS Monitor Documentation
#######################################

.. image:: /rst/figures/Logo.png
  :height: 100px
  :align: left
  :alt: eProsima
  :target: http://www.eprosima.com/

*eProsima DDS Monitor* is a graphical desktop application aimed at monitoring DDS environments deployed using the
*eProsima Fast DDS* library.
Thus, the user can monitor in real time the status of publication/subscription communications between DDS entities.
They can also choose from a wide variety of communication parameters to be measured (latency, throughput, packet loss,
etc.), as well as record and compute in real time statistical measurements on these parameters
(mean, variance, standard deviation, etc.).

Furthermore, the user can check the status of the deployed DDS network at any time, i.e. see for each DDS
Domain which DomainParticipants are instantiated, as well as their publishers and subscribers and the topics
they publish under or they subscribe to, respectively.
It is also possible to visualize the physical architecture of the network on which the DDS applications that use
*Fast DDS* are running.

########################
DDS Monitor |Pro|
########################

*DDS Monitor Pro* is the commercial edition of *eProsima DDS Monitor*, designed for professional
deployments that require advanced monitoring capabilities and a richer user experience.

It extends the open-source version with premium features such as:

* :ref:`Modern Chart Workspace <dockable_panes>` |Pro| with a dockable and splittable pane layout for
  statistics and topic charts, improved zoom, legend, and time-window controls.
* :ref:`Dark Mode <theming>` |Pro| offering light and dark palettes
  applied consistently across the entire application.
* :ref:`Multiple Monitor Support <multiple_monitors>` |Pro| to observe several DDS Domains, Discovery
  Servers, or XML-configured environments side by side in the same workspace.
* :ref:`Offline Mode <offline_mode>` |Pro| for opening a captured DDS recording (MCAP or SQLite) and
  inspecting it with full playback control - scrub, play, pause, loop, and change speed through the
  recorded timeline.
* :ref:`Domain Removal <pro_stop_monitor>` |Pro| to stop monitoring a specific domain at any time,
  keeping all existing panes and charts open in an inactive state.
* :ref:`Workspace Save and Restore <workspace>` |Pro| to save and reload the full workspace state across
  sessions, preserving layouts, chart configuration, alerts, and tab order.
* :ref:`Topics Panel <topics_panel>` |Pro| as a dedicated topic navigation panel with text filtering,
  expandable field trees, and context actions for opening Spy or Topic Chart panes.
* :ref:`Custom Series <custom_series_panel>` |Pro| for defining data series computed from a JavaScript
  formula that binds one or more topic fields to variables, then plotting the result on a topic chart.
* :ref:`On-Demand Statistics Readers <statistics_readers_panel>` |Pro| for controlling which statistics
  DataReaders are active, so only the statistics you ask for are collected.
* :ref:`Alert Configuration Pane <pro_alert_configuration_panel>` |Pro| as an integrated form in
  the left sidebar for creating and editing alert rules inline, replacing the previous dialog-based
  workflow.
* :ref:`Entity Summary Bar <entity_summary_bar>` |Pro| showing live entity counters at the bottom of the
  window for a quick overview of the monitored DDS network.
* :ref:`Image Pane <image_pane>` |Pro| for rendering live image data from DDS topics directly
  inside the monitor workspace.
* :ref:`Topic Time Series Charts <topic_charts>` |Pro| for plotting live numeric values from any DDS topic as a
  time-series chart, supporting multiple series and field selection.
* :ref:`XY Charts <xy_charts>` |Pro| for plotting two numeric DDS topic fields against each other as a
  real-time scatter chart, enabling phase-space or correlation analysis between any pair of numeric fields.
* :ref:`Publisher Pane <publisher_pane>` |Pro| for publishing user-defined samples on any discovered DDS
  topic, with a form built automatically from the topic's dynamic type and support for one-shot and
  continuous publishing.
* :ref:`Register Type <register_type>` |Pro| for registering a user-supplied data type from its IDL,
  optionally under a custom name, so it can be used for spying, publishing, and charting on topics
  whose type was never discovered on the network.
* :ref:`Right-Side Pane Configuration <right_pane_config>` |Pro| for creating and editing all pane types
  from an inline sidebar without opening separate dialogs.

##################
Feature Comparison
##################

The following table summarizes the differences between *DDS Monitor* and *DDS Monitor Pro*:

.. raw:: html

  <style>
    .md-table {
      width: 100%;
      border-collapse: collapse;
      font-family: sans-serif;
      font-size: 0.95em;
    }
    .md-table th, .md-table td {
      border: 1px solid var(--color-background-border, #dfe2e5);
      padding: 10px 16px;
      text-align: left;
      color: var(--color-foreground-primary, inherit);
      background-color: var(--color-background-primary, transparent);
    }
    .md-table thead tr {
      background-color: var(--color-background-secondary, #f6f8fa) !important;
      font-weight: bold;
      text-align: center;
    }
    .md-table tbody tr:nth-child(even) td {
      background-color: var(--color-background-secondary, #f6f8fa);
    }
    .md-table tbody tr:hover td {
      background-color: var(--color-background-hover, #eef2f5);
    }
    .md-table .section-header {
      background-color: var(--color-background-secondary, #e8ecef) !important;
      font-weight: bold;
      text-align: center;
      color: var(--color-foreground-secondary, #444);
      letter-spacing: 0.05em;
      text-transform: uppercase;
      font-size: 0.85em;
    }
  </style>

  <table class="md-table">
    <thead>
      <tr>
        <th style="width:30%"></th>
        <th style="width:35%; text-align:center;">DDS Monitor Pro</th>
        <th style="width:35%; text-align:center;">DDS Monitor (Community)</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <th>Target usage</th>
        <td>Production systems, robotics, industrial, defense</td>
        <td>Evaluation, prototyping, development, research</td>
      </tr>
      <tr>
        <th>License</th>
        <td>Commercial (eProsima Software License Agreement)</td>
        <td>Open Source (GPL-3.0)</td>
      </tr>
      <tr>
        <th>Statistics charts</th>
        <td>✅ Full (dockable panes)</td>
        <td>✅ Full (fixed layout)</td>
      </tr>
      <tr>
        <th>Spy topics</th>
        <td>✅ Multiple dockable panes</td>
        <td>✅ Single fixed tab view</td>
      </tr>
      <tr>
        <th>IDL view</th>
        <td>✅ Multiple dockable panes</td>
        <td>✅ Single fixed tab view</td>
      </tr>
      <tr>
        <th>Alert configuration</th>
        <td>✅ Configuration pane</td>
        <td>✅ Configuration dialog</td>
      </tr>
      <tr>
        <th>DDS Domain monitoring</th>
        <td>✅ Multiple domains simultaneously</td>
        <td>⚠️ Single domain only</td>
      </tr>
      <tr>
        <th>Discovery Server monitoring</th>
        <td>✅ Multiple servers simultaneously</td>
        <td>⚠️ Single server only</td>
      </tr>
      <tr>
        <th>XML profile monitoring</th>
        <td>✅ Multiple profiles simultaneously</td>
        <td>⚠️ Single profile only</td>
      </tr>
      <tr>
        <th>Domain graph</th>
        <td>✅ + Visibility control panel</td>
        <td>⚠️ Filter by topic only</td>
      </tr>
      <tr>
        <th>Support</th>
        <td>✅ Direct engineering support</td>
        <td>❌ Community-based</td>
      </tr>
      <tr>
        <th>Maintenance / LTS</th>
        <td>✅ Long-term support with backports</td>
        <td>❌ No guaranteed maintenance</td>
      </tr>
      <tr>
        <th>Offline mode (open recording)</th>
        <td>✅ MCAP / SQLite playback</td>
        <td>❌</td>
      </tr>
      <tr>
        <th>Custom Series (JavaScript formulas)</th>
        <td>✅</td>
        <td>❌</td>
      </tr>
      <tr>
        <th>On-demand statistics readers</th>
        <td>✅</td>
        <td>❌</td>
      </tr>
      <tr>
        <th>Image Pane</th>
        <td>✅</td>
        <td>❌</td>
      </tr>
      <tr>
        <th>Topic Charts (time series)</th>
        <td>✅</td>
        <td>❌</td>
      </tr>
      <tr>
        <th>XY Charts (scatter plot)</th>
        <td>✅</td>
        <td>❌</td>
      </tr>
      <tr>
        <th>Publisher Pane (publish topic data)</th>
        <td>✅</td>
        <td>❌</td>
      </tr>
      <tr>
        <th>Register Type from IDL</th>
        <td>✅</td>
        <td>❌</td>
      </tr>
      <tr>
        <th>Dark mode and theming</th>
        <td>✅</td>
        <td>❌</td>
      </tr>
      <tr>
        <th>Topics panel</th>
        <td>✅</td>
        <td>❌</td>
      </tr>
      <tr>
        <th>Workspace save &amp; restore</th>
        <td>✅</td>
        <td>❌</td>
      </tr>
      <tr>
        <th>Help pop-ups &amp; tooltips</th>
        <td>✅</td>
        <td>❌</td>
      </tr>
      <tr>
        <th>Richer user experience</th>
        <td>✅ Entity summary bar, tab reordering, inline pane configuration, unified menu bar, domain removal...</td>
        <td>❌</td>
      </tr>
    </tbody>
  </table>

.. |eprosima_monitor_pro_website| raw:: html

   <a href="https://forms.eprosima.com/reach/form/CommercialSupportRequest/formperma/Ac8GwewD7PTDadQZIV92qDEzNFfMlJnYmA029mSJtJ8" target="_blank" rel="noopener noreferrer">share your contact details</a>

To discover all features and request a commercial license please |eprosima_monitor_pro_website|.

#################################
Commercial Support and Licenses
#################################

*DDS Monitor Pro* is distributed under the **eProsima Software License Agreement** and requires
a valid license to run.
The application checks for a license automatically at startup.
If a valid license is found, the application launches normally; if no license is detected, an error
message is shown and the application exits.

To get a commercial license or to request commercial support, reach out to eProsima through any of
the following channels:

* **Email:** info@eprosima.com
* **Web:** `eProsima's webpage <https://eprosima.com/>`_
* **License request form:** |eprosima_monitor_pro_website|.

The *eProsima Software License Agreement* governs all use of *DDS Monitor Pro*.
A copy of the license is included with the software distribution.
Using the application means you accept the terms of that agreement.

The open-source *DDS Monitor* is a separate product distributed under the GPL-3.0 license and
does not require a commercial license.

########
Overview
########

*eProsima DDS Monitor* is designed to meet the following criteria:

#. **Monitoring**: real-time tracking of network status and DDS communication.
#. **Intuitive**: graphical user interface developed following a user experience design approach.
#. **Introspection**: easily navigate through the deployed and active DDS entities being able to inspect their
   configuration and physical deployment.
#. **Troubleshooting**: detect at a glance the possible issues or anomalous events that may occur in the communication.

.. thumbnail:: /rst/figures/screenshots/working_example2.gif
    :align: center

The source code for the Monitor application and the documentation can be found in our
`GitHub repository <https://github.com/eProsima/DDS-Monitor>`_.

############
Contributing
############

*DDS Monitor* is an open source project, and as such all contributions, both in the form of
feedback and content generation, are most welcomed.
To make such contributions, please refer to the
`Contribution Guidelines <https://github.com/eProsima/all-docs/blob/master/CONTRIBUTING.md>`_ hosted in our GitHub
repository.

##############################
Structure of the documentation
##############################

This documentation is organized into the sections below.

* :ref:`Installation Manual <installation_manual_linux>`
* :ref:`Getting Started <entities>`
* :ref:`DDS Monitor Pro <pro_features>`
* :ref:`DDS Monitor Basic <initialize_monitoring>`
* :ref:`Developer Manual <developer_manual_installation_sources_linux>`
* :ref:`ROS 2 <ros_section>`
* :ref:`Docker Image <docker>`
* :ref:`Release Notes <release_notes>`
