.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _topic_charts:

##################
Topic Charts |Pro|
##################

A *Topic Chart* plots the live values of numeric fields from a DDS topic over time. Where statistics charts
show pre-computed DDS metrics such as latency or throughput, topic charts work directly with the raw data
published on any user-defined topic and update in real time as samples arrive.

Each chart can hold multiple series at the same time, where every series tracks one numeric field from one
DDS topic. Fields that are integers, floats, or doubles can be plotted. Struct and array fields are not
plotted directly but can be expanded to reach their numeric leaf fields.

.. _topic_charts_creating:

Opening a Topic Chart
=====================

There are several ways to open a new Topic Chart pane:

* Right-click a topic in the :ref:`topics_panel`, the :ref:`logical_panel`, or the domain graph and choose
  **Chart topic data**. Built-in and statistics Fast DDS topics cannot be charted and this option is
  disabled for them.

* Use **Add Topic Live Chart** in the application menu bar.

* Use the :ref:`right_pane_config` sidebar. A **Topic Chart** button is present in the configuration panel
  of any existing pane type, letting you replace the current pane with a new Topic Chart.

* Click the three-dots button in the header of any existing pane to open the split menu, then choose
  **Split right** or **Split down** and select **Topic Chart** to open a new chart alongside the current
  pane.

* Drag a numeric field from an open :ref:`Spy Pane <dockable_spy_pane>` and drop it onto an existing Topic
  Chart. The field is added as a new series on that chart. If you drop it onto an empty area of the
  workspace, a new Topic Chart is created with that field as its first series.

.. _topic_charts_series:

Managing Series
===============

**Adding a series:**

* Click **+ Add Series** in the **Series** section to expand the series creation form. Select a topic from
  the filtered list and then pick a numeric leaf field. Fields only appear after the first DDS sample has
  arrived on that topic. Click **Add Series** to confirm, or double-click a field to add it immediately.

* Drag a numeric field leaf directly from an open :ref:`Spy Pane <dockable_spy_pane>` and drop it onto the
  chart. The field is added as a new series immediately.

* Drag a numeric field leaf from the :ref:`topics_panel` on the left sidebar and drop it onto an existing
  Topic Chart. The field must belong to a topic on the same domain as the chart.

**Editing a series:**

Right-clicking a series entry in the legend opens a context menu with the following options:

* **Rename series** opens a dialog to give the series a custom display name shown in the legend.
* **Change color** opens a color picker to assign a custom line color.
* **Hide series** / **Display series** toggles the series visibility on the chart without removing it.
* **Set max data points** sets how many recent data points this series retains in memory.
* **Remove series** removes the series from the chart permanently.

The same options are available from the **Series** section of the :ref:`right_pane_config` sidebar, where
each series has a row with a color swatch, rename, visibility toggle, and remove button.

**Bulk actions:**

The **Actions** section of the :ref:`right_pane_config` sidebar provides:

* **Show All Series** makes every hidden series visible at once.
* **Hide All Series** hides all series without removing them.
* **Clear Chart** removes all series and resets the chart.

.. _topic_charts_controls:

Chart Header Controls
=====================

The chart header provides the following buttons from left to right:

* |add_series| **Add Series** opens the inline add-series panel in the :ref:`right_pane_config` sidebar.

* |resize| **Reset View** returns both axes to their default range after any manual zooming or panning.

* |legend| **Toggle Legend** shows or hides the legend listing all active series and their colors.

* |pause| / |play| **Pause / Resume** pauses live data ingestion, freezing the chart at its current state.
  Samples received while paused are discarded. Resuming restarts the live feed from the current time.

* |help| **Help** opens a contextual help panel with a description of the Topic Chart, usage tips,
  available mouse and keyboard interactions, and a link to this documentation page.

* The expand button maximizes the pane to fill the full workspace. Clicking it again restores the previous
  layout.

* |gear| **Panel Settings** opens the :ref:`right_pane_config` sidebar for this chart.

* The three-dots button opens the split menu to open a new pane to the right or below the current one.

* |cross| **Close** closes the pane.

.. _topic_charts_interaction:

Interactive Chart Controls
==========================

The following mouse and keyboard interactions are available directly on the chart area:

* **Click on a data point** to show its exact value.
* **Scroll wheel** to zoom the X axis in and out.
* **Ctrl + scroll wheel** to zoom the Y axis in and out.
* **Shift + drag** to zoom into a selected area.
* **Ctrl + click and drag** to scroll (pan) the axes without zooming.

.. _topic_charts_config:

Right-Side Configuration Panel
===============================

Opening the :ref:`right_pane_config` sidebar for a Topic Chart (via the |gear| button) shows the following
sections:

**Pane Settings**

Controls that apply to the whole chart:

* **Domain** selects which monitored DDS domain the chart subscribes to.
* **Time window** sets the width of the visible time range in seconds (1 to 86400; default 120).
* **Max points** sets the total number of data points the chart retains across all series (default 1000).
  When the limit is reached, the oldest points are removed as new samples arrive.
* **Apply & Reset Chart** applies any changes to these three fields and clears all existing series. This
  button is disabled when no domain is selected.

**Chart Name**

A text field and confirm button to rename the chart title shown in the pane header.

**Display**

* **Show legend** toggles the chart legend on or off.
* **Show points** toggles whether individual data points are drawn on series lines.
* **Sliding Window** when on, the chart scrolls in real time as new samples arrive (running mode). When
  off, the chart is paused and the view stays fixed until manually resumed.

**Series**

Lists every series currently added to the chart. Each row shows the series name, a color swatch to change
the line color, a visibility toggle, and a remove button. An **Add Series** button at the bottom expands
the inline series-creation section described below.

**Add Series** *(collapsible)*

* **Filter topics** narrows the topic list by name.
* The topic list shows all topics discovered on the selected domain. Selecting a topic populates the field
  list.
* **Filter fields** narrows the field path list by name.
* The field list shows the numeric leaf fields available for the selected topic, populated after the first
  DDS sample arrives on that topic. Double-clicking a field adds it as a series immediately.
* **Add Series** confirms the selection and adds the field as a new series to the chart.

**Axes**

* **Lock Y axis** switches the Y axis from auto-scale to a fixed range. When locked, **Y min** and
  **Y max** fields become editable.
* **Lock X axis** switches the X axis to a fixed range, capturing the current viewport as the initial
  bounds. When locked, **X min** and **X max** fields (format ``yyyy-MM-dd hh:mm:ss``) become editable.
* **Reset Zoom** returns both axes to their default range, equivalent to the |resize| button in the header.

**Panel Actions**

* **Split right** and **Split down** each expand a submenu to open a new pane alongside the current pane.
* **Save screenshot** saves a PNG image of the chart to disk.
* **Copy screenshot to clipboard** copies the chart image to the clipboard.

**Actions**

* **Show All Series** makes every hidden series visible.
* **Hide All Series** hides all series without removing them.
* **Clear Chart** removes all series and resets the chart.
