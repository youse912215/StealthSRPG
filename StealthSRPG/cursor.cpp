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

void Cursor::move_1(const int& px, const int& py, const int& ex1, const int& ey1, const int& ex2, const int& ey2,
                    const int& ex3, const int& ey3, const int& ex4, const int& ey4, const int& ex5, const int& ey5,
                    const int& ex6, const int& ey6, const int& ex7, const int& ey7, const int& ex8, const int& ey8) {
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
	case 3:
		current_x = ex4;
		current_y = ey4;
		break;
	case 4:
		current_x = ex5;
		current_y = ey5;
		break;
	case 5:
		current_x = ex6;
		current_y = ey6;
		break;
	case 6:
		current_x = ex7;
		current_y = ey7;
		break;
	case 7:
		current_x = ex8;
		current_y = ey8;
		break;
	default:
		current_x = px;
		current_y = py;
		break;
	}
}

void Cursor::move_2(const int& px, const int& py, const int& ex1, const int& ey1, const int& ex2, const int& ey2,
                    const int& ex3, const int& ey3, const int& ex4, const int& ey4, const int& ex5, const int& ey5,
                    const int& ex6, const int& ey6, const int& ex7, const int& ey7, const int& ex8, const int& ey8,
                    const int& ex9, const int& ey9, const int& ex10, const int& ey10, const int& ex11,
                    const int& ey11) {
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
	case 3:
		current_x = ex4;
		current_y = ey4;
		break;
	case 4:
		current_x = ex5;
		current_y = ey5;
		break;
	case 5:
		current_x = ex6;
		current_y = ey6;
		break;
	case 6:
		current_x = ex7;
		current_y = ey7;
		break;
	case 7:
		current_x = ex8;
		current_y = ey8;
		break;
	case 8:
		current_x = ex9;
		current_y = ey9;
		break;
	case 9:
		current_x = ex10;
		current_y = ey10;
		break;
	case 10:
		current_x = ex11;
		current_y = ey11;
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
