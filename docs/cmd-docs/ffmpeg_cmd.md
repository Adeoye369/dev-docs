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
