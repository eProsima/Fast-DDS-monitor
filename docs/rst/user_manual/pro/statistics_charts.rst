.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _pro_chart_view:
.. _pro_chartbox_layout:

#################
Statistics Charts
#################

A *Statistics Chartbox* plots pre-computed DDS metrics - such as latency, throughput, and packet
counts - collected from the monitored DDS network.
Where :ref:`Topic Charts <topic_charts>` work with raw values published on user-defined topics,
Statistics Charts show the statistical summaries computed by the *Fast DDS* statistics module.

.. thumbnail:: /rst/figures/screenshots/statistics_charts_pro.png
    :align: center

Two chart modes are available:

* **Historical** - displays data over a user-specified past time range, using a fixed time window
  and an aggregation operation (mean, median, standard deviation, etc.).
* **Real-time** - updates continuously as new statistical samples arrive, scrolling the time axis
  forward as the session progresses.

Multiple series from different entities can be overlaid on the same chart.

Opening a Statistics Chart
==========================

To create a new Statistics Chartbox:

* Use **Add → Add Statistics Chart** in the application menu.
* Click the |historical_chart| button for a historical chart or |dynamic_chart| for a real-time
  chart in the shortcuts bar.
* Use the :ref:`right_pane_config` sidebar from any existing pane and select **Statistics Chart**.
* Click the three-dots button in any pane header, choose **Split right** or **Split down**, and
  select **Statistics Chart** from the pane-type menu.

When the chart opens, a series creation dialog appears automatically.
See :ref:`historic_series` for historical chart configuration and :ref:`dynamic_series` for
real-time chart configuration.

.. _pro_create_new_series_layout:

Series Management
=================

**Adding a series:**

Click **Series → Add Series** in the Chartbox toolbar to open the series creation dialog.
Each series tracks one data kind for one or more entities over the configured time window.

**Editing a series:**

Right-clicking a series name in the legend opens a context menu with the following options:

* **Rename series** - assign a custom display name.
* **Change color** - open a color picker to assign a custom line color.
* **Hide series** / **Show series** - toggle visibility without removing the series.
* **Set max data points** - limit how many data points this series retains in memory.
* **Remove series** - permanently delete the series from the chart.
* **Export to CSV** - export only this series to a CSV file.

**Bulk actions:**

* **Series → Hide All Series** - hide every series at once.
* **Series → Display All Series** - reveal all hidden series.
* **Chart → Clear chart** - remove all series and reset the chart.

Chart Header Controls
=====================

The Chartbox toolbar provides the following actions from left to right:

* |resize| **Reset Zoom** - returns both axes to their default range, fitting all visible data.
  Also accessible from **Chart → Reset Zoom**.

* |editaxis| **Set Axes** - opens a dialog to lock the Y axis to a fixed range.
  Changing the X (time) axis is disabled by default, allowing dynamic charts to keep scrolling
  while the Y axis stays fixed.
  Also accessible from **Chart → Set axes**.

* |historical_chart| / |dynamic_chart| **Chart mode** - indicates the chart type (historical or
  real-time).

* |play| / |pause| **Pause / Resume** (real-time charts only) - freezes or resumes the time-axis
  scroll.
  While paused, data continues to be received but the view stays fixed, allowing zooming and
  panning over historical data.

* |help| **Chart Controls** - opens a contextual help panel with usage tips and a link to this
  documentation page.

* **Chart → Rename chart box** - change the title shown in the Chartbox header.

* **Chart → Export to CSV** - export all series in this chart to a CSV file.
  See :ref:`pro_export_data` for the file format.

* **Chart → Close chart box** - remove the Chartbox from the workspace.

Interactive Chart Controls
==========================

The following mouse and keyboard interactions are available directly on the chart area:

* **Click a data point** to display an info box showing its exact timestamp and value.
* **Ctrl + scroll wheel** to zoom in or out on the chart center.
* **Ctrl + click and drag** to scroll (pan) the view without zooming.
* **Reset Zoom** (|resize| button or **Chart → Reset Zoom**) to return to the default view.

Right-Side Configuration Panel
================================

When the :ref:`right_pane_config` sidebar is open for a Statistics Chart (via the |gear| button)
it provides access to all the above actions in a single inline panel, including series management,
axis controls, export, and split actions.
