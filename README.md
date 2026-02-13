# Space Invaders - C Console Edition

A classic Space Invaders game built in C for the Windows console. This project features a user system, shop, level progression, and AI-controlled enemies.

## 🚀 Key Features

* User System: Secure Sign-up and Login with masked password entry.
* Dynamic Gameplay: Smooth movement and dual-sided shooting (Player & Enemies).
* AI Enemies: * Close-Range (Square): Tracks and attacks when within 1 cell distance.
    * Long-Range (Triangle): Keeps its distance and fires red bullets.
* In-Game Shop: Buy Health, Damage upgrades, and increased Bullet capacity using earned coins.
* Leveling System: Enemies get stronger and more numerous as you level up.
* Leaderboard: Displays the Top 10 players based on coins and levels reached.

## 🎮 Controls

| Key | Action |
| :--- | :--- |
| W, A, S, D | Move Player |
| SPACE | Shoot Bullets |
| B | Open Shop |
| ESC | Exit Menu |

## 🛠️ How to Compile and Run

1.  Open your terminal in the project folder.
2.  Compile the project using GCC:
   
bash
    gcc main.c game.c menu.c map.c elements.c -o run.exe
    
3.  Run the game:
   
bash
    ./run.exe
    

## 📋 File Structure

* main.c: Game loop and menu handling.
* game.c: Core logic (Movement, AI, Collisions).
* menu.c: Sign-up, Login, and Leaderboard logic.
* elements.h: Definitions of structs and shared variables (extern).
* users.txt: Database for storing player credentials.

## ⚠️ Requirements

* OS: Windows (Required for conio.h and windows.h).
* Font: For the best experience, set your console font to Consolas or Lucida Console.

---
Developed for University Project - 2026
