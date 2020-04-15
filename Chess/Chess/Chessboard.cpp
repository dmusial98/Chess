#include "Chessboard.h"

Chessboard::Chessboard() {
	fill_board();
	set_sprite();
}

Chessboard::~Chessboard() {

}

void Chessboard::fill_board() {

	for (char letter = 'a'; letter <= 'h'; letter++) {
		for (int number = '1'; number <= '8'; number++) {
			chessboard[letter - A_NUMBER_ASCII][number - ONE_NUMBER_ASCII].set_position(letter, number);
		}
	}


	chessboard[0][0].set_piece(pieces.wh_rook1);
	chessboard[7][0].set_piece(pieces.wh_rook2);
	chessboard[1][0].set_piece(pieces.wh_knight1);
	chessboard[6][0].set_piece(pieces.wh_knight2);
	chessboard[2][0].set_piece(pieces.wh_bishop1);
	chessboard[5][0].set_piece(pieces.wh_bishop2);
	chessboard[3][0].set_piece(pieces.wh_queen);
	chessboard[4][0].set_piece(pieces.wh_king);

	chessboard[0][1].set_piece(pieces.wh_pawn1); 
	chessboard[1][1].set_piece(pieces.wh_pawn2);
	chessboard[2][1].set_piece(pieces.wh_pawn3);
	chessboard[3][1].set_piece(pieces.wh_pawn4);
	chessboard[4][1].set_piece(pieces.wh_pawn5);
	chessboard[5][1].set_piece(pieces.wh_pawn6);
	chessboard[6][1].set_piece(pieces.wh_pawn7);
	chessboard[7][1].set_piece(pieces.wh_pawn8);

	chessboard[0][7].set_piece(pieces.bl_rook1);
	chessboard[7][7].set_piece(pieces.bl_rook2);
	chessboard[1][7].set_piece(pieces.bl_knight1);
	chessboard[6][7].set_piece(pieces.bl_knight2);
	chessboard[2][7].set_piece(pieces.bl_bishop1);
	chessboard[5][7].set_piece(pieces.bl_bishop2);
	chessboard[3][7].set_piece(pieces.bl_queen);
	chessboard[4][7].set_piece(pieces.bl_king);

	chessboard[0][6].set_piece(pieces.bl_pawn1);
	chessboard[1][6].set_piece(pieces.bl_pawn2);
	chessboard[2][6].set_piece(pieces.bl_pawn3);
	chessboard[3][6].set_piece(pieces.bl_pawn4);
	chessboard[4][6].set_piece(pieces.bl_pawn5);
	chessboard[5][6].set_piece(pieces.bl_pawn6);
	chessboard[6][6].set_piece(pieces.bl_pawn7);
	chessboard[7][6].set_piece(pieces.bl_pawn8);
		
	}

void Chessboard::display(sf::RenderWindow &window, Position &pos) {
	window.clear();
	window.draw(sprite);

	display_rect(window, pos);

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			chessboard[i][j].display(window);
		}
	}
	window.display();
}

void Chessboard::set_sprite() {

	if (!texture.loadFromFile("board.png"))
	{
		//here will be message about wrong loading from file
	}
	sprite.setTexture(texture);  //loading sprite with texture
	sprite.setScale(1.5, 1.5);	     //setting 	bigger board sprite up
}

void Chessboard::display_rect(sf::RenderWindow &win, Position &act_square) {

	uint8_t red = 111, green = 187, blue = 55;
	sf::Color color(red, green, blue);
	sf::RectangleShape rect;
	rect.setFillColor(color);			/// tu jest moja zabawa rysowaniem prostok¹ta :D
	rect.setPosition(edge_width + (act_square.get_letter() - A_NUMBER_ASCII) * field_size, edge_width + (act_square.get_number() - ONE_NUMBER_ASCII) * field_size);
	rect.setSize(sf::Vector2f(field_size, field_size));


	win.draw(rect);
}

void Chessboard::set_choosen(Position pos, bool ch) {
	chessboard[pos.get_letter() - A_NUMBER_ASCII]['8' - pos.get_number()].set_choosen(ch);
}

bool Chessboard::get_choosen(Position pos) {
	return chessboard[pos.get_letter() - A_NUMBER_ASCII]['8' - pos.get_number()].get_choosen();
}

Square * Chessboard::get_sq(char let, char num)
{
	return &chessboard[let - 'a'][num - '1'];
}

