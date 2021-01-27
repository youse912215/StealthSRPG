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
	void move_0(const int& px, const int& py, const int& ex1, const int& ey1,
	            const int& ex2, const int& ey2, const int& ex3, const int& ey3);

private:
	int disp_x;
	int disp_y;

	void pick();
	void draw();
	void Rangelimit();
};
