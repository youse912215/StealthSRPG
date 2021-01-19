#pragma once
#include "charactor.h"

class Player : public Charactor {
public:
	int hp; //HP
	int range; //移動範囲
	bool activity; //行動状態（trueなら行動済み）
	bool isAlive; //生存状態
	bool duplication_flag[8]; //他のキャラクターとの重複フラグ
	int tracking_priority; //追跡優先度

	Player(int x, int y, int graph, int moving_distance, int hp, int range, bool activity, bool isAlive);
	virtual ~Player();
	void get_moving_range(int range);
	virtual void pickup_switching();
};
