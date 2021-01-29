#include "shadowWarrior_3.h"
#include "inputProcess.h"
#include "DxLib.h"
#include "cursor.h"
#include "mapAll.h"
#include "sceneTransition.h"

ShadowWarrior_3::ShadowWarrior_3(int x, int y, int graph, int moving_quantity, int hp, int range, bool activity,
                                 bool isAlive,
                                 Input& input):
	Player(x, y, graph, moving_quantity, hp, range, activity, isAlive), input(input),
	duplication_flag(30) {
	this->moving_flag = -1;
	this->tracking_priority = 3;
	old_x = 0;
	old_y = 0;
}


void ShadowWarrior_3::Update() {
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
/// 描画処理
/// </summary>
void ShadowWarrior_3::Draw() {
	if (this->isAlive) {
		DrawRectGraph(this->x - current_x + BLOCK_SIZE * 9,
		              this->y - INIT_POSITION - current_y + BLOCK_SIZE * 9,
		              src_x * BLOCK_SIZE, BLOCK_SIZE,
		              BLOCK_SIZE, BLOCK_SIZE,
		              this->graph, true, false);
	}
	/*DrawFormatString(300, 45, GetColor(0, 0, 0), "兵3(%d, %d)",
	                 this->x / BLOCK_SIZE, this->y / BLOCK_SIZE, false);
	DrawFormatString(300, 60, GetColor(255, 0, 0), "Fl%d,Ac%d",
	                 moving_flag, this->activity, false);
	DrawFormatString(300, 75, GetColor(255, 0, 0), "De%d,Hp%d",
	                 this->isAlive, this->hp, false);*/
}

/// <summary>
/// プレイヤーフェイズの時
/// 現在のカーソル座標とプレイヤー座標が一致しているとき、プレイヤーをPickupする
/// </summary>
void ShadowWarrior_3::Pickup() {
	if (current_x == x && current_y == y && Map::scene % 2 == 0) {
		if (input.keys[KEY_INPUT_Z] && !input.oldkeys[KEY_INPUT_Z] && !this->activity) {
			pickup_switching();
		}
	}
}

/// <summary>
/// 他のキャラクターと重複していなければ、移動完了
/// </summary>
void ShadowWarrior_3::pickup_switching() {
	if (!this->duplication_flag[_princess] && !this->duplication_flag[_s_warrior1]
		&& !this->duplication_flag[_s_warrior2]) {
		if (!this->duplication_flag[_e_warrior1] && !this->duplication_flag[_e_warrior2]
			&& !this->duplication_flag[_e_warrior2] && !this->duplication_flag[_e_warrior4]
			&& !this->duplication_flag[_e_warrior5] && !this->duplication_flag[_e_warrior6]
			&& !this->duplication_flag[_e_bandits1] && !this->duplication_flag[_e_bandits2]
			&& !this->duplication_flag[_e_bandits3] && !this->duplication_flag[_e_bandits4]
			&& !this->duplication_flag[_e_wolf1] && !this->duplication_flag[_e_wolf2]
			&& !this->duplication_flag[_e_wolf3] && !this->duplication_flag[_e_wolf4]) {
			moving_flag *= -1; //フラグ状態反転
			range_flag *= -1; //フラグ状態反転
			//すでに移動している場合、行動済みとする
			this->activity = (range_x != this->x || range_y != this->y) ? true : false;
		}
	}
}

/// <summary>
/// キャラクターの重複判定
/// </summary>
void ShadowWarrior_3::duplicate_decision(const int& other_x, const int& other_y, const int& name) {
	this->duplication_flag[name] = (this->x == other_x && this->y == other_y) ? true : false;
}

/// <summary>
/// 移動処理
/// Pickupしているプレイヤーの移動フラグがtrueなら、
/// 現在のカーソル座標の位置とプレイヤー座標を同じにする
/// </summary>
void ShadowWarrior_3::Move() {
	if (moving_flag == 1) {
		x = current_x;
		y = current_y;
		moving_range = this->range;
	}
	else if (moving_flag == -1 && Map::scene % 2 != 0) {
		this->activity = false;
	}
}

/// <summary>
/// 死亡処理
/// </summary>
void ShadowWarrior_3::Dead(vector<vector<int>>& map) {
	if (map[this->y / BLOCK_SIZE][this->x / BLOCK_SIZE] == TIDE
		&& Map::scene == NIGHT_PLAY) {
		get_survival_activity();
	}

	if (this->hp <= 0 && Map::turn_timer > DEAD_TIME) get_survival_activity();
}

void ShadowWarrior_3::get_survival_activity() {
	this->isAlive = false; //生存状態をfalse
	this->x = -1;
	this->y = -1;
}

void ShadowWarrior_3::get_old_node() {
	if (moving_flag == -1 && !this->activity) {
		old_x = this->x;
		old_y = this->y;
	}
}

void ShadowWarrior_3::act_cancel() {
	if (input.keys[KEY_INPUT_X] && !input.oldkeys[KEY_INPUT_X]
		&& this->activity && Map::scene % 2 == 0) {
		this->x = old_x;
		this->y = old_y;
		this->activity = false;
	}
}

void ShadowWarrior_3::set_next_map_node(const int& c_scene) {
	if (c_scene == TUTORIAL) {
		this->x = BLOCK_SIZE * 7;
		this->y = BLOCK_SIZE * 8;
		this->hp = 6;
		this->isAlive = true;
	}
}
