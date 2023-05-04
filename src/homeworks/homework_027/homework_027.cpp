#include <iostream>
#include <queue>
#include <utility>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

// Constants
#define CARDS_DECK_QUANTITY 52

// Enums
enum CardSuit {
  HEARTS = 1,
  DIAMONDS = 2,
  CLUBS = 3,
  SPADES = 4
};

enum Winner {
  PLAYER1 = 1,
  PLAYER2 = 2,
  TIE = 3
};

// Class that represents a card
class Card {
 private:
  int value;
  CardSuit suit;

  // Method that validates the card input parameters
  void validate() const {
    // Check if the card suit is valid
    if (suit < 1 || suit > 4) {
      throw invalid_argument("Invalid card suit");
    }

    // Check if the card value is valid
    if (value < 2 || value > 14) {
      throw invalid_argument("Invalid card value");
    }
  }

  // Method that returns the card suit icon
  static string getSuitIcon(CardSuit _suit) {
    switch (_suit) {
      case HEARTS : return "♥";
      case DIAMONDS : return "♦";
      case CLUBS : return "♣";
      case SPADES : return "♠";
      default : throw invalid_argument("Invalid suit");
    }
  }
 public:
  // Constructor
  Card(int _value, CardSuit _suit) : value(_value), suit(_suit) {
    // Validate the card input parameters
    validate();
  }

  // Method that prints the card
  void print() {
    cout << this->toString() << " ";
  }

  // Method that returns the card value as a string
  string toString() {
    string result;
    if (value < 11) {
      result += to_string(value);
    } else if (value == 11) {
      result += "J";
    } else if (value == 12) {
      result += "Q";
    } else if (value == 13) {
      result += "K";
    } else if (value == 14) {
      result += "A";
    }
    result += getSuitIcon(suit);
    return result;
  }

  // Getters
  [[nodiscard]] int getValue() const {
    return value;
  }
};

// Class that represents a deck of cards
class CardsDeck {
 private:
  queue<Card> cards;
  bool isSplit = false;

  // Method that shuffles the deck of cards
  void shuffle() {
    // Copy the queue to a vector
    vector<Card> tempCardsDeck;
    while (!cards.empty()) {
      tempCardsDeck.push_back(cards.front());
      cards.pop();
    }

    // Shuffle the vector randomly
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    ::shuffle(tempCardsDeck.begin(), tempCardsDeck.end(), default_random_engine(seed));

    // Copy the vector back to the queue
    for (auto card : tempCardsDeck) {
      cards.push(card);
    }
  }
 public:
  // Constructor
  explicit CardsDeck(bool _isSplit = false) : isSplit(_isSplit) {
    // If the deck is not split, add all cards to the queue and shuffle them
    if (!isSplit) {
      for (int i = 0; i < CARDS_DECK_QUANTITY; i++) {
        int value = i % 13 + 2;
        auto suit = static_cast<CardSuit>(i / 13 + 1);
        cards.emplace(value, suit);
      }
      shuffle();
    }
  }

  // Method that splits the deck of cards into two decks
  pair<CardsDeck, CardsDeck> split() {
    // Check if the deck is already split
    if (isSplit) {
      throw invalid_argument("Deck is already split");
    }

    // Create two new decks
    CardsDeck cardsDeck1(true);
    CardsDeck cardsDeck2(true);

    // Split the cards into two decks
    queue<Card> temp = cards;
    while (!temp.empty()) {
      cardsDeck1.addCard(temp.front());
      temp.pop();
      cardsDeck2.addCard(temp.front());
      temp.pop();
    }

    // Return the two new decks as a pair
    return make_pair(cardsDeck1, cardsDeck2);
  }

  // Method that adds a card to the deck
  void addCard(Card card) {
    cards.push(card);
  }

  // Method that adds a queue of cards to the deck
  void addCards(queue<Card> _cards) {
    while (!_cards.empty()) {
      cards.push(_cards.front());
      _cards.pop();
    }
  }

  // Method that prints the deck of cards
  void print() {
    queue<Card> temp = cards;
    while (!temp.empty()) {
      Card card = temp.front();
      card.print();
      temp.pop();
    }
    cout << "\n";
  }

  // Getters
  Card getTopCard() {
    if (cards.empty()) {
      throw invalid_argument("No cards left");
    }
    Card card = cards.front();
    cards.pop();
    return card;
  }

  [[nodiscard]] bool isEmpty() const {
    return cards.empty();
  }

  Card getTop() {
    return cards.front();
  }
};

// Class that represents a player
class Player {
 private:
  CardsDeck cardsDeck;
 public:
  // Constructor
  explicit Player() = default;

  // Method that adds a card to the player's cards
  void addCard(Card card) {
    cardsDeck.addCard(card);
  }

  // Method that adds a queue of cards to the player's cards
  void addCards(queue<Card> _cards) {
    cardsDeck.addCards(std::move(_cards));
  }

  // Method that prints the player's cards
  void printCardsDeck() {
    cardsDeck.print();
  }

