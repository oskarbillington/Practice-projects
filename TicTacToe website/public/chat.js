// Make connection
var socket = io.connect(); // "http://localhost:5000"

// Query DOM
var message = document.getElementById('message'),
      handle = document.getElementById('handle'),
      btn = document.getElementById('send'),
      output = document.getElementById('output'),
      feedback = document.getElementById('feedback');


// Emit events
btn.addEventListener("click", function(){
  if (handle.value.length != 0 && message.value.length != 0) {
    socket.emit("chat",{
      message: message.value,
      handle: handle.value,
      player1: socket.id
      //player2: ""
    });
    socket.emit("flags", {
      empty_fields: 0
    });
  }
  else {
    socket.emit("flags",{
      empty_fields: 1
    });
  }
});

message.addEventListener("keypress", function(){
  socket.emit("typing",handle.value);
});


// Listen for events
socket.on("chat_return", function(data){
  feedback.innerHTML = "";
  output.innerHTML += "<p><strong>" + data.handle + "</strong> " + data.message + "</p>";
});

socket.on("typing_return", function(data){
  feedback.innerHTML = "<p><em>" + data + " is typing a message...</em><p>";
});

socket.on("flags_return", function(data){
  if (data.empty_fields == 1) {
    output.innerHTML += "<p><i>" + "Some fields are empty" + "</i></p>";
  }
  else if (data.empty_fields == 2) {
    output.innerHTML += "<p><i>" + "You need a handle (name) to play" + "</i></p>";
  }
});



// Tic tac toe stuff...

var ttt_running = false; // should also hide html board while false
socket.on("ttt_restart", function(data){

  // Setup O/C
  feedback.innerHTML = "";
  ttt_running = true;
  var gameover = false;
  var new_game = true;
  var full_game = false;
  var prev_player = ""; //x

  var player1 = data.player1;
  var player2 = "";
  var handle1 = data.handle;
  var handle2 = "";




  if (document.querySelector) {
    	document.documentElement.classList.add('js');

      output.innerHTML += "<p><b>" + "Tic Tac Toe game started, " + data.handle + " begins</b></p>";
      var first_player = data.handle;

      // Clear board (graphics)
      var tempID;
      for (var i = 0; i < 3; i++) {
        for (var j = 0; j < 3; j++) {
          tempID = i.toString(8);
          tempID = tempID.concat(j.toString(8));
          var parentElement = document.getElementById(tempID);
          parentElement.innerHTML = "";
          parentElement.classList = "";
        }
      }

    	var ticTacToeElement = document.querySelector('#tic-tac-toe');
    	var isPlayerXMoving = true;
    	var board = [
    		[0, 0, 0],
    		[0, 0, 0],
    		[0, 0, 0]
    	];

    	ticTacToeElement.addEventListener('click', ticTacToeClickHandler);
    }




  socket.on("ttt_update_return", function(data){

    if (gameover == false && prev_player != data.current_clicker) {

      // Only 2 players allowed
      if (data.current_clicker != player1 && full_game == false && new_game == false && data.handle.length != 0) {
        player2 = data.current_clicker;
        handle2 = data.handle;
        output.innerHTML += "<p><b>" + handle1 + " is playing against: " + handle2 + "</b></p>";
        full_game = true;
      }

      if (data.current_clicker == player1 || (data.current_clicker == player2 && new_game == false)) {
        if (new_game == true) {
          new_game = false;
        }

        prev_player = data.current_clicker;

        // Update board graphics
        var row = data.row;
        var column = data.column;
        board[row][column] = isPlayerXMoving ? 1 : -1;
        var elementID = row.toString(8);
        elementID = elementID.concat(column.toString(8));
        var parentElement = document.getElementById(elementID);
        parentElement.innerHTML = isPlayerXMoving ? 'x' : 'o';
        parentElement.classList.add(isPlayerXMoving ? 'piece-x' : 'piece-o');

        // Game over?
        var sum = Array(8).fill(0);
        for (var i = 0; i < 3; i++){
        	for (var j = 0; j < 3; j++){
        		sum[i] += board[i][j]; // Rows
            sum[3+i] += board[j][i]; // Columns
        	}
          sum[6] += board[i][i]; // Diagonal down
          sum[7] += board[i][2-i]; // Diagonal up
        }
        for (var i = 0; i < 8; i++){
          if (Math.abs(sum[i]) == 3) {
            gameover = true;
          }
        }

        if (gameover == true) {
          output.innerHTML += "<p><b>Game over, " + (isPlayerXMoving ? handle1 + " ❌" : handle2 + " ⭕") + " wins!</b></p>";
          ttt_running = false;
        }
        else {
          isPlayerXMoving = !isPlayerXMoving;
        }

      }

    }

  });

});




function ticTacToeClickHandler(event) {
  if (ttt_running == true) {
  	var targetElement = event.target;
  	var parentElement = targetElement.parentElement;
  	var row, column;

  	if (targetElement.nodeName == 'BUTTON')
  	{
  		row = parseInt(targetElement.dataset.row);
  		column = parseInt(targetElement.dataset.column);

      socket.emit("ttt_update", {
        row: row,
        column: column,
        current_clicker: socket.id,
        handle: handle.value,
        connections: []
        //isPlayerXMoving: isPlayerXMoving,
        //parentElement: parentElement
      });
  	}
  }
}
