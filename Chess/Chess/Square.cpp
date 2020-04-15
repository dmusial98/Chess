#include "Square.h"

Square::Square(Position pos) : position(pos) {
	piece_ptr = nullptr;
}

Square::Square() {
	piece_ptr = nullptr;
}

Square::~Square() {

}

char Square::get_number()
{
	return position.get_number();
}

char Square::get_letter()
{
	return position.get_letter();
}

Color Square::get_color()
{
	if(piece_ptr)
		return piece_ptr->get_color();
	
	return none;
}

void Square::set_position(char let, char num) {
	position.set_letter(let);
	position.set_number(num);
}

void Square::set_piece(Piece *pc,  bool erase) {

	if (erase) {
		delete_piece();
	}

	piece_ptr = pc;
}

Piece * Square::get_piece()
{
	return piece_ptr;
}

void Square::display(sf::RenderWindow &window) {

	if (piece_ptr) { //when piece is on square
		piece_ptr->display(window, position);
	}
}

bool Square::is_it_king()
{
	return piece_ptr->is_it_king();
}

bool Square::is_it_pawn()
{
	return piece_ptr->is_it_pawn();
}

void Square::delete_piece()
{
	delete piece_ptr;
	piece_ptr = nullptr;
}

void Square::set_choosen(bool ch) {
	if (piece_ptr) {
		piece_ptr->set_choosen(ch);
	}
}

bool Square::get_choosen() {
	if (piece_ptr) {
		return piece_ptr->get_choosen();
	}
	return false;
}

int Square::get_moves_count()
{
	return piece_ptr->get_moves_count();
}
