import sys
from pylab import *
import MySQLdb
from datetime import datetime
import numpy as np

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

temp = []
time = []

for record in result:
    temp.append(float(record[0]))
    time.append(record[1])

xs = matplotlib.dates.date2num(time)
hfmt = matplotlib.dates.DateFormatter('%Y-%m-%d\n%H:%M:%S')
fig = figure()
ax = fig.add_subplot(1,1,1)
ax.xaxis.set_major_formatter(hfmt)
ax.plot(xs, temp, linewidth=2)
ax.scatter(xs, temp)
ax.set_title(title)
setp(ax.get_xticklabels(), size=8)
setp(ax.get_yticklabels(), size=8)
grid(True)

F = gcf()
DPI = F.get_dpi()
F.savefig('plot.png',dpi = (1000))
