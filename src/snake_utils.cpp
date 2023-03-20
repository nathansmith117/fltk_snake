#include "snake_utils.h"

bool snake_blocks_hit(int tile_size, SnakeBlock b1, SnakeBlock b2) {
	return b1.x + tile_size >= b2.x
		&& b1.x <= b2.x + tile_size
		&& b1.y + tile_size >= b2.y
		&& b1.y <= b2.y + tile_size;
}

bool snake_block_eat_snack(int tile_size, const Fl_Group * snake_map, SnakeBlock snake_block, SnakeSnack snack) {
	// Get snack x and y pixel locations.
	int snack_x, snack_y;
	snack_x = (snack.x * tile_size) + snake_map->x();
	snack_y = (snack.y * tile_size) + snake_map->y();

	return snake_block.x + tile_size >= snack_x
		&& snake_block.x <= snack_x + tile_size
		&& snake_block.y + tile_size >= snack_y
		&& snake_block.y <= snack_y + tile_size;
}

int put_snake_blocks_side_by_side(int tile_size, SnakeBlock * b1, SnakeBlock b2) {
	if (b1 == NULL)
		return -1;
	if (b1->current_direction != b2.current_direction)
		return -1;

	switch (b1->current_direction) {
		case SNAKE_STILL:
			break;
		case SNAKE_RIGHT:
			b1->x = b2.x - tile_size;
			b1->y = b2.y;
			break;
		case SNAKE_LEFT:
			b1->x = b2.x + tile_size;
			b1->y = b2.y;
			break;
		case SNAKE_UP:
			b1->x = b2.x;
			b1->y = b2.y + tile_size;
			break;
		case SNAKE_DOWN:
			b1->x = b2.x;
			b1->y = b2.y - tile_size;
			break;
		default:
			break;
	}

	return 0;
}

int random_range(int x, int y) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(x, y);

	return distr(gen);
}

void draw_snake_block(MainData * mdata, SnakeBlock snake_block) {
	Fl_Color draw_color;

	switch (snake_block.part) {
		case SNAKE_HEAD:
			draw_color = FL_BLACK;
			break;
		case SNAKE_BODY:
			draw_color = FL_YELLOW;
			break;
		case SNAKE_TAIL:
			draw_color = FL_BLUE;
			break;
		default:
			break;
	}

	fl_rectf(snake_block.x, snake_block.y, mdata->settings.tile_size, mdata->settings.tile_size, draw_color);
}

void draw_snake(MainData * mdata, std::vector<SnakeBlock> snake_blocks) {
	for (auto b : snake_blocks)
		draw_snake_block(mdata, b);
}

void draw_snack(MainData * mdata, const Fl_Group * snake_map, SnakeSnack snack) {
	Fl_PNG_Image * draw_image;
	int draw_x, draw_y;

	draw_image = mdata->images.snack_images_tile_size[snack.type];
	draw_x = (snack.x * mdata->settings.tile_size) + snake_map->x();
	draw_y = (snack.y * mdata->settings.tile_size) + snake_map->y();

	if (draw_image->fail()) {
		fl_rectf(
			draw_x,
			draw_y,
			mdata->settings.tile_size,
			mdata->settings.tile_size,
			0x0
		);

		return;
	}

	draw_image->draw(draw_x, draw_y);
}

int str_to_int(const char * str, size_t n, int * int_value) {
	int i;
	int cvalue;
	int value_muliplier = 1;
	int res_value = 0;
	int neg = 1; // -1 for negative and 1 for whole.
	size_t str_len; // String length.
	int end_at = 0; // Where loop should end.

	if (str == NULL || int_value == NULL || n <= 0)
		return -1;

	// Get string length
	str_len = strnlen(str, n);

	if (str_len <= 0)
		return -1;

	// Is negative.
	if (str[0] == '-') {
		neg = -1;
		end_at = 1; // If negative 0 item in 'str' is skipped.
	}

	// Do the math.
	for (i = str_len - 1; i >= end_at; i--) {
		cvalue = char_to_int(str[i]);

		// Character not a number.
		if (cvalue == -1)
			return -1;

		// Do the same math that is down below.
		res_value += cvalue * value_muliplier;
		value_muliplier *= 10;
	}

	/*
	 * "436"
	 * res_value = (6 * 1) + (3 * 10) + (4 * 100)
	*/

	*int_value = (res_value * neg);
	return 0;
}

int char_to_int(char c) {
	int cvalue = (int)c;

	// Not a number.
	// 48 to 57 is 0 to 9 in ascii.
	if (cvalue < 48 || cvalue > 57)
		return -1;

	return cvalue - 48; // 48 is the value of zero in ascii.
}

void set_snack_images_to_tile_size(MainData * mdata) {
	mdata->images.snack_images_tile_size.clear();

	for (auto img : mdata->images.snack_images)
		mdata->images.snack_images_tile_size.push_back(
			(Fl_PNG_Image*)img->copy(mdata->settings.tile_size, mdata->settings.tile_size)
		);
}
