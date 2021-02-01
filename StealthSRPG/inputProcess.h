#pragma once
#include "cursor.h"
#include <vector>

using namespace std;

class Input : public Cursor {
private:


	void cursorLeft(const int& cursor);
	void cursorRight(const int& cursor);
	void cursorUp(const int& cursor);
	void cursorDown(const int& cursor);
	void cursorLimit(const int& cursor);
	void moving_cursor(const int& cursor);
	void time_change(const int& pickup);

public:
	vector<bool> map_collision_flag;
	vector<bool> enemy_collision_flag;
	bool yes_or_no;
	char keys[256] = {0}; //最新のキーボード情報用
	char oldkeys[256] = {0}; //1ループ(フレーム)前のキーボード情報
	static bool confirmation_flag;
	static int current_map_scene;

	Input();
	void input_info();
	void map_scene_update(const int& cursor, const int& pickup);
	void game_help_update(const int& pickup);
	void return_game(const int& pickup);
	void start_game(const int& stop, const int& start, const int& pickup);
	void game_result_update(const int& rank, const int& pickup, const int& gameover, const int& menu);
	void game_title_update(const int& pickup);
	void map_collision_decision(vector<vector<int>>& map);
	void enemy_collision_decision0(const int& ex1, const int& ey1, const int& ex2, const int& ey2, const int& ex3,
	                               const int& ey3);
	void enemy_collision_decision1(const int& ex1, const int& ey1, const int& ex2, const int& ey2, const int& ex3,
	                               const int& ey3, const int& ex4, const int& ey4, const int& ex5, const int& ey5,
	                               const int& ex6, const int& ey6, const int& ex7, const int& ey7, const int& ex8,
	                               const int& ey8);
	void enemy_collision_decision2(const int& ex1, const int& ey1, const int& ex2, const int& ey2, const int& ex3,
	                               const int& ey3, const int& ex4, const int& ey4, const int& ex5, const int& ey5,
	                               const int& ex6, const int& ey6, const int& ex7, const int& ey7, const int& ex8,
	                               const int& ey8, const int& ex9, const int& ey9, const int& ex10, const int& ey10,
	                               const int& ex11, const int& ey11);
	void collision_update();
};
