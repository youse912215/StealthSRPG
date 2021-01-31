#include "mapMist.h"
#include "DxLib.h"
#include "constant.h"
#include "mapAll.h"

void draw_mist(const int& mist, const int& x, const int& y) {
	DrawGraph(BLOCK_SIZE * x - Map::current_x, BLOCK_SIZE * y - Map::current_y, mist, true);
}
