#include "DxLib.h"
#include "player.h"
#include "constant.h"
#include "playerKnife.h"
#include "playerShield.h"
#include "playerSlash.h"
#include "playerState.h"

PlayerKnife knifeAct;
PlayerSlash slashAct;
PlayerShield shieldAct;
PlayerState stateAct;

Player::Player(Input& input, MapDraw& draw_) : input(input),
                                               draw_(draw_), cooldown(4),

                                               cooldownFlag(4),

                                               knifeCenter(0.0, 0.0), slashCenter(0.0, 0.0),

                                               actionFlag{false, false, false, false} {

	this->pos.dx = static_cast<int>(WIN_WIDTH / 2 - BLOCK_SIZE / 2); //プレイヤーx座標
	this->pos.dy = static_cast<int>(WIN_HEIGHT / 2 - BLOCK_SIZE / 2 - 2); //プレイヤーy座標
	center = HALF_BLOCK_SIZE_D + pos; //プレイヤーの中心座標
}

Player::~Player() {
}

/// <summary>
/// 描画処理
/// </summary>
void Player::draw() {
	//プレイヤー
	DrawRectGraph(static_cast<int>(this->pos.dx), static_cast<int>(this->pos.dy),
	              BLOCK_SIZE * input.moveDirection, BLOCK_SIZE * PlayerState::battleStyle,
	              BLOCK_SIZE, BLOCK_SIZE,
	              source.player, true, false);
}

/// <summary>
/// アクションコマンド処理
/// </summary>
void Player::actionCommand() {
	/* ナイフ入力 */
	if (input.A && cooldown[KNIFE] == 0 && input.anySTICK()) {
		actionFlag[KNIFE] = true; //ナイフ投射
		cooldownFlag[KNIFE] = true; //クールダウンフラグをtrue
	}
	/* 刃入力 */
	if (input.B && cooldown[SLASH] == 0) {
		actionFlag[SLASH] = true; //刃を回転
		cooldownFlag[SLASH] = true; //クールダウンフラグをtrue
	}
	/* シールド */
	if (input.X && !cooldownFlag[SHIELD]) {
		actionFlag[SHIELD] = true; //シールドを付与
		shieldAct.giveShield(PlayerState::battleStyle); //シールド量を追加
		cooldownFlag[SHIELD] = true; //クールダウンフラグをtrue
	}
	/* いずれかの状態異常のとき、状態を解消 */
	if (input.Y && !cooldownFlag[RECOVERY] && stateAct.anyCondition()) {
		actionFlag[RECOVERY] = true; //状態を解消
	}
	/* 戦闘スタイル切替 */
	//Lボタン
	if (input.LB)
		stateAct.changeBattleStyle(LEFT); //左のスタイルへ
	//Rボタン
	if (input.RB)
		stateAct.changeBattleStyle(RIGHT); //右のスタイルへ
}

/// <summary>
/// コインの損失処理
/// </summary>
/// <param name="attackPower">敵の攻撃力</param>
void Player::lostPlayerCoin(const int& attackPower) {
	if (!actionFlag[SHIELD]) {
		PlayerState::coin[PlayerState::battleStyle]
			-= attackPower * stateAct.addConditionDamage(); //コイン損失
		//コインが0以下ならば、
		if (PlayerState::coin[PlayerState::battleStyle] <= 0)
			PlayerState::coin[PlayerState::battleStyle] = 0; //0以下になったら0に戻す
	}
	else {
		shieldAct.value -= attackPower; //シールド量減少
		shieldAct.zeroOut(); //0以下になったとき0に戻す
	}
}

/// <summary>
/// コインの追加処理
/// </summary>
/// <param name="enemyCoin">敵の所持コイン</param>
/// <param name="attribute">敵の属性</param>
void Player::addPlayerCoin(const int& attribute, const int& enemyCoin) {
	PlayerState::coin[attribute] += enemyCoin;
}

/// <summary>
/// 属性値の蓄積処理
/// 属性蓄積値が最大値ではないとき、加算する
/// </summary>
/// <param name="attribute">敵の属性</param>
/// <param name="attributeValue">敵の属性値</param>
void Player::addAttributeAccumulation(const int& attribute, const int& attributeValue) {
	//シールドがないとき
	if (!actionFlag[SHIELD])
		stateAct.calculateValue(attribute, attributeValue); //属性蓄積値の計算

}

/// <summary>
/// 敵へのダメージ
/// </summary>
/// <param name="act">プレイヤーのアクション</param>
int Player::addDamage(const int& act) {
	if (stateAct.battleStyle != BLOODING)
		return act + 1; //通常はact+1ダメージ
	return (act + 1) * 2; //戦闘スタイルが中紅花(対出血)のとき2倍
}

bool Player::state(const int& num) {
	return stateAct.condition[num];
}

bool Player::cool(const int& num) {
	return cooldownFlag[num];
}

