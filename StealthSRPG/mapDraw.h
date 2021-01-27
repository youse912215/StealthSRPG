#pragma once
#include "mapInfomation.h"
#include <vector>

using namespace std;

class MapDraw : public Infomation {
private:
	//int map_20x20[area_width][area_height]; //マップを格納
	//int range_11x11[11][11]; //移動範囲を格納

	int base_graph;
	int map_graph; //マップチップ画像
	int map_graph2;
	int column; //行番号
	int row; //列番号
	int range_width; //移動範囲の横幅
	int range_height; //移動範囲の縦幅
	int draw_range_x;
	int draw_range_y;
	vector<int> info;

	void drawing_enemy_range(const int& ex, const int& ey); //エネミーの移動範囲描画
	void map_import(const int& map_info, vector<vector<int>>& map); //マップ読み込み
	void range_import(const int& map_info, vector<vector<int>>& range); //移動範囲読み込み
	void switching_map_scene();
	void drawing_format(); //フォーマット

public:
	vector<vector<int>> map_20x20;
	vector<vector<int>> range_11x11;
	int map_width; //マップの横幅
	int map_height; //マップの縦幅

	MapDraw(); //コンストラクタ
	~MapDraw(); //デスクトラクタ
	void drawing_map(const int& ew1_x, const int& ew1_y,
	                 const int& ew2_x, const int& ew2_y,
	                 const int& eb1_x, const int& eb1_y,
	                 const int& wl1_x, const int& wl1_y); //マップを描画
};
