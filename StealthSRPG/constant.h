#pragma once

const int WIN_WIDTH = 960; //�E�B���h�E����
const int WIN_HEIGHT = 540; //�E�B���h�E�c��
const int block_size = 48; //�u���b�N�T�C�Y
const int moving_distance = block_size; //�u���b�N�T�C�Y�Ɠ���������
const int area_width = 20;
const int area_height = 20;
const int init_position = block_size * 4; //�����ʒu
const int RANDOM_MIN = 0;
const int RANDOM_MAX = 100;
const int MOVEING_INTERVAL = 20;

enum SCENE {
	NOON_PLAY,
	NOON_ENEMY,
	NIGHT_PLAY,
	NIGHT_ENEMY
};

//--- �}�b�v�`�b�v���� ---//
enum map_info {
	//�C
	SEA = 1,
	//��
	ROAD,
	//�ړI�n�_
	GOAL,
	//��
	TIDE,
	//��
	RAINBOW,
	//��
	BRIDGE,
	//�X
	ICE,
	CENTER = 98,
	//�ړ��͈�
	RANGE,
	//�ړ��͈͊O
	NORANGE
};

enum GRAPH {
	MAP,
	_RANGE
};

enum CHARACTOR {
	_princess,
	_s_warrior1,
	_s_warrior2,
	_s_warrior3,
	_e_warrior1,
	_e_warrior2,
	_e_bandits1,
};

enum DIRECTION {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

enum NODE_X {
	LEFT_X,
	CENTER_X,
	RIGHT_X,
	LEFT_2X,
	RIGHT_2X
};

enum NODE_Y {
	UP_Y,
	CENTER_Y,
	DOWN_Y,
	UP_2Y,
	DOWN_2Y
};

enum XY {
	X,
	Y
};
