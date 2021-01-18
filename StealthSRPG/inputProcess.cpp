#include "DxLib.h"
#include "mapAll.h"
#include "inputProcess.h"
#include "constant.h"
#include "Cursor.h"
#include <cstdlib>

using namespace std;

Input::Input() : collision_flag{} {
}

/// <summary>
/// �L�[�{�[�h���
/// </summary>
void Input::input_info() {
	// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
	for (int i = 0; i < 256; ++i) {
		oldkeys[i] = keys[i];
	}
	// �ŐV�̃L�[�{�[�h�����擾
	GetHitKeyStateAll(keys);
}

/// <summary>
/// ����ύX
/// ��̓G�^�[���Ȃ�A���̃v���C���[�^�[���Ɉڍs
/// </summary>
void Input::time_change() {
	if (keys[KEY_INPUT_SPACE] && !oldkeys[KEY_INPUT_SPACE]) {
		Map::scene = (Map::scene == NIGHT_ENEMY) ? NOON_PLAY : ++Map::scene;
	}
}

void Input::cursorLeft() {
	if (keys[KEY_INPUT_LEFT] && !oldkeys[KEY_INPUT_LEFT] && !collision_flag[LEFT]) {
		qx -= block_size;
		current_x -= block_size;
	}
}

void Input::cursorRight() {
	if (keys[KEY_INPUT_RIGHT] && !oldkeys[KEY_INPUT_RIGHT] && !collision_flag[RIGHT]) {
		qx += block_size;
		current_x += block_size;
	}
}

void Input::cursorUp() {
	if (keys[KEY_INPUT_UP] && !oldkeys[KEY_INPUT_UP] && !collision_flag[UP]) {
		qy -= block_size;
		current_y -= block_size;
	}

}

void Input::cursorDown() {
	if (keys[KEY_INPUT_DOWN] && !oldkeys[KEY_INPUT_DOWN] && !collision_flag[DOWN]) {
		qy += block_size;
		current_y += block_size;
	}
}

/// <summary>
/// x,y�̐�Βl�̍��v�i�ړ��}�X�j���J�[�\���̈ړ��͈͂�
/// </summary>
void Input::cursorLimit() {

	if (abs(range_x - current_x)
		+ abs(range_y - current_y)
		== moving_range * block_size) {

		if (range_x == current_x) {

		}
		else if (range_x < current_x) {
			cursorLeft();
		}
		else if (range_x > current_x) {
			cursorRight();
		}

		if (range_y == current_y) {

		}
		else if (range_y < current_y) {
			cursorUp();
		}
		else if (range_y > current_y) {
			cursorDown();
		}
	}
	else {
		cursorLeft();
		cursorRight();
		cursorUp();
		cursorDown();
	}
}

/// <summary>
/// �J�[�\���̓��쏈��
/// </summary>
void Input::moving_cursor() {

	if (range_flag == 1) {
		cursorLimit();
	}
	else {
		cursorLeft();
		cursorRight();
		cursorUp();
		cursorDown();
	}
}

void Input::collision_flag_update(vector<vector<int>>& map) {
	if (map[(current_y / block_size)][(current_x / block_size) - 1] == SEA) {
		collision_flag[LEFT] = true;
	}
	else if (map[(current_y / block_size)][(current_x / block_size) - 1] == TIDE
		&& Map::scene >= NIGHT_PLAY && range_flag == 1) {
		collision_flag[LEFT] = true;
	}
	else {
		collision_flag[LEFT] = false;
	}

	if (map[(current_y / block_size)][(current_x / block_size) + 1] == SEA) {
		collision_flag[RIGHT] = true;
	}
	else if (map[(current_y / block_size)][(current_x / block_size) + 1] == TIDE
		&& Map::scene >= NIGHT_PLAY && range_flag == 1) {
		collision_flag[RIGHT] = true;
	}
	else {
		collision_flag[RIGHT] = false;
	}

	if (map[(current_y / block_size) - 1][(current_x / block_size)] == SEA) {
		collision_flag[UP] = true;
	}
	else if (map[(current_y / block_size) - 1][(current_x / block_size)] == TIDE
		&& Map::scene >= NIGHT_PLAY && range_flag == 1) {
		collision_flag[UP] = true;
	}
	else {
		collision_flag[UP] = false;
	}

	if (map[(current_y / block_size) + 1][(current_x / block_size)] == SEA) {
		collision_flag[DOWN] = true;
	}
	else if (map[(current_y / block_size) + 1][(current_x / block_size)] == TIDE
		&& Map::scene >= NIGHT_PLAY && range_flag == 1) {
		collision_flag[DOWN] = true;
	}
	else {
		collision_flag[DOWN] = false;
	}
}

void Input::update(vector<vector<int>>& map) {
	if (Map::scene % 2 == 0) moving_cursor();
	time_change();
	collision_flag_update(map);
}
