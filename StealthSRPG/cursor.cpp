#include "Cursor.h"
#include "DxLib.h"
#include "constant.h"

int Cursor::current_x = block_size * 9;
int Cursor::current_y = block_size * 9;
int Cursor::range_x = 0;
int Cursor::range_y = 0;
int Cursor::range_flag = -1;
int Cursor::moving_range = -1;

Cursor::Cursor() {
	disp_x = block_size * 9;
	disp_y = block_size * 5;
	radius = block_size / 2;
	moving_distance = block_size;
	graph = LoadGraph("Source/Charactor/Cursor.png");
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

void Cursor::move() {

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
