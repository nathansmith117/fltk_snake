#include "program_data.h"
#include "app_window.h"
#include "snake_map.h"
#include "top_menu.h"
#include "snake_utils.h"

const char image_list[][NAME_MAX] = {
	"remy_the_rat.png",
	"friendly_frog.png",
	"easter_bunny.png",
	"gidget.png",
	"child_person.png",
	"big_bird.png"
};

void load_images(MainData * mdata) {
	char image_path[NAME_MAX];
	Fl_PNG_Image * new_image = NULL;

	for (auto img : image_list) {
		memset(image_path, 0, NAME_MAX);
		snprintf(image_path, NAME_MAX, "images/%s", img);

		printf("Loading %s\n", image_path);

		new_image = new Fl_PNG_Image(image_path);

		if (new_image->fail())
			fprintf(stderr, "Error loading %s\n", image_path);

		mdata->images.snack_images.push_back(new_image);
	}

	set_snack_images_to_tile_size(mdata);
}

int main(int argc, char ** argv) {
	MainData mdata;

	load_images(&mdata);

	// Create window.
	mdata.win = new AppWindow(
		&mdata,
		Fl::w() / 2,
		Fl::h() / 2,
		"FLTK snake"
	);

	// Snake map.
	mdata.snake_map = new SnakeMap(&mdata);

	// Top menu.
	mdata.top_menu = new Fl_Menu_Bar(
		0,
		0,
		mdata.win->w(),
		mdata.settings.top_menu_height
	);

	// Length output.
	mdata.length_output = new Fl_Output(
		(mdata.win->w() / 2) - (mdata.settings.output_width / 2),
		mdata.top_menu->h(),
		mdata.settings.output_width,
		mdata.settings.output_height,
		"Length"
	);

	mdata.length_output->value("0");

	add_menu_items(&mdata, mdata.top_menu);

	mdata.win->end();
	mdata.win->resizable(mdata.win);

	mdata.win->show(argc, argv);
	return Fl::run();
}
