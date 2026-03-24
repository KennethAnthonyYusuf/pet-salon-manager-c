# 🐾 Pet Salon Manager (C)

A command-line pet salon management system written in C using linked lists, dynamic memory allocation, and interactive commands.

---

## 🚀 Key Highlights

- Built a fully interactive **command-line management system**
- Implemented **linked list data structures** to manage salons and rooms
- Designed modular functions for **salon, room, and pet operations**
- Handled **dynamic memory allocation** safely using `malloc` and `free`
- Demonstrates strong understanding of **C programming and data structures**

---

## 📖 Overview

This project simulates a pet salon business where users can manage multiple salons, create rooms for different pet types, add pets, care for pets, track profit, and organise salon data through typed commands.

The system is fully interactive and demonstrates core concepts in low-level programming and data structures.

---

## ✨ Features

- Manage multiple salons using a linked list structure
- Add and organise pet rooms (cat, dog, rabbit, parrot)
- Insert rooms adjacent to similar pet types
- Add pets to available rooms with capacity limits
- Split rooms into two rooms
- Remove rooms and salons
- Navigate between salons
- Merge two salons into one
- Sort rooms alphabetically
- Track total pets cared for and salon profit
- Handle invalid input with clear error messages
- Free dynamically allocated memory properly

---

## 🛠️ Technologies Used

- **Language:** C  
- **Tools:** GCC, Command Line  

### Concepts Demonstrated

- Structs and enums  
- Singly linked lists  
- Dynamic memory allocation (`malloc`, `free`)  
- Input parsing (`scanf`)  
- String handling  
- Modular function design  
- Error handling  

---

## ▶️ How to Run

```bash
gcc pet_salon.c -o salon
./salon
```

---

## 📦 How to Use the Program

The program runs as an interactive command-line application. After starting the program, you can enter commands to manage salons, rooms, and pets.

Each command is a single character followed by required inputs.

---

### 🏗️ Salon Management

| Command | Description | Example |
|---------|-------------|---------|
| `c <salon_name> <base_cost>` | Create a new salon with a given name and base cost | `c salon2 15` |
| `>` | Move to the next salon | `>` |
| `<` | Move to the previous salon | `<` |
| `d` | Display details of all salons (profit, pets cared, etc.) | `d` |
| `q` | Delete the currently selected salon | `q` |
| `x <new_name> <salon1> <salon2>` | Merge two salons into a new salon | `x merged salon1 salon2` |

---

### 🐾 Room Management

| Command | Description | Example |
|---------|-------------|---------|
| `a <room_name> <pet_type>` | Add a new room to the current salon | `a room1 cat` |
| `i <room_name> <pet_type>` | Insert a room next to rooms of the same pet type | `i room2 dog` |
| `p` | Print all rooms in the current salon | `p` |
| `r <room_name>` | Remove a room from the salon | `r room1` |
| `o` | Sort rooms alphabetically by name | `o` |

---

### 🐶 Pet Management

| Command | Description | Example |
|---------|-------------|---------|
| `m <pet_type> <amount>` | Add pets of a specific type to available rooms | `m cat 5` |
| `h` | Fill all rooms to maximum capacity and display number of pets added | `h` |
| `s <room_name> <new_room_name>` | Split a room into two rooms | `s room1 room2` |
| `f <room_name> <amount>` | Care for pets (remove pets and generate profit) | `f room1 3` |

---

## 🧠 Technical Insights

- **Linked List Design**  
  Salons and rooms are implemented using linked lists, allowing dynamic insertion, deletion, and traversal.

- **Memory Management in C**  
  All data structures are dynamically allocated and properly freed, preventing memory leaks.

- **Command-Based Architecture**  
  The system parses user input and maps commands to specific functions, creating a modular and extensible design.

- **Data Organisation**  
  Rooms are grouped by pet types and can be sorted or rearranged efficiently.

---

## 💡 Why This Project Matters

This project demonstrates the ability to:

- build an interactive system using low-level C
- design and manipulate linked data structures
- handle memory safely and efficiently
- implement modular and maintainable code
- process user input and manage program state

It reflects strong foundations in **data structures, systems programming, and problem-solving**, which are valuable in software engineering roles.

---

## 📝 Notes

- Valid pet types: `cat`, `dog`, `rabbit`, `parrot`
- Each room has a maximum capacity of 10 pets
- Commands are case-sensitive
- The program runs continuously until terminated (`Ctrl + D`)

---

## 🚀 Author

**Kenneth Anthony Yusuf**  
Computer Science Student @ UNSW