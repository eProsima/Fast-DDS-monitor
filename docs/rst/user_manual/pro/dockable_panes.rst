.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _dockable_panes:

#############################
Dockable Pane Workspace |Pro|
#############################

In *Fast DDS Monitor Pro*, every visualization and inspection view lives in a dockable pane. Statistics
charts, topic charts, spy panes, IDL panes, and image panes can all be arranged side by side in
a freely configurable split layout. You can resize, split, and close panes at any time to organize the
workspace in a way that suits your monitoring session.

.. _dockable_panes_layout:

Pane Layout
===========

The main content area of each monitor tab is a grid where each cell holds one pane. A single pane can
display any of the following view types:

* :ref:`Statistics chart <chart_panel>` (historic or dynamic series)
* :ref:`Topic Chart <topic_charts>`
* :ref:`Spy Pane <dockable_spy_pane>`
* :ref:`IDL Pane <dockable_idl_pane>`
* :ref:`Image Pane <image_pane>`

A single monitor tab supports up to **six panes** open at the same time.

.. _dockable_panes_splitting:

Splitting and Resizing
======================

To add a pane next to an existing one, use the split button in the pane header. This divides the current
cell horizontally or vertically and opens a new empty pane in the resulting space. To resize, drag the
divider between any two adjacent panes. The layout adjusts automatically whenever a pane is added or closed.

.. _dockable_spy_pane:

Spy Pane
========

A Spy pane subscribes to a DDS topic and shows the live data samples published on it in real time.

**Opening a Spy pane:**

There are several ways to open a new Spy pane:

* Right-click a topic in the :ref:`topics_panel`, the :ref:`logical_panel`, or the domain graph and choose
  **Spy topic data**.
* Use **Add Spy Topic View** in the application menu bar.
* Click the **Spy Topic View** button shown in an empty pane placeholder or in the workspace when no panes
  are open yet.
* Use the :ref:`right_pane_config` sidebar. A **Spy Topic View** button is present in the configuration
  panel of any existing pane type, including statistics charts, topic charts, IDL panes, and other spy
  panes, letting you replace the current pane with a new Spy pane.
* Click the three-dots button in the header of any existing pane to open the split menu, then choose
  **Split right** or **Split down** and select **Spy Topic View** to open a new Spy pane alongside the
  current one.

**Pane header controls:**

* The header shows the name of the topic being spied.
* The play/pause button (|play| / |pause|) starts and stops the live subscription without closing the pane.
* The copy button (|copy|) copies the last received sample as JSON to the clipboard in one click.
* The expand button maximizes the pane to fill the full workspace. Clicking it again restores the previous
  layout.
* The |gear| button opens the :ref:`right_pane_config` sidebar for this pane.
* The three-dots button opens the split menu to open a new pane to the right or below the current one.
* The |cross| button stops the subscription and removes the pane.

**Right-side configuration panel:**

When the :ref:`right_pane_config` sidebar is open for a Spy pane it shows four sections:

* **Pane Settings** lets you select a different domain and topic and apply the change with the
  **Apply & Restart** button, which restarts the subscription on the new topic immediately.
* **Playback** has a toggle to start or stop the live subscription without leaving the configuration panel.
* **Panel Actions** expands **Split right** and **Split down** submenus. Each submenu lets you open a new
  pane alongside the current one.
* **Actions** provides **Expand All** and **Collapse All** to unfold or fold the entire sample tree at once,
  **Clear** to discard all received samples from the view, and **Copy JSON to Clipboard** to copy the last
  sample.

You can have several Spy panes open at once, each subscribing to a different or the same topic.

.. _dockable_idl_pane:

IDL Pane
========

An IDL pane displays the Interface Definition Language (IDL) type description for a selected DDS topic.
The IDL is shown in a scrollable, selectable monospace text view. When a topic is not yet discovered the
pane waits and loads the IDL automatically once the topic becomes available.

**Opening an IDL pane:**

There are several ways to open a new IDL pane:

* Right-click a topic in the :ref:`topics_panel`, the :ref:`logical_panel`, or the domain graph and choose
  **Data type IDL view**.
* Use **Add Topic Type View (IDL)** in the application menu bar.
* Use the :ref:`right_pane_config` sidebar. A **Topic Type View (IDL)** button is present in the
  configuration panel of any existing pane type, letting you replace the current pane with a new IDL pane.
* Click the three-dots button in the header of any existing pane to open the split menu, then choose
  **Split right** or **Split down** and select **Topic Type View (IDL)** to open a new IDL pane alongside
  the current one.

**Pane header controls:**

* The header shows the type name of the topic followed by "(IDL)".
* The copy button (|copy|) copies the full IDL text to the clipboard in one click.
* The expand button maximizes the pane to fill the full workspace. Clicking it again restores the previous
  layout.
* The |gear| button opens the :ref:`right_pane_config` sidebar for this pane.
* The three-dots button opens the split menu to open a new pane to the right or below the current one.
* The |cross| button closes the pane.

**Text area interactions:**

* You can select text with the mouse or keyboard. Right-clicking opens a context menu with **Copy** (copies
  the selection, or the full IDL if nothing is selected) and **Select All**.
* For ROS 2 types, the IDL is shown in demangled form by default. A notice reading "ROS 2 Demangling
  applied" appears in the upper-right corner of the pane. To revert it, open the **View** menu and choose
  **Revert ROS 2 Demangling**. To re-apply it, use **View** > **Perform ROS 2 Demangling**. This setting
  also controls the toggle in the **Display** section of the right-side configuration panel.

**Right-side configuration panel:**

When the :ref:`right_pane_config` sidebar is open for an IDL pane it shows four sections:

* **Topic** displays the current topic name, domain number, and resolved type name as read-only labels.
* **Change Topic** lets you select a different domain and topic and apply the change with the
  **Apply & Reload** button, which fetches and displays the IDL for the new topic immediately.
* **Display** has a toggle to enable or disable ROS 2 demangling for the current pane. This is the same
  setting as the one controlled by the **View** menu and applies to all IDL panes at once.
* **Panel Actions** expands **Split right** and **Split down** submenus. Each submenu lets you open a new
  pane alongside the current one.
* **Actions** provides a **Select All** button to select the full IDL text in one click.
