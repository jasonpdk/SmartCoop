# SmartCoop: An Automated Chicken Coop
## Year 3 Project: Jason Keane

### Proposal
There are many things to think about when keeping chickens. You have to get up with the sunrise to let them out and put them in at sunset. You have to give them water and feed them every day. I am trying to lessen the workload with automation.

The Smart Coop fetches the sunrise and sunset times at the user's location each day from an online API. The automatic door will then open and close at these times. There is an automatic watering system that uses a water level sensor and a solenoid valve to ensure that the chickens are never short of water. There is an automatic feeder that drops the correct amount of feed every day. The temperature of the coop is continually monitored and if it dips below zero degrees an infra red heat lamp will turn on. There is also a camera inside the coop so the user can check the chickens from anywhere. All communication with the user is done through a website which is developed so that all of the automatic functions can be operated manually. All of these features are implemented using the Intel Galileo Gen 2.


### Notes
##### Camera:
The web page for the camera is run on a server created by mjpg-streamer at galileoIP:8080/?action=stream. This is displayed using an "img" tag on the web page.

##### Graphing App:
The graphs are made with python and matplotlib. The python script is run by nodeJS the user can specify the dates to graph from a web page.
