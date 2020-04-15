
#ifndef SQUARE_H
#define SQUARE_H


#include "Position.h"

#include "Piece.h"
#include "Enums.h"

class Square {

	Position position;
	Piece *piece_ptr;

public:
	Square(Position);
	Square();
	~Square();

	char get_number();
	char get_letter();
	Color get_color();
	void set_position(char, char);
	void set_choosen(bool);
	bool get_choosen();
	int get_moves_count();
	void set_piece(Piece* pc = nullptr, bool erase = false);
	Piece* get_piece();
	void display(sf::RenderWindow&);
	bool is_it_king();
	bool is_it_pawn();
	void delete_piece();

};

#endif