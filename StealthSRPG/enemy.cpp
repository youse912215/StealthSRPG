#include "enemy.h"
#include "constant.h"
#include "DxLib.h"

int Enemy::motion = 0;

Enemy::Enemy(int x, int y, int graph, int moving_quantity, int attack, int range, bool activity, bool isAlive) :
	Charactor(x, y, graph, moving_quantity),
	attack(attack), range(range), activity(activity), isAlive(isAlive) {
	slash = LoadGraph("Source/Effect/slash.png");
	impact = LoadGraph("Source/Effect/impact.png");
	dead = LoadGraph("Source/Effect/dead.png");
	//motion = 0;
	impact_motion = 0;
	dead_motion = 0;
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

void Enemy::get_slash_motion(const int& a_activity, int* motion) {
	if (motion == nullptr) { return; }
	*motion = a_activity ? ++*motion : -1;
}
