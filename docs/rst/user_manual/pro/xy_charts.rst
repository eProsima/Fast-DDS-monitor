.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _xy_charts:

#################
XY Charts  |Pro|
#################

An *XY Chart* (also called a *phase plot* or *scatter chart*) plots the relationship between two numeric
fields extracted from live DDS topic samples.
Unlike a Topic Chart, whose X axis is always a time axis, an XY Chart has both axes as value axes: the X
axis is driven by one numeric field and the Y axis by another.
New data points appear in real time as samples arrive from the monitored DDS network.

Multiple series can be plotted in the same XY Charts pane. Each series independently sources its X and Y
values, and the two values may come from the same topic or from different topics within the same DDS domain.
Fields that are integers, floats, or doubles can be plotted. Struct and array fields are not plotted
directly but can be expanded to reach their numeric leaf fields.

.. _xy_charts_creating:

Opening XY Charts
=================

There are several ways to open a new XY Charts pane:

* Use **Topic Charts View** in the application menu bar.

* Use the :ref:`right_pane_config` sidebar. When the New Topic Chart form is open, switch the plot mode to
  **XY Chart** to switch from a time-based topic chart to an XY scatter chart.

* Click the three-dots button in the header of any existing pane to open the split menu, then choose
  **Split right** or **Split down** and select **Topic Chart** to open a new chart alongside the current
  pane.

.. _xy_charts_series:

Managing Series
===============

**Adding a series:**

Click **+ Add XY Series** in the **Series** section to expand the series creation form.
For each new series, select:

* An **X Axis Topic** and an **X Field** - the topic and numeric field whose values drive the X axis.
* A **Y Axis Topic** and a **Y Field** - the topic and numeric field whose values drive the Y axis.

Fields only appear after the first DDS sample has arrived on the selected topic.
Click **Add** to confirm. The picker stays open so that additional series can be added without reopening
it. Click the toggle button again to collapse it.

.. note::

    A data point is produced whenever a sample arrives that contains both a valid X value and a valid Y
    value.
    When X and Y come from different topics, the monitor pairs each new X sample with the most recent Y
    sample (and vice versa), so plotted points always reflect the latest paired values at the time of
    arrival.

.. note::

    Fields only appear in the picker after the first sample has arrived on the selected topic.
    If the field list is empty, wait for traffic on that topic or verify that the topic is being published.

**Editing a series:**

Right-clicking a series entry in the legend opens a context menu with the following options:

* **Rename series** opens a dialog to give the series a custom display name shown in the legend.
* **Change color** opens a color picker to assign a custom scatter marker color.
* **Hide series** / **Display series** toggles the series visibility on the chart without removing it.
* **Set max data points** sets how many recent data points this series retains in the rolling buffer.
* **Remove series** removes the series from the chart permanently.

The same options are available from the **Series** section of the :ref:`right_pane_config` sidebar, where
each series has a row with a color swatch, rename, visibility toggle, and remove button.

**Bulk actions:**

The **Actions** section of the :ref:`right_pane_config` sidebar provides:

* **Show All Series** makes every hidden series visible at once.
* **Hide All Series** hides all series without removing them.
* **Clear Chart** removes all series and resets the chart.

.. _xy_charts_controls:

Chart Header Controls
=====================

The chart header provides the following buttons from left to right:

* |add_series| **Add Series** opens the inline add-series panel in the :ref:`right_pane_config` sidebar.

* |resize| **Reset View** returns both axes to their auto-fit range calculated from the current data.

* |legend| **Toggle Legend** shows or hides the legend listing all active series and their colors.

* |pause| / |play| **Pause / Resume** pauses live data ingestion, freezing the chart at its current state.
  Samples received while paused are discarded. Resuming restarts the live feed from the current time.

* |help| **Help** opens a contextual help panel showing a brief description of XY Charts, usage tips,
  and a link to this documentation page.

* The expand button maximizes the pane to fill the full workspace. Clicking it again restores the previous
  layout.

* |gear| **Panel Settings** opens the :ref:`right_pane_config` sidebar for this chart.

* The three-dots button opens the split menu to open a new pane to the right or below the current one.

* |cross| **Close** closes the pane.

.. _xy_charts_interaction:

Interactive Chart Controls
==========================

The following mouse and keyboard interactions are available directly on the chart area:

* **Click on a data point** to show its exact (X, Y) value.
* **Scroll wheel** to zoom the X axis in and out.
* **Ctrl + scroll wheel** to zoom the Y axis in and out.
* **Shift + drag** to zoom into a selected area.
* **Ctrl + click and drag** to scroll (pan) the axes without zooming.

.. _xy_charts_config:

Right-Side Configuration Panel
===============================

Opening the :ref:`right_pane_config` sidebar for XY Charts (via the |gear| button) shows the following
sections:

**Pane Settings**

Controls that apply to the whole chart:

* **Domain** selects which monitored DDS domain the chart subscribes to.
* **Time window** sets how long data is retained in the rolling buffer (1 to 86400 seconds; default 120).
  Data points older than the time window are discarded as new samples arrive.
* **Max points** sets the total number of data points the chart retains across all series (default 500).
  When the limit is reached, the oldest points are removed as new samples arrive.
* **Apply & Reset Chart** applies any changes to these fields and clears all existing series. This button
  is disabled when no domain is selected.

**Chart Name**

A text field and confirm button to rename the chart title shown in the pane header.

**Display**

* **Show legend** toggles the chart legend on or off.
* **Show lines** connects successive scatter points with a line in addition to the scatter markers.
* **Running** when on, the chart accepts new data in real time. When off, the chart is paused and the
  view stays fixed; resuming restarts the live feed.

**Series**

Lists every series currently added to the chart. Each row shows the series name, a color swatch to change
the marker color, a visibility toggle, and a remove button. An **Add XY Series** button at the bottom
expands the inline series-creation section described below.

**Add XY Series** *(collapsible)*

* **X Axis Topic** - filter and select the topic that provides the X values.
* **X Field** - filter and select the numeric leaf field within that topic.
* **Y Axis Topic** - filter and select the topic that provides the Y values.
* **Y Field** - filter and select the numeric leaf field within that topic.
* Click **Add XY Series** to create the series. The picker remains open for adding further series.

**Axes**

* **Lock Y axis** switches the Y axis from auto-scale to a fixed range. When locked, **Y min** and
  **Y max** fields become editable.
* **Lock X axis** switches the X axis to a fixed range. When locked, **X min** and **X max** fields
  become editable.
* **Reset Zoom** returns both axes to their auto-fit range, equivalent to the |resize| button in the
  header.

**Panel Actions**

* **Split right** and **Split down** each expand a submenu to open a new pane alongside the current pane.
* **Save screenshot** saves a PNG image of the chart to disk.
* **Copy screenshot to clipboard** copies the chart image to the clipboard.

**Actions**

* **Show All Series** makes every hidden series visible.
* **Hide All Series** hides all series without removing them.
* **Clear Chart** removes all series and resets the chart.