/// <summary>
/// ナイフ更新処理
/// </summary>
void Player::knifeUpdate() {
	knifeAct.initialize(this->pos, knifeCenter); //ナイフの初期化
	knifeAct.countCooldown(cooldown, cooldownFlag); //ナイフのクールダウン処理

	//ナイフ入力があったとき
	if (actionFlag[KNIFE]) {
		knifeAct.setKnifePosition(this->pos); //ナイフのポジジョンセット
		knifeAct.accelKnife(input); //ナイフの加速
		knifeAct.resetKnifePosition(center, actionFlag); //ナイフのポジジョンリセット
		knifeAct.calculateRadian(this->pos);
		knifeAct.draw(source); //描画処理
	}
}

/// <summary>
/// 刃更新処理
/// </summary>
void Player::slashUpdate() {
	slashAct.initialize(this->pos); //刃の初期化
	slashAct.countCooldown(cooldown, cooldownFlag, actionFlag);

	//刃の入力があったとき
	if (actionFlag[SLASH]) {
		slashAct.countTime(); //描画時間カウント
		slashAct.draw(source); //描画処理
	}
}

/// <summary>
/// シールド更新処理
/// </summary>
void Player::shieldUpdate() {
	shieldAct.initialize(this->pos); //シールドの初期化
	shieldAct.countCooldown(cooldown, cooldownFlag, actionFlag); //シールドのクールダウン処理

	if (shieldAct.value <= 0) actionFlag[SHIELD] = false; //シールド量が0になったら、シールド消失

	//シールドの入力があったとき
	if (actionFlag[SHIELD]) shieldAct.draw(source); //描画処理
}

/// <summary>
/// 状態更新処理
/// </summary>
void Player::stateUpdate() {
	stateAct.valueReset(actionFlag, cooldownFlag); //状態異常等を解消
	stateAct.countCooldown(cooldown, cooldownFlag); //状態解消のクールダウン処理
	stateAct.conditionUpdate(draw_); //状態異常更新処理
	stateAct.switchStyleAutomatically(); //生存状態を更新
}

/// <summary>
/// 現在のマップを返す
/// </summary>
/// <param name="pos">xまたはy</param>
int Player::currentMapPos(const int& pos) {
	if (pos == POSITION_X) return draw_.currentMap.x; //xマップ
	return draw_.currentMap.y; //yマップ
}

