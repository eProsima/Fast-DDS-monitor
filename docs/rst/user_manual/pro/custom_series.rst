.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _custom_series_panel:

###################
Custom Series |Pro|
###################

A *Custom Series* is a user-defined data series computed from a JavaScript formula.
Instead of plotting a single field straight from a DDS topic, you bind one or more topic fields (and
optional constants) to variables and write a short function that returns the value to plot.
The result behaves like any other topic-chart series: it can be dragged onto a :ref:`Topic Chart
<topic_charts>`, colored, hidden, and exported.

Custom series are managed from the **Custom Series** panel in the left sidebar and edited in a
dedicated central-tab editor.

.. thumbnail:: /rst/figures/screenshots/custom_series_chart_pro.png
    :align: center

.. _custom_series_panel_location:

The Custom Series Panel
=======================

Open the panel by clicking the **Custom Series** icon in the vertical icon bar on the far left of the
window (hover any icon to see its tooltip). The panel header reads *CUSTOM SERIES* and provides, from
left to right:

* **Export Custom Series** - saves all defined series to a ``.json`` file.
* **Import Custom Series** - loads series definitions from a ``.json`` file.
* |help| - opens a contextual help panel with usage tips and a link to this documentation page.
* |plus| - creates a new custom series and opens the editor.

When no series are defined yet, the panel shows *No custom series defined. Click + to create one.*

Each defined series appears as a row showing its name. Hovering a row reveals a |gear| **Edit** button
and a red |cross| **Delete** button. Right-clicking a row opens a context menu with:

* **Change alias** - rename the series.
* **Plot on chart** - add the series to the active :ref:`Topic Chart <topic_charts>` (disabled when
  the series has an error).
* **Edit** - open the formula editor.
* **View error** - shown only when the series failed to evaluate; opens the error message.
* **Delete** - remove the series (asks for confirmation; this cannot be undone).

A series can also be plotted by **dragging its row onto a Topic Chart pane**. A series that currently
has an error cannot be dragged or plotted until the error is fixed.

.. _custom_series_editor:

The Formula Editor
==================

Creating or editing a series opens a central-tab editor organized into the following sections.

.. _custom_series_name:

Series Name
-----------

A text field holding the series name. The name must be non-empty and unique across all custom series.

.. _custom_series_bindings:

Data Sources
------------

Each *data source* binds a numeric field of a DDS topic to a variable name that the formula can read:

#. Select a **Domain** and a **Topic**.
#. Pick a **Field** from the field tree. A filter field (*Filter fields...*) narrows the list. While
   no data has arrived the list shows *Waiting for first sample...*; before a topic is chosen it shows
   *Select a topic first*.
#. Enter a variable name in **As var**. The name must be a valid JavaScript identifier (start with a
   letter, ``_`` or ``$``; no spaces or special characters).
#. Click **Add Binding**.

Added bindings are listed as ``varName = topic.fieldPath`` and can be removed individually. At least
one data source binding is required before a series can be saved.

.. _custom_series_globals:

Global Variables
----------------

Optional named constants available to the formula. Enter a **name** and a **value** (a JavaScript
literal such as ``42``, ``3.14``, ``"text"``, ``true``, ``false``, or ``null``) and click
**Add Global Variable**.

.. _custom_series_formula:

JavaScript Function Body
------------------------

The formula itself. The editor shows an auto-generated signature line that updates as you add data
sources:

.. code-block:: javascript

    function(time, <your variables>) {
        // write the function body here and return the value to plot
    }

* ``time`` is the sample timestamp; each bound variable and each global variable is in scope.
* **Return the value to plot** - the returned number becomes the series data point.
* **Return** ``undefined`` **(or nothing) to skip a point** - this is not an error and simply produces
  no data point for that sample.

Formulas run in *Qt*'s built-in JavaScript engine (``QJSEngine``) and support standard ECMAScript. All
standard built-ins are available, including ``Math``, ``JSON``, ``Number``, ``String``, ``Array``,
``Object``, ``Date``, ``RegExp``, ``parseInt``, ``parseFloat``, ``isNaN``, and ``isFinite``.

For safety, the following identifiers are **not** available inside a formula and are rejected during
validation: ``console``, ``window``, ``document``, ``XMLHttpRequest``, ``fetch``, ``setTimeout``,
``clearTimeout``, ``setInterval``, ``clearInterval``, and ``qt``.

.. thumbnail:: /rst/figures/screenshots/custom_series_editor_pro.png
    :align: center

.. _custom_series_saving:

Saving a Series
---------------

Three buttons are available at the bottom of the editor:

* **Save** - validate and save, keeping the editor open.
* **Save & Exit** - save and close the editor. The editor briefly waits for a runtime error before
  closing; if the formula throws on its first evaluation, the editor stays open so you can fix it.
* **Cancel** - discard changes.

On success the editor shows *Series saved successfully.* Validation reports a specific message when
something is wrong, for example when the series name is empty or already exists, when no data source
binding has been added, when a variable name is not a valid identifier, or when the function body is
empty. If a saved formula throws while running, a **new** series is removed and reported as *not
saved*, while an **edited** series rolls back to its previous formula.

.. _custom_series_import_export:

Importing and Exporting
=======================

Custom series definitions can be persisted to disk and shared between sessions or machines:

* **Export Custom Series** (panel button, or **File → Export Custom Series...**) writes every defined
  series to a ``.json`` file.
* **Import Custom Series** (panel button, or **File → Import Custom Series...**) loads series
  definitions from a ``.json`` file.

See :ref:`pro_application_menu` for the corresponding menu entries.
