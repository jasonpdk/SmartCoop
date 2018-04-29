var galileoIP = "192.168.41.10:8000";

function ledOn()
{
  document.getElementById("updateThis").innerHTML = "On";

  var xhr = new XMLHttpRequest();
  xhr.open('GET', "//" + galileoIP + "?LEDOn", true);
  xhr.send();

}

function ledOff()
{
  document.getElementById("updateThis").innerHTML = "Off";

  var xhr = new XMLHttpRequest();
  xhr.open('GET', "//" + galileoIP + "?LEDOff", true);
  xhr.send();

}

function openDoor()
{
  var xhr = new XMLHttpRequest();
  xhr.open('GET', "//" + galileoIP + "?openDoor", true);
  xhr.send();
}

function closeDoor()
{
  var xhr = new XMLHttpRequest();
  xhr.open('GET', "//" + galileoIP + "?closeDoor", true);
  xhr.send();
}

function feed()
{
  var xhr = new XMLHttpRequest();
  xhr.open('GET', "//" + galileoIP + "?feed", true);
  xhr.send();
}

window.onload = function startClock()
{
        var now = new Date;
        var year = now.getUTCFullYear();
        var month = now.getUTCMonth();
        var date = now.getUTCDate();
        var day = now.getUTCDay();
        var hours = now.getUTCHours();
        var minutes = now.getUTCMinutes();
        var seconds = now.getUTCSeconds();

        var months = new Array('January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December');
        var days = new Array('Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday');

        // add zeros is front of hours, minutes, and seconds
        if(hours < 10)
        {
                hours = "0" + hours;
        }

        if(minutes < 10)
        {
                minutes = "0" + minutes;
        }

        if(seconds < 10)
        {
                seconds = "0" + seconds;
        }

        var string = "" + days[day] + " " + date + " " + months[month] + " " + year + " " + hours + ":" + minutes + ":" + seconds + " UTC" + "<br />All times are UTC.";
        document.getElementById("time").innerHTML = string;
        setTimeout(startClock, 500);
}
