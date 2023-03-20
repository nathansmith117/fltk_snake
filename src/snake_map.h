#pragma once

#include "program_data.h"
#include "snake_utils.h"

class SnakeMap : public Fl_Group {
	public:
		SnakeMap(MainData * md) : Fl_Group(0, 0, 0, 0) {
			main_init(md);
		}

		void draw();
		int handle(int event);
		void update();

		// Always reset size first then snake.
		void reset_size();
		void reset_snake();
		void reset_snack();
		void reset_all();

		SNAKE_DIR snake_direction() { return direction; }
		void snake_direction(SNAKE_DIR direction) { this->direction = direction; }

		void add_snake_block();

		void update_length_output();
	private:
		MainData * mdata;
		SNAKE_DIR direction = SNAKE_STILL;
		SnakeSnack snack;

		std::vector<SnakeBlock> snake_blocks;

		void main_init(MainData * md);
		bool snake_block_out_of_bounds(SnakeBlock snake_block);
};
