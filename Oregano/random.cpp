#include "random.h"
#include "constant.h"
#include "DxLib.h"
#include <random>

using namespace std;

/// <summary>
/// ��߂������_���l�����
/// </summary>
/// <param name="min">�ŏ��l</param>
/// <param name="max">�ő�l</param>
/// <returns>����</returns>
int get_random(int min, int max) {
	random_device rd; //�����_������
	mt19937 mt(rd()); //�����_���̃V�[�h
	uniform_int_distribution<int> rand(min, max); //min~max�͈̔�
	return rand(mt);
}

/// <summary>
/// �����ύX
/// </summary>
/// <returns>����</returns>
int change_sign(const int& min, const int& max) {
	return get_random(min, max) % 2 == 0 ? 1 : -1;
}

/// <summary>
/// �����_���Ȋp�x�����
/// </summary>
/// <returns></returns>
double get_angle(const int& min, const int& max) {
	return get_random(min, max) * (DX_PI / 180);
}

/// <summary>
/// �~�̃|�W�V�������Z�b�g����
/// </summary>
/// <returns></returns>
double set_position() {
	return get_random(0, 180) * 0.001 * change_sign(0, 10);
}
