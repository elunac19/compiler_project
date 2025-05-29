#include<iostream>
#include<string>

class Player {
private:
    std::string name;
    int points;
public:
    Player(std::string n) : name(n), points(0) {}

    std::string getName() { return name; }
    void addPoints(int p) { points += p; }
    int getPoints() { return points; }
};

class Game {
private:
    Player *player1;
    Player *player2;
public:
    Game(std::string name1, std::string name2) {
        player1 = new Player(name1);
        player2 = new Player(name2);
    }

    ~Game() {
        delete player1;
        delete player2;
    }

    void addPointsToPlayer1(int points) {
        player1->addPoints(points);
    }

    void addPointsToPlayer2(int points) {
        player2->addPoints(points);
    }

    void printScores() {
        std::cout << player1->getName() << " has " << player1->getPoints() << " points.\n";
        std::cout << player2->getName() << " has " << player2->getPoints() << " points.\n";
    }
};

int main() {
    Game game("Alice", "Bob");
    game.addPointsToPlayer1(10);
    game.addPointsToPlayer2(15);
    game.printScores();
    return 0;
}