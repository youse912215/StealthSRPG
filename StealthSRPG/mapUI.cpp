#include "mapUI.h"
#include "DxLib.h"
#include "mapAll.h"
#include "inputProcess.h"
#include "constant.h"

int MapUI::blend_time = 0;
bool MapUI::UI_flag = true;

MapUI::MapUI() : UI_graph{
		LoadGraph("Source/UI/DayMy.png"),
		LoadGraph("Source/UI/DayEne.png"),
		LoadGraph("Source/UI/NiMy.png"),
		LoadGraph("Source/UI/NiEne.png"),
	} {
	x = 240;
	y = 220;
	background = LoadGraph("Source/UI/background.png");
	end = LoadGraph("Source/UI/end_the_turn.png");
	yes = LoadGraph("Source/UI/Yes.png");
	no = LoadGraph("Source/UI/No.png");
	red = LoadGraph("Source/UI/red.png");
	status = LoadGraph("Source/UI/Status.png");
	life = LoadGraph("Source/UI/Life.png");
	status_size_x = 240;
	status_size_y = 128;
}

MapUI::~MapUI() {
	DeleteGraph(UI_graph[0]);
	DeleteGraph(UI_graph[1]);
	DeleteGraph(UI_graph[2]);
	DeleteGraph(UI_graph[3]);
	DeleteGraph(background);
	DeleteGraph(end);
	DeleteGraph(yes);
	DeleteGraph(no);
	DeleteGraph(red);
}

void MapUI::update() {

	if (UI_flag) {
		drawing_blend(scene);
		blend_time += 5;
	}
	else
		reset_blend();

	if (turn_timer == ENEMY_TURN_TIME) UI_flag = true;

	if (Input::confirmation_flag) drawing_comfirmation();

	//DrawFormatString(0, 300, GetColor(255, 255, 255), "bT:%d, UF:%d", blend_time, UI_flag, false);
}

void MapUI::reset_blend() {
	blend_time = 0;
}

void MapUI::drawing_blend(const int& graph_num) {
	DrawGraph(0, 0, background, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend_time);
	DrawGraph(x, y, UI_graph[graph_num], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void MapUI::drawing_comfirmation() {
	DrawGraph(0, 0, background, true);
	DrawGraph(x, y, end, true);
	DrawGraph((WIN_WIDTH / 2) - 160, y + 64, yes, true);
	DrawGraph((WIN_WIDTH / 2) + 40, y + 64, no, true);
}

void MapUI::drawing_life_status(const int& p_hp, const int& sw1_hp, const int& sw2_hp, const int& sw3_hp,
                                const bool& p_alive, const bool& sw1_alive, const bool& sw2_alive,
                                const bool& sw3_alive) {
	/*DrawGraph(0, WIN_HEIGHT - 128, status, true);

	if (p_alive) {
		DrawRectGraph(status_size_x * 0, WIN_HEIGHT - status_size_y,
		              status_size_x * (3 - p_hp), 0,
		              status_size_x, status_size_y,
		              life, true, false);
	}
	if (sw1_alive) {
		DrawRectGraph(status_size_x * 1, WIN_HEIGHT - status_size_y,
		              status_size_x * (3 - sw1_hp), 0,
		              status_size_x, status_size_y,
		              life, true, false);
	}
	if (sw2_alive) {
		DrawRectGraph(status_size_x * 2, WIN_HEIGHT - status_size_y,
		              status_size_x * (3 - sw2_hp), 0, status_size_x, status_size_y,
		              life,
		              true, false);
	}
	if (sw3_alive) {
		DrawRectGraph(status_size_x * 3, WIN_HEIGHT - status_size_y,
		              status_size_x * (3 - sw3_hp), 0,
		              status_size_x, status_size_y,
		              life, true, false);
	}*/
}

void MapUI::yes_or_no(const bool& y_n) {
	if (y_n)
		GraphBlend(yes, red, 255, DX_GRAPH_BLEND_NORMAL);
	else
		GraphBlend(no, red, 255, DX_GRAPH_BLEND_NORMAL);
}
