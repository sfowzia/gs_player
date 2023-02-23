<a href="url"><img src="https://github.com/sfowzia1001/gs_player/blob/main/media/gstreamer_player.jpg" align="justify" height="500" width="500" ></a>

# Gstreamer Player

This program uses the GStreamer library to play a video file from a path specified in the command-line when executing the program. The program creates a GStreamer pipeline using the playbin element, which automatically selects the appropriate decoding and playback elements based on the file type. The pipeline is started with the gst_element_set_state function, and the program waits for the playback to finish or for an error to occur using the gst_bus_timed_pop_filtered function. If an error occurs, the program parses the error message using the gst_message_parse_error function and outputs the error message and debugging information to the console.

# Instructions

- Clone this repository in a desired location with `git clone https://github.com/sfowzia1001/gs_player`
- Change directory into gs_player with `cd gs_player`
- Make a build directory with `mkdir build && cd build`
- Compile with CMake with `cmake ..`
- Make the executable with `make`
- Run the example with `./gs_player pixar_intro_sample.mp4`

If you have any questions, please feel free to contact me:
sfowzia00@gmail.com
