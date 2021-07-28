.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _chartbox:

########
Chartbox
########

In this section it is explained the main functionalities and interactions available within a :ref:`chartbox_layout`,
a window contained in the :ref:`main_panel_layout` that displays entities data with different configurations.

To start a new Chartbox, press :ref:`display_historic_data_button` or :ref:`display_dynamic_data_button`
in :ref:`edit_menu` or in :ref:`shortcuts_bar`.
These chartbox will be displayed in the central panel with the title of the *DataKind* they refer to.
In these charts it will be displayed the Series of data that the user initialize.
For how to set a new series please refer to :ref:`create_historic_series` or :ref:`create_dynamic_series`.

.. _chartbox_chart_menu:

Chart Menu
----------
In the top bar of each Chartbox there is a Menu tab *Chart* with the following buttons.

Reset zoom
^^^^^^^^^^
Reset the zoom of the Chartbox to the standard one.
The standard zoom is calculated to fit all the data that is being currently displayed.

Clear chart
^^^^^^^^^^^
Eliminate every data configuration displayed in the Chartbox

Close chart box
^^^^^^^^^^^^^^^
Eliminate the Chartbox and every configuration in it.
It could be removed as well pressing the ``x`` button in the top of the chart.

Export to CSV
^^^^^^^^^^^^^
Export the data of all series in the chart box to a CSV file.
Please refer to section :ref:`export_data` for more information on the format of the generated CSV file.

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

Dynamic chartbox
----------------
The chartbox that holds dynamic series have some extra functionality.
These chartbox could be stopped at any time (or played in case they are already stopped).
This allows to stop the updating the axis, so zoom and move along the chart is available.
The data presented in the chartbox will keep updating with the same time interval independently of the play status.

In order to pause or continue the axis update the chartbox has an extra button in menu *Real Time* or in the top right
of the box to pause or continue regarding the actual state.
