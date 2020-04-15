#include "Position.h"

Position::Position() {

}

Position::Position(char let, char num) : letter(let), number(num) {

}

//Position::Position(Position &) {
//					//dopisaæ!
//}
//
//Position::Position(Position &&) {
//
//}			//dopisaæ!

Position::~Position() {

}

void Position::set_letter(char let) {
	letter = let;
}

void Position::set_number(char num) {
	number = num;
}

char Position::get_letter(){
	return letter;
}

char Position::get_number() {
	return number;
}