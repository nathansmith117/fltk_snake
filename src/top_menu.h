#pragma once

#include "program_data.h"
#include "snake_map.h"

void new_game_cb(Fl_Widget * w, void * d);
void pause_cb(Fl_Widget * w, void * d);

void add_menu_items(MainData * mdata, Fl_Menu_Bar * top_menu);
