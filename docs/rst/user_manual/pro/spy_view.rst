.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _dockable_spy_pane:

##############
Spy Topic View
##############

A *Spy Topic View* subscribes to a DDS topic and shows the live data samples published on it in real
time, displaying each incoming sample as an expandable field tree.
Useful for verifying that the expected data is being published and inspecting individual field values
as they arrive.

.. thumbnail:: /rst/figures/screenshots/spy_pro.png
    :align: center

Opening a Spy Topic View
========================

There are several ways to open a new Spy Topic View:

* Right-click a topic in the :ref:`topics_panel`, the :ref:`pro_logical_panel`, or the :ref:`domain graph <pro_domain_graph>` and
  choose **Spy topic data**.
* Use **Add → Add Spy Topic View** in the application menu bar.
* Click the **Spy Topic View** button shown in an empty pane placeholder or in the workspace when no
  panes are open yet.
* Click the three-dots button in the header of any existing pane, choose **Split right** or
  **Split down**, and select **Spy Topic View** to open a new Spy pane alongside the current one,
  or choose **Replace panel** to replace the current pane with a Spy Topic View.

Pane Header Controls
====================

* The header shows the name of the topic being spied.
* |play| / |pause| - starts and stops the live subscription without closing the pane.
* |copy| - copies the last received sample as JSON to the clipboard in one click.
* |help| - opens a contextual help panel with usage tips and a link to this documentation page.
* |maximize_square| / |minimize_square| - maximizes/ minimizes the pane; click again to restore the previous
  layout.
* |gear| - opens the :ref:`right_pane_config` sidebar for this pane.
* The three-dots button opens the split menu to open a new pane to the right or below.
* |cross| - stops the subscription and removes the pane.

Right-Side Configuration Panel |Pro|
====================================

When the :ref:`right_pane_config` sidebar is open for a Spy Topic View it shows four sections:

* **Pane Settings** - select a different domain and topic, then apply with **Apply & Restart**,
  which restarts the subscription on the new topic immediately.
* **Playback** - toggle to start or stop the live subscription without leaving the sidebar.
* **Actions** - **Expand All** and **Collapse All** to unfold or fold the entire sample tree at once,
  **Clear** to discard all received samples, and **Copy JSON to Clipboard** to copy the last sample.
* **Panel Actions** - **Split right** and **Split down** submenus, each letting you open a new pane
  alongside the current one.

You can have several Spy Topic Views open at once, each subscribing to a different or the same topic.

Field Interactions
==================

Individual fields within an expanded sample tree are interactive beyond just reading their values.

**Right-click a numeric leaf field** to open a context menu with a **Plot field** action.
Selecting it opens a new :ref:`Time Series Chart <time_series>` for that field immediately, without
having to navigate the Add menu.

**Drag a numeric leaf field** from the sample tree and drop it onto an existing
:ref:`Time Series Chart <time_series>` to add that field as a new series on the chart.
Dropping onto an empty area of the workspace creates a new chart with the dragged field as its first
series.

Both interactions work with any field whose IDL type is an integer, float, or double.
Struct and array fields can be expanded to reach their numeric children but cannot be dragged or
plotted directly.
