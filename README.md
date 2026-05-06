# 🚗 Car Dodging Game (C++ + SFML)

A simple and fun Car Dodging Game developed using **C++** and **SFML**.  
The player controls a white car and must dodge incoming enemy cars while the game speed gradually increases over time.

---

# 📌 Features

- 🎮 Smooth player movement
- 🚗 Multiple enemy cars
- ⚡ Increasing game difficulty
- 🔊 Crash sound effects
- ⏸ Pause functionality
- 🔁 Restart system
- 🏆 Score tracking
- 🎯 Difficulty selection
- 🛣 Animated moving road
- 🎨 SFML graphics and textures

---

# 🖥 Technologies Used

- C++
- SFML (Simple and Fast Multimedia Library)

---

# 📂 Project Structure

```bash
Car Dodging Game/
│
├── Assets/
│   ├── WhiteCar.png
│   ├── RedCar1.png
│   ├── RedCar2.png
│   ├── YellowCar1.png
│   ├── YellowCar2.png
│   ├── YellowCar3.png
│   ├── crash.wav
│   └── DejaVuSans-Bold.ttf
│
├── main.cpp
├── highscore.txt
└── README.md
```

---

# 🎮 Controls

| Key | Action |
|------|---------|
| Left Arrow | Move Left |
| Right Arrow | Move Right |
| P | Pause Game |
| R | Restart Game |
| E | Easy Mode |
| M | Medium Mode |
| H | Hard Mode |

---

# 🎯 Difficulty Modes

## Easy
- Lower speed
- Slow enemy spawning

## Medium
- Moderate speed
- Faster enemy spawning

## Hard
- High speed
- Very fast enemy spawning

---

# 🧠 Game Logic

The game includes:

- Random enemy spawning
- Lane-based movement
- Collision detection
- Dynamic speed increase
- Delta-time based movement for smooth gameplay

---

# 🔊 Audio

The game uses SFML Audio module for crash sound effects.

---

# 🛠 How to Run

## Requirements

- C++ Compiler (g++)
- SFML Library

---

## Step 1: Install SFML

Download SFML from:

https://www.sfml-dev.org/download.php

Install the version matching your compiler.

---

## Step 2: Open Terminal / Git Bash

Navigate to the project folder:

```bash
cd /f/"Car Dodging Game"
```

---

## Step 3: Compile the Game

Run the following command:

```bash
g++ main.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

---

## Step 4: Run the Game

```bash
./game
```

or run:

```bash
game.exe
```

---

# Important Note

Make sure the `Assets` folder remains inside the project directory, otherwise textures, fonts, and sounds will not load properly.

---

# 📸 Screenshots

Add gameplay screenshots here later.

---

# 🚀 Future Improvements

- Main menu UI
- High score saving system
- More enemy vehicles
- Background music
- Mobile version
- Multiplayer support
- Better animations

---

# 👨‍💻 Author

Ayushman Sahoo

---

# ⭐ GitHub Repository

If you like this project, give it a star ⭐
