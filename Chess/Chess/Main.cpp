#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <string>

class Piece;
class Chessboard;

#pragma region definitions.h

#define WIDTH_PIECE 56
#define HEIGHT_PIECE 57
#define FIELD_SIZE 84
#define EDGE_WIDTH 42
#define ZERO 0
#define BOARD_SIZE 756
#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define UP_BORDER 0
#define DOWN_BORDER 7
#define LEFT_BORDER 0
#define RIGHT_BORDER 7
#define ENTER 13
#define ESCAPE 27
#define BACKSPACE 8

const float field_size{ 84.0 }, edge_width{ 42.0 };

#pragma endregion definitions.h

#pragma region  Enums.h

enum Color { none = 0, white = 1, black = 2 };

void change_color(Color &color) {
	if (color == white) color = black;
	else if (color == black) color = white;
}
Color temp_change_color(Color color) {
	if (color == white) return black;
	else if (color == black) return white;
	return none;
}
#pragma endregion Enums.h

#pragma region Position.h

class Position {
	char letter;
	char number;

public:
	Position(char, char);
	Position();
	Position(const Position &) = default;
	Position(Position &&) = default;
	~Position() = default;

	Position& operator=(Position &&pos);

	void set_letter(char);
	void set_number(char);

	char get_letter();
	char get_number();

	friend std::fstream& operator<<(std::fstream &stream, Position &pos);
	friend std::fstream & operator>>(std::fstream & stream, Position & pos);
};

#pragma endregion Position.h

#pragma region Square.h

class Square {

	Position position;
	Piece *piece_ptr;

public:
	Square(Position&&, Piece*);
	Square(Position);
	Square();
	Square(const Square&) = default;
	Square(Square&&) = default;
	~Square() = default;

	char get_number();
	char get_letter();
	Color get_color() const;
	Color get_sq_color();
	bool get_choosen();
	int get_moves_count();
	Piece* get_piece() const;
	Position get_position() const;

	void set_position(char, char);
	void set_choosen(bool);
	void set_piece(Piece* pc);

	void display(sf::RenderWindow&);

	Square& operator=(const Square &origin);
	friend std::fstream& operator<<(std::fstream &stream, Square &sq);
	friend std::fstream & operator>>(std::fstream & stream, Square & sq);

	void load_fr_file(std::fstream &stream, Chessboard &board);
};

#pragma endregion Square.h

#pragma region Piece.h

class Piece {

protected:
	Color color;
	Color sq_color; //only for bishop needed
	int moves_count = 0;
	bool choosen;
	bool in_game = true;

	sf::Texture texture;
	sf::Sprite sprite;
	sf::Color out_color{ 0xEE3114FF };
	sf::Color rect_color{ 0x6FBB14FF };
	sf::RectangleShape rect;
	//SFML variables

public:
	enum Orientation { upright, horizontally };

	Color get_color();
	Color get_sq_color();
	bool get_choosen();
	int get_moves_count();

	void set_color(Color col);
	void set_sq_color(Color col);
	void change_in_game(bool);
	void set_choosen(bool);


	void display(sf::RenderWindow &window, Position position);

	void operator++();
	void operator--();
	friend std::fstream& operator<<(std::fstream &stream, Piece &piece);
	friend std::fstream & operator>>(std::fstream & stream, Piece *piece);

	//virtual functions
	virtual bool correct_move(Square mv_fr, Square mv_to, Square last_ene_mv, Chessboard &board) = 0;

	virtual bool is_it_king() { return false; };
	virtual bool is_it_pawn() { return false; };
	virtual bool is_it_queen() { return false; };
	virtual bool is_it_bishop() { return false; };
	virtual bool is_it_rook() { return false; };
	virtual bool is_it_knight() { return false; };
	virtual void set_sprite() = 0;

protected:
	void set_rect();
	void display_rec(sf::RenderWindow&, Position pos);
	bool first_cond(Square, Square);
	bool empty_sq_rook(Orientation, int, Square, Chessboard);
	bool empty_sq_bishop(int, int, Square, Chessboard);
};

#pragma endregion Piece.h

#pragma region Bishop.h

class Bishop : public Piece {


public:
	Bishop(Color, Color);
	Bishop();
	~Bishop() = default;

	bool correct_move(Square mv_fr, Square mv_to, Square last_ene_mv, Chessboard& board);
	bool is_it_bishop() { return true; }

private:
	void set_sprite();
};

#pragma endregion Bishop.h

#pragma region King.h

class King : public Piece {  //król niech sprawdza czy jest zagro¿ony

public:
	King(Color);
	King();
	~King() = default;

	bool is_it_king() { return true; };
	bool correct_move(Square, Square, Square, Chessboard&);

private:
	void set_sprite();
};

#pragma endregion King.h

#pragma region Knight.h

class Knight : public Piece {

public:
	Knight(Color);
	Knight();
	~Knight() = default;

	bool correct_move(Square, Square, Square, Chessboard&);
	bool is_it_knight() { return true; };

private:
	void set_sprite();
};

#pragma endregion Knight.h

#pragma region Pawn.h

class Pawn : public Piece {


public:
	Pawn(Color);
	Pawn();
	~Pawn() = default;

	bool correct_move(Square, Square, Square, Chessboard&);
	bool is_it_pawn() { return true; };

private:
	void set_sprite();
};

#pragma endregion Pawn.h

#pragma region Queen.h

class Queen : public Piece {


public:
	Queen(Color);
	Queen();
	~Queen() = default;

	bool correct_move(Square, Square, Square, Chessboard&);
	bool is_it_queen() { return true; };

private:
	void set_sprite();
};

#pragma endregion Queen.h

#pragma region Rook.h

class Rook : public Piece {

public:
	Rook(Color);
	Rook();
	~Rook() = default;

	bool correct_move(Square, Square, Square, Chessboard&);
	bool is_it_rook() { return true; };

private:
	void set_sprite();
};

#pragma endregion Rook.h

#pragma region Chessboard.h

class Chessboard {
	Square chessboard[8][8];
	sf::Texture texture;
	sf::Sprite sprite;

	struct Pieces {

		King kings[2];
		Queen queens[18];
		Bishop bishops[20];
		Knight knights[20];
		Rook rooks[20];
		Pawn pawns[16];

		int king_num{ 0 },
			queen_num{ 0 },
			bishop_num{ 0 },
			knight_num{ 0 },
			rook_num{ 0 },
			pawn_num{ 0 };

		Pieces() = default;

	} pieces;


public:

	Chessboard();
	~Chessboard() = default;

	int get_king_num();
	int get_queen_num();
	int get_bishop_num();
	int get_knight_num();
	int get_rook_num();
	int get_pawn_num();
	King* get_king();
	Queen* get_queen();
	Bishop* get_bishop();
	Knight* get_knight();
	Rook* get_rook();
	Pawn* get_pawn();
	//pieces support

	void fill_new_game();

	bool is_checkmate(Color color, Square last_ene_mv);
	bool King_thr(Color color, Square last_ene_mv);
	//check and checkmate 

	void display(sf::RenderWindow & window, Square pos, sf::Text &text, sf::Text &text_turn);

	void set_choosen(Position, bool);
	//setters

	bool get_choosen(Position);
	Square* get_sq(char, char);
	//getters

	Square& operator()(char let, char num);
	friend std::fstream& operator<<(std::fstream& stream, Chessboard &board);
	friend std::fstream & operator>>(std::fstream & stream, Chessboard &board);
	//operators

	void add_piece(Position position, Piece *piece);

private:
	void display_rect(sf::RenderWindow&, Position);
	void display_num_let(sf::RenderWindow &window);
	void set_sprite();
};


#pragma endregion Chessboard.h

#pragma region Game.h

class Game {
	Chessboard chessboard;
	sf::RenderWindow window;
	Square *active_square;
	Color act_color;

	struct last_move { //for canceling last move
		Piece *piece_from;
		Piece *piece_to;
		Square *sq_from;
		Square *sq_to;

		last_move();

	} last_mv;

	sf::Text new_game_text{ "New Game", font },
		load_fr_file_text{ "Load from file", font };
	sf::Text text_turn, text, text1, in_text;
	sf::Font font;
	sf::Color font_color{ 0x0800A3FF };
	sf::Color font_color_ch{ 0x008D00FF };
	sf::Texture menu_texture;
	sf::Sprite menu_sprite;
	sf::Event event;
	sf::Music music;
	sf::SoundBuffer buffer;
	sf::Sound sound;  //SFML viarables 

	std::string str;


public:
	Game();
	~Game();

