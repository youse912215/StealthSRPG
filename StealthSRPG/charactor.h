#pragma once
#include "constant.h"
#include "cursor.h"

class Charactor : public Cursor {
public:
	int x;
	int y;
	int graph;
	int moving_quantity;
	int latency; //�ҋ@����

	Charactor(int x, int y, int graph, int moving_quantity = block_size);
	~Charactor();

protected:
	int src_x; //�摜��̍���x���W
	int src_y; //�摜��̍���y���W

	void get_latency();
	void wait_motion();
};
