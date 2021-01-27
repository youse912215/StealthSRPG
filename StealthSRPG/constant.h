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
const int MOVING_INTERVAL = 15;
const int CONFIRMATION_TIME = 100;
const int ENEMY_COST = 3;

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
	DESCRIPTION1,
	DESCRIPTION2,
	GAME_PLAY,
	GAME_RESULT,
	GAME_HELP
};

//--- マップチップ名称 ---//
enum map_info {
	//海
	SEA = 1,
	//陸
	LAND,
	//目的地点
	GOAL,
	//潮
	TIDE,
	//虹
	RAINBOW_WIDTH,
	RAINBOW_HEIGHT,
	//橋
	BRIDGE_WIDTH,
	BRIDGE_HEIGHT,
	//氷
	ICE_LAND,
	ICE_SEA,
	//陸上
	LAND_TOP = 21,
	//陸下
	LAND_BOT,
	//陸左
	LAND_LEFT,
	//陸右
	LAND_RIGHT,
	//陸右下
	LAND_RIGHT_BOT,
	//陸左下
	LAND_LEFT_BOT,
	//陸左上
	LAND_LEFT_TOP,
	//陸右上
	LAND_RIGHT_TOP,
	LAND_RIGHT_BOT2,
	LAND_LEFT_BOT2,
	LAND_RIGHT_TOP2,
	LAND_LEFT_TOP2,
	LAND_OBLIQUE1,
	LAND_OBLIQUE2,
	//移動範囲中央
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

enum ACT_ORDER {
	WARRIOR1,
	WARRIOR2,
	BANDITS1,
	END = 99
};
