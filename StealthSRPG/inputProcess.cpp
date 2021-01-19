#include "DxLib.h"
#include "mapAll.h"
#include "inputProcess.h"
#include "constant.h"
#include "cursor.h"
#include <cstdlib>
#include "enemyWarrior_1.h"

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

	if (range_flag == 1 && Map::scene % 2 == 0) {
		cursorLimit();
	}
	else {
		cursorLeft();
		cursorRight();
		cursorUp();
		cursorDown();
	}
}

void Input::collision_flag_update(vector<vector<int>>& map, const int& ew1_x, const int& ew1_y,
                                  const int& eb1_x, const int& eb1_y) {
	/* ��������������̂Ƃ� */
	if (map[(current_y / block_size)][(current_x / block_size) - 1] == SEA) {
		//�C�̂Ƃ�
		collision_flag[LEFT] = true;
	}
	else if (map[(current_y / block_size)][(current_x / block_size) - 1] == TIDE
		&& Map::scene >= NIGHT_PLAY && range_flag == 1) {
		//�����̂Ƃ�
		collision_flag[LEFT] = true;
	}
	else if (current_x - block_size == ew1_x && current_y == ew1_y && range_flag == 1) {
		//�G�l�~�[1������Ƃ�
		collision_flag[LEFT] = true;
	}
	else if (current_x - block_size == eb1_x && current_y == eb1_y && range_flag == 1) {
		//�G�l�~�[2������Ƃ�
		collision_flag[LEFT] = true;
	}
	else {
		collision_flag[LEFT] = false;
	}

	/* �E������������̂Ƃ� */
	if (map[(current_y / block_size)][(current_x / block_size) + 1] == SEA) {
		//�C�̂Ƃ�
		collision_flag[RIGHT] = true;
	}
	else if (map[(current_y / block_size)][(current_x / block_size) + 1] == TIDE
		&& Map::scene >= NIGHT_PLAY && range_flag == 1) {
		//�����̂Ƃ�
		collision_flag[RIGHT] = true;
	}
	else if (current_x + block_size == ew1_x && current_y == ew1_y && range_flag == 1) {
		//�G�l�~�[1������Ƃ�
		collision_flag[RIGHT] = true;
	}
	else if (current_x + block_size == eb1_x && current_y == eb1_y && range_flag == 1) {
		//�G�l�~�[2������Ƃ�
		collision_flag[RIGHT] = true;
	}
	else {
		collision_flag[RIGHT] = false;
	}

	/* �㑤����������̂Ƃ� */
	if (map[(current_y / block_size) - 1][(current_x / block_size)] == SEA) {
		//�C�̂Ƃ�
		collision_flag[UP] = true;
	}
	else if (map[(current_y / block_size) - 1][(current_x / block_size)] == TIDE
		&& Map::scene >= NIGHT_PLAY && range_flag == 1) {
		//�����̂Ƃ�
		collision_flag[UP] = true;
	}
	else if (current_x == ew1_x && current_y - block_size == ew1_y && range_flag == 1) {
		//�G�l�~�[1������Ƃ�
		collision_flag[UP] = true;
	}
	else if (current_x == eb1_x && current_y - block_size == eb1_y && range_flag == 1) {
		//�G�l�~�[2������Ƃ�
		collision_flag[UP] = true;
	}
	else {
		collision_flag[UP] = false;
	}

	/* ��������������̂Ƃ� */
	if (map[(current_y / block_size) + 1][(current_x / block_size)] == SEA) {
		//�C�̂Ƃ�
		collision_flag[DOWN] = true;
	}
	else if (map[(current_y / block_size) + 1][(current_x / block_size)] == TIDE
		&& Map::scene >= NIGHT_PLAY && range_flag == 1) {
		//�����̂Ƃ�
		collision_flag[DOWN] = true;
	}
	else if (current_x == ew1_x && current_y + block_size == ew1_y && range_flag == 1) {
		//�G�l�~�[1������Ƃ�
		collision_flag[DOWN] = true;
	}
	else if (current_x == eb1_x && current_y + block_size == eb1_y && range_flag == 1) {
		//�G�l�~�[2������Ƃ�
		collision_flag[DOWN] = true;
	}
	else {
		collision_flag[DOWN] = false;
	}
}

void Input::update(vector<vector<int>>& map, const int& ew1_x, const int& ew1_y,
                   const int& eb1_x, const int& eb1_y) {
	moving_cursor();
	time_change();
	collision_flag_update(map, ew1_x, ew1_y, eb1_x, eb1_y);

	if (keys[KEY_INPUT_W] && !oldkeys[KEY_INPUT_W]) {
		EnemyWarrior_1::Y -= block_size;
	}
	if (keys[KEY_INPUT_A] && !oldkeys[KEY_INPUT_A]) {
		EnemyWarrior_1::X -= block_size;
	}
	if (keys[KEY_INPUT_S] && !oldkeys[KEY_INPUT_S]) {
		EnemyWarrior_1::Y += block_size;
	}
	if (keys[KEY_INPUT_D] && !oldkeys[KEY_INPUT_D]) {
		EnemyWarrior_1::X += block_size;
	}
}
