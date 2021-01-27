#include "mapDraw.h"
#include "DxLib.h"
#include "cursor.h"
#include "constant.h"
#include "sceneTransition.h"

MapDraw::MapDraw() : info{
	                     SEA, LAND, GOAL, TIDE, RAINBOW_WIDTH, RAINBOW_HEIGHT, BRIDGE_WIDTH, BRIDGE_HEIGHT, ICE_LAND,
	                     ICE_SEA, LAND_TOP, LAND_BOT, LAND_LEFT, LAND_RIGHT, LAND_RIGHT_BOT, LAND_LEFT_BOT,
	                     LAND_LEFT_TOP, LAND_RIGHT_TOP, LAND_RIGHT_BOT2, LAND_LEFT_BOT2, LAND_RIGHT_TOP2,
	                     LAND_LEFT_TOP2, LAND_OBLIQUE1, LAND_OBLIQUE2, CENTER, RANGE
                     },
                     map_20x20(area_height, vector<int>(area_width)),
                     range_11x11(11, vector<int>(11)) {
	map_graph = LoadGraph("Source/Map/mapchips.png"); //�}�b�v�`�b�v�摜
	map_graph2 = LoadGraph("Source/Map/mapchips2.png"); //�}�b�v�`�b�v�摜
	column = 0; //�s�ԍ�
	row = 0; //��ԍ�
	map_width = map_20x20.at(0).size();
	map_height = map_20x20.size();
	range_width = range_11x11.at(0).size();
	range_height = range_11x11.size();
	draw_range_x = range_x - 5 * block_size;
	draw_range_y = range_y - 9 * block_size;
	base_graph = 0;
}

MapDraw::~MapDraw() {
	DeleteGraph(map_graph);
	DeleteGraph(map_graph2);
}

void MapDraw::map_import(const int& map_info, vector<vector<int>>& map) {
	get_map_info(&column, &row, map_info); //�}�b�v��񂩂��ƍs�����o��
	//�}�b�v�̕`��
	for (int y = 0; y < map_height; y++) {
		for (int x = 0; x < map_width; x++) {
			//map_info�̃`�b�v��dest�̈ʒu�ɕ`��
			if (map[y][x] == map_info) {

				DrawRectGraph(
					x * block_size - qx,
					y * block_size - qy - init_position,
					column * block_size, row * block_size,
					block_size, block_size,
					base_graph, true, false);
			}
		}
	}
}

void MapDraw::range_import(const int& map_info, vector<vector<int>>& range) {

	get_map_info(&column, &row, map_info); //�}�b�v��񂩂��ƍs�����o��
	//�ړ��͈͂̕`��
	for (int y = 0; y < range_height; y++) {
		for (int x = 0; x < range_width; x++) {
			//map_info�̃`�b�v��dest�̈ʒu�ɕ`��
			if (range[y][x] == map_info) {

				DrawRectGraph(
					x * block_size - qx + draw_range_x,
					y * block_size - qy + draw_range_y,
					column * block_size, row * block_size,
					block_size, block_size,
					map_graph, true, false);
			}
		}
	}
}

void MapDraw::switching_map_scene() {
	base_graph = scene < NIGHT_PLAY ? map_graph : map_graph2;
}


/// <summary>
/// �}�b�v�֌W��`��
/// </summary>
void MapDraw::drawing_map(const int& ew1_x, const int& ew1_y,
                          const int& ew2_x, const int& ew2_y,
                          const int& eb1_x, const int& eb1_y,
                          const int& wl1_x, const int& wl1_y) {

	map_file_import(map_20x20, mapcsv_file, SceneTransition::game_scene, MAP);
	switching_map_scene();

	for (int i = 0; i != info.size(); i++) {
		map_import(info[i], map_20x20);
	}

	/* �͈̓t���O��true�̂Ƃ��e�v���C���[�̈ړ��͈͂�`�� */
	if (range_flag == 1) {
		map_file_import(range_11x11, rangecsv_file, moving_range, _RANGE);
		range_import(info[24], range_11x11);
		range_import(info[25], range_11x11);
	}

	if (scene % 2 == 0) {
		drawing_enemy_range(ew1_x, ew1_y); //�G��1
		drawing_enemy_range(ew2_x, ew2_y); //�G��2
		drawing_enemy_range(eb1_x, eb1_y); //�R��
		drawing_enemy_range(wl1_x, wl1_y); //�Ԍ�1
	}
	booting_timer(); //�^�C�}�[�N��
	drawing_format();

}

/// <summary>
/// �G�l�~�[�̍��W�ƌ��݂̃J�[�\�����W����v���Ă���Ƃ��Ɉړ��͈͂�`��
/// </summary>
void MapDraw::drawing_enemy_range(const int& ex, const int& ey) {
	if (current_x == ex && current_y == ey) {
		map_file_import(range_11x11, rangecsv_file, moving_range, _RANGE);
		range_import(info[25], range_11x11);
	}
}

void MapDraw::drawing_format() {
	for (int i = 0; i < 21; i++) {
		DrawLine(0, i * block_size, 20 * block_size, i * block_size, GetColor(55, 55, 55), true);
		DrawLine(i * block_size, 0, i * block_size, 20 * block_size, GetColor(55, 55, 55), true);
	}


	/*DrawFormatString(0, 15, GetColor(255, 255, 255),
	                 "r1(%d), r2(%d), ti(%d), ic(%d), f1(%d), f2(%d), rb(%d)", phenomenonFlag[rain1],
	                 phenomenonFlag[rain2], phenomenonFlag[tide],
	                 phenomenonFlag[ice], phenomenonFlag[fog1], phenomenonFlag[fog2], phenomenonFlag[rainbow], false);
	DrawFormatString(150, 0, GetColor(255, 255, 255), "CurMapInfo:%d",
	                 map_20x20[current_y / block_size][current_x / block_size], false);*/
	DrawFormatString(300, 0, GetColor(255, 255, 255), "TIME:%d", turn_timer, false);
	/*if (scene == NOON_PLAY) DrawFormatString(0, 0, GetColor(0, 200, 0), "���v���C���[", false);
	else if (scene == NOON_ENEMY) DrawFormatString(0, 0, GetColor(0, 200, 0), "���G�l�~�[", false);
	else if (scene == NIGHT_PLAY) DrawFormatString(0, 0, GetColor(0, 200, 0), "��v���C���[", false);
	else if (scene == NIGHT_ENEMY) DrawFormatString(0, 0, GetColor(0, 200, 0), "��G�l�~�[", false);*/

}
