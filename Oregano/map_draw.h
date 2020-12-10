#pragma once
#include "map_import.h"

class Map_draw : public Map_import {
private:

	int map_top_left[area_height][area_width];
	int map_top_central[area_height][area_width];
	int map_top_right[area_height][area_width];
	int map_left_central[area_height][area_width];
	int map_central[area_height][area_width];
	int map_right_central[area_height][area_width];
	int map_bottom_left[area_height][area_width];
	int map_bottom_central[area_height][area_width];
	int map_bottom_right[area_height][area_width];
	void drawing_top_left();
	void drawing_top_central();
	void drawing_top_right();
	void drawing_left_central();
	void drawing_central();
	void drawing_right_central();
	void drawing_bottom_left();
	void drawing_bottom_central();
	void drawing_bottom_right();
public:
	void drawing_map();
};
