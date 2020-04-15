#include "King.h"

King::King(Color col)//: color(col), moves_count(0) //dlaczego nie moge lista innicjalizayjna?
{
	color = { col };
	moves_count = { 0 };
	choosen = { false };
	set_sprite();
}

King::~King() 
{
}

bool King::correct_move(Square mv_fr, Square mv_to, Square last_ene_mv, Chessboard chessboard) {

	if (!first_cond(mv_to)) return false;

	if (abs(mv_to.get_letter() -mv_fr.get_letter()) < 2 && abs(mv_to.get_number()) - mv_fr.get_number() < 2) {
		if (mv_to.get_number() == mv_fr.get_number() && mv_to.get_letter() == mv_fr.get_letter()) return false;
	}
	else return false;
	//verify does King moved at most only one square and it wasn't move on the same square

	return true;

}

bool King::is_it_king() {
	return true;
}

void King::set_sprite() {
	if (!texture.loadFromFile("figures.png")) //loading texture
	{
		//here will be message about wrong loading from file
	}
	sprite.setTexture(texture);

	//setting rectangle sprite up
	if (color == white)
		sprite.setTextureRect(sf::IntRect(WIDTH_PIECE * 4, HEIGHT_PIECE, WIDTH_PIECE, HEIGHT_PIECE));
	else sprite.setTextureRect(sf::IntRect(WIDTH_PIECE * 4, ZERO, WIDTH_PIECE, HEIGHT_PIECE));

	sprite.setScale(1.45f, 1.45f);
}
