
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Chessboard.h"
#include "Position.h"
#include "Square.h"



class Game {
	Chessboard chessboard;
	sf::RenderWindow window;
	 
	Position active_square = Position('e', '4');

public:
	Game();
		//constructor
	~Game();
		//destructor			

	void play();

private:
	void control(Position&, sf::Event, sf::RenderWindow &win);

};

#endif