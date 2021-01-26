#include "enemy.h"
#include "constant.h"
#include "DxLib.h"
#include "mapAll.h"

int Enemy::act_order = 0;

Enemy::Enemy(int x, int y, int graph, int moving_quantity, int attack, int range, int act_time, bool activity,
             bool isAlive) :
	Charactor(x, y, graph, moving_quantity),
	attack(attack), range(range), activity(activity), isAlive(isAlive), act_time(act_time) {
	slash = LoadGraph("Source/Effect/slash.png");
	impact = LoadGraph("Source/Effect/impact.png");
	dead = LoadGraph("Source/Effect/dead.png");
}

Enemy::~Enemy() {
	DeleteGraph(slash);
	DeleteGraph(impact);
	DeleteGraph(dead);
}

int Enemy::add_cost(const int& map_info) {
	if (map_info == SEA) return 10;
	return 10;
}

int Enemy::set_to_one(int x) {
	if (x > 0) return 1;
	if (x < 0) return -1;
	return 0;
}

void Enemy::reset_act_order() {
	if (Map::scene % 2 == 0) act_order = WARRIOR1;
}
