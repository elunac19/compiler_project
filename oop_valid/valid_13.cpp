#include <iostream>
#include <string>

class Player{
private:
    std::string name;
    int points;
public:
    Player(std::string name){
        this->name = name;
        points = 0;
    }
    std::string getName(){
        return name;
    }
    int getPoints(){
        return points;
    }
    void addPoints(int newPoints){
        points += newPoints;
    }
};

class Game{
private:
    Player* player1;
    Player* player2;
public:
    Game(Player* p1, Player* p2){
        player1 = p1;
        player2 = p2;
    }
    void scorePoint(Player* p){
        p->addPoints(1);
        std::cout<< p->getName() << " scores a point!\n";
    }
    void printScore(){
        std::cout << player1->getName() << ": " << player1->getPoints() << "\n";
        std::cout << player2->getName() << ": " << player2->getPoints() << "\n";
    }
};

int main() {
    Player* john = new Player("John");
    Player* steve = new Player("Steve");
    Game* game = new Game(john, steve);
    game->scorePoint(john);
    game->scorePoint(steve);
    game->scorePoint(john);
    game->printScore();
    delete john;
    delete steve;
    delete game;
    return 0;
}