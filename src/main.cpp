#include "auth.h"
#include "vault.h"
#include <iostream>

int main() {
  int choice;

  while (true) {
    std::cout << "\n--- Password Manager ---\n";
    std::cout << "1. Sign Up\n2. Login\n3. Exit\nChoice: ";
    std::cin >> choice;

    switch (choice) {
    case 1:
      signup();
      break;
    case 2:
      if (login()) {
        std::cout << "Login successful!\n";
        std::string username;
        std::cout << "Enter your username again to load your vault: ";
        std::cin >> username;
        vaultMenu(username);
      } else {
        std::cout << "Login failed.\n";
      }
      break;
    case 3:
      std::cout << "Exiting...\n";
      return 0;
    default:
      std::cout << "Invalid choice. Try again.\n";
    }
  }

  return 0;
}
