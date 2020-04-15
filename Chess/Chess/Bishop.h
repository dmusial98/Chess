
#ifndef BISHOP_H
#define BISHOP_H



#include <SFML/Graphics.hpp>
#include "Chessboard.h"
#include "Position.h"
#include "Square.h"
#include "Piece.h"
#include "King.h"
#include "Queen.h"
//#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Pawn.h"
#include "definitions.h"
#include "Enums.h"
#include "Game.h"




class Bishop : public Piece{

public:
	Bishop(Color);
	~Bishop();

	bool correct_move(Square mv_fr, Square mv_to, Square /*lat_ene_mv = Square()*/, Chessboard /*board = Chessboard()*/);

private:
	void set_sprite();
};

#endif