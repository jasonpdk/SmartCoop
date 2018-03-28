var galileoIP = "192.168.41.105:8000";

function ledOn()
{
  var xhr = new XMLHttpRequest();
  xhr.open('GET', "//" + galileoIP + "?LEDOn", true);
  xhr.send();
}

function ledOff()
{
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

function updateLightStat(onoff) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
     document.getElementById("updateThis").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", onoff, true);
  xhttp.send();
}
