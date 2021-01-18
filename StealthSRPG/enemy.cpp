#include "enemy.h"

Enemy::Enemy(int x, int y, int graph, int moving_distance, int attack, int range, bool isAlive) :
	Charactor(x, y, graph, moving_distance),
	attack(attack), range(range), isAlive(isAlive) {
}
