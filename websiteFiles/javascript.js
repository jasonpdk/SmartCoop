function ledOn()
{
  var xhr = new XMLHttpRequest();
  xhr.open('GET', "//192.168.41.103?LEDOn", true);
  xhr.send();
}

function ledOff()
{
  var xhr = new XMLHttpRequest();
  xhr.open('GET', "//192.168.41.103?LEDOff", true);
  xhr.send();
}

function openDoor()
{
  var xhr = new XMLHttpRequest();
  xhr.open('GET', "//192.168.41.103?openDoor", true);
  xhr.send();
}

function closeDoor()
{
  var xhr = new XMLHttpRequest();
  xhr.open('GET', "//192.168.41.103?closeDoor", true);
  xhr.send();
}
