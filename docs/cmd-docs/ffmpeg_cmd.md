# Getting Started with ffmpeg

## Basic Command

### converting one video from one format to another
  
  the basic format is :
  `ffmpeg -i <input_video.mkv> <ouput_video.mp4>`

  ```bash
  ffmpeg -i adv02_Blending.mkv NEW_adv02_Blend.mp4
  ```

### Inverting your video example

```bash
ffmpeg -i adv02_Blend.mp4 -vf negate N_NEG_adv02_Blend.mp4
```

### Overlay one video on top another

Overlay `input_vid2.mkv` on top of `input_vid1.mp4` and output the combined video as `output_vid1.mp4` 

```bash
ffmpeg -i input_vid1.mp4 -i input_vid2.mkv -filter_complex "[0.v][1.1]overlay" output_vid1.mp4
```

NOTE: am not sure what happened to audio of `input_vid2.mp4` it seems to have lost. Not sure the use of this though, I believe it might be useful at some point.

### convert quality of an AVI to Loss-less Lower format

- This takes is the input `.avi` and out any other format `.mp4, .mkv` etc.
- the `-q` filter is the lossless quantity so to say. Think of it like position like, `1` is the first postion, that is the highest quality will as it goes down, the quality reduces, so `100` is a very low file size lossless quality, say last position.  

We can have many other inbetween values, `8, 19, 40 ...` test what works for you.

```bash
ffmpeg -i .\0001-0120.avi -q 49 out_001-0120.mkv // -q for .avi
ffmpeg -i input_vid1.mp4 -crf 100 LOW_out_vid1.mp4 // -crf for .mp4
```

## Size reduce for GIF 

```bash
# Change fps
ffmpeg -i input.gif -vf "fps=10" output_reduced_fps.gif

# scale down
ffmpeg -i input.gif -vf "scale=320:-1" output_scaled.gif 

# Reducing Color information
ffmpeg -i input.gif -vf "palettegen=max_colors=64" palette.png
ffmpeg -i input.gif -i palette.png -filter_complex "paletteuse" output_reduced_colors.gif

```

## Split your video within timestamp

```bash
# split single video
ffmpeg -i ./video_1.mp4 -ss 00:00:00 -to 00:00:05  video_@5sec.mp4 

# splitting multiple
ffmpeg -i ./video_1.mp4 
  -ss 00:00:00 -to 00:00:05  video_1@0.00-5sec.mp4 
  -ss 00:01:00 -to 00:01:12  video_2@1.00-12sec.mp4 
  -ss 00:03:11 -to 00:03:25  video_3@3.11-14sec.mp4 
```

## Getting Image frames from video

The basic way to get frames from your video

```bash
ffmpeg -i ./video_1.mp4 vid_frame%d.png #output: vid_frame1, vid_frame2 ...
ffmpeg -i ./video_1.mp4 vid_frame%3d.png #output: vid_frame001, vid_frame002 ...

# output frames within a time range
ffmpeg -i ./video_1.mp4 -ss 00:00:00 -to 00:00:02  vid_frame%d.png 

# output within time range and scale to 100 
# NOTE scale = 100:-1 means maintain same aspect ratio for height
#      scale = 640:480 means export video in dimension specified
ffmpeg -i ./video_1.mp4 -ss 00:00:00 -to 00:00:02 -vf "scale=100:-1" vid_frame%d.png
```

### Exporting your video images at every secs

the `-vf fps=1` set it to only capture the first frame of every second(24 or 30 frames depending on frame rate)

```bash
ffmpeg -i .\video_2.mp4 -vf fps=1 vid%3d.png 
```

### Extracting Single frame at a specific timestamp

```bash
ffmpeg -ss 00:02:45 -i ./video_1.mp4 -frames:v 1 output_frame.jpg
```

- `-ss 00:02:45` : Seeks to the 5-second mark in the video. The format can be HH:MM:SS or seconds.
- `-frames:v 1` : Specifies that only one video frame should be extracted.
- `output_frame.jpg` : The name of the output image file.

!!! Note
    Placing `-ss` before `-i` enables faster seeking, as FFmpeg will start processing from that point, rather than decoding the entire video up to the timestamp.