	void play();
	void main_menu();

private:
	bool king_thr(Color king_color);
	void after_check();
	bool is_checkmate();
	bool thr_reaction();
	bool is_statement();
	bool possible_mv_stat();
	bool optional_statement();
	// threat and checkmate of king 

	void load_music();
	void load_font();
	//preparing game

	void thr_king_sound();
	void cheers_sound();
	void wr_mv_sound();
	//sound reactions

	bool pawn_promotion();
	//pawn promotion

	bool castling();
	void possible_castling(Position pos[], Position temp_pos, char first_let, char second_let, Square king_sq, int i);
	void find_rook_castling(Position pos[]);
	void do_castling(Square &rook_sq, Square &king_sq);
	bool castling_decision();
	//castling

	void control();
	bool do_move();
	void end_game(bool draw);
	void change_text_turn();
	void back_move();

	void save(std::string file_name);
	bool load_from_file(std::string file_name);
	//file support

	void main_menu_cont(int &act_text);
	void menu_font_switch(int &act_text, sf::Color font_col);

	void save_menu();
	void save_menu_SU();
	void load_menu();
};


#pragma endregion Game.h

#pragma region Bishop.cpp 

Bishop::Bishop(Color col, Color sq_col) {
	color = { col };
	moves_count = (0);
	choosen = { false };
	in_game = true;
	sq_color = sq_col;
	set_sprite();
	set_rect();
}

Bishop::Bishop()
{
	color = none;
	sq_color = none;
	moves_count = { 0 };
	choosen = { false };
	in_game = true;
	set_rect();
}

bool Bishop::correct_move(Square mv_fr, Square mv_to, Square lat_ene_mv, Chessboard &board)
{
	if (!first_cond(mv_fr, mv_to)) return false;

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
		throw std::string{ "load bishop's error" };
	}
	sprite.setTexture(texture);

	//setting rectangle sprite up
	if (color == white)
		sprite.setTextureRect(sf::IntRect(WIDTH_PIECE * 2, HEIGHT_PIECE, WIDTH_PIECE, HEIGHT_PIECE));
	else sprite.setTextureRect(sf::IntRect(WIDTH_PIECE * 2, ZERO, WIDTH_PIECE, HEIGHT_PIECE));

	sprite.setScale(1.45f, 1.45f);
}

#pragma endregion Bishop.cpp 

#pragma region Chessboard.cpp

Chessboard::Chessboard() {

	for (char letter = 'a'; letter <= 'h'; letter++) {
		for (char number = '1'; number <= '8'; number++) {
			chessboard[letter - 'a'][number - '1'].set_position(letter, number);
		}
	}
	set_sprite();
}

int Chessboard::get_king_num()
{
	return pieces.king_num;
}

int Chessboard::get_queen_num()
{
	return pieces.queen_num;
}

int Chessboard::get_bishop_num()
{
	return pieces.bishop_num;
}

int Chessboard::get_knight_num()
{
	return pieces.knight_num;
}

int Chessboard::get_rook_num()
{
	return pieces.rook_num;
}

int Chessboard::get_pawn_num()
{
	return pieces.pawn_num;
}

King* Chessboard::get_king()
{
	King* king = &pieces.kings[pieces.king_num];
	pieces.king_num++;
	return king;
}

Queen * Chessboard::get_queen()
{
	Queen* queen = &pieces.queens[pieces.queen_num];
	pieces.queen_num++;
	return queen;
}

Bishop * Chessboard::get_bishop()
{
	Bishop* bishop = &pieces.bishops[pieces.bishop_num];
	pieces.bishop_num++;
	return bishop;
}

Knight * Chessboard::get_knight()
{
	Knight* knight = &pieces.knights[pieces.knight_num];
	pieces.knight_num++;
	return knight;
}

Rook * Chessboard::get_rook()
{
	Rook* rook = &pieces.rooks[pieces.rook_num];
	pieces.rook_num++;
	return rook;
}

Pawn * Chessboard::get_pawn()
{
	Pawn* pawn = &pieces.pawns[pieces.pawn_num];
	pieces.pawn_num++;
	return pawn;
}

void Chessboard::fill_new_game() {

	pieces.rooks[0].set_color(white);
	pieces.rooks[1].set_color(white);
	pieces.knights[0].set_color(white);
	pieces.knights[1].set_color(white);
	pieces.bishops[0].set_color(white);
	pieces.bishops[1].set_color(white);
	pieces.queens[0].set_color(white);
	pieces.kings[0].set_color(white);

	pieces.bishops[0].set_sq_color(white);
	pieces.bishops[1].set_sq_color(black);

	for (int i = 0; i < 8; i++) {
		pieces.pawns[i].set_color(white);
	}

	pieces.rooks[2].set_color(black);
	pieces.rooks[3].set_color(black);
	pieces.knights[2].set_color(black);
	pieces.knights[3].set_color(black);
	pieces.bishops[2].set_color(black);
	pieces.bishops[3].set_color(black);
	pieces.queens[1].set_color(black);
	pieces.kings[1].set_color(black);

	pieces.bishops[3].set_sq_color(white);
	pieces.bishops[2].set_sq_color(black);

	for (int i = 8; i < 16; i++) {
		pieces.pawns[i].set_color(black);
	}

	chessboard[0][0].set_piece(&pieces.rooks[0]);
	chessboard[7][0].set_piece(&pieces.rooks[1]);
	chessboard[1][0].set_piece(&pieces.knights[0]);
	chessboard[6][0].set_piece(&pieces.knights[1]);
	chessboard[2][0].set_piece(&pieces.bishops[0]);
	chessboard[5][0].set_piece(&pieces.bishops[1]);
	chessboard[3][0].set_piece(&pieces.queens[0]);
	chessboard[4][0].set_piece(&pieces.kings[0]);

	chessboard[0][1].set_piece(&pieces.pawns[0]);
	chessboard[1][1].set_piece(&pieces.pawns[1]);
	chessboard[2][1].set_piece(&pieces.pawns[2]);
	chessboard[3][1].set_piece(&pieces.pawns[3]);
	chessboard[4][1].set_piece(&pieces.pawns[4]);
	chessboard[5][1].set_piece(&pieces.pawns[5]);
	chessboard[6][1].set_piece(&pieces.pawns[6]);
	chessboard[7][1].set_piece(&pieces.pawns[7]);

	chessboard[0][7].set_piece(&pieces.rooks[2]);
	chessboard[7][7].set_piece(&pieces.rooks[3]);
	chessboard[1][7].set_piece(&pieces.knights[2]);
	chessboard[6][7].set_piece(&pieces.knights[3]);
	chessboard[2][7].set_piece(&pieces.bishops[2]);
	chessboard[5][7].set_piece(&pieces.bishops[3]);
	chessboard[3][7].set_piece(&pieces.queens[1]);
	chessboard[4][7].set_piece(&pieces.kings[1]);

	chessboard[0][6].set_piece(&pieces.pawns[8]);
	chessboard[1][6].set_piece(&pieces.pawns[9]);
	chessboard[2][6].set_piece(&pieces.pawns[10]);
	chessboard[3][6].set_piece(&pieces.pawns[11]);
	chessboard[4][6].set_piece(&pieces.pawns[12]);
	chessboard[5][6].set_piece(&pieces.pawns[13]);
	chessboard[6][6].set_piece(&pieces.pawns[14]);
	chessboard[7][6].set_piece(&pieces.pawns[15]);

	pieces.king_num = 2;
	pieces.queen_num = 2;
	pieces.bishop_num = 4;
	pieces.knight_num = 4;
	pieces.rook_num = 4;
	pieces.pawn_num = 16;

}

bool Chessboard::is_checkmate(Color color, Square last_ene_mv)
{

	for (char let_fr = 'a'; let_fr <= 'h'; let_fr++) {
		for (char num_fr = '1'; num_fr <= '8'; num_fr++) {
			if (chessboard[let_fr - 'a'][num_fr - '1'].get_piece()) {
				if (chessboard[let_fr - 'a'][num_fr - '1'].get_color() == color) { //piece with king's color

					for (char let_to = 'a'; let_to <= 'h'; let_to++) {
						for (char num_to = '1'; num_to <= '8'; num_to++) {
							if (chessboard[let_fr - 'a'][num_fr - '1'].get_piece()->correct_move(chessboard[let_fr - 'a'][num_fr - '1'], chessboard[let_to - 'a'][num_to - '1'], last_ene_mv, *this)) {
								//gdy bierka moze ruszyc sie na dane pole

								Piece *temp_piece = chessboard[let_to - 'a'][num_to - '1'].get_piece();
								chessboard[let_to - 'a'][num_to - '1'].set_piece(chessboard[let_fr - 'a'][num_fr - '1'].get_piece());
								chessboard[let_fr - 'a'][num_fr - '1'].set_piece(nullptr);
								//setting piece on new square up for find out is it check in this situation

								if (!King_thr(color, last_ene_mv)) {
									chessboard[let_fr - 'a'][num_fr - '1'].set_piece(chessboard[let_to - 'a'][num_to - '1'].get_piece());
									chessboard[let_to - 'a'][num_to - '1'].set_piece(temp_piece);
									//setting pieces on old squares 
									return false;
								}

								chessboard[let_fr - 'a'][num_fr - '1'].set_piece(chessboard[let_to - 'a'][num_to - '1'].get_piece());
								chessboard[let_to - 'a'][num_to - '1'].set_piece(temp_piece);
							}

						}
					}

				}
			}
		}
	}

	return true;
}

