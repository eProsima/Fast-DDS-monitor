.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _dockable_idl_pane:

###########################
Topic Type View (IDL) |Pro|
###########################

A *Topic Type View* displays the Interface Definition Language (IDL) type description for a selected
DDS topic in a scrollable, selectable monospace text view.
When a topic is not yet discovered, the pane waits and loads the IDL automatically once the topic
becomes available.

.. thumbnail:: /rst/figures/screenshots/idl_pro.png
    :align: center

Opening a Topic Type View
=========================

There are several ways to open a new Topic Type View:

* Right-click a topic in the :ref:`topics_panel`, the :ref:`logical_panel`, or the domain graph and
  choose **Data type IDL view**.
* Use **Add → Add Topic Type View (IDL)** in the application menu bar.
* Use the :ref:`right_pane_config` sidebar - a **Topic Type View (IDL)** button is present in the
  configuration panel of any existing pane type, letting you replace the current pane.
* Click the three-dots button in the header of any existing pane, choose **Split right** or
  **Split down**, and select **Topic Type View (IDL)** to open a new IDL pane alongside the current
  one.

Pane Header Controls
====================

* The header shows the type name of the topic followed by "(IDL)".
* |copy| - copies the full IDL text to the clipboard in one click.
* The expand button maximizes the pane to fill the full workspace; click again to restore.
* |gear| - opens the :ref:`right_pane_config` sidebar for this pane.
* The three-dots button opens the split menu to open a new pane to the right or below.
* |cross| - closes the pane.

Text Area Interactions
======================

* Select text with the mouse or keyboard.
* Right-clicking opens a context menu with **Copy** (copies the selection, or the full IDL if nothing
  is selected) and **Select All**.
* For ROS 2 types, the IDL is shown in demangled form by default.
  A notice reading "ROS 2 Demangling applied" appears in the upper-right corner.
  To revert, open **View → Revert ROS 2 Demangling**.
  To re-apply, use **View → Perform ROS 2 Demangling**.
  This setting also controls the toggle in the **Display** section of the right-side configuration panel.

Right-Side Configuration Panel
================================

When the :ref:`right_pane_config` sidebar is open for a Topic Type View it shows four sections:

* **Topic** - displays the current topic name, domain number, and resolved type name as read-only
  labels.
* **Change Topic** - select a different domain and topic, then apply with **Apply & Reload**, which
  fetches and displays the IDL for the new topic immediately.
* **Display** - toggle to enable or disable ROS 2 demangling for the current pane.
  This setting applies to all IDL panes at once.
* **Panel Actions** - **Split right** and **Split down** submenus, each letting you open a new pane
  alongside the current one.
* **Actions** - **Select All** to select the full IDL text in one click.
