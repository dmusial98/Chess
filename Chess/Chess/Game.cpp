#include "Game.h"

Game::Game() {
	window.create(sf::VideoMode(756, 756), "Chess");
}

Game::~Game() {

}

void Game::play() {
	while (window.isOpen())  //main loop
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				control(active_square, event, window);
			}
			if (event.type == sf::Event::Closed)
				window.close();
		}
		chessboard.display(window, active_square);
	}
}

void Game::control(Position &act_sq, sf::Event event, sf::RenderWindow &win) {

		if (event.key.code == sf::Keyboard::Up) {
			if (act_sq.get_number() == '1')
				act_sq.set_number('8');   // move to up border
			else
				act_sq.set_number(act_sq.get_number() - 1);		// move down
		}
		else if (event.key.code == sf::Keyboard::Left) {
			if (act_sq.get_letter() == 'a')
				act_sq.set_letter('h');   // move to right border
			else
				act_sq.set_letter(act_sq.get_letter() - 1);		// move left
		}
		else if (event.key.code == sf::Keyboard::Right) {
			if (act_sq.get_letter() == 'h')
				act_sq.set_letter('a');   // move to left border
			else
				act_sq.set_letter(act_sq.get_letter() + 1);		// move right
		}
		else if (event.key.code == sf::Keyboard::Down) {
			if (act_sq.get_number() == '8')
				act_sq.set_number('1');   // move to down border
			else
				act_sq.set_number(act_sq.get_number() + 1);		// move up
		}
		else if (event.key.code == sf::Keyboard::Escape)
		{
			win.close();
		}
		else if (event.key.code == sf::Keyboard::Enter) {
			if(chessboard.get_choosen(act_sq))
				chessboard.set_choosen(act_sq, false);
			else if(!chessboard.get_choosen(act_sq))
				chessboard.set_choosen(act_sq, true);
		}
}