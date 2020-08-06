// (in cmd, from the beginning: ... (youtube tutorial), npm install socket.io --save )

var express = require("express");
var socket = require("socket.io");

// App setup
var app = express();
var server = app.listen(5000, function(){
  console.log("listening to request on port 5000");
});

// Static files
app.use(express.static("public"));

// Socket setup
var io = socket(server);
var connections = ["LIST ID"];

io.on("connection",function(socket){
  console.log("made socket connection", socket.id);
  connections.push(socket.id);
  console.log(connections);

  // Handle chat event
  socket.on("chat",function(data){
    if (data.message == "ttt") {
      io.sockets.emit("ttt_restart", data);
    }
    else {
      io.sockets.emit("chat_return", data);
    }
  });

  socket.on("typing",function(data){
    socket.broadcast.emit("typing_return",data);
  });

 // Returning error msg locally if empty field(s)
  socket.on("flags",function(data){
    io.to(socket.id).emit("flags_return", data);
  });

  // Tic tac toe stuff
  socket.on("move_played",function(data){
    io.sockets.emit("move_played_return", data);
  });

  socket.on("ttt_update",function(data){
    data.connections = connections; // Doesn't do anything atm...
    io.sockets.emit("ttt_update_return", data);
  });

  // Handle connections
  socket.on('disconnect', function () {
      console.log("disconnected: ", socket.id);
      for (var i = 0; i < connections.length; i++) {
        if (connections[i] == socket.id) {
          connections.splice(i,1);
        }
      }
      console.log(connections);
  });

});
