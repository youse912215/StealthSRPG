#pragma once
#include "constant.h"
#include "cursor.h"

class Charactor : public Cursor {
public:
	int x;
	int y;
	int graph;
	int moving_quantity;
	int latency; //‘Ò‹@ŠÔ

	Charactor(int x, int y, int graph, int moving_quantity = block_size);
	~Charactor();

protected:
	int src_x; //‰æ‘œã‚Ì¶ãxÀ•W
	int src_y; //‰æ‘œã‚Ì¶ãyÀ•W

	void get_latency();
	void wait_motion();
};
