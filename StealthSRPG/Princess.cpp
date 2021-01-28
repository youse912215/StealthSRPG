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
	this->moving_flag = -1;
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
		DrawRectGraph(this->x - current_x + block_size * 9,
		              this->y - init_position - current_y + block_size * 9,
		              src_x * block_size, 0,
		              block_size, block_size,
		              this->graph, true, false);
	}
	/*DrawFormatString(0, 145, GetColor(0, 0, 0), "�P(%d, %d)",
	                 this->x / block_size, this->y / block_size, false);
	DrawFormatString(0, 160, GetColor(255, 0, 0), "Fl:%d,Ac:%d",
	                 moving_flag, this->activity, false);
	DrawFormatString(0, 175, GetColor(255, 0, 0), "ox:%d,oy:%d",
	                 old_x, old_y, false);*/
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
			moving_flag *= -1; //�t���O��Ԕ��]
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

/// <summary>
/// /// �ړ�����
/// Pickup���Ă���v���C���[�̈ړ��t���O��true�Ȃ�A
/// ���݂̃J�[�\�����W�̈ʒu�ƃv���C���[���W�𓯂��ɂ���
/// </summary>
void Princess::Move() {
	if (moving_flag == 1) {
		this->x = current_x;
		this->y = current_y;
		moving_range = this->range; //�ړ��͈͂��v���C���[�ړ��͈͂ɒu������
	}
	else if (moving_flag == -1 && Map::scene % 2 != 0) {
		this->activity = false;
	}
}

/// <summary>
/// ���S����
/// </summary>
void Princess::Dead(vector<vector<int>>& map) {
	if (map[this->y / block_size][this->x / block_size] == TIDE
		&& Map::scene == NIGHT_PLAY) {
		get_survival_activity();
	}

	if (this->hp <= 0) get_survival_activity();
}

void Princess::get_survival_activity() {
	this->isAlive = false; //������Ԃ�false
	this->x = -1;
	this->y = -1;
}

void Princess::get_old_node() {
	if (moving_flag == -1 && !this->activity) {
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
	case TUTORIAL:
		this->x = block_size * 8;
		this->y = block_size * 8;
		this->hp = 6;
		this->activity = false;
		current_x = this->x;
		current_y = this->y;
		break;

	case STAGE1:
		this->x = block_size * 12;
		this->y = block_size * 12;
		this->hp = 6;
		this->activity = false;
		current_x = this->x;
		current_y = this->y;
		break;
	}

}
