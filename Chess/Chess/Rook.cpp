#include "Rook.h"

Rook::Rook(Color col) {
	color = { col };
	moves_count = { 0 };
	choosen = { false };

	set_sprite();
}

Rook::~Rook()
{
}

bool Rook::correct_move(Square mv_fr, Square mv_to, Square last_ene_mv, Chessboard board) {
	//if (!first_cond(mv_to)) return false;
	////verify does Rook move on square on which lie piece in the same colour

	//if (mv_to.get_letter() == mv_fr.get_letter() || mv_to.get_number() == mv_fr.get_number())
	//{
	//	if (mv_to.get_letter() == mv_fr.get_letter() && mv_to.get_number() == mv_fr.get_number()) return false;
	//	//if Rook haven't moved 

	//	if (!empty_sq_rook(horizontally, mv_to.get_letter() - mv_fr.get_letter(), mv_fr, board)) return false;
	//	if (!empty_sq_rook(upright, mv_to.get_number() - mv_fr.get_number(), mv_fr, board)) return false;
	//	//chceking are empty squares between square starting and target place for Rook
	//	return true;
	//}
	return false;
}

void Rook::set_sprite() {
	if (!texture.loadFromFile("figures.png")) //loading texture
	{
		//here will be message about wrong loading from file
	}
	sprite.setTexture(texture);


	//setting rectangle sprite up
	if (color == white)
		sprite.setTextureRect(sf::IntRect(ZERO, HEIGHT_PIECE, WIDTH_PIECE, HEIGHT_PIECE));
	else sprite.setTextureRect(sf::IntRect(ZERO, ZERO, WIDTH_PIECE, HEIGHT_PIECE));

	sprite.setScale(1.45f, 1.45f);
}