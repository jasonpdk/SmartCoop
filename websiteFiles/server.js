var http = require('http');
var fs = require('fs');

// 404 response
function send404Response(response)
{
  response.writeHead(404, {"Content-Type": "text/plain"});
  response.write("ERROR 404: Page not found!");
  response.end();
}

// Handle user request
function onRequest(request, response)
{
  if (request.method == 'GET' && request.url == '/') // home page
  {
    response.writeHead(200, {"Content-Type": "text/html"});
    fs.createReadStream("./index.html").pipe(response);
  }
  else if (request.method == 'GET' && request.url == '/graphs')
  {
    response.writeHead(200, {"Content-Type": "text/html"});
    fs.createReadStream("./graphs.html").pipe(response);
  }
  else if (request.method == 'GET' && request.url == '/camera')
  {
    response.writeHead(200, {"Content-Type": "text/html"});
    fs.createReadStream("./camera.html").pipe(response);
  }
  else if (request.method == 'GET' && request.url == '/style.css')
  {
    response.writeHead(200, {"Content-Type": "text/css"});
    fs.createReadStream("./style.css").pipe(response);
  }
  else if (request.method == 'GET' && request.url == '/javascript.js')
  {
    response.writeHead(200, {"Content-Type": "text/javascript"});
    fs.createReadStream("./javascript.js").pipe(response);
  }
  else
  {
    send404Response(response);
  }

}

http.createServer(onRequest).listen(8888);
console.log("Server is now running...");
