#pragma once
#include "mapInfomation.h"
#include <vector>

using namespace std;

class MapDraw : public Infomation {
private:
	//int map_20x20[area_width][area_height]; //�}�b�v���i�[
	//int range_11x11[11][11]; //�ړ��͈͂��i�[

	int map_graph; //�}�b�v�`�b�v�摜
	int column; //�s�ԍ�
	int row; //��ԍ�
	int range_width; //�ړ��͈͂̉���
	int range_height; //�ړ��͈͂̏c��
	int draw_range_x;
	int draw_range_y;

public:
	vector<vector<int>> map_20x20;
	vector<vector<int>> range_11x11;
	int map_width; //�}�b�v�̉���
	int map_height; //�}�b�v�̏c��

	MapDraw(); //�R���X�g���N�^
	~MapDraw(); //�f�X�N�g���N�^
	void map_import(const int& map_info, vector<vector<int>>& map);
	void range_import(const int& map_info, vector<vector<int>>& range); //�ړ��͈͓ǂݍ���
	void drawing_map(); //�}�b�v��`��
	void drawing_format();
};
