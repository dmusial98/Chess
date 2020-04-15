
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <SFML/Graphics.hpp>
#include "Position.h"
#include "Square.h"
#include "Piece.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Pawn.h"




class Chessboard {
	Square chessboard[8][8];
	sf::Texture texture;
	sf::Sprite sprite;
	struct Pieces {

		King *wh_king = new King(white);
		King *bl_king = new King(black);
		Queen *wh_queen = new Queen(white);
		Queen *bl_queen = new Queen(black);
		Bishop *wh_bishop1 = new Bishop(white);
		Bishop *wh_bishop2 = new Bishop(white);
		Bishop *bl_bishop1 = new Bishop(black);
		Bishop *bl_bishop2 = new Bishop(black);
		Knight *wh_knight1 = new Knight(white);
		Knight *wh_knight2 = new Knight(white);
		Knight *bl_knight1 = new Knight(black);
		Knight *bl_knight2 = new Knight(black);
		Rook *wh_rook1 = new Rook(white);
		Rook *wh_rook2 = new Rook(white);
		Rook *bl_rook1 = new Rook(black);
		Rook *bl_rook2 = new Rook(black);
		Pawn *wh_pawn1 = new Pawn(white);
		Pawn *wh_pawn2 = new Pawn(white);
		Pawn *wh_pawn3 = new Pawn(white);
		Pawn *wh_pawn4 = new Pawn(white);
		Pawn *wh_pawn5 = new Pawn(white);
		Pawn *wh_pawn6 = new Pawn(white);
		Pawn *wh_pawn7 = new Pawn(white);
		Pawn *wh_pawn8 = new Pawn(white);
		Pawn *bl_pawn1 = new Pawn(black);
		Pawn *bl_pawn2 = new Pawn(black);
		Pawn *bl_pawn3 = new Pawn(black);
		Pawn *bl_pawn4 = new Pawn(black);
		Pawn *bl_pawn5 = new Pawn(black);
		Pawn *bl_pawn6 = new Pawn(black);
		Pawn *bl_pawn7 = new Pawn(black);
		Pawn *bl_pawn8 = new Pawn(black);
	} pieces;


public:
	Chessboard();
	~Chessboard();

	bool is_checkmate(Color king_color);
	bool king_threatened(King *king);
	void delete_piece(Piece *pc);
	void display(sf::RenderWindow&, Position&);
	void set_choosen(Position, bool);
	bool get_choosen(Position);
	Square* get_sq(char, char);

private:
	void display_rect(sf::RenderWindow&, Position&);
	void fill_board();
	void set_sprite();
	//void prep_rect();

};

#endif