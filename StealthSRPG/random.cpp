#include "random.h"
#include "constant.h"
#include "DxLib.h"
#include <random>

using namespace std;

/// <summary>
/// ��߂������_���l�����
/// </summary>
/// <param name="r_min">�ŏ��l</param>
/// <param name="r_max">�ő�l</param>
/// <returns>����</returns>
int get_random(int min, int max) {
	random_device rd; //�����_������
	mt19937 mt(rd()); //�����_���̃V�[�h
	uniform_int_distribution<int> rand(min, max); //r_min~max�͈̔�
	return rand(mt);
}

/// <summary>
/// �����ύX
/// </summary>
/// <returns>����</returns>
int change_sign() {
	return get_random(RANDOM_MIN, RANDOM_MAX) % 2 == 0 ? 1 : -1;
}

/// <summary>
/// �����_���Ȋp�x�����
/// </summary>
/// <returns></returns>
double get_angle() {
	return get_random(RANDOM_MIN, RANDOM_MAX) * (DX_PI / 180);
}

/// <summary>
/// �~�̃|�W�V�������Z�b�g����
/// </summary>
/// <returns></returns>
double set_position() {
	return get_random(0, 180) * 0.001 * change_sign();
}
