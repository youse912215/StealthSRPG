#pragma once
#include "charactor.h"
#include <vector>

using namespace std;

class Player : public Charactor {
public:
	int hp; //HP
	int range; //移動範囲
	bool activity; //行動状態（trueなら行動済み）
	bool isAlive; //生存状態
	int tracking_priority; //追跡優先度

	Player(int x, int y, int graph, int moving_quantity, int hp, int range,
	       bool activity, bool isAlive);
	virtual ~Player();
	void get_moving_range(int range);
	virtual void pickup_switching();
};
