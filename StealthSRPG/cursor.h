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
	int moving_distance; //�ړ�����
	int graph; //�J�[�\���摜
	int qx; //���S�����x�̈ړ���
	int qy; //���S�����y�̈ړ���
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
