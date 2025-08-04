#include "auth.h"
#include "vault.h"
#include <iostream>

int main() {
  int choice;

  while (true) {
    std::cout << "\n=============================\n";
    std::cout << "  OFFLINE PASSWORD MANAGER\n";
    std::cout << "=============================\n";
    std::cout << "1. Add new entry\n";
    std::cout << "2. View entries\n";
    std::cout << "3. Search entry\n";
    std::cout << "4. Update entry\n";
    std::cout << "5. Delete entry\n";
    std::cout << "6. Logout\n";
    std::cout << "=============================\n";
    std::cout << "Choice: ";
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
