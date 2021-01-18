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
	void booting_timer();

public:
	string mapcsv_file; //csv�t�@�C����
	string rangecsv_file; //csv�t�@�C����
	static int scene; //�V�[���i����j
	static int turn_timer; //�G�^�[�����̃^�C�}�[

	Map();
	~Map();
	void map_file_import(vector<vector<int>>& map, string& csv, const int& num, const int& num2); //csv�t�@�C���ǂݍ���
};
