.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _image_pane:

################
Image Pane |Pro|
################

The *Image Pane* is a dockable panel that renders live image or video frames published on a DDS topic.
When you subscribe to a compatible topic, the pane detects the image schema automatically, decodes each
incoming sample, and displays the resulting frame inside the monitor workspace. The decoded image scales to
fit the pane while preserving the original aspect ratio.

.. _image_pane_schemas:

Supported Image Schemas
=======================

The pane detects the topic type automatically and supports two families of schemas:

**ROS 2 sensor_msgs types**

* ``sensor_msgs/msg/Image`` carrying a raw pixel buffer.
* ``sensor_msgs/msg/CompressedImage`` carrying compressed image frames.
* ``sensor_msgs/msg/CompressedVideo`` carrying compressed video frames.

Both the standard ROS 2 type names and their DDS-mangled variants (e.g.
``sensor_msgs::msg::dds_::Image_``) are recognized.

**Generic OMG IDL image types**

* ``RawImage`` for raw pixel buffers.
* ``CompressedImage`` for compressed image frames.
* ``CompressedVideo`` for compressed video frames.

These bare type names are matched regardless of which IDL module wraps them, so they work with any
toolchain that publishes image data using those standard OMG IDL type definitions.

Only topics with a recognized image schema appear in the topic selection lists. Topics that do not match
any supported schema are excluded automatically.

.. _image_pane_encodings:

Supported Encodings
===================

Within each schema family the pane decodes the following payloads:

**Raw pixel buffers** (``sensor_msgs/msg/Image`` and ``RawImage``)

The ``encoding`` field of the sample must be one of:

* ``rgb8`` — 8-bit RGB.
* ``bgr8`` — 8-bit BGR (channels swapped on decode).
* ``rgba8`` — 8-bit RGBA.
* ``bgra8`` — 8-bit BGRA (channels swapped on decode).
* ``mono8`` — 8-bit grayscale.
* ``8uc1`` — single-channel 8-bit (treated as grayscale).

Encoding matching is case-insensitive. Any other value (for example ``yuv422``, ``bayer_*``, ``16UC1``,
``32FC1``) is rejected with a *"Unsupported raw encoding"* error. The maximum supported image dimension
is 16384 × 16384 pixels.

**Compressed images and compressed video**
(``sensor_msgs/msg/CompressedImage``, ``CompressedImage``,
``sensor_msgs/msg/CompressedVideo``, ``CompressedVideo``)

Both compressed schemas are decoded the same way: every sample must be a self-contained frame whose
payload is one of:

* JPEG.
* PNG.

The decoder reads the ``format`` field as a hint and otherwise auto-detects from the payload header.
Streaming video codecs such as H.264 and H.265 are **not supported yet**: a sample carrying such a
payload arrives but cannot be decoded, and the pane displays a *"Unsupported video format"* error.

.. _image_pane_creating:

Opening an Image Pane
=====================

There are several ways to open a new Image Pane:

* Right-click a topic in the :ref:`topics_panel`, the :ref:`logical_panel`, or the domain graph and choose
  **Open image view**. This option is only visible and enabled for topics with a recognized image schema.

* Use the :ref:`right_pane_config` sidebar. A **Image View** button is present in the configuration panel
  of any existing pane type, letting you replace the current pane with a new Image Pane. A domain and topic
  selection wizard appears before the pane is created.

* Click the three-dots button in the header of any existing pane to open the split menu, then choose
  **Split right** or **Split down** and select **Image View** to open a new Image Pane alongside the
  current one.

.. _image_pane_display:

Display and Status
==================

The content area of the pane shows one of the following states at any given time:

* **Live frame** shows the most recently decoded image, scaled to fit the pane while preserving the
  original aspect ratio.
* **Waiting for frames** appears when the pane is active and subscribed but no frame has arrived yet.
* **Stream paused** appears when the subscription has been stopped manually.
* **Decode error** shows a dark overlay with a red warning and the error message when a frame arrives but
  cannot be decoded.

A metadata strip at the bottom of the content area becomes visible once at least one frame has been
received. It shows the frame resolution (width × height), the encoding string, and a running count of
total frames received.

The encoding string reflects what the decoder reported for the current frame:

* For raw frames it is the value of the sample's ``encoding`` field (for example ``rgb8``).
* For compressed image and compressed video frames it is the value of the sample's ``format`` field
  (typically ``jpeg`` or ``png``). When the publisher leaves ``format`` empty, the strip falls back to
  ``compressed`` for compressed images and ``video-frame`` for compressed video.

.. _image_pane_controls:

Pane Header Controls
====================

* The header shows the topic name and domain number of the active subscription.
* The play/pause button (|play| / |pause|) starts and stops the live frame stream without closing the pane.
* The expand button maximizes the pane to fill the full workspace. Clicking it again restores the previous
  layout.
* The |gear| button opens the :ref:`right_pane_config` sidebar for this pane.
* The three-dots button opens the split menu to open a new pane to the right or below the current one.
* The |cross| button stops the subscription and removes the pane.

.. _image_pane_config:

Right-Side Configuration Panel
===============================

Opening the :ref:`right_pane_config` sidebar for an Image Pane shows the following sections:

**Topic**

Read-only labels showing the current topic name and domain number.

**Change Topic**

* **Domain** selects a different monitored domain. Changing the domain refreshes the topic list.
* **Topic** lists only the image-compatible topics discovered on the selected domain. If the domain has no
  compatible topics, a notice is shown in place of the list.
* **Apply & Reload** stops the current stream, switches to the new topic, and restarts the subscription
  immediately. This button is enabled only when both a domain and a topic are selected.

**Playback**

A toggle labelled **Active (receiving frames)** starts or stops the live frame stream. This is equivalent
to the play/pause button in the pane header.

**Status**

A read-only indicator showing the current state of the pane: **Streaming**, **Waiting for frames**,
**Paused**, or **Error**.

**Last Error**

Visible only when a decode error has occurred. Shows the error message returned by the decoder.

**Frame Info**

Visible once at least one frame has been received. Shows three read-only fields: the frame resolution
(width × height), the encoding, and the total number of frames received since the subscription started.

**Panel Actions**

* **Split right** and **Split down** each expand a submenu to open a Statistics Chart, Topic Chart, Spy
  Topic View, Topic Type View (IDL), or Image View alongside the current pane.
