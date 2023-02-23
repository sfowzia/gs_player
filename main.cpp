#include <iostream>
#include <string>
#include <gst/gst.h>

int main(int argc, char *argv[]) {
  GstElement *pipeline;
  GstBus *bus;
  GstMessage *msg;
  GstStateChangeReturn ret;
  std::string file_path;

  // Check for the video file path argument.
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <video-file-path>" << std::endl;
    return -1;
  } else {
    file_path = argv[1];
  }

  // Initialize GStreamer.
  gst_init(&argc, &argv);

  // Create the pipeline.
  pipeline = gst_parse_launch(("playbin uri=file://" + file_path).c_str(), NULL);

  // Start playing.
  ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
  if (ret == GST_STATE_CHANGE_FAILURE) {
    std::cerr << "Failed to start playing " << file_path << std::endl;
    return -1;
  }

  // Wait for the playback to finish or for an error to occur.
  bus = gst_element_get_bus(pipeline);
  msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, static_cast<GstMessageType>(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));

  // Parse the message and handle any errors.
  if (msg != NULL) {
    GError *err;
    gchar *debug_info;

    switch (GST_MESSAGE_TYPE(msg)) {
      case GST_MESSAGE_ERROR:
        gst_message_parse_error(msg, &err, &debug_info);
        std::cerr << "Error received from element " << GST_OBJECT_NAME(msg->src) << ": " << err->message << std::endl;
        std::cerr << "Debugging information: " << (debug_info ? debug_info : "none") << std::endl;
        g_clear_error(&err);
        g_free(debug_info);
        break;

      case GST_MESSAGE_EOS:
        std::cout << "End-Of-Stream reached." << std::endl;
        break;

      default:
        std::cerr << "Unexpected message received." << std::endl;
        break;
    }

    gst_message_unref(msg);
  }

  // Free resources.
  gst_object_unref(bus);
  gst_element_set_state(pipeline, GST_STATE_NULL);
  gst_object_unref(pipeline);

  return 0;
}