#pragma once

class Cursor {
public:
	static int current_x; //���݂�x�̈ʒu
	static int current_y; //���݂�y�̈ʒu
	static int range_x; //�������̈ړ��͈�
	static int range_y; //�������̈ړ��͈�
	static int range_flag;
	static int moving_range;
	int radius; //���a
	int graph; //�J�[�\���摜
	int qx; //���S�����x�̈ړ���
	int qy; //���S�����y�̈ړ���
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