  // Setters
  void setCardsDeck(CardsDeck _cardsDeck) {
    cardsDeck = std::move(_cardsDeck);
  }

  // Getters
  [[nodiscard]] CardsDeck getCardsDeck() const {
    return cardsDeck;
  }

  Card getTopCard() {
    Card card = cardsDeck.getTop();
    cardsDeck.getTopCard();
    return card;
  }
};

class Game {
 private:
  Player player1;
  Player player2;
 public:
  // Constructor
  Game() {
    // Create a deck of cards and split it into two decks for each player
    CardsDeck cardsDeck;
    CardsDeck player1CardsDeck, player2CardsDeck;
    tie(player1CardsDeck, player2CardsDeck) = cardsDeck.split();
    player1.setCardsDeck(player1CardsDeck);
    player2.setCardsDeck(player2CardsDeck);
  }

  // Method that starts the game
  Winner play(bool autoPlay, bool silentMode) {
    // Set the cout to fail if silent mode is on
    if (silentMode) {
      cout.setstate(ios_base::failbit);
    }

    // Set a round counter
    int round = 1;

    // Print the rules and initial decks
    cout << "Welcome to the War Game!\n\n";
    cout << "Rules:\n";
    cout << "   This is a simple card game played between two players.\n";
    cout << "   Each player starts with a deck of 26 cards.\n";
    cout << "   Each round, both players draw a card from the top of their deck.\n";
    cout << "   The player with the higher card wins the round and takes both cards.\n";
    cout << "   If the cards are equal, it's a tie and both players discard 3 cards, then turn up the fourth.\n";
    cout << "   The first player to run out of cards loses.\n\n";
    cout << "Here are the initial decks:\n";
    cout << "   Player 1 deck: ";
    player1.printCardsDeck();
    cout << "   Player 2 deck: ";
    player2.printCardsDeck();
    cout << "\n";

    // Wait for the user to press enter to start the game if autoplay is off
    cout << "==================================\n";
    cout << "Press \"Enter\" to start the game...\n";
    cout << "==================================\n";
    if (autoPlay) {
      cout << "\n";
    } else {
      cin.ignore();
    }

    // Start the game
    while (true) {
      // Print the current round and decks
      cout << "== ROUND: " << round << " ==\n\n";
      cout << "Here are the current decks:\n";
      cout << "   Player 1 deck: ";
      player1.printCardsDeck();
      cout << "   Player 2 deck: ";
      player2.printCardsDeck();

      // Check if player1 has run out of cards
      if (player1.getCardsDeck().isEmpty()) {
        cout << "\nPlayer 1 is out of cards. Player 2 wins!\n";

        // Enable cout back if silent mode is on
        if (silentMode) {
          cout.clear();
        }

        // Return the winner
        return Winner::PLAYER2;
      }

      // Check if player2 has run out of cards
      if (player2.getCardsDeck().isEmpty()) {
        cout << "\nPlayer 2 is out of cards. Player 1 wins!\n";

        // Enable cout back if silent mode is on
        if (silentMode) {
          cout.clear();
        }

        // Return the winner
        return Winner::PLAYER1;
      }

      // Wait for the user to press enter to draw a card if autoplay is off
      cout << "\n===============================\n";
      cout << "Press \"Enter\" to draw a card...\n";
      cout << "===============================\n";
      if (autoPlay) {
        cout << "\n";
      } else {
        cin.ignore();
      }

      // Draw a card from each player's deck
      Card player1Card = player1.getTopCard();
      Card player2Card = player2.getTopCard();

      // Print the cards that were drawn
      cout << "Cards drawn:\n";
      cout << "   Player 1 drew: ";
      player1Card.print();
      cout << "\n   Player 2 drew: ";
      player2Card.print();
      cout << "\n\n";

      // Compare the values of the cards to determine the winner of the round
      if (player1Card.getValue() > player2Card.getValue()) {
        cout << "Player 1 wins the round and takes 2 cards (" << player1Card.toString() << " "
             << player2Card.toString() << ")!\n";

        // Add the cards to player1's deck
        player1.addCard(player1Card);
        player1.addCard(player2Card);
      } else if (player2Card.getValue() > player1Card.getValue()) {
        cout << "Player 2 wins the round and takes 2 cards (" << player2Card.toString() << " "
             << player1Card.toString() << ")!\n";

        // Add the cards to player2's deck
        player2.addCard(player2Card);
        player2.addCard(player1Card);
      } else {
        // If the cards are equal, it's a tie and both players discard 3 cards, then turn up the fourth
        cout << "It's a tie! Each player discards 3 cards, then turns up the fourth.\n";

        // Wait for the user to press enter to proceed if autoplay is off
        cout << "\n===========================\n";
        cout << "Press \"Enter\" to proceed...\n";
        cout << "===========================\n";
        if (autoPlay) {
          cout << "\n";
        } else {
          cin.ignore();
        }

        // Create a temporary deck to store the cards that will be discarded
        queue<Card> cards;
        for (int i = 0; i < 3; i++) {
          if (player1.getCardsDeck().isEmpty() || player2.getCardsDeck().isEmpty()) {
            break;
          }
          cards.push(player1.getTopCard());
          cards.push(player2.getTopCard());
        }

        // Check if the game is a tie
        if (player1.getCardsDeck().isEmpty() || player2.getCardsDeck().isEmpty() || cards.empty()) {
          cout << "Not enough cards to continue the tiebreaker. The game is a tie.\n";

          // Enable cout back if silent mode is on
          if (silentMode) {
            cout.clear();
          }

          // Return the winner
          return Winner::TIE;
        }

        // Draw a card from each player's deck
        player1Card = player1.getTopCard();
        player2Card = player2.getTopCard();

        // Add the cards to the temporary deck
        cards.push(player1Card);
        cards.push(player2Card);

        // Print the cards that were drawn
        cout << "Cards drawn:\n";
        cout << "   Player 1 drew: ";
        player1Card.print();
        cout << "\n";
        cout << "   Player 2 drew: ";
        player2Card.print();
        cout << "\n\n";

        // Compare the values of the cards to determine the winner of the tiebreaker round
        if (player1Card.getValue() > player2Card.getValue()) {
          cout << "Player 1 wins the tiebreaker round and takes all 10 cards!\n";

          // Add the cards to player1's deck
          player1.addCards(cards);
          player1.addCard(player1Card);
          player1.addCard(player2Card);
        } else if (player2Card.getValue() > player1Card.getValue()) {
          cout << "Player 2 wins the tiebreaker round and takes all 10 cards!\n";

          // Add the cards to player2's deck
          player2.addCards(cards);
          player2.addCard(player2Card);
          player2.addCard(player1Card);
        } else {
          // If the cards are equal, it's another tie and the cards are discarded
          cout << "It's another tie! The cards are discarded.\n";
        }
      }

      // Wait for the user to press enter to continue to the next round if autoplay is off
      cout << "\n==============================================\n";
      cout << "Press \"Enter\" to continue to the next round...\n";
      cout << "==============================================\n";
      if (autoPlay) {
        cout << "\n";
      } else {
        cin.ignore();
      }

      // Increment the round counter
      round++;
    }
  }
};

