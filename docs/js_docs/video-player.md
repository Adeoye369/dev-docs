# Video Player Documentation

## Getting the Basics Down


```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Video Player </title>
    <link rel="stylesheet" href="style.css">
</head>
<body>

    <h1>video header</h1>

    
    <div class="video-container">
        <video src="assets/video.mp4" control ></video>
    </div>


</body>
</html>
```

```css

*, *::before, *::after{
    box-sizing: border-box;
}

body{
    margin: 0;
    background-color: #202020;
    color: beige;
    font-family: sans-serif;
}

body{
     /* basic flex settings for child components */
    display: flex;
    justify-content: center;
    flex-direction: column;


    /* Specific generic setting for whole body */
    margin-inline: auto;
    width: 90%;
    max-width: 1000px;
    



}

video{ width: 100%; }


```


## Setting up play and pause button

### Preparing for hover on video container

```html
 <div class="video-container">
            <!-- Handles All controls -->
            <div class="video-controls-container">
    
                <div class="timeline-container"></div>
    
                <div class="controls-container">
    
                    <button class="play-pause-btn">Play</button>
    
                </div>
            </div>
            <video src="assets/videos/video_1.mp4" ></video>
        </div>
```

```css
...
.video-controls-container{
    position: absolute;
    right: 0;
    left: 0;
    bottom: 0;
    color: white;
    z-index: 100;
    opacity: 0;
    transition: opacity 500ms ease-in-out;
}

/* When over video-container, display video controls */
.video-container:hover .video-controls-container{
    opacity: 1;
}
```
<figure markdown='span'>
    ![alt text](img/css-hover-video.gif)
</figure>

## Play Pause Setup

You can use the play / pause button. You can also use the **"Spacebar"**, **"K"** keyboard and click on the video element itself to play and pause

```html
 <div class="video-container paused" >
            <!-- Handles All controls -->
    <div class="video-controls-container">

        <div class="timeline-container"></div>
    
        <div class="controls">
    
            <button class="play-pause-btn">
                    <svg class="play-icon"  viewBox="0 0 24 24">
                        <path d="M8,5.14V19.14L19,12.14L8,5.14Z" fill="currentColor"/>
                    </svg>
      
                    <img class="pause-icon" src="./assets/imgs/pause.svg" alt="Pause icon" >
                </button>
                   
    
            </div>
        </div>
        <video id="video" src="assets/videos/video_1.mp4" ></video>
    </div>
```

```css

...

/* Add black gradient for ease visibility of control */
.video-controls-container::before {
    content: "";
    position: absolute; bottom: 0;
    background: linear-gradient(to top, rgba(0,0,0,1), transparent);
    width: 100%; aspect-ratio: 6 / 1;
    z-index: -1;
    pointer-events: none;
}

/* When over video-container, display video controls */
.video-container.paused .video-controls-container,
.video-container:focus-within .video-controls-container,    
.video-container:hover .video-controls-container{
    opacity: 1;
}

.video-controls-container .controls{
    display: flex;
    gap: .5rem;
    padding: .25rem;
    align-items: center;
}


.video-controls-container .controls button{
    background: none;
    border:none; color:inherit;
    padding: 0;
    width: 30px; height: 30px;
    font-size: 1.1rem;
    cursor: pointer;
    opacity: 0.75; transition: opacity 100ms ease-in-out;
}

.video-controls-container .controls button:hover{
    opacity: 1;
}

/* When PAUSED, Show the Play icon and hide the Pause Icon */
.video-container.paused .pause-icon{
 display: none;
}

/* When PLAYING (not PAUSED) hide the Play icon and show the Pause Icon */
.video-container:not(.paused) .play-icon{
    display: none;
   }

```

![alt text](img/video-play-pause@scale400.gif)



## Fullscreen, Theater mode and Mini-player 

