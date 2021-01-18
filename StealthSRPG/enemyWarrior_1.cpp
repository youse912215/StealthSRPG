#include "enemyWarrior_1.h"
#include "DxLib.h"
#include "cursor.h"
#include "constant.h"
#include "mapAll.h"
#include "random.h"

EnemyWarrior_1::EnemyWarrior_1(int x, int y, int graph, int moving_distance, int attack, int range, bool isAlive) :
	Enemy(x, y, graph, moving_distance, attack, range, isAlive) {
	moving_flag = -1;
	priority = 1;
	moving_quantity = 0.0;
}

void EnemyWarrior_1::Update() {
	Draw();
	Move();
	Attack();
	Dead();
}

void EnemyWarrior_1::Draw() {
	DrawGraph(x - current_x + block_size * 9, y - init_position - current_y + block_size * 9, graph, true);
	DrawFormatString(0, WIN_HEIGHT - block_size - 15, GetColor(0, 0, 0),
	                 "敵兵1(%d, %d)", x / block_size, y / block_size, false);
	DrawFormatString(0, WIN_HEIGHT - block_size, GetColor(0, 0, 0),
	                 "ew1_mq:%.1lf", moving_quantity, false);
	DrawFormatString(0, WIN_HEIGHT - block_size + 15, GetColor(0, 0, 0),
	                 "ew1_r:%d", this->range, false);
	DrawFormatString(0, WIN_HEIGHT - block_size + 30, GetColor(0, 0, 0),
	                 "Rand:%d", get_random(0, 1), false);
}

void EnemyWarrior_1::Move() {
	if (Map::turn_timer == 0) moving_quantity = 0.0;

	if (Map::turn_timer % 50 == 0 && Map::turn_timer != 0 && static_cast<int>(moving_quantity) != this->range) {
		switch (static_cast<int>(moving_quantity)) {
		case 1:
			x += block_size / 2;
			break;
		case 2:
			y += block_size / 2;
			break;
		case 3:
			y += block_size / 2;
			break;
		}
		moving_quantity += 0.5;
	}

	if (this->x == current_x && this->y == current_y) {
		moving_range = this->range; //移動範囲をプレイヤー移動範囲に置換する
	}
}

void EnemyWarrior_1::Attack() {
}

void EnemyWarrior_1::Dead() {
}
