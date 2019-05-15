echo CLIENT RECIVER
echo PROGRAM RUNNING WITH PARAMETRS: "$@"
address=192.168.1.7
port=5000
local=127.0.0.1
argument1="$1"
echo
echo
case $argument1 in
	-l|--local)
	echo LOCAL RECIVER IP: "$local", PORT: "$port"
	gst-launch-1.0 udpsrc address=$local port=$port caps="application/x-rtp" ! queue ! rtpmpadepay ! mpegaudioparse ! mpg123audiodec ! audioconvert ! audioresample ! autoaudiosink
	;;
	-s|--server)
	echo PI RECIVER IP: "$address", PORT: "$port"
	gst-launch-1.0 udpsrc address=$address port=$port caps="application/x-rtp" ! queue ! rtpmpadepay ! mpegaudioparse ! mpg123audiodec ! audioconvert ! audioresample ! autoaudiosink
	;;
esac


