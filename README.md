# SmartCoop: An Automated Chicken Coop
Year 3 Project: Automated Chicken Coop
Jason Keane

CAMERA:
The web page for the camera is run on a server created by mjpg-streamer at 192.168.41.100:8080/camera.html. The arduino server (on port 80) has a link to this in the nav menu.

For now the following two commands must be run manually for the camera to work:

  modprobe uvcvideo

  /home/root/mjpg-streamer/mjpg-streamer/mjpg_streamer -i "/home/root/mjpg-streamer/mjpg-streamer/input_uvc.so -f 15 -r 640x480" -o "/home/root/mjpg-streamer/mjpg-streamer/output_http.so -w /home/root/mjpg-streamer/mjpg-streamer/www"
