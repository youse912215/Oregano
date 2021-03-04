#include "playerState.h"
#include "eventBase.h"
#include "moveProcess.h"

MoveProcess move_;

PlayerState::PlayerState() :
	stateAbnormal{false, false, false, false},
	attributeAccumulation{0, 0, 0, 0} {
	battleStyle = 0;
}

/// <summary>
/// 戦闘スタイルを切り替える
/// </summary>
void PlayerState::changeBattleStyle(std::vector<int>& coin, const int& dir) {
	//Lボタン入力かつ、戦闘スタイルが花萌葱ではないとき
	if (dir == LEFT && battleStyle != 0)
		//前のスタイルのコインが0ではないとき
		battleStyle = coin[battleStyle - 1] != 0 ? --battleStyle : battleStyle; //前のスタイルに切り替え

		//Rボタン入力かつ、戦闘スタイルが中紅花ではないとき
	else if (dir == RIGHT && battleStyle != 3)
		//前のスタイルのコインが0ではないとき
		battleStyle = coin[battleStyle + 1] != 0 ? ++battleStyle : battleStyle; //次のスタイルに切り替え
}

/// <summary>
/// 状態異常を取得
/// </summary>
void PlayerState::getStateAbnormal() {
	for (unsigned int i = 0; i != stateAbnormal.size(); ++i) {
		if (attributeAccumulation[i] < 100) continue; //条件以外のとき、処理をスキップする
		stateAbnormal[i] = true; //状態異常をtrue
	}
}

/// <summary>
/// 状態異常を取得
/// </summary>
/// <param name="draw_">マップの描画クラス</param>
void PlayerState::getPoisonState(MapDraw& draw_) {
	if (move_.mapCondition(draw_, POISON)) {
		stateAbnormal[DEADLY_POISON] = true; //猛毒状態を付与
	}
}

/// <summary>
/// 戦闘スタイルの生存状態を更新
/// </summary>
void PlayerState::switchStyleAutomatically(std::vector<int>& coin) {
	if (coin[battleStyle] <= 0) {
		//全てのコインの中で0以上の要素を探し、見つかった最初の要素のイテレーターを返す
		auto itr = find_if(coin.begin(), coin.end(),
		                   [](int x) { return x > 0; });
		//0以外の要素が見つかれば、その要素をbattleStyleに代入
		if (itr != coin.end())
			battleStyle = distance(coin.begin(), itr); //戦闘スタイルを切り替える
		else
			EventBase::gameScene = END_SCENE; //全てのコインが0になり、ゲームオーバーシーンへ
	}
}

/// <summary>
/// 属性蓄積値の計算
/// </summary>
/// <param name="attribute">敵の属性</param>
/// <param name="attributeValue">敵の属性値</param>
void PlayerState::calculateValue(const int& attribute, const int& attributeValue) {
	//現在の戦闘スタイルと敵の属性が異なるとき
	if (battleStyle != attribute) {
		if (attributeAccumulation[attribute] < 100)
			attributeAccumulation[attribute] += attributeValue; //属性蓄積値を加算
		else if (attributeAccumulation[attribute] >= 100)
			attributeAccumulation[attribute] = 100; //100以上は属性蓄積値を最大値にする
	}
}

/// <summary>
/// 属性耐性値をリセットと状態異常を解消
/// </summary>
/// <param name="elimination">解消フラグ</param>
void PlayerState::valueReset(bool& elimination, std::vector<bool>& cooldownFlag) {
	//現在の戦闘スタイルの状態異常がtrueかつ、解消フラグがtrueのとき
	if (elimination) {
		if (stateAbnormal[battleStyle]) {
			attributeAccumulation[battleStyle] = 0; //属性耐性値をリセット
			stateAbnormal[battleStyle] = false; //状態異常を解消
			cooldownFlag[ELIMINATION] = true; //クールダウンフラグをtrue
		}
		elimination = false; //解消フラグをfalse
	}
}

/// <summary>
/// 状態のクールダウン処理
/// </summary>
/// <param name="cooldown"></param>
/// <param name="cooldownFlag"></param>
void PlayerState::countCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag) {
	if (cooldownFlag[ELIMINATION]) cooldown[ELIMINATION]++; //クールダウン開始

	//クールダウンは120秒
	if (cooldown[ELIMINATION] >= 120) {
		cooldown[ELIMINATION] = 0; //クールダウンをリセット
		cooldownFlag[ELIMINATION] = false; //クールダウンフラグをfalse
	}
}
