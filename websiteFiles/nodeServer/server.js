// load the things we need
var express = require('express');
var mysql = require('mysql');
var fs = require('fs');

var app = express();

app.use(express.static(__dirname + '/public'));

var con = mysql.createConnection({
	host: "192.168.41.11",
	user: "root",
	password: "password",
	database: "SmartCoop"
});


con.connect(function(err) {
	if (err) throw err;
	console.log("Connected to MySQL");
});

function readDoorFile() {
	fs.readFile('/home/root/doorStatus.txt', 'utf8', function(err, data) {
		if (err) throw err;
		if (data[0] == 0)
		{
			return "Closed";
		}
		else
		{
			return "Open";
		}
	});
}

function readLightFile() {
	fs.readFile('/home/root/lightStatus.txt', 'utf8', function(err, data) {
		if (err) throw err;
		if (data[0] == 0)
		{
			return "Off";
		}
		else
		{
			return "On";
		}
	});
}
// set the view engine to ejs
app.set('view engine', 'ejs');

var outsideTemp, insideTemp, humidity, doorStatus, lightStatus;
var sql0 = "SELECT * FROM readings ORDER BY id DESC LIMIT 1";
var sunrise, sunset;
var sql1 = "SELECT * FROM times ORDER BY id DESC LIMIT 1";

// make initial queries
con.query(sql0, function (err, result) {
	if (err) throw err;
	outsideTemp = result[0].temperature;
	insideTemp = result[0].insideTemperature;
	humidity = result[0].humidity;
});


con.query(sql1, function (err, result) {
	sunrise = result[0].sunrise;
	sunset = result[0].sunset;
});

// initial status check
fs.readFile('/home/root/doorStatus.txt', 'utf8', function(err, data) {
	if (err) throw err;
	if (data[0] == 0)
	{
		doorStatus = "Closed";
	}
	else
	{
		doorStatus = "Open";
	}
});

fs.readFile('/home/root/lightStatus.txt', 'utf8', function(err, data) {
	if (err) throw err;
	if (data[0] == 0)
	{
		lightStatus = "Off";
	}
	else
	{
		lightStatus = "On";
	}
});

// index page
app.get('/', function(req, res) {

	console.log(req);
	// query the database everytime index is requested
	con.query(sql0, function (err, result) {
		if (err) throw err;
		outsideTemp = result[0].temperature;
		insideTemp = result[0].insideTemperature;
		humidity = result[0].humidity;
	});

	con.query(sql1, function (err, result) {
		sunrise = result[0].sunrise;
		sunset = result[0].sunset;
	});

	// get door status from text file
	fs.readFile('/home/root/doorStatus.txt', 'utf8', function(err, data) {
		if (err) throw err;
		if (data[0] == 0)
		{
			doorStatus = "Closed";
		}
		else
		{
			doorStatus = "Open";
		}
	});

	/*fs.readFile('/home/root/lightStatus.txt', 'utf8', function(err, data) {
		if (err) throw err;
		if (data[0] == 0)
		{
			lightStatus = "Off";
		}
		else
		{
			lightStatus = "On";
		}
	});*/

	var sCTokens = sunset.split(':');
	var sCHour = Number(sCTokens[0])+1;
	var scheduledClosing = "0" + sCHour + ":" + sCTokens[1] + ":" + sCTokens[2];
	var heatLamp = "Off", fan = "Off";
	if (insideTemp <= 1)
	{
		heatLamp =  "On";
		fan = "Off";
	}
	else if (insideTemp > 26)
	{
		heatLamp = "Off";
		fan = "On";
	}
	else
	{
		heatLamp = "Off";
		fan = "Off";
	}

	res.render('pages/index', {
		insideTemp: insideTemp,
		outsideTemp: outsideTemp,
		humidity: humidity,
		sunrise: sunrise,
		sunset: sunset,
		doorStatus: doorStatus,
		scheduledOpening: sunrise,
		scheduledClosing: scheduledClosing,
		lightStatus: lightStatus,
		heatLamp: heatLamp,
		fan: fan
	});
});

// graphs page
app.get ('/graphs', function(req, res) {
	res.render('pages/graphs');
});

// camera page
app.get ('/camera', function(req, res) {
	res.render('pages/camera');
});


app.get('/On', function(req, res) {
	res.send("On");
	lightStatus = "On";
});

app.get('/Off', function(req, res) {
	res.send("Off");
	lightStatus = "Off";
});

app.get('/updateReadings', function(req, res) {

});

app.listen(80);
console.log('The server is on port 80');
