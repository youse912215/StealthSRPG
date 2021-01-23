#include "charactor.h"
#include "constant.h"

Charactor::Charactor(int x, int y, int graph, int moving_quantity) :
	x(x), y(y), graph(graph),
	moving_quantity(moving_quantity) {
	latency = 0;
	src_x = 0;
	src_y = 0;
}

Charactor::~Charactor() {
}

void Charactor::wait_motion() {
	if (latency % 4 == 0) ++src_x;
	if (src_x >= 4) src_x = 0;
}

void Charactor::get_latency() {
	latency = latency >= 10000 ? 0 : ++latency;
}

//void Charactor::draw() {
//	DrawGraph(quantity_x, quantity_y, graph, true);
//	DrawFormatString(quantity_x, quantity_y, GetColor(255, 255, 255),
//	                 "(quantity_x:%d, quantity_y:%d)", quantity_x / block_size, quantity_y / block_size, false);
//}
