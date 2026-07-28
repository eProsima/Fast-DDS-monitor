.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _image_pane:

################
Image Pane |Pro|
################

The *Image Pane* is a dockable panel that renders live image frames published on a DDS topic.
When you subscribe to a compatible topic, the pane detects the image schema automatically, decodes each
incoming sample, and displays the resulting frame inside the monitor workspace. The decoded image scales to
fit the pane while preserving the original aspect ratio.

.. thumbnail:: /rst/figures/screenshots/image_pro.png
    :align: center

.. _image_pane_schemas:

Supported Image Schemas
=======================

The pane detects the topic type automatically from its type name and recognizes two families of
schemas: the ROS 2 ``sensor_msgs`` image types and the *eProsima Fast DDS* image types. Type-name
matching is case-insensitive, and ROS-style ``/`` separators are treated the same as IDL ``::``
separators.

.. _image_pane_schemas_ros:

ROS 2 sensor_msgs types
-----------------------

The `ROS 2 sensor_msgs <https://github.com/ros2/common_interfaces/tree/rolling/sensor_msgs/msg>`__
image messages, matched on their fully-qualified name:

* `sensor_msgs/msg/Image <https://github.com/ros2/common_interfaces/blob/rolling/sensor_msgs/msg/Image.msg>`__
  carrying a raw pixel buffer.
* `sensor_msgs/msg/CompressedImage <https://github.com/ros2/common_interfaces/blob/rolling/sensor_msgs/msg/CompressedImage.msg>`__
  carrying a compressed (JPEG or PNG) frame.

Both the plain ROS 2 type names and their DDS-mangled variants (the ``dds_`` submodule and trailing
``_``, e.g. ``sensor_msgs::msg::dds_::Image_`` and ``sensor_msgs::msg::dds_::CompressedImage_``) are
recognized.

.. note::

    ROS 2 message types are authored in the ``.msg`` format (linked above) and converted to IDL
    automatically at build time, which is what defines the DDS type placed on the wire. The ``.msg``
    file is therefore the authoritative definition. The *eProsima Fast DDS* image types below have no
    ``.msg`` counterpart and are defined directly in IDL.

.. _image_pane_schemas_fastdds:

eProsima Fast DDS image types
-----------------------------

The image types owned by *eProsima* under the ``eprosima::fastdds::msg`` module, plus the equivalent
bare (module-independent) type names. These are defined using the `OMG IDL
<https://www.omg.org/spec/IDL/>`__ type-definition language:

* ``Image`` (i.e. ``eprosima::fastdds::msg::Image``), or the generic name ``RawImage``, for a raw
  pixel buffer.
* ``CompressedImage`` (i.e. ``eprosima::fastdds::msg::CompressedImage``) for a compressed (JPEG or
  PNG) frame.

The bare leaf names ``RawImage``, ``Image``, and ``CompressedImage`` are matched regardless of which
IDL module wraps them, so any toolchain that publishes image data under one of those struct names is
recognized.

The canonical IDL definition of the *eProsima Fast DDS* image types is published in the monitor
repository, in `resources/idl/FastDdsImage.idl
<https://github.com/eProsima/Fast-DDS-monitor/blob/main/resources/idl/FastDdsImage.idl>`__:

.. code-block:: omg-idl

    module eprosima {
    module fastdds {
    module msg {

    struct Image
    {
        string frame_id;
        unsigned long height;
        unsigned long width;
        string encoding;
        uint8 is_bigendian;
        unsigned long step;
        sequence<uint8> data;
    };

    struct CompressedImage
    {
        string frame_id;
        string format;
        sequence<uint8> data;
    };

    }; }; };

Only topics with a recognized image schema appear in the image topic selection list. Topics that do
not match any of the schemas above are excluded automatically, but they can still be rendered by
mapping their fields manually - see :ref:`image_pane_custom_topic`.

.. _image_pane_encodings:

Supported Encodings
===================

The pane decodes the following payloads, depending on whether the schema is a raw or a compressed
image:

**Raw pixel buffers** (``sensor_msgs/msg/Image``, ``eprosima::fastdds::msg::Image``, and ``RawImage``)

The ``encoding`` field of the sample must be one of the following
`ROS 2 image encodings <https://github.com/ros2/common_interfaces/blob/rolling/sensor_msgs/include/sensor_msgs/image_encodings.hpp>`__:

* ``rgb8`` 8-bit RGB.
* ``bgr8`` 8-bit BGR (channels swapped on decode).
* ``rgba8`` 8-bit RGBA.
* ``bgra8`` 8-bit BGRA (channels swapped on decode).
* ``mono8`` 8-bit grayscale.
* ``8uc1`` single-channel 8-bit (treated as grayscale).

Encoding matching is case-insensitive. Any other value (for example ``yuv422``, ``bayer_*``, ``16UC1``,
``32FC1``) is rejected with an *"Unsupported raw encoding"* error. The maximum supported image dimension
is 16384 × 16384 pixels.

**Compressed frames** (``sensor_msgs/msg/CompressedImage``,
``eprosima::fastdds::msg::CompressedImage``, and ``CompressedImage``)

Every sample must be a self-contained frame whose payload is one of:

* JPEG.
* PNG.

The decoder reads the ``format`` field as a hint to select the codec. Both the bare form
(``jpeg``, ``png``) used by the *eProsima Fast DDS* types and the structured ROS
``compressed_image_transport`` grammar (``ORIG_PIXFMT; CODEC compressed [PIXFMT]``, for example
``rgb8; jpeg compressed bgr8``) are understood: the codec token is extracted from the string. When
the ``format`` field is empty or carries no recognized codec, the decoder auto-detects from the
payload header.

.. _image_pane_creating:

