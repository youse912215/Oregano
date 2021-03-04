#include "playerState.h"
#include "eventBase.h"
#include "moveProcess.h"

MoveProcess move_;

PlayerState::PlayerState() : poisonTime(0), roughTime(0), attributeMax(100), timeMax(100), cooldownMax(120),
                             poisonDamage(50), roughDamage(100),
                             eliminateCoin(300),
                             stateAbnormal{false, false, false, false}, attributeAccumulation{0, 0, 0, 0},
                             coin{100, 100, 100, 100},
                             battleStyle(0) {
}

/// <summary>
/// 状態異常を取得
/// </summary>
void PlayerState::getStateAbnormal() {
	for (unsigned int i = 0; i != stateAbnormal.size(); ++i) {
		if (attributeAccumulation[i] < attributeMax) continue; //条件以外のとき、処理をスキップする
		stateAbnormal[i] = true; //状態異常をtrue
	}
}

/// <summary>
/// 床上での状態を取得
/// </summary>
/// <param name="draw_">マップの描画クラス</param>
void PlayerState::getFloorState(MapDraw& draw_) {
	if (move_.mapCondition(draw_, POISON)) {
		stateAbnormal[DEADLY_POISON] = true; //猛毒状態を付与
	}
	else if (move_.mapCondition(draw_, ROUGH)) {
		//0から100まで時間を動かす
		roughTime = roughTime <= timeMax ? ++roughTime : 0; //凸凹時間をカウント
	}
	else roughTime = 0; //凸凹時間をリセット
}

/// <summary>
/// 猛毒状態をカウント
/// </summary>
void PlayerState::countStateTime() {
	if (stateAbnormal[DEADLY_POISON])
		poisonTime++; //猛毒状態なら時間をカウント
	else if (poisonTime >= timeMax || !stateAbnormal[DEADLY_POISON])
		poisonTime = 0; //最大時間または猛毒状態が解消されたら、時間をリセット
}

/// <summary>
/// 継続ダメージを付与
/// </summary>
/// <param name="time">時間</param>
/// <param name="value">ダメージ量</param>
void PlayerState::continuousDamage(const int& time, const int& value) {
	//timeがtimeMaxのとき
	if (time % timeMax == 0 && time != 0)
		coin[battleStyle] -= value; //value分コインを減らす
}

/// <summary>
/// 状態異常更新処理
/// </summary>
/// <param name="draw_"></param>
void PlayerState::stateAbnormalUpdate(MapDraw& draw_) {
	getStateAbnormal(); //状態異常を取得
	getFloorState(draw_); //猛毒状態を取得
	countStateTime(); //猛毒時間をカウント
	continuousDamage(poisonTime, poisonDamage); //猛毒ダメージを付与
	continuousDamage(roughTime, roughDamage); //凸凹ダメージを付与
}

/// <summary>
/// 戦闘スタイルを切り替える
/// </summary>
void PlayerState::changeBattleStyle(const int& dir) {
	//Lボタン入力かつ、戦闘スタイルが花萌葱(対猛毒スタイル)ではないとき
	if (dir == LEFT && battleStyle != DEADLY_POISON)
		//前のスタイルのコインが0ではないとき
		battleStyle = coin[battleStyle - 1] != 0 ? --battleStyle : battleStyle; //前のスタイルに切り替え

		//Rボタン入力かつ、戦闘スタイルが中紅花(対出血スタイル)ではないとき
	else if (dir == RIGHT && battleStyle != BLOODING)
		//前のスタイルのコインが0ではないとき
		battleStyle = coin[battleStyle + 1] != 0 ? ++battleStyle : battleStyle; //次のスタイルに切り替え
}

/// <summary>
/// 戦闘スタイルの生存状態を更新
/// </summary>
void PlayerState::switchStyleAutomatically() {
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
		if (attributeAccumulation[attribute] < attributeMax)
			attributeAccumulation[attribute] += attributeValue; //属性蓄積値を加算
		else if (attributeAccumulation[attribute] >= attributeMax)
			attributeAccumulation[attribute] = attributeMax; //100以上は属性蓄積値を最大値にする
	}
}

/// <summary>
/// 属性耐性値をリセットと状態異常を解消
/// </summary>
/// <param name="elimination">解消フラグ</param>
/// <param name="cooldownFlag">クールダウンフラグ</param>
/// <param name="coin">プレイヤーコイン</param>
void PlayerState::valueReset(bool& elimination, vector<bool>& cooldownFlag) {
	//現在の戦闘スタイルの状態異常がtrueかつ、解消フラグがtrueのとき
	if (elimination) {
		if (stateAbnormal[battleStyle] && coin[battleStyle] >= eliminateCoin) {
			attributeAccumulation[battleStyle] = 0; //属性耐性値をリセット
			stateAbnormal[battleStyle] = false; //状態異常を解消
			cooldownFlag[ELIMINATION] = true; //クールダウンフラグをtrue
			coin[battleStyle] -= eliminateCoin;
		}
		elimination = false; //解消フラグをfalse
	}
}

/// <summary>
/// 状態のクールダウン処理
/// </summary>
/// <param name="cooldown">クールダウン</param>
/// <param name="cooldownFlag">クールダウンフラグ</param>
void PlayerState::countCooldown(vector<int>& cooldown, vector<bool>& cooldownFlag) {
	if (cooldownFlag[ELIMINATION]) cooldown[ELIMINATION]++; //クールダウン開始

	//クールダウンはcooldownMax秒
	if (cooldown[ELIMINATION] >= cooldownMax) {
		cooldown[ELIMINATION] = 0; //クールダウンをリセット
		cooldownFlag[ELIMINATION] = false; //クールダウンフラグをfalse
	}
}
