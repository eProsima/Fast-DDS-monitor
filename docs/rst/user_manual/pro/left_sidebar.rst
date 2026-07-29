.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _pro_left_sidebar:

############
Left Sidebar
############

The left sidebar contains several panels accessible via the icon bar on the left edge of the window.
Each icon switches the sidebar to the corresponding panel, and hovering an icon shows its tooltip.
The sidebar can be hidden entirely from **View → Hide Left Sidebar** and resized by dragging its border.

- :ref:`Explorer Panel <pro_left_panel>` (*DDS Entities Explorer*) - shows all DDS entities discovered
  by the monitor in collapsible, interactive lists organized by DDS, Physical, Logical, and
  Info/Statistics sub-panels.
- :ref:`Topics Panel <topics_panel>` |Pro| (*Topics Explorer*) - topic-centered view with text
  filtering, expandable field trees, and direct actions (Spy, Chart, Publish, IDL) for any topic.
- :ref:`Custom Series Panel <custom_series_panel>` |Pro| (*Custom Series*) - define, edit, and manage
  user-defined data series computed from a JavaScript formula.
- :ref:`Enable / Disable Statistics Panel <statistics_readers_panel>` |Pro| - control which statistics
  DataReaders are active, enabling on-demand collection of only the statistics you need.
- :ref:`Alerts Panel <pro_alerts_panel>` - define threshold-based alert rules and view their status
  and configuration details.
- :ref:`Monitor Status Panel <pro_status_panel>` (*Monitor Status*) - live entity counts, active
  domains, and a scrollable log of DDS network events.
- :ref:`Issues Panel <pro_issues_panel>` (*Issues*) - operational error events reported by the
  application.

.. note::

    The *Custom Series*, *Alerts*, and *Enable / Disable Statistics* panels are hidden in
    :ref:`offline mode <offline_mode>` while inspecting a recording.

.. toctree::
    :hidden:

    /rst/user_manual/pro/explorer_panel
    /rst/user_manual/pro/topics_panel
    /rst/user_manual/pro/custom_series_panel
    /rst/user_manual/pro/statistics_readers_panel
    /rst/user_manual/pro/alerts_panel
    /rst/user_manual/pro/status_panel
    /rst/user_manual/pro/issues_panel
