
#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
#include "definitions.h"
#include "Enums.h"
#include "Square.h"
#include "Chessboard.h"







class Piece {

protected:
	Color color;
	int moves_count;
	bool choosen;
	sf::Texture texture;
	sf::Sprite sprite;

public:

	Color get_color();
	void display(sf::RenderWindow &window, Position position);
	void set_choosen(bool);
	bool get_choosen();
	int get_moves_count();

	//virtual functions
	virtual bool correct_move(Square, Square, Square, Chessboard); //= 0;
	virtual bool is_it_king() { return false; }; //czy dawaæ funkcja() = 0; ??? 
	virtual bool is_it_pawn() { return false; };
	

protected:
	void display_rec(sf::RenderWindow&, Position pos);
	bool first_cond(Square);
	bool empty_sq_rook(Orientation, int, Square, Chessboard);
	bool empty_sq_bishop(int, int, Square, Chessboard);
	

};

#endif