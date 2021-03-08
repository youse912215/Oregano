#include "playerKnife.h"
#include "DxLib.h"
#include <cmath>

PlayerKnife::PlayerKnife() :
	center(0.0, 0.0), radian(0.0), sign(0.0), curvatureSpeed(KNIFE_SPEED / 2.0),
	maxRange(BLOCK_SIZE * 3.0), reverseFlag(false), knifePos(0.0, 0.0), knifeAddPos(0.0, 0.0) {
}

/// <summary>
/// 描画用のラジアン計算
/// </summary>
/// /// <param name="pos">プレイヤー座標</param>
void PlayerKnife::calculateRadian(Vec2d& pos) {
	changeDirection(pos); //方向変更

	//ラジアンを計算し、ナイフの位置によって、signが変わる
	radian = atan2(this->center.dy - (pos.dy + HALF_BLOCK_SIZE_D),
	               abs(this->center.dx - (pos.dx + HALF_BLOCK_SIZE_D))) * sign;
}

/// <summary>
/// 方向変更
/// </summary>
/// <param name="pos">プレイヤー座標</param>
void PlayerKnife::changeDirection(Vec2d& pos) {
	//ナイフの位置がプレイヤーより左側にあるとき
	if (this->center.dx <= pos.dx + HALF_BLOCK_SIZE_D) {
		reverseFlag = true; //反転
		sign = -1.0; //反転
	}
		//右側にあるとき
	else {
		reverseFlag = false; //通常
		sign = 1.0; //通常
	}
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="pos">プレイヤーの座標</param>
/// <param name="knifeCenter">プレイヤーの中心座標</param>
void PlayerKnife::initialize(Vec2d& pos, Vec2d& knifeCenter) {
	knifePos = pos + knifeAddPos; //ナイフの座標の更新
	this->center = HALF_BLOCK_SIZE_D + knifePos; //ナイフの中心位置の更新
	knifeCenter = this->center; //プレイヤーに渡す
}

/// <summary>
/// ナイフのクールダウン処理
/// </summary>
/// <param name="cooldown">クールダウン</param>
/// <param name="cooldownFlag">クールダウンフラグ</param>
void PlayerKnife::countCooldown(vector<int>& cooldown, vector<bool>& cooldownFlag) {
	if (cooldownFlag[KNIFE]) cooldown[KNIFE]++; //クールダウン開始

	//クールダウンは30秒
	if (cooldown[KNIFE] >= 30) {
		cooldown[KNIFE] = 0; //クールダウンをリセット
		cooldownFlag[KNIFE] = false; //クールダウンフラグをfalse
	}
}

/// <summary>
/// ナイフのポジジョンをセットする
/// </summary>
void PlayerKnife::setKnifePosition(Vec2d& pos) {
	/* x方向 */
	if (knifePos.dx < pos.dx) knifeAddPos.dx -= KNIFE_SPEED;
	else if (knifePos.dx > pos.dx) knifeAddPos.dx += KNIFE_SPEED;
	else knifeAddPos.dx = 0.0;
	/* y方向 */
	if (knifePos.dy < pos.dy) knifeAddPos.dy -= KNIFE_SPEED;
	else if (knifePos.dy > pos.dy)knifeAddPos.dy += KNIFE_SPEED;
	else knifeAddPos.dy = 0.0;
}

/// <summary>
/// ナイフのポジジョンをリセットする
/// </summary>
void PlayerKnife::resetKnifePosition(Vec2d& playerCenter, vector<bool>& actionFlag) {
	if (deleteKnife(playerCenter)) {
		actionFlag[KNIFE] = false;
		knifeAddPos = 0.0;
	}
}

/// <summary>
/// ナイフの加速（ジョイパッドだと曲げることも可能）
/// スティック方向に対して、曲げる速度を加算
/// </summary>
void PlayerKnife::accelKnife(Input& input) {
	/* x方向 */
	if (input.STICK[LEFT]) knifeAddPos.dx -= curvatureSpeed;
	else if (input.STICK[RIGHT]) knifeAddPos.dx += curvatureSpeed;
	/* y方向 */
	if (input.STICK[UP]) knifeAddPos.dy -= curvatureSpeed;
	else if (input.STICK[DOWN]) knifeAddPos.dy += curvatureSpeed;
}

/// <summary>
/// ナイフの削除条件
/// </summary>
/// <returns></returns>
bool PlayerKnife::deleteKnife(Vec2d& playerCenter) {
	//プレイヤーからの距離が3マス分離れているか
	return abs(this->center.dx - playerCenter.dx) >= maxRange
		|| abs(this->center.dy - playerCenter.dy) >= maxRange;
}

/// <summary>
/// 描画処理
/// ナイフを正しい向きで描画する
/// </summary>
/// <param name="source">データソース</param>
void PlayerKnife::draw(DataSource& source) {
	DrawRotaGraph(static_cast<int>(this->center.dx),
	              static_cast<int>(this->center.dy),
	              1.0, radian,
	              source.knifeGraph, true, reverseFlag);


}
