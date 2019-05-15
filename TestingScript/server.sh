echo AUDIO TEST SRC SERVER
echo ACCESS IP:127.0.0.1 PORT:5000
echo "Skrypt uruchomiono z parametrami: $@"

echo
echo "Argument 1: $1"
argument="$1"
localHost="127.0.0.1"
localPort="5000"

raspHost="192.168.1.7"
raspPort="5000"

echo RASPBERRY PI ACCESS:
echo HOST: "$raspHost" PORT: "$raspPort"
echo
echo

case $argument in
	-t|--test)
	echo "TEST START"
	gst-launch-1.0 audiotestsrc ! audioconvert ! lamemp3enc ! rtpmpapay ! udpsink host="$localHost" port="$localPort"
	;;
	-r|--rasptest)
	echo "STREAMING TEST TO RASPBERRY"
	gst-launch-1.0 audiotestsrc ! audioconvert ! lamemp3enc ! rtpmpapay ! udpsink host="$raspHost" port="$raspPort"
	;;
	-s|--stream)
	echo "MUSIC STREAMING START"
	gst-launch-1.0 filesrc location="../PigeonJohn-TheBomb.mp3" ! mpegaudioparse ! rtpmpapay ! udpsink host="$localHost" port="$localPort"
	;;
	-p|--play)
	echo "MUSIC PLAYING START"
	gst-launch-1.0 filesrc location="../PigeonJohn-TheBomb.mp3" ! mpegaudioparse ! mpg123audiodec ! audioconvert ! autoaudiosink
	;;
	-n)
	echo "NEW PIPELINE"
	gst-launch-1.0 filesrc location="../PigeonJohn-TheBomb.mp3" ! mpegaudioparse ! rtpmpapay ! udpsink host=192.168.1.7 port=5000
	;;

esac

