#include "shadowWarrior_3.h"
#include "inputProcess.h"
#include "DxLib.h"
#include "cursor.h"
#include "mapAll.h"

ShadowWarrior_3::ShadowWarrior_3(int x, int y, int graph, int moving_quantity, int hp, int range, bool activity,
                                 bool isAlive,
                                 Input& input):
	Player(x, y, graph, moving_quantity, hp, range, activity, isAlive), input(input) {
	this->moving_flag = -1;
	this->duplication_flag[7] = {};
	this->tracking_priority = 3;
	old_x = 0;
	old_y = 0;
}


void ShadowWarrior_3::Update(const int& p_x, const int& p_y, const int& sw1_x, const int& sw1_y,
                             const int& sw2_x, const int& sw2_y, const int& ew1_x, const int& ew1_y,
                             const int& ew2_x, const int& ew2_y, const int& eb1_x, const int& eb1_y) {
	get_latency();
	wait_motion();
	Draw();
	if (!Input::confirmation_flag) {
		Move();
		Pickup();
		get_old_node();
		act_cancel();
	}
	duplicate_decision(p_x, p_y, sw1_x, sw1_y, sw2_x, sw2_y, ew1_x, ew1_y, ew2_x, ew2_y, eb1_x, eb1_y);
}

/// <summary>
/// 描画処理
/// </summary>
void ShadowWarrior_3::Draw() {
	if (this->isAlive) {
		DrawRectGraph(this->x - current_x + block_size * 9,
		              this->y - init_position - current_y + block_size * 9,
		              src_x * block_size, block_size,
		              block_size, block_size,
		              this->graph, true, false);
	}
	/*DrawFormatString(300, 45, GetColor(0, 0, 0), "兵3(%d, %d)",
	                 this->x / block_size, this->y / block_size, false);
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
		if (!this->duplication_flag[_e_warrior1] && !this->duplication_flag[_e_bandits1]) {
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
void ShadowWarrior_3::duplicate_decision(const int& p_x, const int& p_y, const int& sw1_x, const int& sw1_y,
                                         const int& sw2_x, const int& sw2_y, const int& ew1_x, const int& ew1_y,
                                         const int& ew2_x, const int& ew2_y, const int& eb1_x, const int& eb1_y) {
	this->duplication_flag[_princess] = (this->x == p_x && this->y == p_y) ? true : false;
	this->duplication_flag[_s_warrior1] = (this->x == sw1_x && this->y == sw1_y) ? true : false;
	this->duplication_flag[_s_warrior2] = (this->x == sw2_x && this->y == sw2_y) ? true : false;
	this->duplication_flag[_e_warrior1] = (this->x == ew1_x && this->y == ew1_y) ? true : false;
	this->duplication_flag[_e_warrior2] = (this->x == ew1_x && this->y == ew1_y) ? true : false;
	this->duplication_flag[_e_bandits1] = (this->x == eb1_x && this->y == eb1_y) ? true : false;
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
	if (map[this->y / block_size][this->x / block_size] == TIDE
		&& Map::scene == NIGHT_PLAY) {
		get_survival_activity();
	}

	if (this->hp <= 0) get_survival_activity();
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
