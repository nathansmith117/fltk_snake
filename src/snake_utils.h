#pragma once

#include "program_data.h"

enum SNAKE_DIRECTIONS {
	SNAKE_STILL,
	SNAKE_RIGHT,
	SNAKE_LEFT,
	SNAKE_UP,
	SNAKE_DOWN
};

typedef unsigned char SNAKE_DIR;

enum SNAKE_PARTS {
	SNAKE_HEAD,
	SNAKE_BODY,
	SNAKE_TAIL
};

typedef unsigned char SNAKE_PART;

struct SnakeBlock {
	SNAKE_PART part;
	SNAKE_DIR current_direction;
	int x, y;
};

// Please dont sue.  Its open source software.
enum SNACKS_TYPES {
	REMY_THE_RAT = 0, // From a movie about a rat that cooks which is kind of gross
				  // when you think about it.
	FRIENDLY_FROG = 1, // Something I made up.
	EASTER_BUNNY = 2, // Hopefully not copyrighted.  If so my childhood was a lie
				  // )---:
	GIDGET_THE_POMERANIAN = 3, // A dogo in a movie made for a generation of childen
						   // that cant sit through an entire movie.
	CHILD_PERSON = 4, // What the hell is a child person?
	BIG_BIRD = 5 // A big fat bird that hants peoples nightmears.
};

#define SNACK_COUNT 5

// You can put your lawers away now, Chairen (I most like messspeld 'Chairen'
// but thats ok because I am a Utard).

typedef unsigned char SNACK_TYPE;

struct SnakeSnack {
	SNACK_TYPE type;
	int x, y; // Tile position on snake map.
};

bool snake_blocks_hit(int tile_size, SnakeBlock b1, SnakeBlock b2);
bool snake_block_eat_snack(int tile_size, const Fl_Group * snake_map, SnakeBlock snake_block, SnakeSnack snack);

int put_snake_blocks_side_by_side(int tile_size, SnakeBlock * b1, SnakeBlock b2);

int random_range(int x, int y);

// Drawing.
void draw_snake_block(MainData * mdata, SnakeBlock snake_block);
void draw_snake(MainData * mdata, std::vector<SnakeBlock> snake_blocks);

// 'Fl_Group * snake_map' is just the SnakeMap.
void draw_snack(MainData * mdata, const Fl_Group * snake_map, SnakeSnack snack);

int str_to_int(const char * str, size_t n, int * int_value);
int char_to_int(char c);

void set_snack_images_to_tile_size(MainData * mdata);
