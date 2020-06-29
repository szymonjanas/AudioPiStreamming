Audio Pi Streamming 

Build: [![Build Status](https://travis-ci.com/szymonjanas/AudioPiStreamming.svg?token=7zqskTqUVeesY8JKkTYf&branch=master)](https://travis-ci.com/szymonjanas/AudioPiStreamming)

### Project in progress
## _Multimedia management system with sound streaming_ 

**Idea:** User can connect from computer (with Linux) or smartphone (with Android) using application to base computer (headquarters - RaspberryPi) via Wi-Fi and give a request to do something. 

**Features:**
- local music playing
- wireless music playing: 
  - streaming live from system 
  - streaming live from file
  
**Technology:**
- GStreamer >1.0 for multimedia playing and udp streaming  
- Qt5 for GUI
- ZeroMQ for tcp communication between devices

**Devices used in tests:**
- Headquarter: Raspberry Pi 3B+
- Client: Ubuntu 19