bool Chessboard::King_thr(Color color, Square last_ene_mv)
{
	for (char k_letter = 'a'; k_letter <= 'h'; k_letter++) {
		for (char k_number = '1'; k_number <= '8'; k_number++) {
			if (chessboard[k_letter - 'a'][k_number - '1'].get_piece()) {
				if (chessboard[k_letter - 'a'][k_number - '1'].get_piece()->is_it_king() && chessboard[k_letter - 'a'][k_number - '1'].get_piece()->get_color() == color) {
					//finding king

					for (char p_letter = 'a'; p_letter <= 'h'; p_letter++) {
						for (char p_number = '1'; p_number <= '8'; p_number++) {
							if (get_sq(p_letter, p_number)->get_piece()) {  //if on a square is any piece
								if (get_sq(p_letter, p_number)->get_color() != color) {		//when piece have color different than King
									if (get_sq(p_letter, p_number)->get_piece()->correct_move(chessboard[p_letter - 'a'][p_number - '1'], chessboard[k_letter - 'a'][k_number - '1'], last_ene_mv, *this)) return true;
									//if piece can move into square on which is King
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}

void Chessboard::display(sf::RenderWindow &window, Square pos, sf::Text &text, sf::Text &text_turn) {
	window.clear();
	window.draw(sprite);
	for (int i = 0; i < 5; i++) {
		sprite.setPosition(0, 756 + i * (edge_width - 7));
		window.draw(sprite);
	}
	sprite.setPosition(0, 0);

	display_rect(window, pos.get_position());

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			chessboard[i][j].display(window);
		}
	}
	window.draw(text_turn);
	window.draw(text);
	display_num_let(window);
	window.display();
}

void Chessboard::set_sprite() {

	if (!texture.loadFromFile("board.png"))
	{
		throw std::string("board sprite load error");
	}
	sprite.setTexture(texture);  //loading sprite with texture
	sprite.setScale(1.5, 1.5);	     //setting 	bigger board sprite up
}

void Chessboard::display_rect(sf::RenderWindow &win, Position act_square) {

	uint8_t red = 111, green = 187, blue = 55;
	sf::Color color(red, green, blue);
	sf::RectangleShape rect;
	rect.setFillColor(color);
	rect.setPosition(edge_width + (act_square.get_letter() - 'a') * field_size, edge_width + (act_square.get_number() - '1') * field_size);
	rect.setSize(sf::Vector2f(field_size, field_size));
	win.draw(rect);
}

void Chessboard::display_num_let(sf::RenderWindow &window)
{
	sf::Font font;
	font.loadFromFile("Storyboo.TTF");
	sf::Text text;
	text.setFont(font);
	int8_t red = 8, green = 0, blue = 163;
	sf::Color color(red, green, blue);
	text.setFillColor(color);

	std::string number("1");
	for (int i = 0; i < 8; i++) {
		text.setString(number);
		text.setPosition(10.f, 60.f + i * field_size);
		window.draw(text);

		number[0]++;
	}

	std::string letter("A");

	for (int i = 0; i < 8; i++) {
		text.setString(letter);
		text.setPosition(70.f + i * field_size, 2.f);
		window.draw(text);
		letter[0]++;
	}

}

void Chessboard::set_choosen(Position pos, bool ch) {
	chessboard[pos.get_letter() - 'a']['8' - pos.get_number()].set_choosen(ch);
}

bool Chessboard::get_choosen(Position pos) {
	return chessboard[pos.get_letter() - 'a']['8' - pos.get_number()].get_choosen();
}

Square * Chessboard::get_sq(char let, char num)
{
	return &chessboard[let - 'a'][num - '1'];
}

Square & Chessboard::operator()(char let, char num)
{
	return chessboard[let - 'a'][num - '1'];
}

void Chessboard::add_piece(Position position, Piece * piece)
{
	chessboard[position.get_letter() - 'a'][position.get_number() - '1'].get_piece()->change_in_game(false);
	chessboard[position.get_letter() - 'a'][position.get_number() - '1'].set_piece(piece);
}

std::fstream & operator<<(std::fstream & stream, Chessboard &board)
{
	for (int let = 0; let < 8; let++) {
		for (int num = 0; num < 8; num++) {
			stream << board.chessboard[let][num];
		}
	}

	return stream;
}

std::fstream & operator>>(std::fstream & stream, Chessboard &board)
{
	for (int let = 0; let < 8; let++) {
		for (int num = 0; num < 8; num++) {
			board.chessboard[let][num].load_fr_file(stream, board);
		}
	}

	return stream;
}

#pragma endregion Chessboard.cpp

#pragma region Game.cpp

Game::Game() : act_color(white)
{
	window.create(sf::VideoMode(756, 900), "Chess");
	active_square = chessboard.get_sq('e', '5');
	last_mv.sq_to = chessboard.get_sq('e', '5');
	load_font();
	text.setString("Please choose correct piece.");
	text_turn.setString("White's turn.");
	load_music();
}

Game::~Game() {}

void Game::play() {

	if (act_color == black) change_text_turn();
	chessboard.display(window, *active_square, text, text_turn);
	music.play();

	while (window.isOpen())  //main loop
	{
		if (do_move()) continue;

		if (king_thr(temp_change_color(act_color))) {
			back_move();
			thr_king_sound();
			continue;
		}		//ods³oniêcie siê na szacha

		if (thr_reaction()) continue;;
		if (is_statement()) {
			end_game(true);
			continue;
		}
		if (pawn_promotion()) thr_reaction();
	}
}

bool Game::do_move() {

	bool correct_move = false;

	while (!correct_move) {

		control();

		while (active_square->get_color() != act_color) {
			if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)  return true;
			text.setString("It's not your turn.\nPlease choose correct piece .");
			chessboard.display(window, *active_square, text, text_turn);
			wr_mv_sound();
			control();
		}
		if (castling()) {
			chessboard.display(window, *active_square, text, text_turn);
			return false;
		}

		Piece *choosen_piece = active_square->get_piece();
		Square *mv_fr = active_square;
		choosen_piece->set_choosen(true);
		text.setString("Please choose field for your piece.");
		chessboard.display(window, *active_square, text, text_turn);
		control();
		if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape) return true;

		if (choosen_piece->correct_move(*mv_fr, *active_square, *last_mv.sq_to, chessboard)) {

			last_mv.piece_from = choosen_piece;
			last_mv.piece_to = active_square->get_piece();
			if (last_mv.piece_to) last_mv.piece_to->change_in_game(false);
			last_mv.sq_from = mv_fr;
			last_mv.sq_to = active_square;			//setting last move up

			++(*choosen_piece);			//moves_count increment
			active_square->set_piece(choosen_piece);
			mv_fr->set_piece(nullptr);
			change_color(act_color);
			choosen_piece->set_choosen(false);
			change_text_turn();
			correct_move = true;
		}
		else {
			text.setString("Incorrect move.\nPlease choose piece and correct field.");
			choosen_piece->set_choosen(false);
			wr_mv_sound();
		}
		chessboard.display(window, *active_square, text, text_turn);
	}

	return false;

}
bool Game::king_thr(Color king_color)
{
	if (chessboard.King_thr(king_color, *last_mv.sq_to)) return true;
	else return false;
}

bool Game::is_checkmate()
{
	if (chessboard.is_checkmate(act_color, *last_mv.sq_to))
		return true;

	return false;
}

void Game::after_check()
{
	Color king_color = act_color;

	while (king_thr(king_color)) {
		do_move();
		if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed) return;
		if (king_thr(king_color)) {

			last_mv.sq_from->set_piece(last_mv.piece_from); //setting pieces up on old squares
			last_mv.sq_to->set_piece(last_mv.piece_to);
			change_color(act_color);
			change_text_turn();
			text.setString("You're king is threatened,\nplease do correct move.");
			chessboard.display(window, *active_square, text, text_turn);
			thr_king_sound();
		}
	}
	text.setString("Please choose correct piece.");
}

void Game::load_font()
{
	if (!font.loadFromFile("Storyboo.ttf")) {
		throw std::string("font load error");
	}
	text.setFont(font);
	text_turn.setFont(font);
	text.setFillColor(font_color);
	text_turn.setFillColor(font_color);
	new_game_text.setFillColor(font_color_ch);
	load_fr_file_text.setFillColor(font_color);
	text_turn.setPosition(10.f, field_size * 8 + edge_width * 2);
	text.setPosition(10.f, field_size * 8 + edge_width * 2 + 30.f);
	new_game_text.setPosition(300.f, 250.f);
	load_fr_file_text.setPosition(278.f, 350.f);
}

void Game::end_game(bool draw)
{
	text_turn.setString("");

	if (!draw) {
		if (act_color == white) text.setString("Black pieces won.\nPress Esc for exit.");
		else text.setString("White pieces won.\nPress Esc for exit.");
	}
	else {
		text.setString("It's statement.\nPress Esc for exit.");
	}
	chessboard.display(window, *active_square, text, text_turn);
	sf::Event event;
	cheers_sound();
	do {
		window.pollEvent(event);
	} while (event.key.code != sf::Keyboard::Escape && event.type != sf::Event::Closed);
	window.close();
}

void Game::change_text_turn()
{
	if (act_color == white) text_turn.setString("White's turn.");
	else text_turn.setString("Black's turn.");
}

void Game::back_move()
{
	last_mv.sq_from->set_piece(last_mv.piece_from);
	last_mv.sq_to->set_piece(last_mv.piece_to);
	if (last_mv.piece_to) last_mv.piece_to->change_in_game(true);
	last_mv.sq_from--;
	change_color(act_color);
	change_text_turn();
	text.setString("You can't do that,\nyour king would be threaten");
	chessboard.display(window, *active_square, text, text_turn);
}

void Game::save(std::string file_name)
{
	std::fstream file;
	file.open(file_name, std::ios_base::out | std::ios_base::binary);

	file << chessboard;
	file << act_color;
	file << " ";
	std::string buffer{ text_turn.getString() };
	size_t str_length = buffer.length();
	for (int i = 0; i < str_length; i++) {
		if (buffer[i] == ' ') buffer[i] = '0';
		if (buffer[i] == 10) buffer[i] = '9';
	}

	file << str_length;
	file << " ";
	file << buffer;
	file << " ";
	buffer = text.getString();
	str_length = buffer.length();
	for (int i = 0; i < str_length; i++) {
		if (buffer[i] == ' ') buffer[i] = '0';
		if (buffer[i] == 10) buffer[i] = '9';
	}
	file << str_length;
	file << " ";
	file << buffer;
	file << " ";

	file.close();
}

bool Game::load_from_file(std::string file_name)
{
	std::fstream file;
	file.open(file_name, std::ios_base::in || std::ios_base::binary);
	if (!file.is_open()) return false;
	file >> chessboard;

	int buf;
	file >> buf;
	act_color = (Color)buf;

	std::string str;
	int str_length;

	file >> str_length;
	str.resize(str_length);
	for (int i = 0; i < str_length; i++) {
		file >> str[i];
		if (str[i] == '0') str[i] = ' ';
		if (str[i] == '9') str[i] = 10;
	}
	text_turn.setString(str);
	file >> str_length;
	str.resize(str_length);
	for (int i = 0; i < str_length; i++) {
		file >> str[i];
		if (str[i] == '0') str[i] = ' ';
		if (str[i] == '9') str[i] = 10;
	}
	text.setString(str);

	file.close();
	return true;
}

void Game::main_menu_cont(int &act_text)
{
	while (window.waitEvent(event)) {
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Up) {
				menu_font_switch(act_text, font_color);

				if (act_text == 1) act_text = 2;
				else act_text--;
				menu_font_switch(act_text, font_color_ch);

			}
			else if (event.key.code == sf::Keyboard::Down) {
				menu_font_switch(act_text, font_color);

				if (act_text == 2) act_text = 1;
				else act_text++;
				menu_font_switch(act_text, font_color_ch);

			}
			else if (event.key.code == sf::Keyboard::Enter) {
				return;
			}
			else if (event.key.code == sf::Keyboard::Escape)
				window.close();
		}
		else if (event.type == sf::Event::Closed) window.close();

		window.draw(menu_sprite);
		window.draw(new_game_text);
		window.draw(load_fr_file_text);
		window.display();
	}
}

void Game::menu_font_switch(int & act_text, sf::Color font_col)
{
	switch (act_text) {
	case 1:
		new_game_text.setFillColor(font_col);
		window.draw(new_game_text);
		window.display();
		break;
	case 2:
		load_fr_file_text.setFillColor(font_col);
		window.draw(load_fr_file_text);
		window.display();
		break;
	}
}


void Game::save_menu()
{
	save_menu_SU();
	window.clear();
	window.draw(menu_sprite);
	window.draw(text1);
	window.draw(in_text);
	window.display();

	while (window.waitEvent(event)) {
		if (event.type == sf::Event::TextEntered)
		{
			// Handle ASCII characters only
			if (event.text.unicode < 128)
			{
				if (event.text.unicode != ENTER && event.text.unicode != ESCAPE && event.text.unicode != 58 && event.text.unicode != 34
					&& event.text.unicode != 59 && event.text.unicode != 47 && event.text.unicode != 63 && event.text.unicode != 60
					&& event.text.unicode != 62 && event.text.unicode != 92 && event.text.unicode != 42 && event.text.unicode != 124) {

					if (event.text.unicode == BACKSPACE) {
						if (str.length() != 0) {
							str.pop_back();
							in_text.setString(str);
						}
					}
					else {
						str += static_cast<char>(event.text.unicode);
						in_text.setString(str);
					}
				}
				else if (event.text.unicode == ENTER) {
					if (str.length() > 0) {

						save(str + ".txt");
						text1.setString("Game saved.\nPress Esc for exit.");
						window.clear();
						window.draw(menu_sprite);
						window.draw(text1);
						window.display();
						do  window.waitEvent(event); while (event.key.code != sf::Keyboard::Escape);
						window.close();
						return;
					}
				}
				window.clear();
				window.draw(menu_sprite);
				window.draw(text1);
				window.draw(in_text);
				window.display();
			}
		}
	}
}

void Game::save_menu_SU()
{
	text1.setFont(font);
	text1.setFillColor(font_color);
	text1.setPosition(180.f, 150.f);
	text1.setString("Please type name of file.");

	menu_texture.loadFromFile("nowa_tekstura_menu.png");
	menu_sprite.setTexture(menu_texture);
	in_text.setFont(font);
	in_text.setPosition(190.f, 250.f);
	in_text.setFillColor(font_color);
}

void Game::load_menu()
{
	save_menu_SU();
	window.display();

	while (window.waitEvent(event)) {
		if (event.type == sf::Event::TextEntered)
		{
			// Handle ASCII characters only
			if (event.text.unicode < 128)
			{

				if (event.text.unicode != ENTER && event.text.unicode != ESCAPE && event.text.unicode != 58 && event.text.unicode != 34
					&& event.text.unicode != 59 && event.text.unicode != 47 && event.text.unicode != 63 && event.text.unicode != 60
					&& event.text.unicode != 62 && event.text.unicode != 92 && event.text.unicode != 42 && event.text.unicode != 124) {

					if (event.text.unicode == BACKSPACE) {
						if (str.length() != 0) {
							str.pop_back();
							in_text.setString(str);
						}
					}
					else {
						str += static_cast<char>(event.text.unicode);
						in_text.setString(str);
					}
				}
				else if (event.text.unicode == ENTER) {
					if (str.length() > 0) {
						if (!load_from_file(str + ".txt")) {
							text1.setString("Wrong file's name.\nPress Esc for exit.");

							window.clear();
							window.draw(menu_sprite);
							window.draw(text1);
							window.display();
							do {
								window.waitEvent(event);
							} while (event.key.code != sf::Keyboard::Escape);
							window.close();
							return;
						}

						play();
						return;
					}
				}
				window.clear();
				window.draw(menu_sprite);
				window.draw(text1);
				window.draw(in_text);
				window.display();
			}
		}
	}
}


void Game::main_menu()
{
	menu_texture.loadFromFile("nowa_tekstura_menu.png");
	menu_sprite.setPosition(0.f, 0.f);
	menu_sprite.setTexture(menu_texture);
	//menu texture setting up

	int act_text = 1;

	window.draw(menu_sprite);
	window.draw(new_game_text);
	window.draw(load_fr_file_text);
	window.display();

	main_menu_cont(act_text);

	switch (act_text) {
	case 1:
		chessboard.fill_new_game();
		play();
		break;
	case 2:
		load_menu();
		break;
	}
}

void Game::load_music()
{
	music.openFromFile("chess_soundtrack.ogg");
	music.setLoop(true);
}

void Game::wr_mv_sound()
{
	buffer.loadFromFile("announcement_end.wav");
	sound.setBuffer(buffer);
	sound.setVolume(35.f);
	music.pause();
	sound.play();
	while (sound.getStatus() == sf::SoundSource::Status::Stopped) {}
	//music pause during sound playing
	music.play();
}

void Game::thr_king_sound()
{
	buffer.loadFromFile("piano_notification3.ogg");
	sound.setBuffer(buffer);
	music.pause();
	sound.play();
	while (sound.getStatus() == sf::SoundSource::Status::Stopped) {}
	music.play();
}

void Game::cheers_sound()
{
	buffer.loadFromFile("cheer_ii.wav");
	sound.setBuffer(buffer);
	sound.setVolume(35.f);
	sound.play();
}

bool Game::pawn_promotion()
{
	if (last_mv.piece_from) {
		if (last_mv.piece_from->is_it_pawn() && (last_mv.sq_to->get_number() == '8' || last_mv.sq_to->get_number() == '1')) {
			text.setString("Pawn promotion\nFor which piece do you want change pawn?\nq - queen, r - rook, b - bishop, k - knight");
			chessboard.display(window, *active_square, text, text_turn);

			sf::Event event;
			do {
				window.waitEvent(event);
			} while (event.key.code != sf::Keyboard::Q && event.key.code != sf::Keyboard::R &&
				event.key.code != sf::Keyboard::B && event.key.code != sf::Keyboard::K);

			if (event.key.code == sf::Keyboard::Q) {
				Queen *new_queen = chessboard.get_queen();
				new_queen->set_color(last_mv.piece_from->get_color());
				chessboard.add_piece(Position(last_mv.sq_to->get_letter(), last_mv.sq_to->get_number()), new_queen);
			}
			else if (event.key.code == sf::Keyboard::R) {
				Rook *new_rook = chessboard.get_rook();
				new_rook->set_color(last_mv.piece_from->get_color());
				chessboard.add_piece(Position(last_mv.sq_to->get_letter(), last_mv.sq_to->get_number()), new_rook);
			}
			else if (event.key.code == sf::Keyboard::B) {
				Color new_col = white;
				if ((last_mv.sq_from->get_letter() == 'a' && last_mv.sq_from->get_number() == '8') ||
					(last_mv.sq_from->get_letter() == 'b' && last_mv.sq_from->get_number() == 'a') ||
					(last_mv.sq_from->get_letter() == 'c' && last_mv.sq_from->get_number() == '8') ||
					(last_mv.sq_from->get_letter() == 'd' && last_mv.sq_from->get_number() == '1') ||
					(last_mv.sq_from->get_letter() == 'e' && last_mv.sq_from->get_number() == '8') ||
					(last_mv.sq_from->get_letter() == 'f' && last_mv.sq_from->get_number() == '1') ||
					(last_mv.sq_from->get_letter() == 'g' && last_mv.sq_from->get_number() == '8') ||
					(last_mv.sq_from->get_letter() == 'h' && last_mv.sq_from->get_number() == '1'))
					new_col = black;

				Bishop *new_bishop = chessboard.get_bishop();
				new_bishop->set_color(last_mv.piece_from->get_color());
				chessboard.add_piece(Position(last_mv.sq_to->get_letter(), last_mv.sq_to->get_number()), new_bishop);
			}
			else if (event.key.code == sf::Keyboard::K) {
				Knight *new_knight = chessboard.get_knight();
				new_knight->set_color(last_mv.piece_from->get_color());
				chessboard.add_piece(Position(last_mv.sq_to->get_letter(), last_mv.sq_to->get_number()), new_knight);
			}
			text.setString("Please choose correct piece.");
			chessboard.display(window, *active_square, text, text_turn);
			return true;
		}
	}
	return false;
}

bool Game::castling()
{
	if (active_square->get_piece()->is_it_king()) {
		if (!active_square->get_piece()->get_moves_count()) {

			Position pos[2];
			find_rook_castling(pos);

			if (pos[0].get_letter() != '0' && pos[1].get_letter() != '0') {

				if (castling_decision()) {
					text.setString("Which rook do you want move for castling?\nl - left, r - right");
					chessboard.display(window, *active_square, text, text_turn);
					do {
						window.waitEvent(event);
					} while (event.key.code != sf::Keyboard::L && event.key.code != sf::Keyboard::R);

					if (event.key.code == sf::Keyboard::L) {
						do_castling(*chessboard.get_sq(pos[0].get_letter(), pos[0].get_number()), *chessboard.get_sq('e', pos[0].get_number()));
						return true;
					}
					else if (event.key.code == sf::Keyboard::R) {
						do_castling(*chessboard.get_sq(pos[1].get_letter(), pos[1].get_number()), *chessboard.get_sq('e', pos[1].get_number()));
						return true;
					}
				}
				else return false;
			}
			else if (pos[0].get_letter() != '0') {
				if (castling_decision()) {
					do_castling(*chessboard.get_sq(pos[0].get_letter(), pos[0].get_number()), *chessboard.get_sq('e', pos[0].get_number()));
					return true;
				}
				else return false;
			}
			else if (pos[1].get_letter() != '0') {
				if (castling_decision())
				{
					do_castling(*chessboard.get_sq(pos[1].get_letter(), pos[1].get_number()), *chessboard.get_sq('e', pos[1].get_number()));
					return true;
				}
				else return false;
			}
		}
	}
	return false;
}

void Game::possible_castling(Position pos[], Position temp_pos, char first_let, char second_let, Square king_sq, int i)  //DOPISAÆ, ¿eby position ju¿ domylnie wyoe³niony by³ zerami!!!!!!!!!!!!!!!!!!!!!!
{
	if (chessboard.get_sq(temp_pos.get_letter(), temp_pos.get_number())->get_piece()->correct_move(Square{ *chessboard.get_sq(temp_pos.get_letter(), temp_pos.get_number()) },
		Square{ *chessboard.get_sq(first_let, temp_pos.get_number()) }, *last_mv.sq_to, chessboard)) {
		//empty fields for castling

		if (!king_thr(king_sq.get_color())) {  //king aren't threatened

			chessboard.get_sq(first_let, temp_pos.get_number())->set_piece(king_sq.get_piece());
			active_square->set_piece(nullptr);

			if (!king_thr(king_sq.get_color())) {  //king aren't threatend on second field

				chessboard.get_sq(second_let, temp_pos.get_number())->set_piece(king_sq.get_piece());
				chessboard.get_sq(first_let, temp_pos.get_number())->set_piece(nullptr);

				if (!king_thr(chessboard.get_sq(second_let, temp_pos.get_number())->get_color())) {
					pos[i] = Position{ temp_pos.get_letter(), temp_pos.get_number() };
					//if all 3 squares for castling aren't threatend -> give information about possible castling

				}
				else pos[i] = Position{ '0', '0' };
			}
			else pos[i] = Position{ '0', '0' };
		}
		else pos[i] = Position{ '0', '0' };

		active_square->set_piece(king_sq.get_piece());
		chessboard.get_sq(second_let, temp_pos.get_number())->set_piece(nullptr);
		chessboard.get_sq(first_let, temp_pos.get_number())->set_piece(nullptr);
		//setting pieces up on old positions
	}
	else {
		pos[i] = Position{ '0', '0' };
	}
}

void Game::find_rook_castling(Position pos[])
{
	char let = 'a', num;

	if (act_color == white) { num = '1'; }
	else num = '8';

	for (int i = 0; i < 2; i++) {

		if (i == 1) { let = 'h'; }

		if (chessboard.get_sq(let, num)->get_piece()) {
			if (chessboard.get_sq(let, num)->get_piece()->is_it_rook() && !chessboard.get_sq(let, num)->get_moves_count()) {
				//exist rook which wasn't moved with the same rank

				char first_let = 'f', second_let = 'g';
				Position temp_pos{ let, num };
				Square king_sq = *active_square;

				if (active_square->get_letter() - chessboard.get_sq(let, num)->get_letter() < 0) {  //rook on the right side of king
					possible_castling(pos, temp_pos, first_let, second_let, king_sq, i);
				}
				else {  //rook on the left side of king
					first_let = 'd';
					second_let = 'c';
					possible_castling(pos, temp_pos, first_let, second_let, king_sq, i);
				}
			}
			else pos[i] = Position{ '0', '0' };
		}
		else pos[i] = Position{ '0', '0' };
	}
}

void Game::do_castling(Square &rook_sq, Square &king_sq)
{
	char first_let, second_let;

	if (rook_sq.get_letter() == 'a') {
		first_let = 'd';
		second_let = 'c';
	}
	else {
		first_let = 'f';
		second_let = 'g';
	}
	++*(king_sq.get_piece());
	++*(rook_sq.get_piece());
	chessboard.get_sq(first_let, rook_sq.get_number())->set_piece(rook_sq.get_piece());
	chessboard.get_sq(second_let, rook_sq.get_number())->set_piece(king_sq.get_piece());
	king_sq.set_piece(nullptr);
	rook_sq.set_piece(nullptr);
	change_color(act_color);
	king_sq.set_choosen(false);
	change_text_turn();
	text.setString("Please choose correct piece.");

}

bool Game::castling_decision()
{
	text.setString("Do you want move castling?\n1 - yes, 2 - no.");
	chessboard.display(window, *active_square, text, text_turn);
	sf::Event event;
	do {
		window.waitEvent(event);
	} while (event.key.code != sf::Keyboard::Num1 && event.key.code != sf::Keyboard::Num2);

	if (event.key.code == sf::Keyboard::Num2) return false;

	return true;
}

bool Game::thr_reaction()
{
	if (king_thr(act_color)) {
		text.setString("Your king is threatened.\nPlease do correct move.");
		chessboard.display(window, *active_square, text, text_turn);
		thr_king_sound();
		if (is_checkmate()) {
			end_game(false);
			return true;
		}
		else after_check();
	}
	return false;
}

bool Game::is_statement()
{
	if (possible_mv_stat())
		return true;

	if (optional_statement())
		return true;

	return false;
}

bool Game::possible_mv_stat()
{
	if (!king_thr(act_color)) {
		if (!is_checkmate()) {

			for (char let_fr = 'a'; let_fr <= 'h'; let_fr++) {
				for (char num_fr = '1'; num_fr <= '8'; num_fr++) {
					if (chessboard.get_sq(let_fr, num_fr)) {
						if (chessboard.get_sq(let_fr, num_fr)->get_color() == act_color) {
							for (char let_to = 'a'; let_to <= 'h'; let_to++) {
								for (char num_to = '1'; num_to <= '8'; num_to++) {
									if (chessboard.get_sq(let_fr, num_fr)->get_piece()->correct_move(*chessboard.get_sq(let_fr, num_fr), *chessboard.get_sq(let_to, num_to), *last_mv.sq_to, chessboard)) return false;
									//possible move
								}
							}
						}
					}
				}
			} return true;

		} return false;
	}
	return false;
}

bool Game::optional_statement()
{
	Square pieces[2];
	int index = 0;
	pieces[0].set_piece(nullptr);
	pieces[1].set_piece(nullptr);
	pieces[0].set_position('0', '0');
	pieces[1].set_position('0', '0');
	Color color;

	for (char let = 'a'; let <= 'h'; let++) {
		for (char num = '1'; num <= '8'; num++) {
			if (chessboard.get_sq(let, num)->get_piece()) {
				if (!chessboard.get_sq(let, num)->get_piece()->is_it_king() && !chessboard.get_sq(let, num)->get_piece()->is_it_bishop() && !chessboard.get_sq(let, num)->get_piece()->is_it_knight())
					return false;

				if (!chessboard.get_sq(let, num)->get_piece()->is_it_king()) {
					if (index == 2) return false;
					if (index == 0)  color = chessboard.get_sq(let, num)->get_color();
					if (color == chessboard.get_sq(let, num)->get_color()) {
						pieces[index] = *chessboard.get_sq(let, num);
						index++;
						change_color(color);
					}
					else return false;
				}
			}
		}
	}
	if (!pieces[0].get_piece() && !pieces[1].get_piece()) return true;
	else if (pieces[0].get_piece()->is_it_bishop() && !pieces[1].get_piece()) return true;
	else if (pieces[0].get_piece()->is_it_knight() && !pieces[1].get_piece()) return true;
	else if (pieces[0].get_piece()->is_it_bishop() && pieces[1].get_piece()->is_it_bishop()) {
		if (pieces[0].get_sq_color() == pieces[1].get_sq_color()) return true;
		return false;
	}
	else return false;
}

void Game::control() {

	while (window.waitEvent(event)) {
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Up) {
				if (active_square->get_number() == '1')
					active_square = chessboard.get_sq(active_square->get_letter(), '8');   // move to up border
				else
					active_square = &chessboard(active_square->get_letter(), active_square->get_number() - 1);
			}
			else if (event.key.code == sf::Keyboard::Left) {
				if (active_square->get_letter() == 'a')
					active_square = chessboard.get_sq('h', active_square->get_number());   // move to right border
				else
					active_square = chessboard.get_sq(active_square->get_letter() - 1, active_square->get_number());  // move left
			}
			else if (event.key.code == sf::Keyboard::Right) {
				if (active_square->get_letter() == 'h')
					active_square = chessboard.get_sq('a', active_square->get_number());   // move to left border
				else
					active_square = chessboard.get_sq(active_square->get_letter() + 1, active_square->get_number());  // move right
			}
			else if (event.key.code == sf::Keyboard::Down) {
				if (active_square->get_number() == '8')
					active_square = chessboard.get_sq(active_square->get_letter(), '1');   // move to down border
				else
					active_square = chessboard.get_sq(active_square->get_letter(), active_square->get_number() + 1);   // move up
			}
			else if (event.key.code == sf::Keyboard::Escape)
			{
				sound.resetBuffer();
				save_menu();
				music.stop();
				window.close();
			}
			else if (event.key.code == sf::Keyboard::Enter) {
				return;
			}
			chessboard.display(window, *active_square, text, text_turn);
		}
		else if (event.type == sf::Event::Closed) {
			sound.resetBuffer();
			save_menu();
			music.stop();
			window.close();
		}
	}
}

