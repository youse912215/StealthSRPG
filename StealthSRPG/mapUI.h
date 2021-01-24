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

private:
	int x;
	int y;
	int background;
	vector<int> UI_graph;
	int end;
	int yes;
	int no;
	int red;

	void reset_blend();
	void drawing_blend(const int& graph_num);
	void drawing_comfirmation();
};
