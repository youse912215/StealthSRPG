#pragma once
#include "mapInfomation.h"
#include <vector>

using namespace std;

class MapDraw : public Infomation {
private:
	//int map_20x20[area_width][area_height]; //�}�b�v���i�[
	//int range_11x11[11][11]; //�ړ��͈͂��i�[

	int base_graph;
	int map_graph; //�}�b�v�`�b�v�摜
	int map_graph2;
	int column; //�s�ԍ�
	int row; //��ԍ�
	int range_width; //�ړ��͈͂̉���
	int range_height; //�ړ��͈͂̏c��
	int draw_range_x;
	int draw_range_y;
	vector<int> info;

	void drawing_enemy_range(const int& ex, const int& ey); //�G�l�~�[�̈ړ��͈͕`��
	void map_import(const int& map_info, vector<vector<int>>& map); //�}�b�v�ǂݍ���
	void range_import(const int& map_info, vector<vector<int>>& range); //�ړ��͈͓ǂݍ���
	void switching_map_scene();
	void drawing_format(); //�t�H�[�}�b�g

public:
	vector<vector<int>> map_20x20;
	vector<vector<int>> range_11x11;
	int map_width; //�}�b�v�̉���
	int map_height; //�}�b�v�̏c��

	MapDraw(); //�R���X�g���N�^
	~MapDraw(); //�f�X�N�g���N�^
	void drawing_map(const int& ew1_x, const int& ew1_y,
	                 const int& ew2_x, const int& ew2_y,
	                 const int& eb1_x, const int& eb1_y); //�}�b�v��`��
};
