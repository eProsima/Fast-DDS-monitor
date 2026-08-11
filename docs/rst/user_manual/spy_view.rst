.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _spy_view:

##############
Spy Topic View
##############

A *Spy Topic View* subscribes to a DDS Topic and shows the live data samples published on it in
real time, displaying each incoming sample as an expandable field tree.
It is useful for verifying that the expected data is being published and for inspecting individual
field values as they arrive.

Opening a Spy Topic View
========================

Right-click a *Topic* in the :ref:`Domain view <domain_graph>` or the *Logical Panel* and select
**Spy topic data**.
This opens (or reuses) a single **Spy View** tab in the Main Panel and immediately starts
receiving live samples from the selected topic.

This option is disabled for Fast DDS metatraffic (discovery) topics, which cannot be spied on.
Fast DDS statistics topics and the monitor service topic can be spied on like any other topic.

.. note::

    The free version of *DDS Monitor* only has a single Spy View tab.
    Spying on a different topic reuses that same tab: it stops the previous subscription, clears
    the previously received samples, and starts spying on the newly selected topic.

Spy View Controls
==================

The Spy View header provides the following actions:

* **Play / Pause** - starts or stops the underlying topic subscription. While paused, previously
  received samples remain visible but no new samples are received.
* **Expand All** / **Collapse All** - expands or collapses every node of the sample field tree.
* **Copy JSON** - copies the currently received data to the clipboard as JSON.
* **Clear** - discards the samples currently displayed without stopping the subscription.

Reading the Field Tree
=======================

Each received sample is rendered as a two-column tree (*Name* and *Value*), one top-level node per
top-level field of the topic's data type:

* A primitive field (number, string or boolean) is shown as a leaf node with its value next to it.
* A nested struct field is shown as a node with no value of its own; expanding it reveals one child
  node per field of that struct, recursively.
* A sequence or array field is shown the same way, with one indexed child per element (``0``,
  ``1``, ``2``, ...), each expandable in turn if its element type is itself a struct.
