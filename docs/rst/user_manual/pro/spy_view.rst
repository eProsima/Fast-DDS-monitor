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

* Right-click a topic in the :ref:`topics_panel`, the :ref:`logical_panel`, or the domain graph and
  choose **Spy topic data**.
* Use **Add → Add Spy Topic View** in the application menu bar.
* Click the **Spy Topic View** button shown in an empty pane placeholder or in the workspace when no
  panes are open yet.
* Use the :ref:`right_pane_config` sidebar - a **Spy Topic View** button is present in the
  configuration panel of any existing pane type, letting you replace the current pane.
* Click the three-dots button in the header of any existing pane, choose **Split right** or
  **Split down**, and select **Spy Topic View** to open a new Spy pane alongside the current one.

Pane Header Controls
====================

* The header shows the name of the topic being spied.
* |play| / |pause| - starts and stops the live subscription without closing the pane.
* |copy| - copies the last received sample as JSON to the clipboard in one click.
* The expand button maximizes the pane to fill the full workspace; click again to restore.
* |gear| - opens the :ref:`right_pane_config` sidebar for this pane.
* The three-dots button opens the split menu to open a new pane to the right or below.
* |cross| - stops the subscription and removes the pane.

Right-Side Configuration Panel
================================

When the :ref:`right_pane_config` sidebar is open for a Spy Topic View it shows four sections:

* **Pane Settings** - select a different domain and topic, then apply with **Apply & Restart**,
  which restarts the subscription on the new topic immediately.
* **Playback** - toggle to start or stop the live subscription without leaving the sidebar.
* **Panel Actions** - **Split right** and **Split down** submenus, each letting you open a new pane
  alongside the current one.
* **Actions** - **Expand All** and **Collapse All** to unfold or fold the entire sample tree at once,
  **Clear** to discard all received samples, and **Copy JSON to Clipboard** to copy the last sample.

You can have several Spy Topic Views open at once, each subscribing to a different or the same topic.
