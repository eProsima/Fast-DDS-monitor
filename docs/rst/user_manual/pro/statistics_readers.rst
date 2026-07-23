.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _statistics_readers_panel:

#################################
Enable / Disable Statistics |Pro|
#################################

*Fast DDS Monitor Pro* creates its statistics DataReaders **on demand** to save resources: a reader
that collects a particular statistic is only created when something actually needs it. The
*Enable / disable statistics* panel gives you direct control over which statistics readers are active,
so you only gather the data you ask for.

.. thumbnail:: /rst/figures/screenshots/statistics_readers_pro.png
    :align: center

.. _statistics_readers_panel_location:

Accessing the Panel
===================

Open the panel by clicking the **Enable/Disable Statistics** icon in the vertical icon bar on the far
left of the window (hover any icon to see its tooltip). The panel header reads
*ENABLE / DISABLE STATISTICS* and includes a |help| button with a link to this documentation page.

.. _statistics_readers_panel_usage:

Toggling Statistics Readers
===========================

The panel lists the available statistics, each with a toggle switch labeled with the statistic name:

* **Turning a toggle on** creates and keeps the corresponding DataReader alive on **every monitored
  domain**, so that statistic is always collected even when no chart or alert currently uses it.
* **Turning a toggle off** removes the reader on every domain, even if a chart still references it.
  Existing charts remain open but stop receiving new data for that statistic.

.. _statistics_readers_panel_automatic:

Automatic (On-Demand) Readers
=============================

Creating a :ref:`Statistics Chart <pro_chart_view>` or an :ref:`alert <pro_alerts_panel>` automatically
creates and enables the reader it needs, even if you had disabled it, because the chart or alert could
not work otherwise. Such a reader is removed again once its last chart or alert is gone, **unless** you
have enabled it manually here.

A reader that is currently active only because a chart or alert needs it is marked with an info
icon. Its tooltip explains why it is active (for example, *Active because a chart is currently using
it. Enable it here to keep it.*). Toggle it on if you want it to persist after that chart or alert is
removed.

Two readers are always active and are therefore **not** listed in this panel:

* The **monitor service** reader, which is required for the monitor to work at all.
* The **physical data** reader, which feeds the Physical view (hosts, users, and processes).

Manual overrides (readers you have explicitly enabled or disabled) are preserved when you
:ref:`save and restore a workspace <workspace>`. Readers that are active only because a chart or alert
needs them are not persisted, since they are recreated automatically when that chart or alert is
restored.
