#pragma once
#include "charactor.h"
#include <vector>

using namespace std;

class Player : public Charactor {
public:
	int hp; //HP
	int range; //�ړ��͈�
	bool activity; //�s����ԁitrue�Ȃ�s���ς݁j
	bool isAlive; //�������
	int tracking_priority; //�ǐ՗D��x

	Player(int x, int y, int graph, int moving_quantity, int hp, int range,
	       bool activity, bool isAlive);
	virtual ~Player();
	void get_moving_range(int range);
	virtual void pickup_switching();
};
