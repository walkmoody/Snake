gcc main.cpp menus.cpp game.cpp snake.cpp -o game.exe -O1 -Wall -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -lstdc++
.\game.exe