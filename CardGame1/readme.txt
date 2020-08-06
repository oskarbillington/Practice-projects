"Combined" holds all the code for my first C++ cardgame project
Developed in online IDE, url: repl.it; (FB login)


---------
Version 1
---------
Just a backup of some progress.


---------
Version 2
---------
Classes work, 
	- Card, Deck, Hand
Main contains tests.


---------
Version 3
---------
Playable (terminal) multiplayer Vriåtter.
	- Main function: turn. Takes game setup and computes the move: play a legal card, pick from the deck or pass the turn.
Main contains the game.

Learning outcomes:
	- Transferrable C++ skills; syntax profficiency, bug fix, object structure.
	- Card game dev.
		- Deck and Hand are similar. Can make one class Set for all sets of cards (hand, deck, table, stikk), and give it 
		  methods like "new_deck(int size)". Or generally, for larger games: plan ahead the class structure better.
		- May want to have Card class fundamentally represent cards with ints only, strings only attached at cout.
		- Much of this code can be copied to new projects. (May consider stealing better code for these common classes).

Learning potentials:
	- I often come across more sophisticated, cleaner code compared to my "brute force" interative sequences. Return to this 
	  project later after having spent time learning to code "better" in this sense.
	- I am not too concerned with execution speed with this code, although it will be important for ORS projects. Keep that
	  more in mind in future projects.
	- Partially following from the former remark: Learn about (sorting-) algorithms i.e. computer science for cleaner and faster 
	  code that, also importantly, uses less memory.
	- *Inheritance*
	
Project development:
	- Vriåtter can be given an interface/platform/app form (with C#?).
		- The code must be adapted with the interface to allow player number selection, hiding your cards from the opponent,
		  setting up various parameters in a pause menu, etc.
	- New method: shuffle_hand(), sort_hand()
		- How to sort a random sample from the deck (a hand) without brut forcing checking the hand for each successive card?
	- Game just crashes when the deck has been picked empty.
	- Input check: disallow all nonsense cin >>. Not sure if the code is bug free (consider combinations of allowable starter 
	  hand/deck sizes etc.). Bug test algorithm (@compsci)?
	- Computer opponent? Should be quite simple to hard code in this case if I don't consider strategy other than always playing 
	  a card if it can and just playing the first available legal card in the hand.
		- Would have to make sensible use of 8s, e.g. "if no card != 8 can be played or if all cards in the hand but 1 is an 
		  8, vri to the suit dominating the hand".
	- Interface with machine learning agent / reinforcement learning project?

