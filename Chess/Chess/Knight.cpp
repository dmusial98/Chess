#include "Knight.h"

Knight::Knight(Color col) {
	color = { col };
	moves_count = { 0 }; 
	choosen = { false };

	set_sprite();
}

Knight::~Knight()
{
}


void Knight::set_sprite() {
	if (!texture.loadFromFile("figures.png")) //loading texture
	{
		//here will be message about wrong loading from file
	}
	sprite.setTexture(texture);

	//setting rectangle sprite up
	if (color == white)
		sprite.setTextureRect(sf::IntRect(WIDTH_PIECE, HEIGHT_PIECE, WIDTH_PIECE, HEIGHT_PIECE));
	else sprite.setTextureRect(sf::IntRect(WIDTH_PIECE, ZERO, WIDTH_PIECE, HEIGHT_PIECE));

	sprite.setScale(1.45f, 1.45f);
}

bool Knight::correct_move(Square mv_fr, Square mv_to, Square last_ene_mv, Chessboard board) {
	
	if (!first_cond(mv_to)) return false;

	if (abs(mv_to.get_number() - mv_fr.get_number()) == 2 && abs(mv_to.get_letter() - mv_fr.get_letter()) == 1) return true;
	else if (abs(mv_to.get_number() - mv_fr.get_number()) == 1 && abs(mv_to.get_letter() - mv_fr.get_letter()) == 2) return true;

	return false;
}