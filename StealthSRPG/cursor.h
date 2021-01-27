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
	int graph; //カーソル画像
	int qx; //中心からのxの移動量
	int qy; //中心からのyの移動量
	Cursor();
	~Cursor();
	void update();
	void move(const int& p_x, const int& p_y, const int& ew1_x, const int& ew1_y, const int& ew2_x, const int& ew2_y,
	          const int& eb1_x, const int& eb1_y, const int& wl1_x, const int& wl1_y);

private:
	int disp_x;
	int disp_y;

	void pick();
	void draw();
	void Rangelimit();
};
