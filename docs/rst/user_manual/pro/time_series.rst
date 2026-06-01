.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _time_series:

#######################
Time Series Charts |Pro|
#######################

A *Time Series Chart* plots the live values of one or more numeric fields from DDS topics over time.
Each series tracks one numeric field from one DDS topic and updates in real time as samples arrive.

Fields that are integers, floats, or doubles can be plotted.
Struct and array fields cannot be plotted directly but can be expanded to reach their numeric leaf fields.

.. _time_series_creating:

Opening a Time Series Chart
============================

There are several ways to open a new Time Series Chart pane:

* Right-click a topic in the :ref:`topics_panel`, the :ref:`logical_panel`, or the domain graph and choose
  **Chart topic data**. Built-in and statistics Fast DDS topics cannot be charted and this option is
  disabled for them.

* Use **Add Topic Live Chart** in the application menu bar.

* Use the :ref:`right_pane_config` sidebar. A **Topic Chart** button is present in the configuration panel
  of any existing pane type, letting you replace the current pane with a new Time Series Chart.

* Click the three-dots button in the header of any existing pane to open the split menu, then choose
  **Split right** or **Split down** and select **Topic Chart** to open a new chart alongside the current
  pane.

* Drag a numeric field from an open :ref:`Spy Pane <dockable_spy_pane>` and drop it onto an existing Time
  Series Chart. The field is added as a new series on that chart. Dropping it onto an empty area of the
  workspace creates a new chart with that field as its first series.

.. _time_series_series:

Managing Series
===============

**Adding a series:**

* Click **+ Add Series** in the **Series** section to expand the series creation form. Select a topic from
  the filtered list and then pick a numeric leaf field. Fields only appear after the first DDS sample has
  arrived on that topic. Click **Add Series** to confirm, or double-click a field to add it immediately.

* Drag a numeric field leaf from an open :ref:`Spy Pane <dockable_spy_pane>` and drop it onto the chart.
  The field is added as a new series immediately.

* Drag a numeric field leaf from the :ref:`topics_panel` on the left sidebar and drop it onto an existing
  chart. The field must belong to a topic on the same domain as the chart.

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

.. _time_series_controls:

Chart Header Controls
=====================

The chart header provides the following buttons from left to right:

* |add_series| **Add Series** opens the inline add-series panel in the :ref:`right_pane_config` sidebar.

* |resize| **Reset View** returns both axes to their default range after any manual zooming or panning.

* |legend| **Toggle Legend** shows or hides the legend listing all active series and their colors.

* |pause| / |play| **Lock / Resume chart scroll** locks both the X and Y axes so the chart stops
  auto-scrolling while data keeps flowing in. The button shows |pause| while at least one axis is still
  auto-scrolling and switches to |play| once both are locked. Clicking it again unlocks both axes and
  resumes auto-scroll. Data reception is unaffected; to pause ingestion use the **Running** toggle in the
  sidebar.

* |help| **Help** opens a contextual help panel with a description of the chart, usage tips, available
  interactions, and a link to this documentation page.

* The expand button maximizes the pane to fill the full workspace. Clicking it again restores the previous
  layout.

* |gear| **Panel Settings** opens the :ref:`right_pane_config` sidebar for this chart.

* The three-dots button opens the split menu to open a new pane to the right or below the current one.

* |cross| **Close** closes the pane.

.. _time_series_interaction:

Interactive Chart Controls
==========================

The following mouse and keyboard interactions are available directly on the chart area:

* **Click on a data point** to show its exact value.
* **Scroll wheel** to zoom the X axis in and out.
* **Ctrl + scroll wheel** to zoom the Y axis in and out.
* **Shift + drag** to zoom into a selected area.
* **Ctrl + click and drag** to scroll (pan) the axes without zooming.

.. _time_series_config:

Right-Side Configuration Panel
===============================

Opening the :ref:`right_pane_config` sidebar for a Time Series Chart (via the |gear| button) shows the
following sections:

**Pane Settings**

Controls that apply to the whole chart:

* **Domain** selects which monitored DDS domain the chart subscribes to.
* **Time window** sets the width of the visible time range in seconds (1 to 86400; default 120).
* **Max points** sets the total number of data points the chart retains across all series (default 1000).
  When the limit is reached, the oldest points are removed as new samples arrive.
* **Apply & Reset Chart** applies any changes to these three fields and clears all existing series.
  This button is disabled when no domain is selected.

**Chart Name**

A text field and confirm button to rename the chart title shown in the pane header.

**Display**

* **Show legend** toggles the chart legend on or off.
* **Show points** toggles whether individual data points are drawn on series lines.
* **Running** when on, the chart accepts new data in real time. When off, data ingestion is paused and
  samples received while paused are discarded; resuming restarts the live feed from the current time.
  This is independent from the header |pause| / |play| button, which only locks or unlocks axis scroll.

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
