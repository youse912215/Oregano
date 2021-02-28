#include "random.h"
#include "constant.h"
#include "DxLib.h"
#include <random>

using namespace std;

/// <summary>
/// 定めたランダム値を入手
/// </summary>
/// <param name="min">最小値</param>
/// <param name="max">最大値</param>
/// <returns>乱数</returns>
int getRandom(int min, int max) {
	random_device rd; //ランダム生成
	mt19937 mt(rd()); //ランダムのシード
	uniform_int_distribution<int> rand(min, max); //min~maxの範囲
	return rand(mt);
}

/// <summary>
/// 符号変更
/// </summary>
/// <returns>符号</returns>
int changeSign(const int& min, const int& max) {
	return getRandom(min, max) % 2 == 0 ? 1 : -1;
}

/// <summary>
/// ランダムな角度を入手
/// </summary>
/// <returns></returns>
double getAngle(const int& min, const int& max) {
	return getRandom(min, max) * (DX_PI / 180);
}

/// <summary>
/// 円のポジションをセットする
/// </summary>
/// <returns></returns>
double setCirclePosition() {
	return getRandom(0, 180) * 0.001 * changeSign(0, 10);
}
