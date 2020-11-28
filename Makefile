main:
	g++ -o game main.cpp Game.cpp Button.cpp Nivel.cpp Coordinate.cpp Cholo.cpp Kevin.cpp Bayron.cpp Character.cpp Match.cpp Brayan.cpp Principal.cpp -lSDL2_image -lSDL2 -lSDL2_ttf
	@echo "Compiled succesfully. Run ./game"

