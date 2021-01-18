#include "enemyBandits.h"
#include "DxLib.h"
#include "cursor.h"
#include "constant.h"

EnemyBandits::EnemyBandits(int x, int y, int graph, int moving_distance, int attack, int range, bool isAlive) :
	Enemy(x, y, graph, moving_distance, attack, range, isAlive) {
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
	DrawGraph(x - current_x + block_size * 9, y - init_position - current_y + block_size * 9, graph, true);
	DrawFormatString(100, WIN_HEIGHT - block_size - 15, GetColor(0, 0, 0),
	                 "ŽR‘¯(%d, %d)", x / block_size, y / block_size, false);

}

void EnemyBandits::Move() {
}

void EnemyBandits::Attack() {
}

void EnemyBandits::Dead() {
}
