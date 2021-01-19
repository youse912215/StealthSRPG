#include "enemyBandits.h"
#include "DxLib.h"
#include "cursor.h"
#include "constant.h"

EnemyBandits::EnemyBandits(int x, int y, int graph, int moving_quantity, int attack, int range, bool activity,
                           bool isAlive) :
	Enemy(x, y, graph, moving_quantity, attack, range, activity, isAlive) {
	moving_flag = -1;
	priority = 1;
}

void EnemyBandits::Update() {
	Draw();
	Move();
	Attack();
	Dead();
}

void EnemyBandits::Draw() {
	if (this->x == current_x && this->y == current_y) {
		moving_range = this->range; //�ړ��͈͂��v���C���[�ړ��͈͂ɒu������
	}
	DrawGraph(x - current_x + block_size * 9, y - init_position - current_y + block_size * 9, graph, true);
	DrawFormatString(200, WIN_HEIGHT - block_size - 15, GetColor(0, 0, 0),
	                 "�R��(%d, %d)", x / block_size, y / block_size, false);

}

void EnemyBandits::Move() {

}

void EnemyBandits::Attack() {
}

void EnemyBandits::Dead() {
}
