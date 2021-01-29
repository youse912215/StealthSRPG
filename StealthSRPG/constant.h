#pragma once

const int WIN_WIDTH = 960; //�E�B���h�E����
const int WIN_HEIGHT = 540; //�E�B���h�E�c��
const int BLOCK_SIZE = 48; //�u���b�N�T�C�Y
const int MOVING_DISTANCE = BLOCK_SIZE; //�u���b�N�T�C�Y�Ɠ���������
const int AREA_WIDTH = 20;
const int AREA_HEIGHT = 20;
const int INIT_POSITION = BLOCK_SIZE * 4; //�����ʒu
const int RANDOM_MIN = 0;
const int RANDOM_MAX = 100;
const int MOVING_INTERVAL = 15;
const int CONFIRMATION_TIME = 100;
const int ENEMY_COST = 15;
const int DEAD_TIME = 45;

enum MAP_SCENE {
	NOON_PLAY,
	NOON_ENEMY,
	NIGHT_PLAY,
	NIGHT_ENEMY
};

enum GAME_SCENE {
	TUTORIAL,
	STAGE1,
	STAGE2,
	GAME_TITLE,
	GAME_PLAY,
	GAME_RESULT,
	GAME_HELP
};

//--- �}�b�v�`�b�v���� ---//
enum map_info {
	//�C
	SEA = 1,
	//��
	LAND,
	//�ړI�n�_
	GOAL,
	//��
	TIDE,
	//��
	RAINBOW_WIDTH,
	RAINBOW_HEIGHT,
	//��
	BRIDGE_WIDTH,
	BRIDGE_HEIGHT,
	//�X
	ICE_LAND,
	ICE_SEA,
	//����
	LAND_TOP = 21,
	//����
	LAND_BOT,
	//����
	LAND_LEFT,
	//���E
	LAND_RIGHT,
	//���E��
	LAND_RIGHT_BOT,
	//������
	LAND_LEFT_BOT,
	//������
	LAND_LEFT_TOP,
	//���E��
	LAND_RIGHT_TOP,
	//���p
	LAND_RIGHT_BOT2,
	LAND_LEFT_BOT2,
	LAND_RIGHT_TOP2,
	LAND_LEFT_TOP2,
	//���΂�
	LAND_OBLIQUE1,
	LAND_OBLIQUE2,
	//��
	MIST,
	//�ړ��͈͒���
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
	_e_warrior3,
	_e_warrior4,
	_e_warrior5,
	_e_warrior6,
	_e_bandits1,
	_e_bandits2,
	_e_bandits3,
	_e_bandits4,
	_e_bandits5,
	_e_bandits6,
	_e_wolf1,
	_e_wolf2,
	_e_wolf3,
	_e_wolf4,
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

enum ACT_ORDER {
	WARRIOR1,
	WARRIOR2,
	BANDITS1,
	WOLF1,
	END = 99
};
