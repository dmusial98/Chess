
#ifndef QUEEN_H
#define QUEEN_H


#include "Chessboard.h"
#include "Square.h"
#include "Piece.h"
#include "definitions.h"
#include "Enums.h"
#include <SFML/Graphics.hpp>




class Queen : public Piece {


public:
	Queen(Color);

	~Queen();


	bool correct_move(Square, Square, Square, Chessboard);


private:
	void set_sprite();
};

#endif