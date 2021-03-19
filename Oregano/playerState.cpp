#include "playerState.h"
#include "moveProcess.h"
#include "sceneLoad.h"

MoveProcess move_;

vector<bool> PlayerState::condition = {false, false, false, false}; //状態異常
vector<int> PlayerState::coin = {10, 10, 10, 10}; //コイン
vector<int> PlayerState::attributeAccumulation = {0, 0, 0, 0}; //属性耐久値
int PlayerState::battleStyle = 0; //戦闘スタイル

PlayerState::PlayerState() :
	/* 初期値 */
	poisonTime(0), roughTime(0), crampsTime(0),

	/* 固定値 */
	damageTimeMax(100), crampsTimeMax(60), cooldownMax(120),
	attributeMax(10), poisonDamage(1), roughDamage(2), recoveryCoin(10),

	/* ダメージフラグ */
	poisonDamageFlag(false), roughDamageFlag(false) {
}

/// <summary>
/// 状態異常を取得
/// </summary>
void PlayerState::getCondition() {
	for (unsigned int i = 0; i != condition.size(); ++i) {
		if (attributeAccumulation[i] < attributeMax) continue; //条件以外のとき、処理をスキップする
		condition[i] = true; //状態異常をtrue
	}
}

/// <summary>
/// 床上での状態を取得
/// </summary>
/// <param name="draw_">マップの描画クラス</param>
void PlayerState::getFloorState(MapDraw& draw_) {
	//毒床の上にいるときかつ、戦闘スタイルが花萌葱(対猛毒)以外のとき
	if (move_.mapCondition(draw_, POISON) && battleStyle != DEADLY_POISON) {
		condition[DEADLY_POISON] = true; //猛毒状態を付与
	}
		//凸凹床の上にいるときかつ、戦闘スタイルが燕子花(対混乱)以外のとき
	else if (move_.mapCondition(draw_, ROUGH) && battleStyle != CONFUSION) {
		//0から100まで時間を動かす
		roughTime = roughTime <= damageTimeMax ? ++roughTime : 0; //凸凹時間をカウント
	}
	else roughTime = 0; //凸凹時間をリセット
}

/// <summary>
/// 猛毒状態をカウント
/// </summary>
void PlayerState::countStateTime() {
	if (condition[DEADLY_POISON])
		poisonTime++; //猛毒状態なら時間をカウント
	else if (poisonTime >= damageTimeMax || !condition[DEADLY_POISON])
		poisonTime = 0; //最大時間または猛毒状態が解消されたら、時間をリセット
}

/// <summary>
/// 継続ダメージを付与
/// </summary>
/// <param name="time">時間</param>
/// <param name="value">ダメージ量</param>
void PlayerState::continuousDamage(const int& time, const int& value, DataSource& source) {
	//timeがtimeMaxのとき
	if (time % damageTimeMax == 0 && time != 0) {
		coin[battleStyle] -= value; //value分コインを減らす
		source.playSe(source.seDamage); //ダメージSE

		if (time == poisonTime) poisonDamageFlag = true; //猛毒ダメージフラグをtrue
		else roughDamageFlag = true; //凸凹ダメージフラグをtrue
	}
}

/// <summary>
/// 状態異常更新処理
/// </summary>
/// <param name="draw_"></param>
void PlayerState::conditionUpdate(MapDraw& draw_, DataSource& source) {
	getCondition(); //状態異常を取得
	getFloorState(draw_); //猛毒状態を取得
	countStateTime(); //猛毒時間をカウント
	continuousDamage(poisonTime, poisonDamage, source); //猛毒ダメージを付与
	continuousDamage(roughTime, roughDamage, source); //凸凹ダメージを付与
	resetCoin(); //コインを0にリセット
	countCrampsTime(); //痙攣時間をカウント
}

/// <summary>
/// コインを0にリセット
/// </summary>
void PlayerState::resetCoin() {
	//現在の戦闘スタイルのコインが0になったら、0にする
	if (coin[battleStyle] < 0)
		coin[battleStyle] = 0; //0にする
}

/// <summary>
/// 痙攣時間をカウント
/// </summary>
void PlayerState::countCrampsTime() {
	//痙攣状態のとき
	if (condition[CRAMPS]) {
		crampsTime = crampsTime++; //痙攣時間をカウント
	}

	if (crampsTime >= crampsTimeMax) {
		condition[CRAMPS] = false; //状態解除
		attributeAccumulation[CRAMPS] = 0; //耐久値リセット
		crampsTime = 0; //時間をリセット
	}
}

