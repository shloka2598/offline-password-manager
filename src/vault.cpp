#include "vault.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::string vaultPath(const std::string &username) {
  return "data/vault_" + username + ".db";
}

void addEntry(const std::string &username) {
  std::string site, uname, password, notes;

  std::cout << "Site: ";
  std::cin >> site;
  std::cout << "Username: ";
  std::cin >> uname;
  std::cout << "Password: ";
  std::cin >> password;
  std::cin.ignore();
  std::cout << "Notes (optional): ";
  std::getline(std::cin, notes);

  std::string encrypted = hashPassword(password); // XOR for now

  std::ofstream file(vaultPath(username), std::ios::app);
  file << site << "|" << uname << "|" << encrypted << "|" << notes << "\n";

  std::cout << "✅ Entry saved!\n";
}

void viewEntries(const std::string &username) {
  std::ifstream file(vaultPath(username));
  std::string line;

  if (!file.is_open()) {
    std::cout << "No entries found.\n";
    return;
  }

  std::cout << "\n--- Saved Entries ---\n";
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string site, uname, encryptedPass, notes;
    std::getline(ss, site, '|');
    std::getline(ss, uname, '|');
    std::getline(ss, encryptedPass, '|');
    std::getline(ss, notes);

    std::string decrypted = hashPassword(encryptedPass); // XOR decrypt

    std::cout << "Site: " << site << "\n"
              << "Username: " << uname << "\n"
              << "Password: " << decrypted << "\n"
              << "Notes: " << notes << "\n"
              << "-----------------------------\n";
  }
}

void deleteEntry(const std::string &username) {
  std::string keyword;
  std::cout << "Enter site to delete: ";
  std::cin >> keyword;

  std::ifstream file(vaultPath(username));
  std::ofstream temp("data/temp.db");
  std::string line;
  bool deleted = false;

  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string site;
    std::getline(ss, site, '|');

    if (site == keyword) {
      deleted = true;
      continue; // skip writing this line
    }
    temp << line << "\n";
  }

  file.close();
  temp.close();
  std::remove(vaultPath(username).c_str());
  std::rename("data/temp.db", vaultPath(username).c_str());

  if (deleted)
    std::cout << "✅ Entry deleted.\n";
  else
    std::cout << "❌ No entry found for: " << keyword << "\n";
}

void searchEntry(const std::string &username) {
  std::string keyword;
  std::cout << "Enter site to search: ";
  std::cin >> keyword;

  std::ifstream file(vaultPath(username));
  std::string line;
  bool found = false;

  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string site, uname, encryptedPass, notes;
    std::getline(ss, site, '|');
    std::getline(ss, uname, '|');
    std::getline(ss, encryptedPass, '|');
    std::getline(ss, notes);

    if (site == keyword) {
      std::cout << "\n--- Found Entry ---\n";
      std::cout << "Site: " << site << "\n"
                << "Username: " << uname << "\n"
                << "Password: " << hashPassword(encryptedPass) << "\n"
                << "Notes: " << notes << "\n";
      found = true;
      break;
    }
  }

  if (!found)
    std::cout << "No entry found for site: " << keyword << "\n";
}

void updateEntry(const std::string &username) {
  std::string keyword;
  std::cout << "Enter site to update: ";
  std::cin >> keyword;

  std::ifstream file(vaultPath(username));
  std::ofstream temp("data/temp.db");
  std::string line;
  bool updated = false;

  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string site, uname, encryptedPass, notes;
    std::getline(ss, site, '|');
    std::getline(ss, uname, '|');
    std::getline(ss, encryptedPass, '|');
    std::getline(ss, notes);

    if (site == keyword) {
      std::cout << "Enter new username: ";
      std::cin >> uname;
      std::cout << "Enter new password: ";
      std::cin >> encryptedPass;
      std::cin.ignore();
      std::cout << "Enter new notes: ";
      std::getline(std::cin, notes);
      encryptedPass = hashPassword(encryptedPass); // encrypt again
      updated = true;
    }

    temp << site << "|" << uname << "|" << encryptedPass << "|" << notes << "\n";
  }

  file.close();
  temp.close();
  std::remove(vaultPath(username).c_str());
  std::rename("data/temp.db", vaultPath(username).c_str());

  if (updated)
    std::cout << "✅ Entry updated.\n";
  else
    std::cout << "❌ No entry found for: " << keyword << "\n";
}

void vaultMenu(const std::string &username) {
  int choice;
  while (true) {
    std::cout << "\n--- Vault Menu: " << username << " ---\n";
    std::cout << "1. Add Entry\n";
    std::cout << "2. View All Entries\n";
    std::cout << "3. Search Entry\n";
    std::cout << "4. Delete Entry\n";
    std::cout << "5. Update Entry\n";
    std::cout << "6. Logout\n";
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice) {
    case 1:
      addEntry(username);
      break;
    case 2:
      viewEntries(username);
      break;
    case 3:
      searchEntry(username);
      break;
    case 4:
      deleteEntry(username);
      break;
    case 5:
      updateEntry(username);
      break;
    case 6:
      std::cout << "Logging out...\n";
      return;
    default:
      std::cout << "Invalid choice.\n";
    }
  }
}
