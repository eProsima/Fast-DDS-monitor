.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _topic_charts:

##################
Topic Charts |Pro|
##################

*Topic Charts* |Pro| visualize live data published on any user-defined DDS topic, working directly
with the raw values from incoming samples rather than pre-computed DDS statistics metrics.

Two chart types are available:

* :ref:`Time Series Charts <time_series>` |Pro| plot one or more numeric fields against time as samples
  arrive, with support for multiple series, per-series color and visibility controls, and pause/resume.

* :ref:`XY Charts <xy_charts>` |Pro| plot two numeric fields against each other as a real-time scatter
  chart, enabling phase-space or correlation analysis between any pair of numeric fields within the same
  DDS domain.

Fields that are integers, floats, or doubles can be plotted in both chart types.
Struct and array fields cannot be plotted directly but can be expanded to reach their numeric leaf fields.

.. toctree::
    :hidden:

    /rst/user_manual/pro/time_series
    /rst/user_manual/pro/xy_charts
