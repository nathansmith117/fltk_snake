#include "snake_map.h"

void SnakeMap::main_init(MainData * md) {
	mdata = md;

	end();
	reset_all();
}

void SnakeMap::draw() {
	fl_rectf(x(), y(), w(), h(), color());
	fl_rect(x(), y(), w(), h(), 0x0);

	draw_snake(mdata, snake_blocks);
	draw_snack(mdata, this, snack);
}

int SnakeMap::handle(int event) {
	switch (event) {
		case FL_FOCUS:
		case FL_UNFOCUS:
			return 1;
		case FL_KEYDOWN:

			if (mdata->paused)
				goto end_of_keydown;

			switch (Fl::event_key()) {
				case FL_Right:
					if (direction != SNAKE_LEFT)
						direction = SNAKE_RIGHT;

					break;
				case FL_Left:
					if (direction != SNAKE_RIGHT)
						direction = SNAKE_LEFT;

					break;
				case FL_Up:
					if (direction != SNAKE_DOWN)
						direction = SNAKE_UP;

					break;
				case FL_Down:
					if (direction != SNAKE_UP)
						direction = SNAKE_DOWN;

					break;
				default:
					break;
			}

end_of_keydown: // Yes I know. goto sucks.
			mdata->win->handle(FL_SHORTCUT); // A hack for keyboard shortcuts.
			return 1;
		case FL_KEYUP:
			return 1;
		default:
			return 0;
	}
}

void SnakeMap::update() {
	int i;
	SnakeBlock block_behind;
	SNAKE_DIR snake_dir;

	if (mdata->paused)
		return;

	// Set head direction.
	snake_blocks.front().current_direction = direction;

	// Update snake blocks.
	for (i = 0; i < snake_blocks.size(); i++) {

		// Update direction.
		snake_dir = snake_blocks[i].current_direction;

		// Go to update_position if head.
		if (i == 0)
			goto update_position;

		block_behind = snake_blocks[i - 1];

		switch (block_behind.current_direction) {
			case SNAKE_STILL:
				break;
			case SNAKE_RIGHT:
				snake_dir = (snake_blocks[i].y > block_behind.y) ? SNAKE_UP : SNAKE_DOWN;

				// Set to same direction.
				if (abs(snake_blocks[i].y - block_behind.y) <= mdata->settings.snake_speed)
					snake_dir = SNAKE_RIGHT;
				break;
			case SNAKE_LEFT:
				snake_dir = (snake_blocks[i].y > block_behind.y) ? SNAKE_UP : SNAKE_DOWN;

				if (abs(snake_blocks[i].y - block_behind.y) <= mdata->settings.snake_speed)
					snake_dir = SNAKE_LEFT;
				break;
			case SNAKE_UP:
				snake_dir = (snake_blocks[i].x > block_behind.x) ? SNAKE_LEFT : SNAKE_RIGHT;

				if (abs(snake_blocks[i].x - block_behind.x) <= mdata->settings.snake_speed)
					snake_dir = SNAKE_UP;
				break;
			case SNAKE_DOWN:
				snake_dir = (snake_blocks[i].x > block_behind.x) ? SNAKE_LEFT : SNAKE_RIGHT;

				if (abs(snake_blocks[i].x - block_behind.x) <= mdata->settings.snake_speed)
					snake_dir = SNAKE_DOWN;
				break;
			default:
				break;
		}

		// Set new direction value.
		snake_blocks[i].current_direction = snake_dir;
		put_snake_blocks_side_by_side(mdata->settings.tile_size, &snake_blocks[i], block_behind);
		
update_position:
		// Update position.
		switch (snake_dir) {
			case SNAKE_STILL:
				break;
			case SNAKE_RIGHT:
				snake_blocks[i].x += mdata->settings.snake_speed;
				break;
			case SNAKE_LEFT:
				snake_blocks[i].x -= mdata->settings.snake_speed;
				break;
			case SNAKE_UP:
				snake_blocks[i].y -= mdata->settings.snake_speed;
				break;
			case SNAKE_DOWN:
				snake_blocks[i].y += mdata->settings.snake_speed;
				break;
			default:
				break;
		}

		// Hit self (but not the first and second block).
		if (mdata->settings.die_when_hit_self && i > 2)
			if (snake_blocks_hit(mdata->settings.tile_size, snake_blocks.front(), snake_blocks[i])) {
				reset_all();
				return;
			}
	}

	// Check is out of bounds.
	if (snake_block_out_of_bounds(snake_blocks.front())) {
		reset_all();
		return;
	}

	// Eat yummies.
	if (snake_block_eat_snack(mdata->settings.tile_size, this, snake_blocks.front(), snack)) {
		reset_snack();
		add_snake_block();
		return;
	}
}

void SnakeMap::reset_size() {
	w(mdata->settings.tile_size * mdata->settings.tile_count_w);
	h(mdata->settings.tile_size * mdata->settings.tile_count_h);

	// Center.
	position(
		(mdata->win->w() / 2) - (w() / 2),
		(mdata->win->h() / 2) - (h() / 2)
	);

	mdata->win->redraw();
}

void SnakeMap::reset_snake() {
	direction = SNAKE_STILL;
	snake_blocks.clear();

	// Create snake head.
	SnakeBlock head_block;
	head_block.part = SNAKE_HEAD;
	head_block.current_direction = SNAKE_STILL;

	// Center snake.
	head_block.x = x() + (w() / 2);
	head_block.y = y() + (h() / 2);

	snake_blocks.push_back(head_block);
	update_length_output();
}

void SnakeMap::reset_snack() {
	snack.type = (SNACK_TYPE)random_range(0, SNACK_COUNT);
	snack.x = random_range(0, mdata->settings.tile_count_w - 1);
	snack.y = random_range(0, mdata->settings.tile_count_h - 1);
}

void SnakeMap::reset_all() {
	reset_size();
	reset_snake();
	reset_snack();
}

bool SnakeMap::snake_block_out_of_bounds(SnakeBlock snake_block) {
	int tile_size = mdata->settings.tile_size;

	bool x_out = (snake_block.x < x()) | (snake_block.x + tile_size > x() + w());
	bool y_out = (snake_block.y < y()) | (snake_block.y + tile_size > y() + h());

	return x_out | y_out;
}

void SnakeMap::add_snake_block() {
	SnakeBlock block_behind;
	block_behind = snake_blocks.back();

	if (snake_blocks.size() > 1)
		snake_blocks.back().part = SNAKE_BODY;

	// Create new block.
	SnakeBlock new_block;
	new_block.part = SNAKE_TAIL;
	new_block.current_direction = block_behind.current_direction;

	// Set position.
	put_snake_blocks_side_by_side(mdata->settings.tile_size, &new_block, block_behind);

	snake_blocks.push_back(new_block);
	update_length_output();
}

void SnakeMap::update_length_output() {
	if (mdata->length_output == NULL)
		return;

	char buf[NAME_MAX];
	memset(buf, 0, NAME_MAX);

	snprintf(buf, NAME_MAX, "%d", snake_blocks.size() - 1); // Head does not
															// count.
	mdata->length_output->value(buf);
}
