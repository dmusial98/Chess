#ifndef PAWN_H
#define PAWN_H

#include "Chessboard.h"
#include "Square.h"
#include "Piece.h"
#include "definitions.h"
#include "Enums.h"
#include <SFML/Graphics.hpp>




class Pawn : public Piece {


public:
	Pawn(Color);
	~Pawn();

	bool correct_move(Square, Square, Square, Chessboard);
	bool is_it_pawn();
	

private:
	void set_sprite();
};


#endif