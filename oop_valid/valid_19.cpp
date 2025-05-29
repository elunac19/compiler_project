#include<iostream>
#include<string>

class Duration {
private:
    int minutes;
    int seconds;

public:
    Duration(int m, int s) : minutes(m), seconds(s) {}

    int getMinutes() const {
        return this->minutes;
    }

    int getSeconds() const {
        return this->seconds;
    }

    void printDuration() const {
        std::cout << minutes << ":" << ((seconds < 10) ? "0" : "") << seconds;
    }
};

class Song {
private:
    std::string title;
    std::string artist;
    Duration duration;

public:
    Song(std::string t, std::string a, int m, int s) : title(t), artist(a), duration(m, s) {}

    void printSong() const {
        std::cout << "Title: " << title << "\nArtist: " << artist 
                  << "\nDuration: "; duration.printDuration(); std::cout << "\n";
    }
};

int main() {
    Song mySong("Imagine", "John Lennon", 3, 01);
    mySong.printSong();
    return 0;
}