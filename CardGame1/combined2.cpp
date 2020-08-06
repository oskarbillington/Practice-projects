#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <random>       // std::default_random_engine
#include <chrono>
#include <algorithm>    //std::shuffle
#include <cstdlib>

using namespace std;

class Card {
  
  int Rank;
  string Suit;

  public:
    
    Card(int type = 0, int value = 0) {

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
          Suit = "Err.";
          cout << "Error. Select type 1-4.\n";
        }
    }

    Card(string type, int value) {

      if (value >= 0 && value <= 13) {
        Rank = value;
      }
      else {
        Rank = 0;
        cout << "Error value selection.\n";
      }

      if (type == "clubs" || type == "Clubs") {
        Suit = "Clubs";
      }
      else if (type == "diamonds" || type == "Diamonds") {
        Suit = "Diamonds";
      }
      else if (type == "hearts" || type == "Hearts") {
        Suit = "Hearts";
      }
      else if (type == "spades" || type == "Spades") {
        Suit = "Spades";
      }
      else if (type == " ") {
        Suit = "";
      }
      else {
        Suit = "Err.";
        cout << "Error. Select type 1-4.\n";
      }  
      
    }
    
    int get_rank() {
      return Rank;
    }

    string get_suit() {
      return Suit;
    }

    void print_card() {
      if (Suit != "") {
        cout << Rank << " of " << Suit;
      }
      else {
        cout << Rank;
      }
    }

};

class Deck {

  vector<Card> this_deck;

  public :

    int size; // deck size, counting rank-suit upto 52

    Deck(int n = 52) : this_deck(n), size(n)
    {
      int k = 0, i, j;
      for (i = 1; i <= 4; i++) {
        for (j = 1; j <= 13; j++) {
          if (k < size) {
            Card a(i,j);
            this_deck[(i-1)*13 + (j-1)] = a;
            k++;
          }
        }
      }
    }

    Card pick_card_top() {
      
      int end_s, end_r;
      end_r = (size-1)%13 + 1;
      end_s = (size-end_r)/13 + 1;

      Card picked;
      picked = this_deck[(end_s-1)*13 + (end_r-1)];
      Card a(0,0);
      this_deck[(end_s-1)*13 + (end_r-1)] = a;

      size--;
      return picked;
      
      // return and erase without leaving a 0,0 card:
      //Card picked;
      //picked = this_deckthis_deck.end()};
      //this_deck.erase(this_deck.begin() + (end_s-1)*13 + (end_r-1));
      // ...
      
    }

    Card pick_card_random() {
      return 0;
    }

    Card pick_card_specific(int a_suit, int a_rank) {
      return 0;
    }

    void change_card(int pos_s, int pos_r, int suit, int rank, bool print = 0) {
      if ((13*(pos_s-1)+pos_r) <= size) {
        Card new_card(suit,rank);
        this_deck[(pos_s-1)*13 + (pos_r-1)] = new_card;
        if (print == 1) {
          print_deck();
        }
      }
      else {
        cout << "This position is outside of the deck boundaries.\n";
      }
    }

    void add_card_top(string a_suit, int a_rank) {
      size++;
      Card a_card(a_suit,a_rank);
      //this_deck.push_back(a_card);
      this_deck.insert(this_deck.end(), a_card);
    }

    void add_card_top(Card a_card) {
      //this_deck.push_back(a_card);
      size++;
      //this_deck.resize(size);
      this_deck.insert(this_deck.end(), a_card);
    }

    void sort_deck(bool sure = 0) { // actually reset
      if (sure == 0) {
        cout << "Are you sure you want to sort the deck? ";
        cin >> sure;
      }
      if (sure == true) {
        int n = size;
        int k = 1;
        int i, j;
        for (i = 1; i <= 4; i++) {
          for (j = 1; j <= 13; j++) {
            if (k <= n) {
              Card a(i,j);
              this_deck[(i-1)*13 + (j-1)] = a;
              k++;
            }
            else {
              Card a(0,0);
              this_deck[(i-1)*13 + (j-1)] = a;
            }
          }
        }
      }
      else {
        cout << "The deck was not sorted.\n";
      }
    }

    void shuffle_deck(bool sure = 0) {
      if (sure == 0) {
        cout << "Are you sure you want to shuffle the deck? ";
        cin >> sure;
      }
      if (sure == true) { //shuffle algoritm
        // "size" consecutive integers
        int list[size];
        int i = 0;
        while (i < size) {
          list[i] = i + 1;
          i++;
        }

        // shuffle integers
        int shuffled_list[size];
        srand(time(0));
        for (int j = 0; j < size; j++) {
          shuffled_list[j] = 0;
        }
        for (int j = 0; j < size; j++) {
          int list_member = list[j];
          while (list_member != size+1) {
            int p = rand() % size;
            if (shuffled_list[p] == 0) {
              shuffled_list[p] = list_member;
              list_member = size + 1;
            }
          }
        }
        
        // rearrange this deck according to shuffled list
        Card shuffled_deck[size];
        for (int j = 0; j < size; j++) {
          shuffled_deck[j] = this_deck[shuffled_list[j]];
        }
        for (int j = 0; j < size; j++) {
          this_deck[j] = shuffled_deck[j];
        }
      }
      else {
        cout << "The deck was not shuffled.\n";
      }
    }

