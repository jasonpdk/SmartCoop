var galileoIP = "192.168.41.111";

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