Game::last_move::last_move()
{
	piece_from = nullptr;
	piece_to = nullptr;
	sq_from = nullptr;
	sq_to = nullptr;
}

#pragma endregion Game.cpp

#pragma region  King.cpp

King::King(Color col)
{
	color = { col };
	moves_count = { 0 };
	choosen = { false };
	in_game = true;
	sq_color = none;
	set_sprite();
	set_rect();
}

King::King()
{
	color = none;
	sq_color = none;
	moves_count = { 0 };
	choosen = { false };
	in_game = true;
	set_rect();
}

bool King::correct_move(Square mv_fr, Square mv_to, Square last_ene_mv, Chessboard &chessboard) {

	if (!first_cond(mv_fr, mv_to)) return false;

	if (abs(mv_to.get_letter() - mv_fr.get_letter()) < 2 && abs(mv_to.get_number() - mv_fr.get_number()) < 2) {
		if (mv_to.get_number() == mv_fr.get_number() && mv_to.get_letter() == mv_fr.get_letter()) return false;
	}
	else return false;
	//verify does King moved at most only one square and it wasn't move on the same square

	return true;
}

void King::set_sprite() {
	if (!texture.loadFromFile("figures.png")) //loading texture
	{
		throw std::string{ "load king's texture error" };
	}
	sprite.setTexture(texture);

	//setting rectangle sprite up
	if (color == white)
		sprite.setTextureRect(sf::IntRect(WIDTH_PIECE * 4, HEIGHT_PIECE, WIDTH_PIECE, HEIGHT_PIECE));
	else sprite.setTextureRect(sf::IntRect(WIDTH_PIECE * 4, ZERO, WIDTH_PIECE, HEIGHT_PIECE));

	sprite.setScale(1.45f, 1.45f);
}


