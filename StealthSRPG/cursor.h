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
	void move_1(const int& px, const int& py, const int& ex1, const int& ey1,
	            const int& ex2, const int& ey2, const int& ex3, const int& ey3,
	            const int& ex4, const int& ey4, const int& ex5, const int& ey5,
	            const int& ex6, const int& ey6, const int& ex7, const int& ey7,
	            const int& ex8, const int& ey8);
	void move_2(const int& px, const int& py, const int& ex1, const int& ey1,
	            const int& ex2, const int& ey2, const int& ex3, const int& ey3,
	            const int& ex4, const int& ey4, const int& ex5, const int& ey5,
	            const int& ex6, const int& ey6, const int& ex7, const int& ey7,
	            const int& ex8, const int& ey8, const int& ex9, const int& ey9,
	            const int& ex10, const int& ey10, const int& ex11, const int& ey11);

private:
	int disp_x;
	int disp_y;

	void pick();
	void draw();
	void Rangelimit();
};
