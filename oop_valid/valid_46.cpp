#include<iostream>
using namespace std;

class Volume {
    private:
        int level;
    public:
        Volume(int l) {
            level = l;
        }
        int getLevel() {
            return level;
        }
        void setLevel(int l) {
            level = l;
        }
};

class Speaker {
    private:
        string name;
        Volume *volume;
    public:
        Speaker(string n, int l) {
            name = n;
            volume = new Volume(l);
        }
        void increaseVolume(int l) {
            int currentLevel = volume->getLevel();
            volume->setLevel(currentLevel + l);
        }
        void decreaseVolume(int l) {
            int currentLevel = volume->getLevel();
            volume->setLevel(currentLevel - l);
        }
        void printStatus() {
            cout << "Speaker: " << name << ", Volume: " << volume->getLevel() << endl;
        }
};

int main() {
    Speaker mySpeaker("JBL", 5);
    mySpeaker.printStatus();
    mySpeaker.increaseVolume(2);
    mySpeaker.printStatus();
    mySpeaker.decreaseVolume(3);
    mySpeaker.printStatus();

    return 0;
}