#pragma endregion King.cpp

#pragma region Knight.cpp

Knight::Knight(Color col) {
	color = { col };
	sq_color = none;
	moves_count = { 0 };
	choosen = { false };
	in_game = true;
	set_rect();
	set_sprite();
}

Knight::Knight()
{
	color = none;
	sq_color = none;
	moves_count = { 0 };
	choosen = { false };
	in_game = true;
	set_rect();
}

void Knight::set_sprite() {
	if (!texture.loadFromFile("figures.png")) //loading texture
	{
		throw std::string{ "load knight's texture error" };
	}
	sprite.setTexture(texture);

	//setting rectangle sprite up
	if (color == white)
		sprite.setTextureRect(sf::IntRect(WIDTH_PIECE, HEIGHT_PIECE, WIDTH_PIECE, HEIGHT_PIECE));
	else sprite.setTextureRect(sf::IntRect(WIDTH_PIECE, ZERO, WIDTH_PIECE, HEIGHT_PIECE));

	sprite.setScale(1.45f, 1.45f);
}

bool Knight::correct_move(Square mv_fr, Square mv_to, Square last_ene_mv, Chessboard &board) {

	if (!first_cond(mv_fr, mv_to)) return false;

	if (abs(mv_to.get_number() - mv_fr.get_number()) == 2 && abs(mv_to.get_letter() - mv_fr.get_letter()) == 1) return true;
	else if (abs(mv_to.get_number() - mv_fr.get_number()) == 1 && abs(mv_to.get_letter() - mv_fr.get_letter()) == 2) return true;

	return false;
}