    void print_deck() {
      int k = 0;
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
          if (k < size) {
            cout << this_deck[i*13 + j].get_rank() << "," << this_deck[i*13 + j].get_suit() << "  ";
            k++;
          }
        }
        if (k < size) {
          cout << "\n\n";
        }
      }
      cout << "\n\n";
    }
  
};

class Hand {
  
  vector<Card> this_hand;

  public:

    int size;
  
    Hand(Deck &a_deck, int n = 1) :  this_hand(0)
    {
      size = n;
      while (this_hand.size() < size) {
        Card a_card = a_deck.pick_card_top();
        this_hand.insert(this_hand.end(), a_card);
      }
    }

    void sort_hand() {

    }
    
    void print_hand() {

      for (int i = 0; i < size; i++) {
        if (i < (size-1)) {
          cout << this_hand[i].get_rank() << " of " << this_hand[i].get_suit() << ", ";
        }
        else {
          cout << this_hand[i].get_rank() << " of " << this_hand[i].get_suit() << ".\n";
        }
      }
    }

    Card pick_card_specific(int pick_suit, int pick_rank) {
      
      Card pick_card(pick_suit, pick_rank), picked;

      for (int i = 0; i < size; i++) {

        string check_suit = this_hand[i].get_suit();
        int check_rank = this_hand[i].get_rank();
        string my_suit = pick_card.get_suit();
        int my_rank = pick_rank;

        bool found = (check_suit == my_suit && check_rank == my_rank);

        if (found) {
          picked = this_hand[i];
          this_hand.erase(this_hand.begin()+i);
          size--;
          return picked;
        }
      }

      cout << "This card is not in the hand.\n";
      return 0;
    }

    Card pick_card_specific(Card pick_card) {
      
      Card picked;

      for (int i = 0; i < size; i++) {

        string check_suit = this_hand[i].get_suit();
        int check_rank = this_hand[i].get_rank();
        string my_suit = pick_card.get_suit();
        int my_rank = pick_card.get_rank();

        bool found = (check_suit == my_suit && check_rank == my_rank);

        if (found) {
          picked = this_hand[i];
          this_hand.erase(this_hand.begin()+i);
          size--;
          return picked;
        }
      }

      cout << "This card is not in the hand.\n";
      return 0;
    }

    Card pick_card_random() {
      return 0;
    }

};

int main() {

  // setup
  bool test1 = 0;
  bool test2 = 0;
  bool game = 0;
  
  if (test1 == true) {
    int my_type, my_value;

    cout << "Define a card.\nSuit: ";
    cin >> my_type;
    cout << "Rank: ";
    cin >> my_value;
    cout << "\n";

    Card my_card(my_type, my_value);

    cout << "Your card is " << my_card.get_rank() << " of " << my_card.get_suit() << ".\n";

    Deck my_deck(50);
    cout << "\n\n";
    my_deck.print_deck();
    cout << "\n\n";
    my_deck.change_card(1,1,4,12,0);
    my_deck.change_card(4,11,my_type,my_value,1);

    my_deck.sort_deck();
    cout << "\n";
    my_deck.print_deck();

    my_deck.shuffle_deck();
    cout << "\n\n";
    my_deck.print_deck();

    Card a_card = my_deck.pick_card_top();
    cout << "You picked " << a_card.get_rank() << " of " << a_card.get_suit() << ".\n";
    cout << "The new deck size is " << my_deck.size << " cards.\n\n";
    my_deck.print_deck();

    while (true) {
      string input;
      string pick = "pick";
      string sort = "sort";
      string shuffle = "shuffle";
      string print = "print";
      cout << "pick, sort, shuffle, print: ";
      cin >> input;
      cout << "\n";
      
      if (input == pick) {
        my_deck.pick_card_top();
        input = "";
      }
      else if (input == sort) {
        my_deck.sort_deck();
        input = "";
      }
      else if (input == shuffle) {
        my_deck.shuffle_deck();
        input = "";
      }
      else if (input == print) {
        my_deck.print_deck();
        input = "";
      }
      else {
        cout << "Enter a valid method.\n";
        input = "";
      }
    }
  }
  
  if (test2 == true) {

    Deck my_deck(50);
    //my_deck.shuffle_deck(1);
    //my_deck.print_deck();
    my_deck.change_card(4,9,4,12);
    Hand my_hand(my_deck, 5);
    cout << "\n\n";
    my_deck.print_deck();
    cout << "\n\n";
    my_hand.print_hand();
    Card my_card = my_hand.pick_card_specific(4,12);
    cout << "\n";
    my_card.print_card();
    cout << ", ";
    //cout << "\n\n";
    //my_hand.print_hand();
    
    Card card2("spades",7);
    Card card3 = my_hand.pick_card_specific(card2);
    card3.print_card();
    cout << "\n\n";
    my_hand.print_hand();
    cout << "\n\n";

    cout << "On the table: ";
    Deck table(0);
    table.add_card_top(card3);
    table.print_deck();
    Card card4("clubs", 10);
    table.add_card_top(card4);
    table.print_deck();
    table.add_card_top("spades",5);
    table.print_deck();

  }


  if (game == true) {
    
  }


  return 0;
};