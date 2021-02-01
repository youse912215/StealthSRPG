#pragma once
#include "cursor.h"
#include <string>
#include <vector>

using namespace std;

class Map : public Cursor {
private:
	const string mapcsv_num[3] = {"00", "01", "02"}; //�}�b�v�ԍ�
	const string rangecsv_num[6] = {"00", "01", "02", "03", "04", "05"}; //�ړ��͈͂̑傫���i�ԍ��j
	string comma; //�J���}
	string map_confirmation(const int& num, const int& num2, string& csv); //csv�̖��O��ύX

protected:
	const int ENEMY_TURN_TIME = 180;


public:
	string mapcsv_file; //csv�t�@�C����
	string rangecsv_file; //csv�t�@�C����
	static int scene; //�V�[���i����j
	static int turn_timer; //�G�^�[�����̃^�C�}�[
	static int turn_count; //���^�[�����J�E���g
	static int random_mist;

	Map();
	~Map();
	void booting_timer(const int& stop, const int& start);
	void map_file_import(vector<vector<int>>& map, string& csv, const int& num, const int& num2); //csv�t�@�C���ǂݍ���
};
