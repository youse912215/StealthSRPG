#include "charactor.h"
#include "constant.h"

Charactor::Charactor(int x, int y, int graph, int moving_quantity) :
	x(x), y(y), graph(graph),
	moving_quantity(moving_quantity) {
}

Charactor::~Charactor() {
}

//void Charactor::draw() {
//	DrawGraph(quantity_x, quantity_y, graph, true);
//	DrawFormatString(quantity_x, quantity_y, GetColor(255, 255, 255),
//	                 "(quantity_x:%d, quantity_y:%d)", quantity_x / block_size, quantity_y / block_size, false);
//}