```html
<button class="mini-player-btn">
    <svg viewBox="0 0 24 24">
        <path fill="currentColor" d="M21 3H3c-1.1 0-2 .9-2 2v14c0 1.1.9 2 2 2h18c1.1 0 2-.9 2-2V5c0-1.1-.9-2-2-2zm0 16H3V5h18v14zm-10-7h9v6h-9z"/>
    </svg>
</button>

<button class="theater-mode-btn">
    <!-- Theater mode button -->
    <svg class="tall" viewBox="0 0 24 24">
        <path fill="currentColor" d="M19 6H5c-1.1 0-2 .9-2 2v8c0 1.1.9 2 2 2h14c1.1 0 2-.9 2-2V8c0-1.1-.9-2-2-2zm0 10H5V8h14v8z"/>
    </svg>
    
    <svg class="wide" viewBox="0 0 24 24">
        <path fill="currentColor" d="M19 7H5c-1.1 0-2 .9-2 2v6c0 1.1.9 2 2 2h14c1.1 0 2-.9 2-2V9c0-1.1-.9-2-2-2zm0 8H5V9h14v6z"/>
    </svg>
</button>

<button class="fullscreen-mode-btn">
    <!-- Full screen button -->
    <svg class="open" viewBox="0 0 24 24">
        <path fill="currentColor" d="M7 14H5v5h5v-2H7v-3zm-2-4h2V7h3V5H5v5zm12 7h-3v2h5v-5h-2v3zM14
        5v2h3v3h2V5h-5z"/>
        </svg>

    <svg class="close" viewBox="0 0 24 24">
    <path fill="currentColor" d="M5 16h3v3h2v-5H5v2zm3-8H5v2h5V5H8v3zm6
    11h2v-3h3v-2h-5v5zm2-11V5h-2v5h5V8h-3z"/>
    </svg>
</button>
    
```

```js
const playPauseBtn      = document.querySelector(".play-pause-btn")
const minPlayerBtn      = document.querySelector(".mini-player-btn")
const theaterBtn      = document.querySelector(".theater-mode-btn")
const fullScreenBtn      = document.querySelector(".fullscreen-mode-btn")
const video               = document.querySelector("video")
const videoContainer      = document.querySelector(".video-container")
const vidConClist       = videoContainer.classList;

///... Play / Pause code ...
/**
 *============== View Modes function ======================= **
 */
theaterBtn.addEventListener('click', toggleTheaterMode)
fullScreenBtn.addEventListener('click', toggleFullScreenMode)
minPlayerBtn.addEventListener('click', toggleMiniPlayerMode)

function toggleTheaterMode(){
    vidConClist.toggle("theater")
}

function toggleFullScreenMode(){

    // Removes theater if present
    if(document.fullscreenElement == null){
        // make full screen request
        videoContainer.requestFullscreen()

        // hide theater button
        document.querySelector('.theater-mode-btn').style.display='none';
    }else{
        // Exit fullscreen 
        document.exitFullscreen()

        // show theater button
        document.querySelector('.theater-mode-btn').style.display='block';
       }
}

function toggleMiniPlayerMode(){
    if( !vidConClist.contains('mini-player')){
        video.requestPictureInPicture()
    }else
         document.exitPictureInPicture()
}

document.addEventListener('fullscreenchange',()=>{
    vidConclist.toggle('fullscreen', document.fullscreenElement)
})

document.addEventListener('enterpictureinpicture', ()=>vidConClist.add('mini-player' ))
document.addEventListener('leavepictureinpicture', ()=>vidConClist.remove('mini-player' ))

// Keyboard listener
document.addEventListener('keydown',(e)=>{
    const tagName = document.activeElement.tagName.toLowerCase()
    if(tagName === "input") return

    switch(e.key.toLowerCase()){
        case  " " :
            if(tagName === "button") return
        case  "k" :
            togglePlay()
            break
        case "f":
            toggleFullScreenMode()
            break
        case "t":
            toggleTheaterMode()
            break
        case "i":
            toggleMiniPlayerMode()
            break
        default:
            console.log("Invalid Key Button")
    
    }
})
```
<figure markdown='span'>
![alt text](img/video-view-mode@540.gif)
<figcaption>Fullscreen, theater and pictureInPicture mode</figcaption>
</figure>

