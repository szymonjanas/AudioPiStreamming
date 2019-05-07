echo CLIENT TEST
echo ACCESS PORT=5000
gst-launch-1.0 udpsrc address=192.168.1.7 port=5000 caps="application/x-rtp" ! queue ! rtpmpadepay ! mpegaudioparse ! mpg123audiodec ! audioconvert ! audioresample ! autoaudiosink

