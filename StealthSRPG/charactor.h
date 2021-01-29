#pragma once
#include "constant.h"
#include "cursor.h"

class Charactor : public Cursor {
public:
	int x;
	int y;
	int graph;
	int moving_quantity;
	int latency;

	Charactor(int x, int y, int graph, int moving_quantity);
	~Charactor();

protected:
	int src_x;
	int src_y;

	void get_latency();
	void wait_motion();
};
