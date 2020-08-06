/* 07.08.2019 = start date
built using repl.it (website, FB login)
single "combined" file as I didn't understand how to compile only a user defined 
set of files on the website (nor use the terminal in general) */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Card {
  
  int Rank;
  string Suit;

  public:
    
    Card(int type = 1, int value = 1) {

      if (value >= 0 && value <= 13) {
        Rank = value;
      }
      else {
        Rank = 0;
        cout << "Error value selection.\n";
      }
  
      switch (type) {
        case 1 :
          Suit = "Clubs";
          break;
        case 2 :
          Suit = "Diamonds";
           break;
        case 3 :
          Suit = "Hearts";
          break;
        case 4 :
          Suit = "Spades";
          break;
        case 0 :
          Suit = "";
          break;
        default :
          Suit = "Error. Select type 1-4.";
          cout << "Error type selection.\n";
        }
    }
    
    int get_rank() {
      return Rank;
    }

    string get_suit() {
      return Suit;
    }

};

class Deck {

  Card fresh_deck[4][13];
  int size; // deck size, counting rank-suit upto 52

  public :

    Deck(int n = 52) {
      size = n;
      int k = 1;
      int i, j;
      for (i = 1; i <= 4; i++) {
        for (j = 1; j <= 13; j++) {
          if (k <= n) {
            Card a(i,j);
            fresh_deck[i-1][j-1] = a;
            k++;
          }
          else {
            Card a(0,0);
            fresh_deck[i-1][j-1] = a;
          }
        }
      }
    }

    void print_deck() {
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
          cout << fresh_deck[i][j].get_rank() << "," << fresh_deck[i][j].get_suit() << "  ";
        }
       cout << "\n\n";
      }
    }

    void change_card(int pos_s, int pos_r, int suit, int rank, bool print = 0) {
      if ((13*(pos_s-1)+pos_r) <= size) {
        Card new_card(suit,rank);
        fresh_deck[pos_s-1][pos_r-1] = new_card;
        if (print == 1) {
          print_deck();
        }
      }
      else {
        cout << "This position is outside of the deck boundaries.\n";
      }
    }
  
};

int main() {

  int my_type, my_value;

  cout << "Define a card.\nSuit: ";
  cin >> my_type;
  cout << "Rank: ";
  cin >> my_value;
  cout << "\n";

  Card my_card(my_type, my_value);

  cout << "Your card is " << my_card.get_rank() << " of " << my_card.get_suit() << ".\n";

  Deck my_deck(15);
  cout << "\n\n";
  my_deck.print_deck();
  cout << "\n\n";
  //my_deck.change_card(1,1,4,12,0);
  //my_deck.change_card(3, 2, my_type, my_value, 1);
  


  return 0;
}