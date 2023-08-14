main:
	g++ -o game src/main.cpp src/gui/Color.cpp src/game/Game.cpp src/gui/Button.cpp src/game/Nivel.cpp src/game/Coordinate.cpp src/characters/Cholo.cpp src/characters/Kevin.cpp src/characters/Bayron.cpp src/characters/Character.cpp src/game/Match.cpp src/characters/Brayan.cpp src/characters/Principal.cpp -lSDL2_image -lSDL2 -lSDL2_ttf
	@echo "Compiled succesfully. Run ./game"

