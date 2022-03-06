# Game Of Life

This is an implementation in `c++` of Conway's Game Of Life, using `OOP`, and a graphic interface made with the `olcPixelGameEngine` from @OneLoneCoder.

# How to use it

You can ust run the file `GameOfLife` if you are a GNU/Linux user. \
Else, you might compile the code yourself. \
If you've made changes and want to compile the code, you can run :
``` bash
g++ -o GameOfLife GameOfLife.cpp Visual.cpp -std=c++17 -lX11 -lGL -lpthread -lpng -lstdc++fs -O3 && ./GameOfLife
```

# Fonctions

In the `Visual.cpp`, you have the following options : 

- c : clear 
- r : random
- UP : go faster
- DOWN : go slower
- RIGHT : go way faster
- LEFT : go way slower
- s : save to file (test.txt)
- o : open file (test.txt)
- 0 : open patterns/gospers_gun.txt
- 1 : open patterns/demonoid.txt
- 2 : open patterns/wheel.txt
- SPACE : pause/play
- Clicking with the mouse : change a cell

In `main.cpp`, there is a basic implemetation of the `GameOfLife` class.

# License

The `olcPixelGameEngine` is published under the `OLC-3` license (see in the file itself). \
The rest of the code is published under the `GPL v3`.