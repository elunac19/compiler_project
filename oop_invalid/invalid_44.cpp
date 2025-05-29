#include <iostream>
#include <string>

struct Song {
    std::string title;
    int duration; // in seconds

    void setTitle(std::string t) {
        title = t;
    }

    std::string getTitle() {
        return title;
    }

    void setDuration(int d) {
        duration = d;
    }

    int getDuration() {
        return duration;
    }

    void play() {
        std::cout << "Playing " << title << " for " << duration << " seconds." << std::endl;
    }
};

int main() {
    Song mySong;
    mySong.setTitle("Bohemian Rhapsody");
    mySong.setDuration(44);
    mySong.play();

    return 0;
}