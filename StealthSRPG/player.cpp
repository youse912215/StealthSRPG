#include "player.h"
#include "cursor.h"

Player::Player(int x, int y, int graph, int moving_distance, int hp, int range, bool activity, bool isAlive) :
	Charactor(x, y, graph, moving_distance),
	hp(hp), range(range), activity(activity), isAlive(isAlive) {
}

Player::~Player() {
}

void Player::get_moving_range(int range) {


}

void Player::pickup_switching() {
}
