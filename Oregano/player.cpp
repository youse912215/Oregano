#include "DxLib.h"
#include "player.h"
#include "constant.h"
#include "eventBase.h"
#include <algorithm>

#include "playerKnife.h"
#include "playerShield.h"
#include "playerSlash.h"

PlayerKnife knifeAct;
PlayerSlash slashAct;
PlayerShield shieldAct;

Player::Player(Input& input) :
	input(input), cooldown(3), cooldownFlag(3),

	coin{50, 0, 0, 0}, attributeAccumulation{0, 0, 0, 0},

	stateAbnormal(4), knifeCenter(0.0, 0.0),
	slashCenter(0.0, 0.0), knife(false), slash(false), shield(false),

	/* データ類 */
	status(PLAYER_STATUS_SIZE), possessionItem(PLAYER_ITEM_SIZE),
	possessionAccessory(PLAYER_ACCESSORY_SIZE), possessionJewel(PLAYER_JEWEL_SIZE),
	possessionMineral(PLAYER_MINERAL_SIZE) {

	this->pos.dx = static_cast<int>(WIN_WIDTH / 2 - BLOCK_SIZE / 2); //プレイヤーx座標
	this->pos.dy = static_cast<int>(WIN_HEIGHT / 2 - BLOCK_SIZE / 2 - 2); //プレイヤーy座標
	center = HALF_BLOCK_SIZE_D + pos; //プレイヤーの中心座標

	battleStyle = 0;
}

Player::~Player() {
}

/// <summary>
/// 描画処理
/// </summary>
void Player::draw() {
	//プレイヤー
	DrawRectGraph(static_cast<int>(this->pos.dx),
	              static_cast<int>(this->pos.dy),
	              0, 0, BLOCK_SIZE, BLOCK_SIZE,
	              source.player, true, false);

	DrawFormatString(static_cast<int>(this->pos.dx), static_cast<int>(this->pos.dy),
	                 GetColor(255, 0, 0), "%lf, %lf, %lf, %lf",
	                 this->pos.dx, this->pos.dy, center.dx, center.dy, false);
}

/// <summary>
/// アクションコマンド処理
/// </summary>
void Player::actionCommand() {
	/* ナイフ入力 */
	if (input.A && cooldown[KNIFE] == 0 && input.anySTICK()) {
		knife = true; //ナイフ投射
		cooldownFlag[KNIFE] = true; //クールダウンフラグをtrue
	}
	/* 刃入力 */
	if (input.B && cooldown[SLASH] == 0) {
		slash = true; //刃を回転
		cooldownFlag[SLASH] = true; //クールダウンフラグをtrue
	}
	/* シールド */
	if (input.X && !cooldownFlag[SHIELD]) {
		shield = true; //シールドを付与
		shieldAct.shieldValue = 15;
		cooldownFlag[SHIELD] = true; //クールダウンフラグをtrue
	}

	//Lボタン
	if (input.LB && battleStyle != 0)
		changeBattleStyle(LEFT);
	//Rボタン
	if (input.RB && battleStyle != 3)
		changeBattleStyle(RIGHT);
}

/// <summary>
/// コイン更新処理
/// </summary>
void Player::coinUpdate() {
}

