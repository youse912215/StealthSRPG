#pragma once
#include "constant.h"
#include "cursor.h"

class Charactor : public Cursor {
public:
	int x;
	int y;
	int graph;
	int moving_quantity;
	int latency; //待機時間

	Charactor(int x, int y, int graph, int moving_quantity = block_size);
	~Charactor();

protected:
	int src_x; //画像上の左上x座標
	int src_y; //画像上の左上y座標

	void get_latency();
	void wait_motion();
};
