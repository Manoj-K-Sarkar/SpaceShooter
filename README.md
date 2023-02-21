# SpaceShooter
SFML CPP GAME

## Run Locally

Clone the project

```bash
  git clone https://github.com/Manoj-K-Sarkar/SpaceShooter.git
```

Go to the project directory

```bash
  cd SpaceShooter
```

Install dependencies

```bash
  sudo apt-get update
  sudo apt-get install libsfml-dev
```

Compile and Build

```bash
  g++ -c Bullet.cpp Enemy.cpp Game.cpp Player.cpp Main.cpp
  g++ Main.o Game.o Player.o Enemy.o Bullet.o -o main-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

Run

```bash
  ./main-app
```