#pragma endregion Knight.cpp

#pragma region Pawn.cpp

Pawn::Pawn(Color col) {
	color = { col };
	sq_color = none;
	moves_count = { 0 };
	choosen = { false };
	in_game = true;
	set_sprite();
	set_rect();
}

Pawn::Pawn()
{
	color = none;
	sq_color = none;
	moves_count = { 0 };
	choosen = { false };
	in_game = true;
	set_rect();
}

void Pawn::set_sprite() {
	if (!texture.loadFromFile("figures.png")) //loading texture
	{
		throw std::string("load pawn's texture error");
	}
	sprite.setTexture(texture);

	//setting rectangle sprite up
	if (color == white)
		sprite.setTextureRect(sf::IntRect(WIDTH_PIECE * 5, HEIGHT_PIECE, WIDTH_PIECE, HEIGHT_PIECE));
	else sprite.setTextureRect(sf::IntRect(WIDTH_PIECE * 5, ZERO, WIDTH_PIECE, HEIGHT_PIECE));

	sprite.setScale(1.45f, 1.45f);
}

bool Pawn::correct_move(Square mv_fr, Square mv_to, Square last_ene_mv, Chessboard &board) {

	if (!first_cond(mv_fr, mv_to)) return false;

	Square *temp_sq;
	int	upr_diff = mv_to.get_number() - mv_fr.get_number();

	if (mv_fr.get_letter() == mv_to.get_letter() && mv_to.get_piece() == nullptr && !mv_fr.get_moves_count()
		&& empty_sq_rook(upright, upr_diff, mv_fr, board)) {

		if (upr_diff == 2 && mv_fr.get_color() == white) return true;
		else if (upr_diff == 1 && mv_fr.get_color() == white) return true;
		else if (upr_diff == -2 && mv_fr.get_color() == black) return true;
		else if (upr_diff == -1 && mv_fr.get_color() == black) return true;
	}  //First move of Pawn
	else if (mv_to.get_letter() == mv_fr.get_letter() && mv_to.get_piece() == nullptr) {

		if (mv_fr.get_color() == white && upr_diff == 1) return true;
		else if (mv_fr.get_color() == black && upr_diff == -1) return true;
	}  //move Pawn one square forward

	else if (abs(mv_fr.get_letter() - mv_to.get_letter()) == 1) {
		if (upr_diff == 1 && mv_to.get_color() == black && mv_fr.get_color() == white) return true;
		else if (upr_diff == -1 && mv_to.get_color() == white && mv_fr.get_color() == black) return true;
	} // capture obliquely


	else if (last_ene_mv.get_color() == white && last_ene_mv.get_piece()->is_it_pawn() && mv_to.get_number() == '3' && mv_fr.get_number() == '4' && last_ene_mv.get_number() == '4') {
		temp_sq = board.get_sq(mv_to.get_letter(), '3');
		temp_sq->set_piece(nullptr);
		return true;
	}  //En passant for black Pawn
	else if (last_ene_mv.get_color() == black && last_ene_mv.get_piece()->is_it_pawn() && mv_to.get_number() == '6' && mv_fr.get_number() == '5' && last_ene_mv.get_number() == '5') {
		temp_sq = board.get_sq(mv_to.get_letter(), '4');
		temp_sq->set_piece(nullptr);
		return true;
	} //En passant for white Pawn

	return false;
}

