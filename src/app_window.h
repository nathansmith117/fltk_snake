#pragma once

#include "program_data.h"
#include "snake_map.h"

class AppWindow : public Fl_Double_Window {
	public:
		AppWindow(MainData * md, int X, int Y, const char * l=0) : Fl_Double_Window(X, Y, l) {
			main_init(md, X, Y, l);
		}
	private:
		MainData * mdata;

		static void update_cb(void * d);
		static void draw_cb(void * d);

		void main_init(MainData * md, int X, int Y, const char * l=0);
};
