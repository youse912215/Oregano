#include "DxLib.h"
#include "player.h"
#include "constant.h"
#include "playerKnife.h"
#include "playerShield.h"
#include "playerSlash.h"
#include "playerState.h"

PlayerKnife knifeAct; //ナイフクラス
PlayerSlash slashAct; //刃クラス
PlayerShield shieldAct; //シールドクラス
PlayerState stateAct; //プレイヤー状態クラス

Player::Player(Input& input, MapDraw& draw_, DataSource& source) :
	input(input), draw_(draw_), source(source),

	pos(static_cast<int>(WIN_WIDTH / 2 - BLOCK_SIZE / 2), static_cast<int>(WIN_HEIGHT / 2 - BLOCK_SIZE / 2 - 2)),

	cooldown(4), damageFlag(false), center(HALF_BLOCK_SIZE_D + pos),

	knifeCenter(0.0, 0.0), slashCenter(0.0, 0.0),

	actionFlag{false, false, false, false}, cooldownFlag(4) {
}

Player::~Player() {
}

/// <summary>
/// 描画処理
/// </summary>
void Player::draw() {
	//各ダメージフラグがfalseのとき
	if (!(stateAct.poisonDamageFlag || stateAct.roughDamageFlag || damageFlag)) {
		//通常時のプレイヤー画像
		DrawRectGraph(static_cast<int>(this->pos.dx), static_cast<int>(this->pos.dy),
		              BLOCK_SIZE * input.moveDirection, BLOCK_SIZE * PlayerState::battleStyle,
		              BLOCK_SIZE, BLOCK_SIZE,
		              source.player, true, false);
	}
	else {
		//ダメージ受けたときのプレイヤー画像
		DrawRectGraph(static_cast<int>(this->pos.dx), static_cast<int>(this->pos.dy),
		              BLOCK_SIZE * input.moveDirection, BLOCK_SIZE * PlayerState::battleStyle,
		              BLOCK_SIZE, BLOCK_SIZE,
		              source.playerDamage, true, false);
	}
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

		damageFlag = true; //ダメージフラグをtrue
		source.playSe(source.seDamage); //ダメージSE

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
		knifeAct.calculateRadian(this->pos); //ラジアン計算
		knifeAct.draw(source); //描画処理
	}
}

/// <summary>
/// 刃更新処理
/// </summary>
void Player::slashUpdate() {
	slashAct.initialize(this->pos); //刃の初期化
	slashAct.countCooldown(cooldown, cooldownFlag, actionFlag); //クールダウン処理

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
	stateAct.conditionUpdate(draw_, source); //状態異常更新処理
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

	/* ダメージフラグをリセット */
	damageFlag = false;
	stateAct.resetDamageFlag();

	knifeUpdate(); //ナイフ更新処理
	slashUpdate(); //刃更新処理
	shieldUpdate(); //シールド更新処理
	stateUpdate(); //状態更新処理
}