// Function that starts a new game
void startGame() {
  Game game;
  game.play(false, false);
}

// Function that starts a new game with autoplay on
void startAutoGame() {
  Game game;
  game.play(true, false);
}

// Function that generates statistics for a given number of games
void generateStatistics(int numberOfGames) {
  // Define variables to store the number of wins and ties
  int player1Wins = 0;
  int player2Wins = 0;
  int ties = 0;

  // Run the games
  for (int i = 0; i < numberOfGames; i++) {
    Game game;
    Winner winner = game.play(true, true);
    if (winner == Winner::PLAYER1) {
      player1Wins++;
    } else if (winner == Winner::PLAYER2) {
      player2Wins++;
    } else {
      ties++;
    }
    cout << "Game " << i + 1 << " complete.\n";
  }

  // Print the results
  cout << "\n===================================\n";
  cout << "Here are the results of " << numberOfGames << " games:\n";
  cout << "===================================\n\n";
  cout << "Player 1 wins: " << player1Wins << " (" << (double) player1Wins / numberOfGames * 100 << "%" << ")\n";
  cout << "Player 2 wins: " << player2Wins << " (" << (double) player2Wins / numberOfGames * 100 << "%" << ")\n";
  cout << "Ties: " << ties << " (" << (double) ties / numberOfGames * 100 << "%" << ")\n";
}

// Main function
int main() {
  while (true) {
    // Ask the user which mode they want to play
    cout << "=========\nMain menu\n=========\n\n";
    cout << "Main menu:\n";
    cout << "   1. Play a game\n";
    cout << "   2. Play a game (autoplay)\n";
    cout << "   3. Generate statistics\n";
    cout << "   0. Exit\n\n";
    cout << "Enter your choice:\n--> ";
    int mode;
    cin >> mode;
    cout << "\n";

    // Validate the user's input
    while (mode < 0 || mode > 3) {
      cout << "Invalid input. Please enter a number between 1 and 3: ";
      cin >> mode;
      cout << "\n";
    }

    // Start the game based on the user's choice
    switch (mode) {
      case 1:cout << "=========\nGame mode\n=========\n\n";
        // Workaround for "Enter" key triggering the next round on start
        cin.ignore();
        startGame();
        cout << "\n";
        break;
      case 2:cout << "====================\nGame mode (autoplay)\n====================\n\n";
        startAutoGame();
        cout << "\n";
        break;
      case 3:int numberOfGames;
        cout << "Enter the number of games you want to play:\n--> ";
        cin >> numberOfGames;
        cout << "\n===============\nStatistics mode\n===============\n\n";
        generateStatistics(numberOfGames);
        cout << "\n";
        break;
      case 0:return 0;
      default:break;
    }
  }
}
