# use "make" command in cmd to run
all:
	g++ -ISDL\include\SDL2  -LSDL\lib -o Brick_game src\\*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf 