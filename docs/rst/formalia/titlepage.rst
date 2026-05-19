#######################################
eProsima Fast DDS Monitor Documentation
#######################################

.. image:: /rst/figures/Logo.png
  :height: 100px
  :align: left
  :alt: eProsima
  :target: http://www.eprosima.com/

*eProsima Fast DDS Monitor* is a graphical desktop application aimed at monitoring DDS environments deployed using the
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
Fast DDS Monitor |Pro|
########################

*Fast DDS Monitor Pro* is the commercial edition of *eProsima Fast DDS Monitor*, designed for professional
deployments that require advanced monitoring capabilities and a richer user experience.

It extends the open-source version with premium features such as:

* :ref:`Multiple Monitor Support <multiple_monitors>` |Pro| to observe several DDS Domains, Discovery
  Servers, or XML-configured environments side by side in the same workspace.
* :ref:`Modern Chart Workspace <dockable_panes>` |Pro| with a dockable and splittable pane layout for
  statistics and topic charts, improved zoom, legend, and time-window controls.
* :ref:`Topic Charts <topic_charts>` |Pro| for plotting live numeric values from any DDS topic as a
  time-series chart, supporting multiple series and field selection.
* :ref:`XY Charts <xy_charts>` |Pro| for plotting two numeric DDS topic fields against each other as a
  real-time scatter chart, enabling phase-space or correlation analysis between any pair of numeric fields.
* :ref:`Image Pane <image_pane>` |Pro| for rendering live image and video data from DDS topics directly
  inside the monitor workspace.
* :ref:`Topics Explorer <topics_panel>` |Pro| as a dedicated topic navigation panel with text filtering,
  expandable field trees, and context actions for opening Spy or Topic Chart panes.
* :ref:`Workspace Save and Restore <workspace>` |Pro| to save and reload the full workspace state across
  sessions, preserving layouts, chart configuration, alerts, and tab order.
* :ref:`Right-Side Pane Configuration <right_pane_config>` |Pro| for creating and editing all pane types
  from an inline sidebar without opening separate dialogs.
* :ref:`Entity Summary Bar <entity_summary_bar>` |Pro| showing live entity counters at the bottom of the
  window for a quick overview of the monitored DDS network.
* :ref:`Dark Mode <theming>` |Pro| offering light and dark palettes
  applied consistently across the entire application.

The following table summarizes the differences between *Fast DDS Monitor* and *Fast DDS Monitor Pro*:

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
        <th style="width:35%; text-align:center;">Fast DDS Monitor Pro</th>
        <th style="width:35%; text-align:center;">Fast DDS Monitor (Community)</th>
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
        <th>Support</th>
        <td>✅ Direct engineering support</td>
        <td>❌ Community-based</td>
      </tr>
      <tr>
        <th>Maintenance / LTS</th>
        <td>✅ Long-term support with backports</td>
        <td>❌ No guaranteed maintenance</td>
      </tr>
      <tr class="section-header">
        <td colspan="3">Monitoring</td>
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
        <th>Statistics charts</th>
        <td>✅ Full (dockable panes)</td>
        <td>✅ Full (fixed layout)</td>
      </tr>
      <tr>
        <th>Domain graph</th>
        <td>✅ Improved</td>
        <td>✅</td>
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
        <th>Image / Video Pane</th>
        <td>✅</td>
        <td>❌</td>
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
      <tr class="section-header">
        <td colspan="3">UI / UX</td>
      </tr>
      <tr>
        <th>Dark mode and theming</th>
        <td>✅</td>
        <td>❌</td>
      </tr>
      <tr>
        <th>Topics Explorer panel</th>
        <td>✅</td>
        <td>❌</td>
      </tr>
      <tr>
        <th>Workspace save &amp; restore</th>
        <td>✅</td>
        <td>❌</td>
      </tr>
      <tr>
        <th>Richer user experience</th>
        <td>✅ Entity summary bar, tab reordering, inline pane configuration, unified menu bar...</td>
        <td>❌</td>
      </tr>
    </tbody>
  </table>

.. |eprosima_monitor_pro_website| raw:: html

   <a href="https://forms.eprosima.com/reach/form/CommercialSupportRequest/formperma/Ac8GwewD7PTDadQZIV92qDEzNFfMlJnYmA029mSJtJ8" target="_blank" rel="noopener noreferrer">share your contact details</a>

To discover all features and request a commercial license please |eprosima_monitor_pro_website|.

##################
Commercial Support
##################

Looking for commercial support? Write us to info@eprosima.com

Find more about us at `eProsima's webpage <https://eprosima.com/>`_.

########
Overview
########

*eProsima Fast DDS Monitor* is designed to meet the following criteria:

#. **Monitoring**: real-time tracking of network status and DDS communication.
#. **Intuitive**: graphical user interface developed following a user experience design approach.
#. **Introspection**: easily navigate through the deployed and active DDS entities being able to inspect their
   configuration and physical deployment.
#. **Troubleshooting**: detect at a glance the possible issues or anomalous events that may occur in the communication.

.. thumbnail:: /rst/figures/screenshots/working_example2.gif
    :align: center

The source code for the Monitor application and the documentation can be found in our
`GitHub repository <https://github.com/eProsima/Fast-DDS-monitor>`_.

############
Contributing
############

*Fast DDS Monitor* is an open source project, and as such all contributions, both in the form of
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
* :ref:`User Manual <initialize_monitoring>`
* :ref:`Fast DDS Monitor Pro <pro_features>`
* :ref:`Developer Manual <developer_manual_installation_sources_linux>`
* :ref:`ROS 2 <ros_section>`
* :ref:`Docker Image <docker>`
* :ref:`Release Notes <release_notes>`
