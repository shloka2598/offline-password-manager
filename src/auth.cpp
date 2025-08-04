#include "auth.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

const std::string USERS_DB = "data/users.db";

bool usernameExists(const std::string &username) {
  std::ifstream file(USERS_DB);
  std::string line;

  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string storedUsername;
    std::getline(ss, storedUsername, ':');

    if (storedUsername == username)
      return true;
  }
  return false;
}

void signup() {
  std::string username, password;

  std::cout << "Enter new username: ";
  std::cin >> username;

  if (usernameExists(username)) {
    std::cout << "Username already exists.\n";
    return;
  }

  std::cout << "Enter password: ";
  std::cin >> password;

  std::string hashed = hashPassword(password);

  std::ofstream file(USERS_DB, std::ios::app);
  file << username << ":" << hashed << "\n";

  std::cout << "Signup successful!\n";
}

bool login() {
  std::string username, password;
  std::cout << "Enter username: ";
  std::cin >> username;
  std::cout << "Enter password: ";
  std::cin >> password;

  std::string hashed = hashPassword(password);

  std::ifstream file(USERS_DB);
  std::string line;
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string storedUsername, storedHash;
    std::getline(ss, storedUsername, ':');
    std::getline(ss, storedHash);

    if (storedUsername == username && storedHash == hashed)
      return true;
  }

  return false;
}
