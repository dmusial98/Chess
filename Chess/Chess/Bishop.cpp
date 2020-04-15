#include"Bishop.h"

Bishop::Bishop(Color col) {
	color = { col };
	moves_count = (0);
	choosen = { false };

	set_sprite();
}

Bishop::~Bishop()
{
}

bool Bishop::correct_move(Square mv_fr, Square mv_to, Square lat_ene_mv, Chessboard board)
{
	if (!first_cond(mv_to)) return false;

	if (abs(mv_fr.get_letter() - mv_to.get_letter()) == abs(mv_fr.get_number() - mv_to.get_number()) && (mv_to.get_number() != mv_fr.get_number()))
	{ //verifying if Bishop moved crosswise

		if (!empty_sq_bishop(mv_to.get_letter() - mv_fr.get_letter(), mv_to.get_number() - mv_fr.get_number(), mv_fr, board))
			return false;

		else return true;
	}
	else return false;
}

void Bishop::set_sprite() {
	if (!texture.loadFromFile("figures.png")) //loading texture
	{
		//here will be message about wrong loading from file
	}
	sprite.setTexture(texture);

	//setting rectangle sprite up
	if (color == white)
		sprite.setTextureRect(sf::IntRect(WIDTH_PIECE * 2, HEIGHT_PIECE, WIDTH_PIECE, HEIGHT_PIECE));
	else sprite.setTextureRect(sf::IntRect(WIDTH_PIECE * 2, ZERO, WIDTH_PIECE, HEIGHT_PIECE));

	sprite.setScale(1.45f, 1.45f);
}