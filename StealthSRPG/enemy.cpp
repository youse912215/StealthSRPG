#include "enemy.h"
#include "constant.h"

Enemy::Enemy(int x, int y, int graph, int moving_quantity, int attack, int range, bool activity, bool isAlive) :
	Charactor(x, y, graph, moving_quantity),
	attack(attack), range(range), activity(activity), isAlive(isAlive) {
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
