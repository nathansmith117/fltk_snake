#include "app_window.h"

void AppWindow::main_init(MainData * md, int X, int Y, const char * l) {
	mdata = md;

	Fl::add_timeout(1.0 / mdata->settings.update_fps, update_cb, (void*)this);
	Fl::add_timeout(1.0 / mdata->settings.draw_fps, draw_cb, (void*)this);
}

void AppWindow::update_cb(void * d) {
	AppWindow * win = (AppWindow*)d;
	MainData* mdata = win->mdata;

	mdata->snake_map->update();

	Fl::repeat_timeout(1.0 / win->mdata->settings.update_fps, update_cb, d);
}

void AppWindow::draw_cb(void * d) {
	AppWindow * win = (AppWindow*)d;
	MainData* mdata = win->mdata;

	mdata->snake_map->redraw();

	Fl::repeat_timeout(1.0 / win->mdata->settings.draw_fps, draw_cb, d);
}
