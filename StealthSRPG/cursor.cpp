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

void Cursor::move_0(const int& px, const int& py, const int& ex1, const int& ey1,
                    const int& ex2, const int& ey2, const int& ex3, const int& ey3) {
	switch (Enemy::act_order) {
	case 0:
		current_x = ex1;
		current_y = ey1;
		break;
	case 1:
		current_x = ex2;
		current_y = ey2;
		break;
	case 2:
		current_x = ex3;
		current_y = ey3;
		break;
	default:
		current_x = px;
		current_y = py;
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
