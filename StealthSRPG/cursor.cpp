#include "Cursor.h"
#include "DxLib.h"
#include "constant.h"
#include "enemy.h"
#include "sceneTransition.h"

int Cursor::current_x = block_size * 8;
int Cursor::current_y = block_size * 8;
int Cursor::range_x = 0;
int Cursor::range_y = 0;
int Cursor::range_flag = -1;
int Cursor::moving_range = -1;

Cursor::Cursor() {
	disp_x = block_size * 9 - 8;
	disp_y = block_size * 5 - 8;
	radius = block_size / 2;
	graph = LoadGraph("Source/Charactor/Cursor2.png");
	qx = current_x - block_size * 9;
	qy = current_y - block_size * 9;
}

Cursor::~Cursor() {
	DeleteGraph(this->graph);
}

void Cursor::update() {
	draw();
	Rangelimit();
}

void Cursor::move(const int& p_x, const int& p_y, const int& ew1_x, const int& ew1_y, const int& ew2_x,
                  const int& ew2_y, const int& eb1_x, const int& eb1_y) {
	switch (Enemy::act_order) {
	case WARRIOR1:
		current_x = ew1_x;
		current_y = ew1_y;
		break;
	case WARRIOR2:
		current_x = ew2_x;
		current_y = ew2_y;
		break;
	case BANDITS1:
		current_x = eb1_x;
		current_y = eb1_y;
		break;
	default:
		current_x = p_x;
		current_y = p_y;
		break;
	}
}

void Cursor::pick() {
}

void Cursor::draw() {
	DrawGraph(disp_x, disp_y, graph, true);
	//DrawFormatString(400, 300, GetColor(255, 0, 0), "cq(%d, %d)", qx / block_size, qy / block_size, false);
}

/// <summary>
/// ˆÚ“®”ÍˆÍ‚ÌŒÀŠE‚ðŽæ“¾
/// </summary>
void Cursor::Rangelimit() {
	if (range_flag == -1) {
		range_x = current_x;
		range_y = current_y;
	}
}
