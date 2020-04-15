#include "Queen.h"

Queen::Queen(Color col){
	color = { col };
	moves_count = { 0 };
	choosen = { false };

	set_sprite();
}

Queen::~Queen() 
{
}

bool Queen::correct_move(Square mv_fr, Square mv_to, Square last_ene_mv, Chessboard board) {
	return true;
}

void Queen::set_sprite() {
	if (!texture.loadFromFile("figures.png")) //loading texture
	{
		//here will be message about wrong loading from file
	}
	sprite.setTexture(texture);


	//setting rectangle sprite up
	if (color == white)
		sprite.setTextureRect(sf::IntRect(WIDTH_PIECE * 3, HEIGHT_PIECE, WIDTH_PIECE, HEIGHT_PIECE));
	else sprite.setTextureRect(sf::IntRect(WIDTH_PIECE * 3, ZERO, WIDTH_PIECE, HEIGHT_PIECE));

	sprite.setScale(1.45f, 1.45f);
}