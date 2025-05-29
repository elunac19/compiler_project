#include <iostream>
#include <string>
#include <vector>

struct Contact {
  std::string name;
  std::string phone;
};

struct Agenda {
  std::vector<Contact> contacts;

  void addContact(std::string name, std::string phone) {
    Contact newContact;
    newContact.name = name;
    newContact.phone = phone;
    contacts.push_back(newContact);
  }

  void printContacts() {
    for (int i = 0; i < contacts.size(); i++) {
      std::cout << "Contact " << i+1 << ": " << contacts[i].name << ", " << contacts[i].phone << std::endl;
    }
  }
};

int main() {
  Agenda agenda;

  agenda.addContact("John Doe", "123-456-7890");
  agenda.addContact("Jane Doe", "098-765-4321");

  agenda.printContacts();

  return 0;
}