## Volume control Setup

```html
   <!-- Volume Container holds all the button type -->
                     <div class="volume-container">
                        <button class="mute-btn">
                            <svg class="volume-high-icon" viewBox="0 0 24 24">
                                <path fill="currentColor" d="M14, 3.23V5.29C16.89,6.15 19,8.83 19, 12C19,15.17 16.89,17.84 14,18.7V20.77C18,19.86 21,16.28 21,12C21,7.72 18,4.14 14,3.23M16.5,12C16.5,10.23 15.5,8.71 14,7.97V16C15.5,15.29 16.5,13.76 16.5,12M3,9V15H7L12, 20V4L7,9H3Z" />
                                </svg>
                                
                                <svg class="volume-low-icon" viewBox="0 0 24 24">
                                <path fill="currentColor" d="M5, 9V15H9L14, 20V4L9,9M18.5,12C18.5,10.23 17.5,8.71 16,7.97V16C17.5,15.29 18.5,13.76 18.5,12Z" />
                                </svg>
                                
                                <svg class="volume-muted-icon" viewBox="0 0 24 24">
                                <path fill="currentColor" d="M12,4L9.91,6.09L12,8.18M4.27,3L3,4.27L7.73,9H3V15H7L12,20V13.27L16.25,17.53C15.58,18.04 14.83,18.46 14,18.7V20.77C15.38,20.45 16.63,19.82 17.68,18.96L19.73,21L21, 19.73L12, 10.73M19, 12C19,12.94 18.8,13.82 18.46, 14.64L19.97,16.15C20.62,14.91 21, 13.5 21,12C21,7.72 18,4.14 14,3.23V5.29C16.89,6.15 19,8.83 19,12M16.5,12C16.5,10.23 15.5,8.71 14,7.97V10.18L16.45,12.63C16.5,12.43 16.5,12.21 16.5,12Z" />
                                </svg>
                        </button>

                        <input class="volume-slider" type="range" min="0" max="1" step="any" value="0">
                     </div> <!--End volume div  -->
                    
```

```css
.volume-high-icon, .volume-low-icon, .volume-muted-icon{
    display: none;
}

.video-container[data-volume-level="high"] .volume-high-icon{
display: block;
}
.video-container[data-volume-level="low"] .volume-low-icon{
display: block;
}
.video-container[data-volume-level="muted"] .volume-muted-icon{
display: block;
}

.volume-container{
    display: flex;
    align-items: center;
}

.volume-slider{
    width: 0;
    transform-origin: left ;
    transform: scaleX(0);
    transition: width 300ms ease-in-out, transform 300ms ease-in-out;
}

.volume-container:hover .volume-slider,
.volume-slider:focus-within{
    width: 100px;
    transform: scaleX(1);
    
}
```

```js
////// Volume relate ================================================
function css(css_query){return document.querySelector(css_query)}
...
const volumeSlider        = css(".volume-slider")
const mutedBtn            = css(".mute-btn")
...

// Toggle Muted
function toggleMute(){
    video.muted = !video.muted
}
mutedBtn.addEventListener('click', toggleMute)

// volume value update
volumeSlider.addEventListener('input', e => {
    video.volume = e.target.value
    video.muted = e.target.value === 0 // mute if the value is zero
})

// onVolume change

video.addEventListener('volumechange', ()=>{
    volumeSlider.value =  video.volume
    let volumeLevel

    if(video.muted || video.volume === 0){
        volumeSlider.value = 0
        volumeLevel = "muted"
    }else if(video.volume >= .5){
        volumeLevel = "high"
    }else{
        volumeLevel = "low"
    }
    videoContainer.dataset.volumeLevel = volumeLevel
})

```
