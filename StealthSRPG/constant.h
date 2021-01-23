#pragma once

const int WIN_WIDTH = 960; //ウィンドウ横幅
const int WIN_HEIGHT = 540; //ウィンドウ縦幅
const int block_size = 48; //ブロックサイズ
const int moving_distance = block_size; //ブロックサイズと同じ分動く
const int area_width = 20;
const int area_height = 20;
const int init_position = block_size * 4; //初期位置
const int RANDOM_MIN = 0;
const int RANDOM_MAX = 100;
const int MOVEING_INTERVAL = 20;

enum SCENE {
	NOON_PLAY,
	NOON_ENEMY,
	NIGHT_PLAY,
	NIGHT_ENEMY
};

//--- マップチップ名称 ---//
enum map_info {
	//海
	SEA = 1,
	//道
	ROAD,
	//目的地点
	GOAL,
	//潮
	TIDE,
	//虹
	RAINBOW,
	//橋
	BRIDGE,
	//氷
	ICE,
	CENTER = 98,
	//移動範囲
	RANGE,
	//移動範囲外
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
