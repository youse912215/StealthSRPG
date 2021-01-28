#pragma once
#include "mapAll.h"
#include "inputProcess.h"
#include <vector>

using namespace std;

class MapUI : public Map {
public:
	static int blend_time;
	static bool UI_flag;

	MapUI();
	~MapUI();
	void update();
	void yes_or_no(const bool& y_n);
	void drawing_life_status(const int& p_hp, const int& sw1_hp, const int& sw2_hp, const int& sw3_hp,
	                         const bool& p_alive, const bool& sw1_alive, const bool& sw2_alive, const bool& sw3_alive);
	void drawing_main_status(const int& p_x, const int& p_y, const int& sw1_x, const int& sw1_y,
	                         const int& sw2_x, const int& sw2_y, const int& sw3_x, const int& sw3_y);

private:
	int x;
	int y;
	int background_black;
	vector<int> UI_graph;
	int end;
	int yes;
	int no;
	int red;
	int status;
	int status2;
	int life;
	int sun;
	int moon;
	int status_size_x;
	int status_size_y;

	void reset_blend();
	void drawing_blend(const int& graph_num);
	void drawing_comfirmation();
	void drawing_scene_symbol();
};
