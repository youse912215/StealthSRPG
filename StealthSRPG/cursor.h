#pragma once

class Cursor {
public:
	static int current_x; //現在のxの位置
	static int current_y; //現在のyの位置
	static int range_x; //正方向の移動範囲
	static int range_y; //負方向の移動範囲
	static int range_flag;
	static int moving_range;
	int radius; //半径
	int moving_distance; //移動距離
	int graph; //カーソル画像
	int qx; //中心からのxの移動量
	int qy; //中心からのyの移動量
	Cursor();
	~Cursor();
	void update();

private:
	int disp_x;
	int disp_y;
	void move();
	void pick();
	void draw();
	void Rangelimit();
};