#pragma endregion Pawn.cpp

#pragma region Piece.cpp

Color Piece::get_color() {
	return color;
}

void Piece::set_color(Color col)
{
	color = col;
	in_game = true;
	set_sprite();
}

Color Piece::get_sq_color()
{
	return sq_color;
}

void Piece::set_sq_color(Color col)
{
	sq_color = col;
}

void Piece::change_in_game(bool val)
{
	in_game = val;
}

void Piece::display(sf::RenderWindow &window, Position pos) {

	if (choosen) display_rec(window, pos);

	sprite.setPosition((float)(EDGE_WIDTH + FIELD_SIZE * (pos.get_letter() - 'a')), (float)(EDGE_WIDTH + FIELD_SIZE * (pos.get_number() - '1')));
	sprite.setScale(1.45f, 1.45f);
	window.draw(sprite);
}

void Piece::set_rect()
{
	rect.setOutlineColor(out_color);
	rect.setSize(sf::Vector2f(field_size, field_size));
	rect.setOutlineThickness(-4.f);
	rect.setFillColor(rect_color);
}

void Piece::display_rec(sf::RenderWindow &win, Position pos) {

	rect.setPosition(edge_width + (pos.get_letter() - 'a') * field_size, edge_width + (pos.get_number() - '1') * field_size);
	win.draw(rect);
}

bool Piece::empty_sq_rook(Orientation ort, int diff, Square mv_fr, Chessboard board)
{
	Square *temp_sq;
	if (diff) {
		if (diff < 0) diff++;
		else diff--;

		switch (ort) {
		case horizontally:
			while (abs(diff) > 0) {
				temp_sq = board.get_sq(mv_fr.get_letter() + diff, mv_fr.get_number());
				if (temp_sq->get_piece()) return false;
				//veryfying if all squares between initial and target square are empty horizontally 
				if (diff < 0) diff++;
				else diff--;
			}
			break;

		case upright:
			while (abs(diff) > 0) {
				temp_sq = board.get_sq(mv_fr.get_letter(), mv_fr.get_number() + diff);
				if (temp_sq->get_piece()) return false;
				//veryfying if all squares between initial and target square are empty upright
				if (diff < 0) diff++;
				else diff--;
			}
		}
	}
	return true;

}

bool Piece::empty_sq_bishop(int diff_hor, int diff_upr, Square mv_fr, Chessboard board)
{
	Square *temp_sq;
	if (diff_hor) {
		if (diff_hor < 0) diff_hor++; else diff_hor--;
		if (diff_upr < 0) diff_upr++; else diff_upr--;

		while (abs(diff_hor) > 0) {
			temp_sq = board.get_sq(mv_fr.get_letter() + diff_hor, mv_fr.get_number() + diff_upr);
			if (temp_sq->get_piece()) return false;

			if (diff_hor < 0) diff_hor++; else diff_hor--;
			if (diff_upr < 0) diff_upr++; else diff_upr--;
		}
	}
	return true;
}

void Piece::set_choosen(bool ch) {
	choosen = ch;
}

bool Piece::get_choosen() {
	return choosen;
}

int Piece::get_moves_count() {
	return moves_count;
}

void Piece::operator++()
{
	moves_count++;
}

void Piece::operator--()
{
	moves_count--;
}

bool Piece::first_cond(Square mv_fr, Square mv_to) {
	if ((mv_fr.get_color() == mv_to.get_color())) return false;

	return true;
}

std::fstream & operator<<(std::fstream & stream, Piece & piece)
{
	if (piece.color == white) stream << '1';
	else if (piece.color == black) stream << '2';
	if (piece.color == none) stream << '0';

	stream << ' ';
	if (piece.sq_color == white) stream << '1';
	else if (piece.sq_color == black) stream << ('2');
	if (piece.sq_color == none) stream << '0';

	stream << ' ';

	stream << piece.moves_count;  //int
	stream << ' ';
	stream << piece.choosen;  //bool
	stream << ' ';
	stream << piece.in_game; //bool
	stream << ' ';
	return stream;
}

std::fstream & operator>>(std::fstream & stream, Piece *piece)
{
	int buffer_int;
	bool buffer_bool;
	char buffer_ch;
	stream >> buffer_ch;

	piece->color = (Color)(buffer_ch - '0');
	stream >> buffer_ch;
	piece->sq_color = (Color)(buffer_ch - '0');
	stream >> buffer_int;
	piece->moves_count = buffer_int;
	stream >> buffer_bool;
	piece->choosen = buffer_bool;
	stream >> buffer_bool;
	piece->in_game = buffer_bool;
	piece->set_sprite();

	return stream;
}