Opening an Image Pane
=====================

There are several ways to open a new Image Pane:

* Right-click a topic in the :ref:`topics_panel`, the :ref:`pro_logical_panel`, or the :ref:`domain graph <pro_domain_graph>` and choose
  **Open image view**. This option is only visible and enabled for topics with a recognized image schema.

* Use **Add → Add Image View** in the application menu bar.

* Click the **Image View** button in an empty pane.

* Click the three-dots button in the header of any existing pane to open the split menu, then choose
  **Split right** or **Split down** and select **Image View** to open a new Image Pane alongside the
  current one, or choose **Replace panel** to replace the current pane with an Image Pane.

When creating an Image View from the configuration sidebar, the **NEW IMAGE VIEW** form lists only
image-compatible topics under **IMAGE TOPIC**. When a domain has no compatible topic it shows
*No compatible topics. Map a custom one below.* and offers the :ref:`Custom Image Topic
<image_pane_custom_topic>` flow described next.

.. _image_pane_custom_topic:

Custom Image Topic
==================

Some topics carry image data but do not use a standard image schema - for example, a topic whose type
has a byte-array field but no ``width``, ``height``, or ``encoding`` fields. The *Custom Image Topic*
mapping lets you turn such a topic into an Image View by telling the monitor how to read the image out
of its fields.

To start, in the **NEW IMAGE VIEW** form select the topic under **CONFIGURE A CUSTOM TOPIC** and click
**Configure as image topic**. Only topics that can carry image data (that is, topics whose type has a
byte-array field) are listed; when there are none the form shows *No topics here can carry image data
(need a byte-array field).* The **CONFIGURE IMAGE TOPIC** panel then opens.

**Visualization Mode**

Choose how the payload is interpreted:

* **Raw image** - an uncompressed pixel buffer.
* **Compressed image** - a self-contained JPEG or PNG frame.

**Field Mapping**

Map each required piece of the image to a field of the topic type, or - when the type has no suitable
field - supply a constant with **Use a fixed value**. Nested fields appear as dotted paths (for
example ``header.payload``). Required fields are marked with ``*``.

Each slot's field dropdown lists only fields of a compatible data type, so it offers different options
depending on the slot: the pixel/compressed data slot lists byte-array fields, width, height, and
step list numeric fields, encoding lists string or enum fields, and format lists string fields.

* For **Raw image**: **Pixel data (bytes)** (required), **Width** (required), **Height** (required),
  **Encoding** (required), and **Step / row stride** (optional). Width, height, and step accept a
  fixed integer value; encoding accepts a fixed value from ``rgb8``, ``bgr8``, ``rgba8``, ``bgra8``,
  ``mono8``, ``8uc1`` (see :ref:`image_pane_encodings`). The encoding field may be a string or an enum
  field (its label is used). Step / row stride is optional: when omitted it is computed as
  *width × bytes-per-pixel*; set it only if the rows are padded.
* For **Compressed image**: **Compressed data (bytes)** (required) and **Format** (optional). JPEG and
  PNG carry their own size and format, so no width, height, or encoding mapping is needed.

For example, a raw-image topic whose type names its fields differently - ``cols``, ``rows``,
``color_format``, ``line_size``, and ``pixels`` instead of ``width``, ``height``, ``encoding``,
``step``, and ``data`` - is rendered by mapping **Width** → ``cols``, **Height** → ``rows``,
**Encoding** → ``color_format``, **Step / row stride** → ``line_size``, and **Pixel data (bytes)** →
``pixels``.

**Actions**

* **Save mapping** - validates the mapping against the topic type and stores it. On success the topic
  becomes selectable in the **IMAGE TOPIC** list so you can immediately **Create Image View**.
* **Remove mapping** - shown only when the topic already has a mapping; deletes it.
* **Cancel** - discards the mapping without saving.

If the mapping does not match the topic type (for example, a field of the wrong kind), the panel shows
the validation error in red. Saved mappings are preserved when you :ref:`save and restore a workspace
<workspace>`.

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
* For compressed frames it is the value of the sample's ``format`` field (typically ``jpeg`` or
  ``png``). When the publisher leaves ``format`` empty, the strip falls back to ``compressed``.

.. _image_pane_controls:

Pane Header Controls
====================

* The header shows the topic name and domain number of the active subscription.
* |play| / |pause| - starts and stops the live frame stream without closing the pane.
* |help| - opens a contextual help panel with usage tips and a link to this documentation page.
* |maximize_square| / |minimize_square| - maximizes/ minimizes the pane; click again to restore the previous
  layout.
* |gear| - opens the :ref:`right_pane_config` sidebar for this pane.
* The three-dots button opens the split menu to open a new pane to the right or below.
* |cross| - stops the subscription and removes the pane.

.. _image_pane_config:

Right-Side Configuration Panel
===============================

Opening the :ref:`right_pane_config` sidebar for an Image Pane (via the |gear| button) shows the
following sections:

* **Topic** - read-only labels showing the current topic name and domain.
* **Change Topic** - domain and topic selection; click **Apply & Reload** to switch to the new topic
  and restart the subscription.
* **Playback** - toggle *Active (receiving frames)* to start or stop the frame stream (equivalent to
  the |play| / |pause| header button).
* **Status** - current state: *Streaming*, *Waiting for frames*, *Paused*, or *Error*.
* **Last Error** - visible only when a decode error occurred; shows the decoder error message.
* **Frame Info** - visible once frames arrive; shows resolution, encoding, and frame count.
* **Actions** - **Save Screenshot** saves the current frame as a PNG; **Copy Screenshot** copies it
  to the clipboard.
* **Panel Actions** - split and replace submenus.

See :ref:`right_pane_config` for the full configuration panel reference.