/// <summary>
/// 戦闘スタイルを切り替える
/// </summary>
void Player::changeBattleStyle(const int& dir) {
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
/// コインの損失処理
/// </summary>
/// <param name="attackPower">敵の攻撃力</param>
void Player::lostPlayerCoin(const int& attackPower) {
	if (!shield)
		coin[battleStyle] -= attackPower;
	else
		shieldAct.shieldValue -= attackPower;
}

/// <summary>
/// コインの追加処理
/// </summary>
/// <param name="enemyCoin">敵の所持コイン</param>
/// <param name="attribute">敵の属性</param>
void Player::addPlayerCoin(const int& attribute, const int& enemyCoin) {
	coin[attribute] += enemyCoin;
}

/// <summary>
/// 属性蓄積値が最大値でないとき、加算する
/// </summary>
/// <param name="attribute">敵の属性</param>
/// <param name="attributeValue">敵の属性値</param>
void Player::addAttributeAccumulation(const int& attribute, const int& attributeValue) {
	//シールドがないときかつ、現在の戦闘スタイルと敵の属性が異なるとき
	if (!shield && battleStyle != attribute) {
		if (attributeAccumulation[attribute] < 100)
			attributeAccumulation[attribute] += attributeValue; //属性蓄積値を加算
		else if (attributeAccumulation[attribute] >= 100)
			attributeAccumulation[attribute] = 100; //100以上は属性蓄積値を最大値にする
	}
}

/// <summary>
/// 戦闘スタイルの生存状態を更新
/// </summary>
void Player::battleStyleUpdate() {
	if (coin[battleStyle] <= 0) {
		//全てのコインの中で0でない要素を探し、見つかった最初の要素のイテレーターを返す
		auto itr = find_if(coin.begin(), coin.end(),
		                   [](int x) { return x != 0; });
		//0以外の要素が見つかれば、その要素をbattleStyleに代入
		if (itr != coin.end())
			battleStyle = distance(coin.begin(), itr); //戦闘スタイルを切り替える
		else
			EventBase::gameScene = END_SCENE; //全てのコインが0になり、ゲームオーバーシーンへ
	}
}

/// <summary>
/// ナイフ更新処理
/// </summary>
void Player::knifeUpdate() {
	knifeAct.initialize(this->pos, knifeCenter); //ナイフの初期化
	knifeAct.knifeCooldown(cooldown, cooldownFlag); //ナイフのクールダウン処理

	//ナイフ入力があったとき
	if (knife) {
		knifeAct.setKnifePosition(this->pos); //ナイフのポジジョンセット
		knifeAct.accelKnife(input); //ナイフの加速
		knifeAct.resetKnifePosition(center, knife); //ナイフのポジジョンリセット
		knifeAct.draw(source); //描画処理
	}
}

/// <summary>
/// 刃更新処理
/// </summary>
void Player::slashUpdate() {
	slashAct.initialize(this->pos); //刃の初期化
	slashAct.slashCooldown(cooldown, cooldownFlag, slash);

	if (slash) slashAct.draw(source);
}

/// <summary>
/// シールド更新処理
/// </summary>
void Player::shieldUpdate() {
	shieldAct.initialize(this->pos); //シールドの初期化
	shieldAct.shieldCooldown(cooldown, cooldownFlag, shield); //シールドのクールダウン処理

	if (shieldAct.shieldValue <= 0) shield = false; //シールド量が0になったら、シールド消失

	if (shield) shieldAct.draw(source);
}

/// <summary>
/// 更新処理
/// </summary>
void Player::update() {


	actionCommand(); //アクションコマンド処理

	knifeUpdate(); //ナイフ更新処理
	slashUpdate(); //刃更新処理
	shieldUpdate(); //シールド更新処理

	coinUpdate();
	battleStyleUpdate();

	draw(); //描画処理

	DrawFormatString(0, 450, GetColor(0, 255, 0), "ナイフ　　TF:%d, CDR:%d", knife, cooldown[0], false);
	DrawFormatString(0, 465, GetColor(0, 255, 0), "　刃　　　TF:%d, CDR:%d", slash, cooldown[1], false);
	DrawFormatString(0, 480, GetColor(0, 255, 0), "シールド　TF:%d, CDR:%d, Value:%d",
	                 shield, cooldown[2], shieldAct.shieldValue, false);
	DrawFormatString(0, 550, GetColor(255, 100, 100), "スタイル:%d", battleStyle, false);
	DrawFormatString(0, 565, GetColor(0x00, 0x8d, 0x56), "花萌葱:%d, コイン:%d", attributeAccumulation[0], coin[0], false);
	DrawFormatString(0, 580, GetColor(0xef, 0xbb, 0x2c), "深支子:%d, コイン:%d", attributeAccumulation[1], coin[1], false);
	DrawFormatString(0, 595, GetColor(0x4b, 0x5e, 0xaa), "燕子花:%d, コイン:%d", attributeAccumulation[2], coin[2], false);
	DrawFormatString(0, 610, GetColor(0xee, 0x86, 0x9a), "中紅花:%d, コイン:%d", attributeAccumulation[3], coin[3], false);

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
