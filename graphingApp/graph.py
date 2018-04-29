import sys
from pylab import *
import MySQLdb
from datetime import datetime

db = MySQLdb.connect('localhost', 'root', 'password', 'SmartCoop');

cursor = db.cursor();
title = ""

if sys.argv[1] == "num":
    if sys.argv[2] == "temp":
        query = 'SELECT temperature,timeLogged FROM readings ORDER BY id DESC LIMIT ' + sys.argv[3]
        title = "Outside Temperature VS Time"
    elif sys.argv[2] == "itemp":
        query = 'SELECT insideTemperature,timeLogged FROM readings ORDER BY id DESC LIMIT ' + sys.argv[3]
        title = "Inside Temperature VS Time"
    elif sys.argv[2] == "hum":
        query = 'SELECT humidity,timeLogged FROM readings ORDER BY id DESC LIMIT ' + sys.argv[3]
        title = "Humidity VS Time"
elif sys.argv[1] == "dates":
    if sys.argv[2] == "temp":
        query = 'SELECT temperature,timeLogged FROM readings WHERE (timeLogged BETWEEN \'' + sys.argv[3] + ' 00:00:00\' AND \' ' + sys.argv[4] + ' 00:00:00\');'
        title = "Outside Temperature from " + sys.argv[3] + " to " + sys.argv[4]
    elif sys.argv[2] == "itemp":
        query = 'SELECT insideTemperature,timeLogged FROM readings WHERE (timeLogged BETWEEN \'' + sys.argv[3] + ' 00:00:00\' AND \' ' + sys.argv[4] + ' 00:00:00\');'
        title = "Inside Temperature from " + sys.argv[3] + " to " + sys.argv[4]
    elif sys.argv[2] == "hum":
        query = 'SELECT humidity,timeLogged FROM readings WHERE (timeLogged BETWEEN \'' + sys.argv[3] + ' 00:00:00\' AND \' ' + sys.argv[4] + ' 00:00:00\');'
        title = "Humidity from " + sys.argv[3] + " to " + sys.argv[4]

cursor.execute(query);
result = cursor.fetchall()

## if there are no entries, quit ##
if len(result) < 1:
    print(1)
    sys.exit()
else:
    print(0)

measurement = []
time = []

# loop through all of the results, the first element is the value this is added into the temp Array
# the second element is the time that value was entered this is added into the time Array
for record in result:
    measurement.append(float(record[0]))
    time.append(record[1])

# Plot and Format
xs = matplotlib.dates.date2num(time)
dateFormat = matplotlib.dates.DateFormatter('%Y-%m-%d\n%H:%M:%S') # set the date format
fig = figure()
ax = fig.add_subplot(1,1,1)
ax.xaxis.set_major_formatter(dateFormat)
ax.plot(xs, measurement, linewidth=2)
ax.scatter(xs, measurement, s=15)
ax.set_title(title)
setp(ax.get_xticklabels(), size=6)
setp(ax.get_yticklabels(), size=6)
grid(True)

# save the plot to an image
F = gcf()
F.savefig('plot.png',dpi = (1000))
