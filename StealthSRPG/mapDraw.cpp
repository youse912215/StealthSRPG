#include "mapDraw.h"
#include "DxLib.h"
#include "cursor.h"
#include "constant.h"

MapDraw::MapDraw() : info{
	                     SEA, LAND, GOAL, TIDE, RAINBOW, BRIDGE, ICE, LAND_TOP, LAND_BOT, LAND_LEFT, LAND_RIGHT,
	                     LAND_RIGHT_BOT, LAND_LEFT_BOT, LAND_LEFT_TOP, LAND_RIGHT_TOP, LAND_RIGHT_BOT2, LAND_LEFT_BOT2,
	                     LAND_RIGHT_TOP2, LAND_LEFT_TOP2, LAND_OBLIQUE1, LAND_OBLIQUE2, CENTER, RANGE
                     },
                     map_20x20(area_height, vector<int>(area_width)),
                     range_11x11(11, vector<int>(11)) {
	map_graph = LoadGraph("Source/Map/mapchips.png"); //マップチップ画像
	column = 0; //行番号
	row = 0; //列番号
	map_width = map_20x20.at(0).size();
	map_height = map_20x20.size();
	range_width = range_11x11.at(0).size();
	range_height = range_11x11.size();
	draw_range_x = range_x - 5 * block_size;
	draw_range_y = range_y - 9 * block_size;
}

MapDraw::~MapDraw() {
	DeleteGraph(map_graph);
}

void MapDraw::map_import(const int& map_info, vector<vector<int>>& map) {

	get_map_info(&column, &row, map_info); //マップ情報から列と行を取り出す
	//マップの描画
	for (int y = 0; y < map_height; y++) {
		for (int x = 0; x < map_width; x++) {
			//map_infoのチップをdestの位置に描画
			if (map[y][x] == map_info) {
				DrawRectGraph(
					x * block_size - qx,
					y * block_size - qy - init_position,
					column * block_size, row * block_size,
					block_size, block_size,
					map_graph, true, false);
			}
		}
	}
}

void MapDraw::range_import(const int& map_info, vector<vector<int>>& range) {

	get_map_info(&column, &row, map_info); //マップ情報から列と行を取り出す
	//移動範囲の描画
	for (int y = 0; y < range_height; y++) {
		for (int x = 0; x < range_width; x++) {
			//map_infoのチップをdestの位置に描画
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


/// <summary>
/// マップ関係を描画
/// </summary>
void MapDraw::drawing_map(const int& ew1_x, const int& ew1_y,
                          const int& ew2_x, const int& ew2_y,
                          const int& eb1_x, const int& eb1_y) {
	map_file_import(map_20x20, mapcsv_file, 0, MAP);

	for (int i = 0; i != info.size(); i++) {
		map_import(info[i], map_20x20);
	}

	/* 範囲フラグがtrueのとき各プレイヤーの移動範囲を描画 */
	if (range_flag == 1) {
		map_file_import(range_11x11, rangecsv_file, moving_range, _RANGE);
		range_import(info[21], range_11x11);
		range_import(info[22], range_11x11);
	}

	drawing_enemy_range(ew1_x, ew1_y); //敵兵1
	drawing_enemy_range(ew2_x, ew2_y); //敵兵2
	drawing_enemy_range(eb1_x, eb1_y); //山賊1
	booting_timer(); //タイマー起動
}

/// <summary>
/// エネミーの座標と現在のカーソル座標が一致しているときに移動範囲を描画
/// </summary>
void MapDraw::drawing_enemy_range(const int& ex, const int& ey) {
	if (current_x == ex && current_y == ey) {
		map_file_import(range_11x11, rangecsv_file, moving_range, _RANGE);
		range_import(info[22], range_11x11);
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
	/*DrawFormatString(300, 0, GetColor(255, 255, 255), "TIME:%d", turn_timer, false);
	if (scene == NOON_PLAY) DrawFormatString(0, 0, GetColor(0, 200, 0), "昼プレイヤー", false);
	else if (scene == NOON_ENEMY) DrawFormatString(0, 0, GetColor(0, 200, 0), "昼エネミー", false);
	else if (scene == NIGHT_PLAY) DrawFormatString(0, 0, GetColor(0, 200, 0), "夜プレイヤー", false);
	else if (scene == NIGHT_ENEMY) DrawFormatString(0, 0, GetColor(0, 200, 0), "夜エネミー", false);*/

}
