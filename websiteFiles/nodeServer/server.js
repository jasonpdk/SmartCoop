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



// set the view engine to ejs
app.set('view engine', 'ejs');

var outsideTemp, insideTemp, humidity, doorStatus;
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

// initial door status check
fs.readFile('/home/root/doorStatus.txt', 'utf8', function(err, data) {
	if (err) throw err;
	if (data[0] == 0)
	{
		doorStatus = "closed";
	}
	else
	{
		doorStatus = "open";
	}
});

// index page
app.get('/', function(req, res) {

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
			doorStatus = "closed";
		}
		else
		{
			doorStatus = "open";
		}
	});

	res.render('pages/index', {
		insideTemp: insideTemp,
		outsideTemp: outsideTemp,
		humidity: humidity,
		sunrise: sunrise,
		sunset: sunset,
		doorStatus: doorStatus
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

app.listen(80);
console.log('The server is on port 80');
