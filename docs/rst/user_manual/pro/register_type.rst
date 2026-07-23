.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _register_type:

###################
Register Type |Pro|
###################

The *Register Type View* lets you register a user-supplied data type from its IDL definition so it can
be used across the monitor even for topics whose type was never discovered on the network (for
example, *Safe DDS* topics). Once a type is registered, it can be paired with any topic name when
:ref:`spying <dockable_spy_pane>`, :ref:`publishing <publisher_pane>`, or :ref:`charting
<topic_charts>`, on every monitored domain.

Where the :ref:`Topic Type View (IDL) <dockable_idl_pane>` only *displays* the IDL of an
already-discovered topic, the Register Type View *supplies* a type definition to the backend.

.. thumbnail:: /rst/figures/screenshots/register_type_pro.png
    :align: center

.. _register_type_opening:

Opening a Register Type View
============================

There are several ways to open a new Register Type View:

* Use **Add → Add Register Type View** in the application menu bar.
* Click the three-dots button in the header of any existing pane, choose **Split right** or
  **Split down**, and select **Register Type View** to open a new pane alongside the current one, or
  choose **Replace panel** to replace the current pane with a Register Type View.

.. _register_type_workflow:

Registering a Type
==================

The pane is organized top to bottom into the following steps.

**Select an existing type or start from scratch**
    A dropdown listing every already-known type plus a **Start from scratch** entry.

    * Choosing **Start from scratch** clears the editor so you can write or paste a fresh IDL.
    * Choosing an existing type loads its IDL into the editor as a starting point; edit it and give it
      a new name to register a new type.

**IDL struct**
    A dropdown listing every struct parsed from the IDL, shown with its fully-qualified name
    (modules included, e.g. ``a::b::MyType``). It defaults to the last struct found in the IDL. When
    the IDL contains no struct the dropdown shows *No struct found in the IDL*.

**Register as**
    A text field with the name under which the type will be registered. It defaults to the selected
    struct's name.

    If you change it to a name that is **not** a struct in the IDL, the type is registered under that
    name as an *XTypes alias* of the selected struct - the struct itself is left unchanged. This is
    useful for registering a type under the exact name a topic expects. The name must not match a
    different struct in the IDL, and it is a type name, not a topic name.

**IDL**
    The IDL editor. Use **Upload IDL** to load an ``.idl`` file, or write / paste the IDL directly.
    A link to the `Fast DDS Gen data types documentation
    <https://fast-dds.docs.eprosima.com/en/latest/fastddsgen/dataTypes/dataTypes.html>`__ is provided
    as a reference for the accepted syntax.

    If the main IDL contains ``#include`` directives, a **tab appears for each included file**: the
    first tab is the main file and the remaining tabs are the includes. Fill in the contents of each
    included file. Tabs that are still empty are marked with a red dot. Uploading an ``.idl`` file
    automatically pre-fills sibling ``.idl`` files found next to it.

**Save**
    Registers the type. The button is enabled only when both the *Register as* name and the IDL are
    non-empty. A status line above the button reports the result in green on success or red on error.

.. _register_type_results:

Registration Results
====================

* On success the pane reports *Type '<name>' registered successfully.*
* When the type completes a topic that had been discovered without type information, the pane reports
  that the previously incomplete type now has its definition.
* Backend validation errors (for example, malformed IDL) are shown verbatim in red.

Registration is a global operation: the registered type becomes available on every monitored domain
and can be paired with any topic name. Registered type definitions are preserved when you
:ref:`save and restore a workspace <workspace>`.

.. _register_type_offline:

Availability in Offline Mode
============================

Registering a type is available in :ref:`offline mode <offline_mode>`. Because registration is a
global backend action that is not tied to any live entity, it applies while inspecting a recording as
well, letting you resolve undiscovered types against recorded topics.

.. _register_type_config:

Right-Side Configuration Panel
==============================

Opening the :ref:`right_pane_config` sidebar for a Register Type View (via the |gear| button) shows a
*REGISTER TYPE* panel. All editing happens inside the pane itself, so the sidebar only offers the
shared **Panel Actions** (split and replace submenus). See :ref:`right_pane_config` for the full
configuration panel reference.
