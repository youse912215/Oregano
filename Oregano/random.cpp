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
int getRandom(int min, int max) {
	random_device rd; //�����_������
	mt19937 mt(rd()); //�����_���̃V�[�h
	uniform_int_distribution<int> rand(min, max); //min~max�͈̔�
	return rand(mt);
}

/// <summary>
/// �����ύX
/// </summary>
/// <returns>����</returns>
int changeSign(const int& min, const int& max) {
	return getRandom(min, max) % 2 == 0 ? 1 : -1;
}

/// <summary>
/// �����_���Ȋp�x�����
/// </summary>
/// <returns></returns>
double getAngle(const int& min, const int& max) {
	return getRandom(min, max) * (DX_PI / 180);
}

/// <summary>
/// �~�̃|�W�V�������Z�b�g����
/// </summary>
/// <returns></returns>
double setCirclePosition() {
	return getRandom(0, 180) * 0.001 * changeSign(0, 10);
}
