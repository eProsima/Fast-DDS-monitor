.. _release_notes:

##############
Version v0.2.0
##############

This release includes the following **improvements**:

* Add ToolTips for dialog parameters
* Add Real-Time charts
* Refactor sidebars
  * New left sidebar with all the DDS, physical and logical entities together with its corresponding information.
  * Separated pane for Fast DDS Monitor status.
  * New pane to display Issues information.
* Possibility to change the Entity name setting an alias for it.
* Entities not alive are marked in gray color.
* Possibility to display/hide the not alive entities.
* Entity menu displayed right-clicking on them.
* Support for Windows platforms.
* Resizable charts in three different sizes: full screen, two chart boxes per row and three chart boxes per row.
* Re-nameable chart boxes.
* Export charts data to CSV. It is possible to export a single series, a whole chartbox or all chartboxes of the
  monitor to a single CSV file.

This release includes the following **bugfixes**:

* Get correct Entity Id on the add statistics series dialog.
* Set correct Entity Id on the add statistics series dialog.
* Icons colorization in Windows platforms.
* Avoid launch a command prompt when the application is executed in Windows.
* TreeModels refactor
  * Convert all arrays to dictionaries with the array index as the element key.
  * Fix item duplication when collapsed.
* Avoid destroy ChartBoxes when they are out of the view.
* Increase Y axis in historic CharBoxes so all the data is visible.
* Refactor Historic series so all the internal data is deleted when graphics are removed.
* Increased the number of characters for series labels.
* Change displayed chart units for some DataKinds.
* Add units to the statistics entity summary.

#################
Previous versions
#################

.. include:: previous_versions/v0.1.0.rst
