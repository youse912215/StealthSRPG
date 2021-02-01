#pragma once
#include "cursor.h"
#include <string>
#include <vector>

using namespace std;

class Map : public Cursor {
private:
	const string mapcsv_num[3] = {"00", "01", "02"}; //マップ番号
	const string rangecsv_num[6] = {"00", "01", "02", "03", "04", "05"}; //移動範囲の大きさ（番号）
	string comma; //カンマ
	string map_confirmation(const int& num, const int& num2, string& csv); //csvの名前を変更

protected:
	const int ENEMY_TURN_TIME = 180;


public:
	string mapcsv_file; //csvファイル名
	string rangecsv_file; //csvファイル名
	static int scene; //シーン（昼夜）
	static int turn_timer; //敵ターン時のタイマー
	static int turn_count; //総ターンをカウント
	static int random_mist;

	Map();
	~Map();
	void booting_timer(const int& stop, const int& start);
	void map_file_import(vector<vector<int>>& map, string& csv, const int& num, const int& num2); //csvファイル読み込み
};
