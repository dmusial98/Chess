#include "Pawn.h"

Pawn::Pawn(Color col) {
	color = { col };
	moves_count = { 0 };
	choosen = { false };

	set_sprite();
}

Pawn::~Pawn()
{
}

bool Pawn::is_it_pawn()
{
	return true;
}

void Pawn::set_sprite() {
	if (!texture.loadFromFile("figures.png")) //loading texture
	{
		//here will be message about wrong loading from file
	}
	sprite.setTexture(texture);


	//setting rectangle sprite up
	if (color == white)
		sprite.setTextureRect(sf::IntRect(WIDTH_PIECE * 5, HEIGHT_PIECE, WIDTH_PIECE, HEIGHT_PIECE));
	else sprite.setTextureRect(sf::IntRect(WIDTH_PIECE * 5, ZERO, WIDTH_PIECE, HEIGHT_PIECE));

	sprite.setScale(1.45f, 1.45f);
}

bool Pawn::correct_move(Square mv_fr, Square mv_to, Square last_ene_mv, Chessboard board) {
	
	//if (!first_cond(mv_to)) return false;

	//int	upr_diff = mv_to.get_number() - mv_fr.get_number();
	//if (mv_to.get_letter() == mv_fr.get_letter() && mv_to.get_piece() == nullptr) {

	//	if (mv_fr.get_color() == white && upr_diff == 1) return true;
	//	else if (mv_fr.get_color() == black && upr_diff == -1) return true;
	//}  //move Pawn one square forward

	//else if (abs(mv_fr.get_letter() - mv_to.get_letter()) == 1) {
	//	if (upr_diff == 1 && mv_to.get_color() == black && mv_fr.get_color == white) return true;
	//	else if (upr_diff == -1 && mv_to.get_color() == white && mv_fr.get_color() == black) return true;
	//} // capture obliquely

	//else if (mv_fr.get_letter() == mv_to.get_letter() && mv_to.get_piece() == nullptr && !mv_fr.get_moves_count()
	//	&& empty_sq_rook(upright, upr_diff, mv_fr, board)) {

	//	if (upr_diff == 2 && mv_fr.get_color == white) return true;
	//	else if (upr_diff == -2 && mv_fr.get_color() == black) return true;
	//}  //First move of Pawn

	//else if (last_ene_mv.get_color() == white && last_ene_mv.is_it_pawn() && mv_to.get_number() == '3' && mv_fr.get_number == '4' && last_ene_mv.get_number() == '4') {
	//	board[mv_to.get_letter - 'a'][3].set_piece(nullptr, true);
	//	return true;
	//}  //En passant for black Pawn
	//else if (last_ene_mv.get_color() == black && last_ene_mv.is_it_pawn() && mv_to.get_number() == '6' && mv_fr.get_number == '5' && last_ene_mv.get_number() == '5') {
	//	board[mv_to.get_letter() - 'a'][4].set_piece(nullptr, true);
	//	return true;
	//} //En passant for white Pawn

	return false;
}

