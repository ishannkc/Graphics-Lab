# GraphicsLab – OpenGL Lab Exercises

Short collection of OpenGL programs for the Computer Graphics Course Lab Assessment. The repo contains self‑contained labs written in C++ using FreeGLUT on Windows. Each lab compiles to a simple executable that opens a window and renders the corresponding output.

## Contents
- `Lab1`: Draw your name with filled polygons (uses GLUT primitives)
- `Lab2`:
	- `lab2a`: DDA line drawing
	- `lab2b`: Bresenham line drawing
	- `lab2c`: Midpoint circle drawing
	- `lab2d`: Line graph using DDA
	- `lab2e`: Simple pie chart

## Prerequisites (Windows)
- MSYS2 with MinGW-w64 toolchain
- FreeGLUT from MSYS2

Install via MSYS2 MINGW64 terminal:

```bash
pacman -S --needed base-devel mingw-w64-x86_64-toolchain
pacman -S mingw-w64-x86_64-freeglut
```

## Build & Run (quick)
Open a PowerShell in a lab folder and build with g++ (paths assume MSYS2 at `C:\msys64`):

```powershell
# Example: Lab2 DDA
cd Lab2
g++ -g -std=c++17 src\lab2a.cpp -o bin\lab2a.exe -IC:\msys64\mingw64\include -LC:\msys64\mingw64\lib -lfreeglut -lopengl32 -lglu32 -lm
.\u005cbin\lab2a.exe
```

Repeat by swapping the source/output names (e.g., `lab2b.cpp` → `lab2b.exe`, etc.). For Lab1:

```powershell
cd Lab1
g++ -g -std=c++17 src\lab1.cpp -o bin\lab1.exe -IC:\msys64\mingw64\include -LC:\msys64\mingw64\lib -lfreeglut -lopengl32 -lglu32 -lm
.\u005cbin\lab1.exe
```

## VS Code Tasks (optional)
From the repo root, use Ctrl+Shift+P → “Tasks: Run Task” and choose one of:
- Build/Run Lab2a/Lab2b/Lab2c/Lab2d/Lab2e

## Notes
- These programs are minimal and focus on the core graphics algorithms.
- Intended for the Computer Graphics course Lab Assessment.