#include "DxLib.h"
#include "Player.h"
#include "constant.h"
#include "mapDraw.h"

Player::Player(Input& input, DataSource& source) :
	input(input), source(source), cooldown(3), cooldownFlag(3),
	status(PLAYER_STATUS_SIZE), possessionItem(PLAYER_ITEM_SIZE),
	possessionAccessory(PLAYER_ACCESSORY_SIZE), possessionJewel(PLAYER_JEWEL_SIZE),
	possessionMineral(PLAYER_MINERAL_SIZE) {
	this->pos.dx = static_cast<int>(WIN_WIDTH / 2 - BLOCK_SIZE / 2);
	this->pos.dy = static_cast<int>(WIN_HEIGHT / 2 - BLOCK_SIZE / 2 - 2);
	center = HALF_BLOCK_SIZE + pos;
	knife = false;
	knifePosition = 0;
	knifePos = 0;
	knifeCenter = 0;
}

Player::~Player() {
}

/// <summary>
/// 描画処理
/// </summary>
void Player::draw() {
	DrawGraph(static_cast<int>(this->pos.dx),
	          static_cast<int>(this->pos.dy), source.player, true); //プレイヤー

	if (knife) //ナイフの入力があったとき
		DrawGraph(static_cast<int>(knifePos.dx), static_cast<int>(knifePos.dy), source.weapon1, true); //ナイフ

	//if (rotatingSlash)
	//	DrawGraph(weapon1X(), weapon1Y(), source.weapon1, TRUE); //回転斬り

	DrawFormatString(static_cast<int>(this->pos.dx), static_cast<int>(this->pos.dy),
	                 GetColor(255, 0, 0), "%lf, %lf, %lf, %lf",
	                 this->pos.dx, this->pos.dy, center.dx, center.dy, false);
	DrawFormatString(static_cast<int>(this->pos.dx), static_cast<int>(this->pos.dy) - 15,
	                 GetColor(255, 0, 0), "X%lf, Y%lf",
	                 knifePos.dx, knifePos.dy, false);
}

/// <summary>
/// アクションコマンド処理
/// </summary>
void Player::actionCommand() {
	/* ナイフ入力 */
	if (input.A && cooldown[KNIFE] == 0 && input.anySTICK()) {
		knife = true;
		cooldownFlag[KNIFE] = true;
	}
	/* 回転斬り入力 */
	if (input.B && cooldown[ROTATING_SLASH] == 0) {
		rotatingSlash = true;
		cooldownFlag[ROTATING_SLASH] = true;
	}
}

/// <summary>
/// ナイフのポジジョンをセットする
/// </summary>
void Player::knifePositionSet() {
	/* x方向 */
	if (knifePos.dx < pos.dx) knifePosition.dx -= KNIFE_SPEED;
	else if (knifePos.dx > pos.dx) knifePosition.dx += KNIFE_SPEED;
	else knifePosition.dx = 0;
	/* y方向 */
	if (knifePos.dy < pos.dy) knifePosition.dy -= KNIFE_SPEED;
	else if (knifePos.dy > pos.dy)knifePosition.dy += KNIFE_SPEED;
	else knifePosition.dy = 0;
}

/// <summary>
/// ナイフのポジジョンをリセットする
/// </summary>
void Player::knifePositionReset() {
	if (deleteKnife()) {
		knife = false;
		knifePosition.dx = 0;
		knifePosition.dy = 0;
	}
}

/// <summary>
/// ナイフの加速（ジョイパッドだと曲げることも可能）
/// </summary>
void Player::accelKnife() {
	/* x方向 */
	if (input.STICK[LEFT]) knifePosition.dx -= KNIFE_SPEED / 2.0;
	else if (input.STICK[RIGHT]) knifePosition.dx += KNIFE_SPEED / 2.0;
	/* y方向 */
	if (input.STICK[UP]) knifePosition.dy -= KNIFE_SPEED / 2.0;
	else if (input.STICK[DOWN]) knifePosition.dy += KNIFE_SPEED / 2.0;
}

/// <summary>
/// ナイフの更新処理
/// </summary>
void Player::knifeUpdate() {
	//ナイフ入力があったとき
	if (knife) {
		knifePositionSet(); //ナイフのポジジョンセット
		accelKnife(); //ナイフの加速
		knifePositionReset(); //ナイフのポジジョンリセット
	}
}

/// <summary>
/// ナイフの削除条件
/// </summary>
/// <returns></returns>
bool Player::deleteKnife() {
	//プレイヤーからの距離が3マス分離れているか
	return abs(knifePos.dx + HALF_BLOCK_SIZE - center.dx) >= BLOCK_SIZE * 3.0
		|| abs(knifePos.dy + HALF_BLOCK_SIZE - center.dy) >= BLOCK_SIZE * 3.0;
}

/// <summary>
/// 更新処理
/// </summary>
void Player::update() {
	if (cooldown[0] >= 30) {
		cooldown[0] = 0;
		cooldownFlag[0] = false;
	}
	if (cooldownFlag[0]) cooldown[0]++;

	knifePos = pos + knifePosition;
	knifeCenter = HALF_BLOCK_SIZE + knifePos;

	actionCommand(); //アクションコマンド処理
	knifeUpdate(); //ナイフ更新処理
	draw(); //描画処理

	DrawFormatString(0, 450, GetColor(0, 255, 0), "TF:%d, CDR:%d", knife, cooldown[0], false);

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
