
#ifndef POSITION_H
#define POSITION_H

class Position {
	char letter;
	char number;

public:
	//konstruktory
	Position(char, char);
	Position();
	//Position(Position &);
	//Position(Position &&);


	//destruktor
	~Position();

	void set_letter(char);
	void set_number(char);

	char get_letter();
	char get_number();
};

#endif