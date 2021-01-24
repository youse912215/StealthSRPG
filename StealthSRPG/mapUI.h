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

private:
	int x;
	int y;
	int background;
	vector<int> UI_graph;
	int end;
	int yes;
	int no;
	int red;
	int status;
	int life;
	int status_size_x;
	int status_size_y;

	void reset_blend();
	void drawing_blend(const int& graph_num);
	void drawing_comfirmation();
};
