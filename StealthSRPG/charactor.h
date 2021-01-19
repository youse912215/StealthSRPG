#pragma once
#include "constant.h"
#include "cursor.h"

class Charactor : public Cursor {
public:
	int x;
	int y;
	int graph;
	int moving_quantity;
	Charactor(int x, int y, int graph, int moving_quantity = block_size);
	~Charactor();
	//void draw();
};
