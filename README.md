Audio Pi Streamming 

Build: [![Build Status](https://travis-ci.com/szymonjanas/AudioPiStreamming.svg?token=7zqskTqUVeesY8JKkTYf&branch=master)](https://travis-ci.com/szymonjanas/AudioPiStreamming)

### Project in progress
## _Multimedia management system with sound streaming_ 

**Idea:** User can connect from computer (with Linux) or smartphone (with Android) using application to base computer (headquarters - RaspberryPi) via Wi-Fi and give a request to do something. 

**Functions:**
- local music playing
- wireless music playing: 
  - streaming live from system 
  - streaming live from file
- control devices:
  - switching hdmi wires
  - switching power strip
- features in prospective:
  - control home multimedia system (amplifers, home ciniema theater etc)
  - streaming video (cast)
  - add better sound card in headquarters device
  - control: lights, temperaure, blinds
  - analysis data from sensors: temperature, humidity, light, air quality,
  
**Goals:**
- reducing the amount of cable
- mobility in media playback
- easy multimedia playback

**Technology:**
- <img src="https://github.com/szymonjanas/AudioPiStreamming/blob/master/githubgraphics/gst.png" /> 
  .. GStreamer >1.0 for multimedia playing and udp streaming  
- <img src="https://github.com/szymonjanas/AudioPiStreamming/blob/master/githubgraphics/qt.png" width="25" height="25" /> 
   .............. Qt5 for GUI
- <img src="https://github.com/szymonjanas/AudioPiStreamming/blob/master/githubgraphics/zmq.jpg" width="40" height="20" /> 
   .......... ZeroMQ for tcp communication between devices

**Devices used in tests:**
- Headquarter: Raspberry Pi 3 Model B with Raspbian <img src="https://github.com/szymonjanas/AudioPiStreamming/blob/master/githubgraphics/RPi.png" width="20" height="25" />
- Client: Acer V5 AMD with Ubuntu 19

### Scheme of first version which I strive for:
<img src="https://github.com/szymonjanas/AudioPiStreamming/blob/master/githubgraphics/diagram.png" width="400" height="400" />

**Project Description in Polish:**
[Overleaf](https://www.overleaf.com/read/wfdrnmkphczn)
<img src="https://github.com/szymonjanas/AudioPiStreamming/blob/master/githubgraphics/ov.png" width="35" height="40" />

**Issues, features and help:**
- If you see somthing that should be fixed or improved feel free to leave issue.
- If you have idea of new feature feel free to leave issue or write e-mail to me.
- If you are interested to be a part of this project please write e-mail to me.
