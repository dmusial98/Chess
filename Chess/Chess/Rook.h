
#ifndef ROOK_H
#define ROOK_H



#include "Chessboard.h"
#include "Square.h"
#include "Piece.h"
#include "definitions.h"
#include "Enums.h"
#include <SFML/Graphics.hpp>




class Rook : public Piece {


public:
	Rook(Color);
	~Rook();
	bool correct_move(Square, Square, Square /*last_ene_mv = Square()*/, Chessboard /*board = Chessboard()*/);

private:
	void set_sprite();
};

#endif