#include<iostream>

class Button {
private:
  std::string function;
  
public:
  Button(std::string function){
    this->function = function;
  }
  
  std::string getFunction(){
    return function;
  }
};

class RemoteControl {
private:
  Button *buttons[24];
  
public:
  RemoteControl() {
    for(int i = 0; i < 24; i++) {
      std::string function = "Function " + std::to_string(i+1);
      buttons[i] = new Button(function);
    }
  }
  
  std::string pressButton(int index) {
    if (index < 0 || index > 23) {
      return "Invalid button index";
    }
    return buttons[index]->getFunction();
  }
  
  ~RemoteControl() {
    for(int i = 0; i < 24; i++) {
      delete buttons[i];
    }
  }
};

int main() {
  RemoteControl remote;
  std::cout << remote.pressButton(5) << std::endl;
  std::cout << remote.pressButton(23) << std::endl;
  return 0;
}