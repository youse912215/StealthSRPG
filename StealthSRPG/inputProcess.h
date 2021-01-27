#pragma once
#include "cursor.h"
#include <vector>

using namespace std;

class Input : public Cursor {
private:


	void cursorLeft();
	void cursorRight();
	void cursorUp();
	void cursorDown();
	void cursorLimit();
	void moving_cursor();
	void time_change();
	void collision_flag_update(vector<vector<int>>& map, const int& ew1_x, const int& ew1_y,
	                           const int& ew2_x, const int& ew2_y, const int& eb1_x, const int& eb1_y);

public:
	bool collision_flag[4];
	bool yes_or_no;
	char keys[256] = {0}; //�ŐV�̃L�[�{�[�h���p
	char oldkeys[256] = {0}; //1���[�v(�t���[��)�O�̃L�[�{�[�h���
	static bool confirmation_flag;
	int current_map_scene;

	Input();
	void input_info();
	void map_scene_update(vector<vector<int>>& map, const int& ew1_x, const int& ew1_y,
	                      const int& ew2_x, const int& ew2_y, const int& eb1_x, const int& eb1_y);
	void game_help_update();
	void game_result_update();
};
