#!/usr/bin/env node

var express = require('express');
var bodyParser = require('body-parser');
var spawn = require("child_process").spawn;
var mysql = require("mysql");
var app = express();

app.get('/', function(req, res){
   res.render('form');
});

app.set('view engine', 'ejs');
app.set('views', './views');

// for parsing application/json
app.use(bodyParser.json());

// for parsing application/xwww-
app.use(bodyParser.urlencoded({ extended: true }));

// for parsing multipart/form-data
//app.use(upload.array());
app.use(express.static('public'));

app.post('/', function(req, res){
  console.log(req.body);
  //res.send("recieved your request!");
  var status;
  var measurement = req.body.measurement;

  if (req.body.numEntries != '' && req.body.lowDate == '' && req.body.upperDate == '') {
    var process = spawn('python',["graph.py", "num", measurement, req.body.numEntries]);
    process.stdout.on('data', (data) => {
      status = `${data}`;
    });

    process.on('exit', function (code, signal) {
      res.download('./plot.png');
    });
  }
  else if (req.body.numEntries == '' && req.body.lowDate != '' && req.body.upperDate != '') {
    var process = spawn('python',["graph.py", "dates", measurement, req.body.lowDate, req.body.upperDate]);

    process.stdout.on('data', (data) => {
      status = `${data}`;
    });

    process.on('exit', function (code, signal) {
      console.log(status);
      if (status == 0) {
        res.download('./plot.png');
      } else {
        res.render('form');
      }
    });

  }
  else {
    res.render('form');
  }
});

app.listen(5000);
