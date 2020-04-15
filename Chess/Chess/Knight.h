
#ifndef KNIGHT_H
#define KNIGHT_H


#include "Chessboard.h"
#include "Square.h"
#include "Piece.h"
#include "definitions.h"
#include "Enums.h"
#include <SFML/Graphics.hpp>




class Knight : public Piece {

public:
	Knight(Color);
	~Knight();

	bool correct_move(Square, Square, Square /*last_ene_mv = Square()*/, Chessboard /*board = Chessboard()*/);

private:
	void set_sprite();
};


#endif