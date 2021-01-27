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
	void move(const int& p_x, const int& p_y, const int& ew1_x, const int& ew1_y, const int& ew2_x, const int& ew2_y,
	          const int& eb1_x, const int& eb1_y, const int& wl1_x, const int& wl1_y);

private:
	int disp_x;
	int disp_y;

	void pick();
	void draw();
	void Rangelimit();
};
