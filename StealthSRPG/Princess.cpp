#include "Princess.h"
#include "inputProcess.h"
#include "DxLib.h"
#include "cursor.h"
#include "mapAll.h"
#include "sceneTransition.h"

Princess::Princess(int x, int y, int graph, int moving_quantity, int hp, int range, bool activity, bool isAlive,
                   Input& input):
	Player(x, y, graph, moving_quantity, hp, range, activity, isAlive), input(input),
	duplication_flag(30) {
	this->moving_flag = false;
	this->tracking_priority = 0;
	old_x = 0;
	old_y = 0;
}

void Princess::Update() {
	get_latency();
	wait_motion();
	if (!Input::confirmation_flag) {
		Move();
		Pickup();
		get_old_node();
		act_cancel();
	}
	Draw();
}

/// <summary>
/// �`�揈��
/// </summary>
void Princess::Draw() {
	if (this->isAlive) {
		DrawRectGraph(this->x - current_x + BLOCK_SIZE * 9,
		              this->y - INIT_POSITION - current_y + BLOCK_SIZE * 9,
		              src_x * BLOCK_SIZE, 0,
		              BLOCK_SIZE, BLOCK_SIZE,
		              this->graph, true, false);
	}
	DrawFormatString(0, 45, GetColor(0, 0, 0), "��1(%d, %d)",
	                 this->x / BLOCK_SIZE, this->y / BLOCK_SIZE, false);
	DrawFormatString(0, 60, GetColor(255, 0, 0), "Fl%d,Ac%d",
	                 moving_flag, this->activity, false);
	DrawFormatString(0, 75, GetColor(255, 0, 0), "De%d,Hp%d",
	                 this->isAlive, this->hp, false);
	DrawFormatString(0, 175, GetColor(255, 0, 0), "ox:%d,oy:%d",
	                 old_x, old_y, false);
}

/// <summary>
/// �v���C���[�t�F�C�Y�̎�
/// ���݂̃J�[�\�����W�ƃv���C���[���W����v���Ă���Ƃ��A�v���C���[��Pickup����
/// </summary>
void Princess::Pickup() {
	if (current_x == this->x && current_y == this->y && Map::scene % 2 == 0) {
		if (input.keys[KEY_INPUT_Z] && !input.oldkeys[KEY_INPUT_Z] && !this->activity) {
			pickup_switching();
		}
	}
}

/// <summary>
/// ���̃L�����N�^�[�Əd�����Ă��Ȃ���΁A�ړ�����
/// </summary>
void Princess::pickup_switching() {
	if (!this->duplication_flag[_s_warrior1] && !this->duplication_flag[_s_warrior2]
		&& !this->duplication_flag[_s_warrior3]) {
		if (!this->duplication_flag[_e_warrior1] && !this->duplication_flag[_e_warrior2]
			&& !this->duplication_flag[_e_warrior2] && !this->duplication_flag[_e_warrior4]
			&& !this->duplication_flag[_e_warrior5] && !this->duplication_flag[_e_warrior6]
			&& !this->duplication_flag[_e_bandits1] && !this->duplication_flag[_e_bandits2]
			&& !this->duplication_flag[_e_bandits3] && !this->duplication_flag[_e_bandits4]
			&& !this->duplication_flag[_e_wolf1] && !this->duplication_flag[_e_wolf2]
			&& !this->duplication_flag[_e_wolf3] && !this->duplication_flag[_e_wolf4]) {
			moving_flag = !moving_flag ? true : false; //�t���O��Ԕ��]
			range_flag *= -1; //�t���O��Ԕ��]
			//���łɈړ����Ă���ꍇ�A�s���ς݂Ƃ���
			this->activity = (range_x != this->x || range_y != this->y) ? true : false;
		}
	}
}

/// <summary>
/// �L�����N�^�[�̏d������
/// </summary>
void Princess::duplicate_decision(const int& other_x, const int& other_y, const int& name) {
	this->duplication_flag[name] = (this->x == other_x && this->y == other_y) ? true : false;
}

void Princess::reset() {
	this->x = BLOCK_SIZE * 8;
	this->y = BLOCK_SIZE * 8;
	this->hp = 4;
	this->isAlive = true;
	this->activity = false;
	current_x = this->x;
	current_y = this->y;

}

/// <summary>
/// /// �ړ�����
/// Pickup���Ă���v���C���[�̈ړ��t���O��true�Ȃ�A
/// ���݂̃J�[�\�����W�̈ʒu�ƃv���C���[���W�𓯂��ɂ���
/// </summary>
void Princess::Move() {
	if (moving_flag == true) {
		this->x = current_x;
		this->y = current_y;
		moving_range = this->range; //�ړ��͈͂��v���C���[�ړ��͈͂ɒu������
	}
	else if (moving_flag == false && Map::scene % 2 != 0) {
		this->activity = false;
	}
}

/// <summary>
/// ���S����
/// </summary>
void Princess::Dead(vector<vector<int>>& map) {
	if (map[this->y / BLOCK_SIZE][this->x / BLOCK_SIZE] == TIDE
		&& Map::scene == NIGHT_PLAY) {
		get_survival_activity();
	}

	if (this->hp <= 0 && Map::turn_timer > DEAD_TIME) get_survival_activity();
}

void Princess::get_survival_activity() {
	this->isAlive = false;
	SceneTransition::game_scene = GAME_RESULT;
}

void Princess::get_old_node() {
	if (moving_flag == false && !this->activity) {
		old_x = this->x;
		old_y = this->y;
	}
}

void Princess::act_cancel() {
	if (input.keys[KEY_INPUT_X] && !input.oldkeys[KEY_INPUT_X]
		&& this->activity && Map::scene % 2 == 0) {
		this->x = old_x;
		this->y = old_y;
		this->activity = false;
	}
}

void Princess::set_next_map_node(const int& c_scene) {
	switch (c_scene) {
	case STAGE1:
		this->x = BLOCK_SIZE * 3;
		this->y = BLOCK_SIZE * 3;
		this->hp = 4;
		this->isAlive = true;
		this->activity = false;
		current_x = this->x;
		current_y = this->y;
		break;

	case STAGE2:
		this->x = BLOCK_SIZE * 16;
		this->y = BLOCK_SIZE * 11;
		this->hp = 4;
		this->isAlive = true;
		this->activity = false;
		current_x = this->x;
		current_y = this->y;
		break;
	}

}
