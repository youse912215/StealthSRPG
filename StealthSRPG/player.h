#pragma once
#include "charactor.h"

class Player : public Charactor {
public:
	int hp; //HP
	int range; //�ړ��͈�
	bool activity; //�s����ԁitrue�Ȃ�s���ς݁j
	bool isAlive; //�������
	bool duplication_flag[8]; //���̃L�����N�^�[�Ƃ̏d���t���O
	int tracking_priority; //�ǐ՗D��x

	Player(int x, int y, int graph, int moving_distance, int hp, int range, bool activity, bool isAlive);
	virtual ~Player();
	void get_moving_range(int range);
	virtual void pickup_switching();
};
