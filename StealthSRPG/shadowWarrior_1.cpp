#include "shadowWarrior_1.h"
#include "inputProcess.h"
#include "DxLib.h"
#include "cursor.h"
#include "mapAll.h"

ShadowWarrior_1::ShadowWarrior_1(int x, int y, int graph, int moving_quantity, int hp, int range, bool activity,
                                 bool isAlive,
                                 Input& input):
	Player(x, y, graph, moving_quantity, hp, range, activity, isAlive), input(input) {
	this->moving_flag = -1;
	this->duplication_flag[7] = {};
	this->tracking_priority = 1;
}

void ShadowWarrior_1::Update(const int& p_x, const int& p_y, const int& sw2_x, const int& sw2_y,
                             const int& sw3_x, const int& sw3_y, const int& ew1_x, const int& ew1_y,
                             const int& eb1_x, const int& eb1_y) {
	Draw();
	Move();
	Pickup();
	duplicate_decision(p_x, p_y, sw2_x, sw2_y, sw3_x, sw3_y, ew1_x, ew1_y, eb1_x, eb1_y);
}

/// <summary>
/// 描画処理
/// </summary>
void ShadowWarrior_1::Draw() {
	if (this->isAlive) {
		DrawGraph(this->x - current_x + block_size * 9,
		          this->y - init_position - current_y + block_size * 9,
		          this->graph, true);
	}
	DrawFormatString(100, 45, GetColor(0, 0, 0), "兵1(%d, %d)",
	                 this->x / block_size, this->y / block_size, false);
	DrawFormatString(100, 60, GetColor(255, 0, 0), "F%d,A%d,D%d",
	                 moving_flag, this->activity, this->isAlive, false);
}

/// <summary>
/// 現在のカーソル座標とプレイヤー座標が一致しているとき、プレイヤーをPickupする
/// </summary>
void ShadowWarrior_1::Pickup() {
	if (current_x == x && current_y == y) {
		if (input.keys[KEY_INPUT_Z] && !input.oldkeys[KEY_INPUT_Z] && !this->activity) {
			pickup_switching();
		}
	}
}

/// <summary>
/// 他のキャラクターと重複していなければ、移動完了
/// </summary>
void ShadowWarrior_1::pickup_switching() {
	if (!this->duplication_flag[_princess] && !this->duplication_flag[_s_warrior2]
		&& !this->duplication_flag[_s_warrior3]) {
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
void ShadowWarrior_1::duplicate_decision(const int& p_x, const int& p_y, const int& sw2_x, const int& sw2_y,
                                         const int& sw3_x, const int& sw3_y, const int& ew1_x, const int& ew1_y,
                                         const int& eb1_x, const int& eb1_y) {
	this->duplication_flag[_princess] = (this->x == p_x && this->y == p_y) ? true : false;
	this->duplication_flag[_s_warrior2] = (this->x == sw2_x && this->y == sw2_y) ? true : false;
	this->duplication_flag[_s_warrior3] = (this->x == sw3_x && this->y == sw3_y) ? true : false;
	this->duplication_flag[_e_warrior1] = (this->x == ew1_x && this->y == ew1_y) ? true : false;
	this->duplication_flag[_e_bandits1] = (this->x == eb1_x && this->y == eb1_y) ? true : false;
}

/// <summary>
/// 移動処理
/// Pickupしているプレイヤーの移動フラグがtrueなら、
/// 現在のカーソル座標の位置とプレイヤー座標を同じにする
/// </summary>
void ShadowWarrior_1::Move() {
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
void ShadowWarrior_1::Dead(vector<vector<int>>& map) {
	if (map[this->y / block_size][this->x / block_size] == TIDE
		&& Map::scene == NIGHT_PLAY) {
		this->isAlive = false; //生存状態をfalse
		this->x = -1;
		this->y = -1;
	}
}
