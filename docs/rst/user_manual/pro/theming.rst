.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _theming:

###########################
Dark Mode |Pro|
###########################

*Fast DDS Monitor Pro* provides a full theming system with two palettes: Light and Dark. When you switch
themes, every part of the application updates instantly: panels, charts, dialogs, icons, controls, and the
unified menu bar all follow the active palette without requiring a restart.

.. _theming_switching:

Switching Between Themes
========================

The theme is selected from the **View** menu in the menu bar. Open **View**, navigate to the **Theme**
submenu, and choose one of the two entries:

* **Light** activates the light palette (white surfaces, dark text, eProsima brand colors on a light
  background).
* **Dark** activates the dark palette (near-black surfaces, light text, eProsima brand colors on a dark
  background).

Both entries are mutually exclusive and are displayed as checkable actions. The currently active theme has
a checkmark next to its name.

The selected theme is persisted in the workspace file. When a workspace is loaded, the theme stored in that
file is restored. If no explicit choice has been made (for example, when no workspace has been saved yet),
the application follows the operating system color scheme preference: it starts in Dark mode on systems that
report a dark scheme and in Light mode otherwise.

.. _theming_coverage:

What the Theme Covers
=====================

The palette is applied reactively across every component in the application. Changing the theme takes
effect immediately without affecting monitor state, data, or alerts.

**Panels and sidebars**

The Explorer, Topics Explorer, Alerts, Status, Issues, and Alert Messages panels all adapt to the active
theme. Background surfaces, text colors, row hover states, scrollbars, and divider lines all follow the
active palette.

**Charts**

Statistics charts and topic charts use themed backgrounds, axis labels, grid lines, and legend text. The
chart series color palette is a fixed set of ten colors that remains the same in both themes.

**Domain graph**

The domain graph view uses themed node colors and edge colors. The host node background changes between
themes; entity status colors (green for alive, yellow for warning, red for error) are fixed.

**Dialogs and wizards**

All dialogs, including the monitor initialization dialogs, alert dialog, alias dialog, and pane creation
wizards, use the active palette for their backgrounds, inputs, and button styles.

**Controls**

Buttons, text fields, spin boxes, combo boxes, toggles, sliders, and scroll bars are all consistently
styled for both palettes. Disabled states use a dedicated muted text color in both themes.

**Icons**

Icons throughout the application switch between their dark and light icon variants automatically. On the
light palette the default icon variant uses black strokes; on the dark palette it switches to white
strokes. Accent, warning, success, and danger icon tints are consistent across both themes.

**Unified menu bar and window controls**

The custom title bar, menu bar, and platform window control buttons (minimize, maximize, close) follow
the active palette. The title bar surface and text color adapt alongside the rest of the application.

.. _theming_palette:

Color Palette Details
=====================

The following table lists every color role that changes between the two themes.

.. list-table::
   :header-rows: 1
   :widths: 30 35 35

   * - Role
     - Light
     - Dark
   * - Application background
     - ``#F5F5F5``
     - ``#181818``
   * - Panel and card surface
     - ``#FFFFFF``
     - ``#1F1F1F``
   * - Dividers and borders
     - ``#BEBEBE``
     - ``#414141``
   * - Emphasized borders
     - ``#CFCFCF``
     - ``#303030``
   * - Primary text
     - ``#111111``
     - ``#EEEEEE``
   * - Secondary text
     - ``#404040``
     - ``#BFBFBF``
   * - Muted text
     - ``#808080``
     - ``#7F7F7F``
   * - Disabled text
     - ``#A3A3A3``
     - ``#5C5C5C``
   * - Hover background
     - ``#F2F2F2``
     - ``#0D0D0D``
   * - Domain graph host node
     - ``#3E3E3E``
     - ``#000000``
   * - Default icon stroke
     - black
     - white

The following brand and status colors are fixed and do not change between themes.

.. list-table::
   :header-rows: 1
   :widths: 40 60

   * - Role
     - Value
   * - eProsima accent (light blue)
     - ``#5EBCE1``
   * - eProsima hover blue
     - ``#0895CD``
   * - eProsima dark blue
     - ``#09487E``
   * - Success (green)
     - ``#88CE28``
   * - Warning (yellow)
     - ``#FFC000``
   * - Danger (red)
     - ``#FF0D0C``

.. _theming_charts:

Chart Series Colors
===================

Charts use a fixed ten-color palette for series regardless of the active theme. The palette cycles through
the following colors in order when new series are added:

``#1f77b4``, ``#ff7f0e``, ``#2ca02c``, ``#d62728``, ``#9467bd``, ``#8c564b``, ``#e377c2``,
``#7f7f7f``, ``#bcbd22``, ``#17becf``

These colors were chosen to be distinguishable in both light and dark environments.
