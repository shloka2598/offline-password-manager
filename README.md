# Offline Password Manager (C++)

A simple, secure, and offline command-line password manager built in C++.  
Allows users to sign up with a master password and store their credentials locally in an encrypted vault.

---

## Features

-  **User Signup & Login**

  - Secure authentication using a master password
  - All passwords are hashed before storage (XOR-based in v0.1)

-  **Per-User Vault System**

  - Each user has their own vault file: `vault_<username>.db`
  - Files are stored locally in `data/` (and ignored from Git)

-  **Add New Entries**

  - Store site name, username, password, and optional notes
  - Passwords are encrypted before being saved

-  **View Entries**

  - See all stored entries (with decrypted password display)

-  **Search Entries**

  - Find saved credentials by website name

-  **Update Existing Entries**

  - Modify stored credentials (site, user, password, notes)

-  **Delete Entries**

  - Remove entries from vault cleanly

-  **Organized Codebase**
  - Separated into modules (`auth`, `vault`, `utils`)
  - Header files and shell build script included

---

##  Project Structure

```markdown
password-manager/
├── src/ # C++ source files
│ ├── main.cpp
│ ├── auth.cpp
│ ├── vault.cpp
│ └── utils.cpp
├── include/ # Header files
│ ├── auth.hpp
│ ├── vault.hpp
│ └── utils.hpp
├── data/ # Runtime files (vaults) (git-ignored)
│ └── .gitkeep
├── build/ # Compiled binary output (git-ignored)
│ └── password-manager
├── build.sh # Simple build script
├── .gitignore # Files/folders excluded from Git
└── README.md
```

---

##  Getting Started

###  Build (Linux/macOS)

```bash
chmod +x build.sh
./build.sh
```

 Run

```bash
./build/password-manager
```

###  Notes

XOR encryption is used for simplicity (not secure in production)

In future versions: switch to AES (Crypto++) + stronger password hashing (e.g., SHA-256 or bcrypt)

This is an evolving project: clean commits coming as features are added

###  Status

  MVP complete  
 Ongoing development (CLI polish, stronger encryption, etc.)  
 Focused on clarity, modularity, and security principles

## Author

Shloka Jain

Built for learning, practice, and showcasing real-world C++ applications
Thapar University '29 | Mayo College Alumnus

## License

MIT License — feel free to fork, improve, or contribute.

---
