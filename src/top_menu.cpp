#include "top_menu.h"


void new_game_cb(Fl_Widget * w, void * d) {
	MainData * mdata = (MainData*)d;

	mdata->snake_map->reset_all();
}

void pause_cb(Fl_Widget * w, void * d) {
	MainData * mdata = (MainData*)d;

	// Get button.
	Fl_Menu_Bar * menu_bar = (Fl_Menu_Bar*)w;
	const Fl_Menu_Item * button = menu_bar->mvalue();

	// Set paused.
	mdata->paused = (bool)button->value();
}

void add_menu_items(MainData * mdata, Fl_Menu_Bar * top_menu) {
	// Game.
	top_menu->add("&game/New game", FL_CTRL + 'n', (Fl_Callback*)new_game_cb, (void*)mdata);
	top_menu->add("&game/pause", 'p', (Fl_Callback*)pause_cb, (void*)mdata, FL_MENU_TOGGLE | (mdata->paused ? FL_MENU_VALUE : 0x0));
}
