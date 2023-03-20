#pragma once

// FLTK headers.
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/x.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Output.H>
#include <FL/fl_ask.H>
#include <FL/names.h>
#include <FL/fl_draw.H>

#define _USE_MATH_DEFINES

// C/C++ headers.
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <iostream>
#include <random>
#include <cmath>
#include <cstring>
#include <ctime>
#include <climits>
#include <vector>
#include <exception>
#include <cerrno>

// OS headers.
#include <sys/types.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <Windows.h>
#include <Lmcons.h>
#define NAME_MAX MAX_PATH
#else
#include <unistd.h>
#endif

struct Settings {
	// Top menu.
	int top_menu_height = 25;

	// Tiles.
	int tile_size = 20;
	int tile_count_w = 30;
	int tile_count_h = 20;

	// speed.
	float update_fps = 60.0;
	float draw_fps = 60.0;
	int snake_speed = 2;

	// Rules.
	bool die_when_hit_self = false;

	// Score output.
	int output_width = 100;
	int output_height = 20;
};

struct GameImages {
	std::vector<Fl_PNG_Image*> snack_images;
	std::vector<Fl_PNG_Image*> snack_images_tile_size;
};

struct MainData {
	Fl_Double_Window * win = NULL;
	class SnakeMap * snake_map = NULL;
	Fl_Menu_Bar * top_menu = NULL;

	Fl_Output * length_output = NULL;

	GameImages images;

	bool paused = false;

	Settings settings;
};
