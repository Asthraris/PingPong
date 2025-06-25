# 🏓 2D Ping Pong Game (Raylib)

![Gameplay Preview](./pingdemo.gif) <!-- Replace with your actual GIF path -->

A fast, minimalistic, and addictive 2D Ping Pong game built using the lightweight C-based graphics library **Raylib**. This game features a responsive game loop with start, pause, and restart mechanics, a high-accuracy AI opponent, and a smooth 120 FPS capped experience to reduce system load.

---

## 🎮 Features

- ✅ Full Game Loop (Start Menu → Gameplay → Pause/Restart)
- 🧠 Intelligent AI Opponent (~97% win accuracy — good luck beating it!)
- 🕹️ Player 1 Controls:  
  - `W`: Move Up  
  - `S`: Move Down  
- 🔁 Restart anytime from the pause menu
- ⏱️ FPS capped at **120** to reduce CPU/GPU overhead

---

## 🌐 Future Roadmap

- 👥 **Multiplayer mode** (local and maybe networked)
- ✨ **Special powerups** (ball speed burst, paddle freeze, etc.)
- 🧠 **Smarter AI** with difficulty levels and adaptive behavior
- 🔄 **Switch sides** (allowing players to play from either end)
- 🎨 Visual polish and sound effects

---

## ⚙️ Why Raylib?

Raylib is a **simple and portable C library for programming games and multimedia applications**, focused on learning and lightweight development.

### Advantages of Raylib:

- 💡 Beginner-friendly with clean API
- 🧱 Built-in support for windowing, input, 2D rendering, and audio
- 🚀 Extremely fast to compile and lightweight runtime
- 📦 Zero external dependencies required

> Perfect for low-level graphics experimentation, game prototypes, or performance-constrained environments.

Learn more about Raylib: [https://www.raylib.com](https://www.raylib.com)

---

## 📦 Build & Run

### Requirements:
- C compiler (GCC / Clang / MSVC)
- [Raylib](https://github.com/raysan5/raylib) installed (or compiled from source)

### Compile (example with GCC on Unix):
```bash
gcc main.c -o pingpong -lraylib -lm -ldl -lpthread -lGL -lrt -lX11
./pingpong
