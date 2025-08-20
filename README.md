# Tic Tac Toe in C++ (with BGI Graphics + Minimax AI)  

![C++](https://img.shields.io/badge/language-C++-blue.svg)  
![Graphics](https://img.shields.io/badge/graphics-BGI-lightgrey.svg)  
![AI](https://img.shields.io/badge/AI-Minimax-green.svg)  
![Status](https://img.shields.io/badge/status-Completed-brightgreen.svg)  

🎮 Tic Tac Toe in C++ (with BGI Graphics)

A graphical implementation of Tic Tac Toe built in C++ using the BGI graphics library on Dev-C++ (32-bit).

This project showcases my progress in learning C++ fundamentals, graphics programming, and basic AI logic.

✨ Features

3x3 Board, neatly centered on a 1920x1080 window.

Two Game Modes:

👤 Player vs Player (PvP) with custom name input inside the graphics window.

🤖 Player vs AI (PvAI) featuring a basic computer opponent.

Retro BGI Graphics for a classic look and feel.

🚀 How to Run

**Put all files in same folder.**

**MAKE SURE TO CREATE IT AS A PROJECT IN DEV-C++.**

Install Dev-C++ 5.11 (32-bit compiler) or any compiler that supports graphics.h (WinBGI).

Clone this repository: git clone https://github.com/yourusername/tic-tac-toe-bgi.git.

Open the project in Dev-C++.

**Project Settings**
1. goto project settings.
2. Then Parameters --> Linker.
3. Add these linkers:
-lbgi

-lgdi32

-lcomdlg32

-luuid

-loleaut32

-lole32

4.Click OK.


Compile and run the game.

**Structure**

/Tic Tac Toe
 ├── main.cpp             # Game source code
 
 ├── tic tac toe.dev      # Project File (open this to run)
 
 ├── tic tac toe.layout   # Project's Layout
 
 ├── graphics.h           # Required BGI graphics header
 
 ├── winbgim.h            # Additional graphics dependency
 
 ├── libbgi.a             # BGI Graphics library
 
 └── README.md            # Project documentation
 

 **📖 Learning Outcomes**

Strengthened C++ basics: arrays, functions, structs, file handling.

Applied graphics programming concepts using graphics.h.

Gained experience with game logic and basic AI implementation.