/// <summary>
/// 更新処理
/// </summary>
void Player::update() {
	actionCommand(); //アクションコマンド処理

	draw(); //描画処理

	knifeUpdate(); //ナイフ更新処理
	slashUpdate(); //刃更新処理
	shieldUpdate(); //シールド更新処理
	stateUpdate(); //更新処理

	/*DrawFormatString(0, 450, GetColor(0, 255, 0), "ナイフ　　CDR:%d", cooldown[0], false);
	DrawFormatString(0, 465, GetColor(0, 255, 0), "　刃　　　CDR:%d", cooldown[1], false);
	DrawFormatString(0, 480, GetColor(0, 255, 0), "シールド　Value:%d", cooldown[2], shieldAct.value, false);
	DrawFormatString(0, 495, GetColor(0, 255, 0), "　解消　　CDR:%d, CDRflag:%d", cooldown[3], cool(3), false);


	DrawFormatString(0, 550, GetColor(255, 100, 100), "スタイル:%d", stateAct.battleStyle, false);
	DrawFormatString(0, 565, GetColor(0x00, 0x8d, 0x56), "花萌葱:%d, コイン:%d, 状態:%d",
	                 PlayerState::attributeAccumulation[0], PlayerState::coin[0], state(0), false);
	DrawFormatString(0, 580, GetColor(0xef, 0xbb, 0x2c), "深支子:%d, コイン:%d, 状態:%d",
	                 PlayerState::attributeAccumulation[1], PlayerState::coin[1], state(1), false);
	DrawFormatString(0, 595, GetColor(0x4b, 0x5e, 0xaa), "燕子花:%d, コイン:%d, 状態:%d",
	                 PlayerState::attributeAccumulation[2], PlayerState::coin[2], state(2), false);
	DrawFormatString(0, 610, GetColor(0xee, 0x86, 0x9a), "中紅花:%d, コイン:%d, 状態:%d",
	                 PlayerState::attributeAccumulation[3], PlayerState::coin[3], state(3), false);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "mX%d, mY%d", draw_.currentMap.x, draw_.currentMap.y, false);*/

	/*DrawFormatString(0, 500, GetColor(120, 0, 100), "トレジャーランク:%d, 花萌葱:%d, 金糸雀:%d, 葡萄染:%d, 白百合:%d",
	                 status[TREASURE_RANK], status[GREEN_COIN], status[YELLOW_COIN],
	                 status[PURPLE_COIN], status[WHITE_COIN], false);
	DrawFormatString(0, 515, GetColor(120, 0, 100), "現在生命力:%d, 最大生命力:%d, 攻撃力:%d, 交渉力:%d",
	                 status[CURRENT_LIFE], status[MAX_LIFE],
	                 status[ATTACK], status[BARGAINING_POWER], false);
	DrawFormatString(0, 530, GetColor(120, 0, 100), "猛毒耐性:%d, 猛毒属性値:%d, 猛毒蓄積:%d,  麻痺耐性:%d, 麻痺属性値:%d, 麻痺蓄積:%d",
	                 status[DEADLY_POISON_RESISTANCE], status[DEADLY_POISON_VALUE],
	                 status[DEADLY_POISON_ACCUMULATION],
	                 status[PARALYSIS_RESISTANCE], status[PARALYSIS_VALUE],
	                 status[PARALYSIS_ACCUMULATION], false);
	DrawFormatString(0, 545, GetColor(120, 0, 100), "催眠耐性:%d, 催眠属性値:%d, 催眠蓄積:%d, 出血耐性:%d, 出血属性値:%d, 出血蓄積:%d",
	                 status[HYPNOSIS_RESISTANCE], status[HYPNOSIS_VALUE],
	                 status[HYPNOSIS_ACCUMULATION],
	                 status[BLOODING_RESISTANCE], status[BLOODING_VALUE],
	                 status[BLOODING_ACCUMULATION], false);
	DrawFormatString(0, 630, GetColor(0, 0, 0), "非常食:%d, パン:%d, 肉:%d, 魚:%d、豆:%d, 地図:%d, ボトル小:%d, ボトル大:%d",
	                 possessionItem[0], possessionItem[1], possessionItem[2],
	                 possessionItem[3], possessionItem[4], possessionItem[5],
	                 possessionItem[6], possessionItem[7], false);
	DrawFormatString(0, 645, GetColor(0, 0, 0),
	                 "不思議なボトル:%d, 毒草:%d, 解毒草:%d, 健康草:%d、チューリップ:%d, アロエ:%d, マリーゴールド:%d, 麻酔花:%d",
	                 possessionItem[8], possessionItem[9], possessionItem[10],
	                 possessionItem[11], possessionItem[12], possessionItem[13],
	                 possessionItem[14], possessionItem[15], false);
	DrawFormatString(0, 660, GetColor(0, 0, 0),
	                 "薔薇:%d, 寝袋:%d, スコップ:%d, ピッケル:%d、ナイフ:%d, 長靴:%d, アロマキノコ:%d, 止血剤:%d",
	                 possessionItem[16], possessionItem[17], possessionItem[18],
	                 possessionItem[19], possessionItem[20], possessionItem[21],
	                 possessionItem[22], possessionItem[23], false);
	DrawFormatString(0, 675, GetColor(0, 0, 0),
	                 "健康食:%d, 猛毒薬:%d, 麻酔薬:%d, 暗視草:%d、ルピナス:%d, タンポポ:%d, マッスルダケ:%d, 豊樹草:%d",
	                 possessionItem[24], possessionItem[25], possessionItem[26],
	                 possessionItem[27], possessionItem[28], possessionItem[29],
	                 possessionItem[30], possessionItem[31], false);
	DrawFormatString(0, 690, GetColor(0, 0, 0),
	                 "赤実:%d, バーナー:%d, 東国飯:%d, シーパワー:%d、ブラッドエキス:%d, ブラッドポーション:%d、快眠ダケ:%d, スリープジェル:%d",
	                 possessionItem[32], possessionItem[33], possessionItem[34],
	                 possessionItem[35], possessionItem[36], possessionItem[37],
	                 possessionItem[38], possessionItem[39], false);
	DrawFormatString(0, 720, GetColor(0, 0, 0), "Bネック:%d, Bチョー:%d, Bペンダ:%d, Bリング:%d、Bピアス:%d, テレサ:%d, マチルダ:%d, ナガタラ:%d",
	                 possessionAccessory[0], possessionAccessory[1], possessionAccessory[2],
	                 possessionAccessory[3], possessionAccessory[4], possessionAccessory[5],
	                 possessionAccessory[6], possessionAccessory[7], false);
	DrawFormatString(0, 735, GetColor(0, 0, 0), "Sネック:%d, Sチョー:%d, Sペンダ:%d, Sリング:%d、Sピアス:%d, 東国紋章:%d, Gネック:%d, Gペンダ:%d",
	                 possessionAccessory[8], possessionAccessory[9], possessionAccessory[10],
	                 possessionAccessory[11], possessionAccessory[12], possessionAccessory[14],
	                 possessionAccessory[15], possessionAccessory[16], false);
	DrawFormatString(0, 770, GetColor(0, 0, 0), "エメラルド:%d, Tガーネット:%d, Cトルマリン:%d, ペリD:%d、花萌葱ロードN:%d",
	                 possessionJewel[0], possessionJewel[1], possessionJewel[2],
	                 possessionJewel[3], possessionJewel[20], false);
	DrawFormatString(0, 800, GetColor(0, 0, 0), "軽石:%d, 東栄石:%d, 南栄石:%d, 西栄石:%d、北栄石:%d, 黄金超石:%d",
	                 possessionMineral[0], possessionMineral[1], possessionMineral[2],
	                 possessionMineral[3], possessionMineral[4], possessionMineral[4], false);*/
}
