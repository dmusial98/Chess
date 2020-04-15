
#ifndef KING_H
#define KING_H


#include "Chessboard.h"
#include "Square.h"
#include "Piece.h"
#include "definitions.h"
#include "Enums.h"
#include <SFML/Graphics.hpp>




class King : public Piece {  //król niech sprawdza czy jest zagro¿ony


public:
	King(Color);
	~King();

	bool is_it_king();
	bool correct_move(Square, Square, Square /*last_ene_mv = Square()*/ , Chessboard /*board = Chessboard()*/);
	bool is_threatened();

private:
	void set_sprite();
};

#endif