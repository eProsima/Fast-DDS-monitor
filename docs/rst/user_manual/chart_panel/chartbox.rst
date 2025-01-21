.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _chartbox:

########
Chartbox
########

This section explains the main functionalities and interactions available within a :ref:`chartbox_layout`,
a window contained in the :ref:`main_panel_layout` that displays entities data with different configurations.

To start a new Chartbox, press :ref:`display_historic_data_button` or :ref:`display_dynamic_data_button`
in :ref:`edit_menu` or in :ref:`shortcuts_bar`.
Any Chartbox will be displayed in the central panel with the title of the *DataKind* they refer to.
In these charts it will be displayed the Series of data that the user initializes.
For how to set a new series please refer to :ref:`create_historic_series` or :ref:`create_dynamic_series`.

.. _chartbox_chart_menu:

Chart Menu
----------
In the top bar of each Chartbox there is a Menu tab *Chart* with the following buttons.

.. _chartbox_chart_menu_reset_zoom:

Reset zoom
^^^^^^^^^^
Reset the zoom of the Chartbox to the standard one.
The standard zoom is calculated to fit all the data that is being currently displayed.
It is also possible to take this action by clicking on the |resize| button displayed in the same chart box.

.. _chartbox_chart_menu_set_axes:

Set axes
^^^^^^^^
This menu opens a dialog pop-up for the user to set the axes of the chart.
Changing the X-axis (time axis) is disabled by default, thus maintaining the time values currently displayed on the
chart.
This allows dynamic charts to continue to update the value of the X-axis while the Y-axis remains fixed.
It is also possible to access this dialog by clicking on the |editaxis| button displayed in the same chart box.

.. figure:: /rst/figures/screenshots/set_axes.png
    :align: center

To return to the original time axis, and allow a dynamic update of the Y-axis, simply click on the
:ref:`chartbox_chart_menu_reset_zoom` button located to the right of the chart.

Clear chart
^^^^^^^^^^^
Eliminate every data configuration displayed in the Chartbox.

Rename chart box
^^^^^^^^^^^^^^^^
Change the name of the chart box.

Close chart box
^^^^^^^^^^^^^^^
Eliminate the Chartbox and every configuration in it.
It could be removed as well pressing the ``x`` button in the top of the chart.

Export to CSV
^^^^^^^^^^^^^
Export the data of all series in the chart box to a CSV file.
Please refer to section :ref:`export_data` for more information on the format of the generated CSV file.

Chart Controls
^^^^^^^^^^^^^^
Displays an informative dialog with the key combination to execute actions on the chart.
It is also possible to access this dialog by clicking on the |info| button displayed in the same chart box.


.. figure:: /rst/figures/screenshots/Chartbox_info.png
    :align: center


Series Menu
-----------
In the top bar of each Chartbox there is a Menu tab *Series* with these buttons.

Add series
^^^^^^^^^^
Add a new series in this Chartbox.
This will open a new :ref:`create_historic_series` or :ref:`create_dynamic_series`.

Hide all series
^^^^^^^^^^^^^^^
Hide all series in this Chartbox.

Display all series
^^^^^^^^^^^^^^^^^^
Reveal all series in this Chartbox.

Chart Interaction
-----------------
The user could interact with the Chartbox and the data in it by resizing and moving the view.

Point description
^^^^^^^^^^^^^^^^^
Clicking in any point of a displayed series, an info box will be prompt with the ``x`` and ``y``
label values of the data point.

Moving the view
^^^^^^^^^^^^^^^
Press and hold ``Ctrl`` key and left click in one point of the Chartbox.
Move the mouse to scroll over the data.

Zoom in/out
^^^^^^^^^^^
Press and hold ``Ctrl`` key and scroll up to zoom in to the center of the Chartbox.
Press and hold ``Ctrl`` key and scroll down to zoom out from the center of the Chartbox.

.. _chartbox_series_configuration:

Series Configuration
--------------------
Right clicking in the name of a series in the *Legend* will open a dialog with the available configurations for
a series.

Remove series
^^^^^^^^^^^^^
Remove this series.

Rename series
^^^^^^^^^^^^^
Change the name of this series.

Change color
^^^^^^^^^^^^
A Dialog will open to choose a new color for the series and the points displayed.
Also available with left click on the color of the series in the *Legend*.

Hide/Show series
^^^^^^^^^^^^^^^^
Hide a series if it is displayed, or it reveal it if it is hide.
Also available with left click on the name of the series in the *Legend*.

Export to CSV
^^^^^^^^^^^^^
Export the series data to a CSV file.
Please refer to section :ref:`export_data` for more information on the format of the generated CSV file.

Set max data points
^^^^^^^^^^^^^^^^^^^
Set a limit on the number of data points displayed for this data series.

Dynamic Chartbox
----------------
The Chartbox that holds dynamic series have some extra functionality.
These Chartbox could be stopped at any time (or played in case they are already stopped).
This allows to stop the updating the axis, enabling zooming and moving along the chart.
The data presented in the Chartbox will keep updating with the same time interval independently of the play status.

To pause the real time update of the time axis, click on the Real-Time menu or on the |play|/|pause| button placed on
the right side of the chart, or set the axes to a specific value with the :ref:`chartbox_chart_menu_set_axes` button.
