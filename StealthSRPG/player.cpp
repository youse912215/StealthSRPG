#include "player.h"
#include "cursor.h"

Player::Player(int x, int y, int graph, int moving_quantity, int hp, int range, bool activity, bool isAlive) :
	Charactor(x, y, graph, moving_quantity),
	hp(hp), range(range), activity(activity), isAlive(isAlive) {
	tracking_priority = 0;
}

Player::~Player() {
}

void Player::get_moving_range(int range) {


}

void Player::pickup_switching() {
}
