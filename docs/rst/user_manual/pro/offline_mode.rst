.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _offline_mode:

##################
Offline Mode |Pro|
##################

*Offline Mode* lets you open a previously captured DDS recording and inspect it inside the monitor
exactly as if it were a live session, but with full playback control over the recorded timeline.
Instead of connecting to a running DDS network, the monitor reads samples from a recording file and
lets you scrub, play, pause, loop, and change speed through the captured data.

.. thumbnail:: /rst/figures/screenshots/offline_pro.png
    :align: center

.. _offline_mode_opening:

Opening a Recording
===================

Use **File → Open Recording...** to select a recording file. Two formats are supported:

* **MCAP** (``.mcap``).
* **SQLite** (``.db``).

While a recording is open, the window title shows ``Fast DDS Monitor Pro | Offline: <filename>`` and a
playback bar appears at the bottom of the window.

Opening a recording never interrupts a live session. If the current window has never started a
monitor, the recording opens in that same window. If a monitor has already been started in it (whether
still active or since stopped), the recording instead opens in a **new, independent monitor
application**, leaving the original live monitor running untouched. The two applications are separate
processes, so you can inspect the recording and keep monitoring at the same time, and closing one does
not close the other.

.. _offline_mode_trim:

Selecting a Range
=================

When a recording opens, a *Select recording range* dialog appears once so you can restrict playback to
a portion of the recording. It offers a range slider (in seconds from the recording start),
decimal-second spin boxes, and absolute wall-clock fields (``YYYY-MM-DD HH:MM:SS``, the date being
optional).

* **Apply range** commits the selected range.
* **Use full recording** (or pressing *Escape* / closing the dialog) loads the entire recording.

.. _offline_mode_transport_bar:

The Playback Bar
================

The playback bar is only visible in offline mode and provides the following controls.

**Recording information (left)**
    A *RECORDING* label, the recording file name (hover to see the full path), and the recording's
    absolute start time and total duration.

**Timeline (center)**
    A scrubber showing the current position (``MM:SS``) and the recording length. Drag the scrubber to
    move the playback cursor; hovering shows the absolute time at that point. Below the scrubber:

    * **Jump to start** - moves the cursor to the beginning.
    * **Back 5 seconds** (*-5s*) and **Forward 5 seconds** (*+5s*).
    * A round **play / pause** button.
    * A **loop** toggle - repeats playback continuously; the tooltip reads *Looping on* when active.

**Speed (right)**
    A *SPEED* control showing the current playback rate. Click it to choose from ``0.1x``, ``0.25x``,
    ``0.5x``, ``1x``, ``2x``, ``4x``, and ``8x``.

    A |help| button opens a contextual help panel with a link to this documentation page.

You can also move the playback cursor directly on a recording chart: left-drag on the plot to move the
cursor, and right-click to read the nearest point's value. On :ref:`Topic Charts <topic_charts>`, each
series' value at the cursor position is shown next to its entry in the chart legend, so the legend
reads out the value of every series at the current playback point as you scrub.

.. _offline_mode_panes:

What Works Offline
==================

Charts show the whole recording at once. Spy and image panes show the last sample at or before the
playback cursor (and appear empty before the first sample arrives). The following panes and panels are
available offline: :ref:`Topic Charts <topic_charts>`, :ref:`Spy Topic Views <dockable_spy_pane>`,
:ref:`Topic Type Views (IDL) <dockable_idl_pane>`, :ref:`Image Panes <image_pane>`, and the
:ref:`Register Type View <register_type>`.

The following are **not** available while inspecting a recording, and their controls are disabled with
the tooltip *Unavailable in offline mode (inspecting a recording)*:

* :ref:`Statistics Charts <pro_chart_view>`.
* :ref:`Publisher Panes <publisher_pane>`.
* :ref:`XY Charts <xy_charts>`.
* The :ref:`Custom Series <custom_series_panel>`, :ref:`Enable / disable statistics
  <statistics_readers_panel>`, and :ref:`Alerts <pro_alerts_panel>` sidebar panels (their icons are
  hidden).
* Live monitoring actions in the application menu.
* :ref:`Workspace <workspace>` save and load.
