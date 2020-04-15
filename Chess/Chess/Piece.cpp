#include "Piece.h"

Color Piece::get_color() {
	return color;
}

void Piece::display(sf::RenderWindow &window, Position pos) {

	if (choosen) {
		display_rec(window, pos);
	}

	sprite.setPosition((float)(EDGE_WIDTH + FIELD_SIZE * (pos.get_letter() - 'a')), (float)(EDGE_WIDTH + FIELD_SIZE * ('8' - pos.get_number())));
	sprite.setScale(1.45f, 1.45f);
	window.draw(sprite);
}

void Piece::display_rec(sf::RenderWindow &win, Position pos) {

	uint8_t red = 238, green = 49, blue = 20;
	sf::Color color(red, green, blue);
	sf::RectangleShape rect;
	rect.setOutlineColor(color);
	
	/// tu jest moja zabawa rysowaniem prostok¹ta :D
	rect.setPosition(edge_width + (pos.get_letter() - A_NUMBER_ASCII) * field_size, edge_width + ('8' - pos.get_number()) * field_size);
	rect.setSize(sf::Vector2f(field_size, field_size));
	rect.setOutlineThickness(-4.f);
	red = 111; green = 187; blue = 55;
	sf::Color color2(red, green, blue);
	rect.setFillColor(color2);
	win.draw(rect);
}

bool Piece::empty_sq_rook(Orientation ort, int diff, Square mv_fr, Chessboard board)
{
	//Square *temp_sq;
	//if (diff) {
	//	if (diff < 0) diff++;
	//	else diff--;

	//	switch (ort) {
	//	case horizontally:
	//		while (abs(diff) > 0) {
	//			temp_sq = board.get_sq(mv_fr.get_letter() + diff, mv_fr.get_number());
	//			if (temp_sq->get_piece()) return false;
	//			//veryfying if all squares between initial and target square are empty horizontally 
	//			if (diff < 0) diff++;
	//			else diff--;
	//		}
	//		break;

	//	case upright:
	//		while (abs(diff) > 0) {
	//			if (board[mv_fr.get_letter() - 'a'][mv_fr.get_number + diff - '1'].get_piece()) return false;
	//			//veryfying if all squares between initial and target square are empty upright
	//			if (diff< 0) diff++;
	//			else diff--;
	//		}
	//	}
	//} 
	return true;

}

bool Piece::empty_sq_bishop(int diff_hor, int diff_upr, Square mv_fr, Chessboard board)
{
	/*if (diff_hor) {
		if (diff_hor < 0) diff_hor++; else diff_hor--;
		if (diff_upr < 0) diff_upr++; else diff_upr--;

		while (abs(diff_hor) > 0) {

			if (board[mv_fr.get_letter() + diff_hor - 'a'][mv_fr.get_number() + diff_upr - '1'].get_piece()) return false;

			if (diff_hor < 0) diff_hor++; else diff_hor--;
			if (diff_upr < 0) diff_upr++; else diff_upr--;
		}
	}*/
	return true;
}

void Piece::set_choosen(bool ch) {
	choosen = ch;
}

bool Piece::get_choosen() {
	return choosen;
}