/// <summary>
/// 状態異常による追加ダメージ
/// </summary>
int PlayerState::addConditionDamage() {
	//出血状態以外のとき
	if (!condition[BLOODING])
		return 1; //追加ダメージなし
	return 3; //ダメージ3倍として返す
}

/// <summary>
/// いずれかの状態異常を返す
/// </summary>
bool PlayerState::anyCondition() {
	if (condition[DEADLY_POISON] || condition[CRAMPS]
		|| condition[CONFUSION] || condition[BLOODING]) {
		return true;
	}
	return false;
}

/// <summary>
/// ダメージフラグをリセット
/// </summary>
void PlayerState::resetDamageFlag() {
	poisonDamageFlag = false; //猛毒ダメージフラグをfalse
	roughDamageFlag = false; //凸凹ダメージフラグをfalse
}

/// <summary>
/// 戦闘スタイルを切り替える
/// </summary>
void PlayerState::changeBattleStyle(const int& dir) {
	//Lボタン入力かつ、戦闘スタイルが花萌葱(対猛毒)ではないとき
	if (dir == LEFT && battleStyle != DEADLY_POISON) {
		//前のスタイルのコインが0ではないとき、前のスタイルに切り替え
		if (coin[battleStyle - 1] != 0)
			battleStyle--;
			//深支子(対痙攣)のコインが0ではないとき
		else if (battleStyle == BLOODING && coin[CRAMPS] != 0)
			battleStyle = CRAMPS;
			//花萌葱(対猛毒)のコインが0ではないとき
		else if ((battleStyle == CONFUSION || battleStyle == BLOODING) && coin[DEADLY_POISON] != 0)
			battleStyle = DEADLY_POISON;
	}

		//Rボタン入力かつ、戦闘スタイルが中紅花(対出血)ではないとき
	else if (dir == RIGHT && battleStyle != BLOODING) {
		//次のスタイルのコインが0ではないとき、次のスタイルに切り替え
		if (coin[battleStyle + 1] != 0)
			battleStyle++;
			//燕子花(対混乱)のコインが0ではないとき
		else if (battleStyle == DEADLY_POISON && coin[CONFUSION] != 0)
			battleStyle = CONFUSION;
			//中紅花(対出血)のコインが0ではないとき
		else if ((battleStyle == DEADLY_POISON || battleStyle == CRAMPS) && coin[BLOODING] != 0)
			battleStyle = BLOODING;
	}
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
			SceneLoad::gameScene = GAME_OVER_SCENE; //全てのコインが0になり、ゲームオーバーシーンへ
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
			attributeAccumulation[attribute] = attributeMax; //attributeMax以上は属性蓄積値を最大値にする
	}
}

/// <summary>
/// 属性耐性値をリセットと状態異常を解消
/// </summary>
/// <param name="actionFlag">アクションフラグ</param>
/// <param name="cooldownFlag">クールダウンフラグ</param>
void PlayerState::valueReset(vector<bool>& actionFlag, vector<bool>& cooldownFlag) {
	//現在の戦闘スタイルの状態異常がtrueかつ、解消フラグがtrueのとき
	if (actionFlag[RECOVERY]) {
		if (condition[battleStyle] && coin[battleStyle] >= recoveryCoin) {
			attributeAccumulation[battleStyle] = 0; //属性耐性値をリセット
			condition[battleStyle] = false; //状態異常を解消
			cooldownFlag[RECOVERY] = true; //クールダウンフラグをtrue
			coin[battleStyle] -= recoveryCoin; //コイン支払い
		}
		actionFlag[RECOVERY] = false; //解消フラグをfalse
	}
}

/// <summary>
/// 状態のクールダウン処理
/// </summary>
/// <param name="cooldown">クールダウン</param>
/// <param name="cooldownFlag">クールダウンフラグ</param>
void PlayerState::countCooldown(vector<int>& cooldown, vector<bool>& cooldownFlag) {
	if (cooldownFlag[RECOVERY]) cooldown[RECOVERY]++; //クールダウン開始

	//クールダウンはcooldownMax秒
	if (cooldown[RECOVERY] >= cooldownMax) {
		cooldown[RECOVERY] = 0; //クールダウンをリセット
		cooldownFlag[RECOVERY] = false; //クールダウンフラグをfalse
	}
}
