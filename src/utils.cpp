
#include <string>

std::string hashPassword(const std::string &password) {
  std::string hashed = password;
  char key = 'K'; // basic XOR key
  for (char &c : hashed)
    c ^= key;
  return hashed;
}
