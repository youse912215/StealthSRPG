#pragma once
#include "constant.h"
#include "cursor.h"

class Charactor : public Cursor {
public:
	int x;
	int y;
	int graph;
	int moving_distance;
	Charactor(int x, int y, int graph, int moving_distance = block_size);
	~Charactor();
	//void draw();
};
