# SmartCoop: An Automated Chicken Coop
## Year 3 Project: Jason Keane

### Proposal
There are many things to think about when keeping chickens. You have to get up with the sunrise to let them out and put them in at sunset. You have to give them water and feed them every day. I am trying to lessen the workload with automation.

The SmartCoop is based on an Intel Galileo Gen 2 running Yocto Linux. The sunrise and sunset times are fetched every day from an online API these times are then used to open and close the door automatically. The inside temperature, inside humidity, and outside temperature are measured every five minutes, these values are then uploaded to a MySQL database.  A heat lamp is turned on if the coop gets too cold and a fan is turned on if it gets too hot.
There is an automatic watering system that always keeps the chickens supply topped up.
All of the communication with the user is done through a website run on the galileo using nodeJS. The user can open and close the door, turn a light on or off, watch the stream from a camera in the coop, and feed the chickens from here.
Finally, there is a separate web app run using nodeJS where the user can graph a specific range of environment measurements. This is achieved using Python with Matplotlib.



### Notes
##### Camera:
The web page for the camera is run on a server created by mjpg-streamer at galileoIP:8080/?action=stream. This is displayed using an "img" tag on the web page.

##### Graphing App:
The graphs are made with python and matplotlib. The python script is run by nodeJS the user can specify the dates to graph from a web page.
