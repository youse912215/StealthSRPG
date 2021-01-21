#include "mapAll.h"
#include "constant.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int Map::scene = NOON_PLAY;
int Map::turn_timer = 0;

Map::Map() {
	mapcsv_file = "Source/Map/map_00.csv";
	rangecsv_file = "Source/Map/rng_04.csv";
	comma = ",";
}

Map::~Map() {
}

void Map::booting_timer() {

	if (scene % 2 != 0) {
		turn_timer++;
		if (turn_timer >= 220) scene = (scene == NIGHT_ENEMY) ? NOON_PLAY : ++scene;
	}
	else turn_timer = 0;
}

/// <summary>
/// MAP��RANGE���œǂݍ��ރt�@�C����؂�ւ���
/// </summary>
/// <param name="num">csv�̔ԍ�</param>
/// <param name="num2">����</param>
/// <param name="csv">csv�t�@�C��</param>
/// <returns>�؂�ւ����csv�t�@�C��</returns>
string Map::map_confirmation(const int& num, const int& num2, string& csv) {
	if (num2 == MAP) csv.replace(15, 2, mapcsv_num[num]);
	else if (num2 == _RANGE) csv.replace(15, 2, rangecsv_num[num]);
	return csv;
}

/// <summary>
/// �t�@�C����ǂݍ��݁A�}�b�v�����}�b�v�z��ɑ��
/// </summary>
/// <param name="map">�}�b�v�z��</param>
/// <param name="range_num">�ړ��͈�</param>
/// <param name="csv">csv�t�@�C��</param>
void Map::map_file_import(vector<vector<int>>& map, string& csv, const int& num, const int& num2) {

	ifstream file(map_confirmation(num, num2, csv));
	string line;
	int j = 0;
	while (getline(file, line)) {
		int i = 0;
		// �J���}����؂蕶���Ƃ��Đ؂蕪���Aint�ɕϊ�����data[][]�Ɋi�[����
		for (string::size_type spos, epos = 0;
		     (spos = line.find_first_not_of(comma, epos)) != string::npos;) {
			string token = line.substr(spos, (epos = line.find_first_of(comma, spos)) - spos);
			map[j][i++] = stoi(token);
		}
		++j;
	}
}