#pragma endregion Piece.cpp

#pragma region Position.cpp

Position::Position() : letter('0'), number('0')
{}

Position::Position(char let, char num) : letter(let), number(num)
{}

Position& Position::operator=(Position &&pos) {
	if (this == &pos) {
		return *this;
	}
	else {
		number = pos.number;
		letter = pos.letter;
	}
	return *this;
}

void Position::set_letter(char let) {
	letter = let;
}

void Position::set_number(char num) {
	number = num;
}

char Position::get_letter() {
	return letter;
}

char Position::get_number() {
	return number;
}

std::fstream & operator<<(std::fstream & stream, Position & pos)
{
	stream << pos.letter;
	stream << ' ';
	stream << pos.number;
	stream << ' ';
	return stream;
}

std::fstream & operator>>(std::fstream & stream, Position & pos)
{
	stream >> pos.letter;
	stream >> pos.number;

	return stream;
}

#pragma endregion Position.cpp

#pragma region Queen.cpp

Queen::Queen(Color col) {
	color = { col };
	sq_color = none;
	moves_count = { 0 };
	choosen = { false };
	in_game = true;
	set_sprite();
	set_rect();
}

Queen::Queen()
{
	color = none;
	sq_color = none;
	moves_count = { 0 };
	choosen = { false };
	in_game = true;
	set_rect();

}

bool Queen::correct_move(Square mv_fr, Square mv_to, Square last_ene_mv, Chessboard &board) {

	if (!first_cond(mv_fr, mv_to)) return false;

	if (abs(mv_fr.get_letter() - mv_to.get_letter()) == abs(mv_fr.get_number() - mv_to.get_number()) && (mv_to.get_number() != mv_fr.get_number()))
	{  //Bishop's move style

		if (!empty_sq_bishop(mv_to.get_letter() - mv_fr.get_letter(), mv_to.get_number() - mv_fr.get_number(), mv_fr, board))
			return false;

		else return true;
	}
	else if (mv_to.get_letter() == mv_fr.get_letter() || mv_to.get_number() == mv_fr.get_number()) //Rook's type move
	{
		if (mv_to.get_letter() == mv_fr.get_letter() && mv_to.get_number() == mv_fr.get_number()) return false;
		//if Rook haven't moved 

		if (!empty_sq_rook(horizontally, mv_to.get_letter() - mv_fr.get_letter(), mv_fr, board)) return false;
		if (!empty_sq_rook(upright, mv_to.get_number() - mv_fr.get_number(), mv_fr, board)) return false;
		//chceking are empty squares between square starting and target place for Rook
		return true;
	}
	else return false;

}

void Queen::set_sprite() {
	if (!texture.loadFromFile("figures.png")) //loading texture
	{
		throw std::string{ "load queen texture error" };
	}
	sprite.setTexture(texture);


	//setting rectangle sprite up
	if (color == white)
		sprite.setTextureRect(sf::IntRect(WIDTH_PIECE * 3, HEIGHT_PIECE, WIDTH_PIECE, HEIGHT_PIECE));
	else sprite.setTextureRect(sf::IntRect(WIDTH_PIECE * 3, ZERO, WIDTH_PIECE, HEIGHT_PIECE));

	sprite.setScale(1.45f, 1.45f);
}

#pragma endregion Queen.cpp

#pragma region Rook.cpp

Rook::Rook(Color col) {
	color = { col };
	sq_color = none;
	moves_count = { 0 };
	choosen = { false };
	in_game = true;
	set_sprite();
	set_rect();
}

Rook::Rook()
{
	color = none;
	sq_color = none;
	moves_count = { 0 };
	choosen = { false };
	in_game = true;
	set_rect();
}


bool Rook::correct_move(Square mv_fr, Square mv_to, Square last_ene_mv, Chessboard &board) {
	if (!first_cond(mv_fr, mv_to)) return false;
	//verify does Rook move on square on which lie piece in the same colour

	if (mv_to.get_letter() == mv_fr.get_letter() || mv_to.get_number() == mv_fr.get_number())
	{
		if (mv_to.get_letter() == mv_fr.get_letter() && mv_to.get_number() == mv_fr.get_number()) return false;
		//if Rook haven't moved 

		if (!empty_sq_rook(horizontally, mv_to.get_letter() - mv_fr.get_letter(), mv_fr, board)) return false;
		if (!empty_sq_rook(upright, mv_to.get_number() - mv_fr.get_number(), mv_fr, board)) return false;
		//chceking are empty squares between square starting and target place for Rook
		return true;
	}
	return false;
}

void Rook::set_sprite() {
	if (!texture.loadFromFile("figures.png")) //loading texture
	{
		throw std::string{ "load rook's texture error" };
	}
	sprite.setTexture(texture);


	//setting rectangle sprite up
	if (color == white)
		sprite.setTextureRect(sf::IntRect(ZERO, HEIGHT_PIECE, WIDTH_PIECE, HEIGHT_PIECE));
	else sprite.setTextureRect(sf::IntRect(ZERO, ZERO, WIDTH_PIECE, HEIGHT_PIECE));

	sprite.setScale(1.45f, 1.45f);
}

#pragma endregion Rook.cpp

#pragma region Square.cpp

Square::Square(Position &&pos, Piece * p_ptr) :position(pos), piece_ptr(p_ptr)
{}

Square::Square(Position pos) : position(pos) {
	piece_ptr = nullptr;
}

Square::Square() {
	piece_ptr = nullptr;
}

Position Square::get_position() const {
	return position;
}

char Square::get_number()
{
	return position.get_number();
}

char Square::get_letter()
{
	return position.get_letter();
}

Color Square::get_color() const
{
	if (piece_ptr)
		return piece_ptr->get_color();

	return none;
}

Color Square::get_sq_color()
{
	if (piece_ptr) return piece_ptr->get_sq_color();
	else return none;
}

void Square::set_position(char let, char num) {
	position.set_letter(let);
	position.set_number(num);
}

void Square::set_piece(Piece *pc) {

	piece_ptr = pc;
}

Piece * Square::get_piece() const
{
	if (!this->piece_ptr) return nullptr;

	return piece_ptr;
}

void Square::display(sf::RenderWindow &window) {

	if (piece_ptr) {
		piece_ptr->display(window, position);
	}
}

Square & Square::operator=(const Square & origin)
{
	if (this == &origin) {
		return *this;
	}
	else {
		position = origin.get_position();
		piece_ptr = origin.get_piece();
		return *this;
	}
}

void Square::load_fr_file(std::fstream &stream, Chessboard &board)
{
	stream >> position;

	char buf;
	stream >> buf;
	if (buf == '1') {
		stream >> buf;

		if (buf == 'K') {
			King *king = board.get_king();
			stream >> king;
			set_piece(king);
		}
		else if (buf == 'Q') {
			Queen *queen = board.get_queen();
			stream >> queen;
			set_piece(queen);
		}
		else if (buf == 'B') {
			Bishop *bishop = board.get_bishop();
			stream >> bishop;
			set_piece(bishop);
		}
		else if (buf == 'N') {
			Knight *knight = board.get_knight();
			stream >> knight;
			set_piece(knight);
		}
		else if (buf == 'R') {
			Rook *rook = board.get_rook();
			stream >> rook;
			set_piece(rook);
		}
		else if (buf == 'P') {
			Pawn *pawn = board.get_pawn();
			stream >> pawn;
			set_piece(pawn);
		}
	}
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

std::fstream & operator<<(std::fstream & stream, Square & sq)
{
	stream << sq.position;

	if (sq.piece_ptr)
	{
		stream << '1';
		stream << ' ';
		if (sq.get_piece()->is_it_king())
			stream << 'K';
		else if (sq.get_piece()->is_it_queen())
			stream << 'Q';
		else if (sq.get_piece()->is_it_bishop())
			stream << 'B';
		else if (sq.get_piece()->is_it_knight())
			stream << 'N';
		else if (sq.get_piece()->is_it_rook())
			stream << 'R';
		else if (sq.get_piece()->is_it_pawn())
			stream << 'P';
		stream << ' ';
		//information about type of piece

		stream << *sq.piece_ptr;

	}
	else stream << '0';
	stream << ' ';
	return stream;
}

std::fstream & operator>>(std::fstream & stream, Square & sq)
{
	stream >> sq.position;
	return stream;
}

#pragma endregion Square.cpp

#include <Windows.h>

int main() {

	Game game;
	game.main_menu();

	return 0;
}