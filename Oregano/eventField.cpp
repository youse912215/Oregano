#include "eventField.h"
#include "constant.h"
#include "mapDraw.h"
#include "DxLib.h"

EventField::EventField(Input& input, EventBase& event, Player& player)
	: input(input), event(event), player(player),
	  /*各フィールドオブジェクトのフラグ*/
	  coinFlag(COIN_EVENT_SIZE), itemFlag(ITEM_EVENT_SIZE), accessoryFlag(ACCESSORY_EVENT_SIZE),
	  jewelFlag(JEWEL_EVENT_SIZE), mineralFlag(MINERAL_EVENT_SIZE),
	  /*コイン量配列*/
	  coinQuantity{5, 10, 50, 100},
	  /*各フィールドオブジェクトの情報格納用の配列*/
	  coin(COIN_INFORMATION_SIZE), item(ITEM_INFORMATION_SIZE), accessory(ACCESSORY_INFORMATION_SIZE),
	  jewel(JEWEL_INFORMATION_SIZE), mineral(MINERAL_INFORMATION_SIZE) {
	actionFlagX = false; //Xボタンアクションフラグ
}

EventField::~EventField() {
}

/// <summary>
/// Xボタンを押したとき、フィールド上の指定の場所でアイテムやコインなどを入手可能にする
/// </summary>
void EventField::getFieldObject(vector<int>& objectName, vector<bool>& eventFlag, vector<int>& saveLocation) {
	for (unsigned int i = 0; i < objectName.size() / EVENT_INFORMATION_SIZE; ++i) {
		if (!( //イベント発生場所の方向を向いているとき
			input.moveDirection == directionReverse(objectName[(i * EVENT_INFORMATION_SIZE) + DIRECTION_])
			//イベントフラグがfalseのとき
			&& !eventFlag[objectName[(i * EVENT_INFORMATION_SIZE) + EVENT_NO_]]
			//イベント発生場所の周辺にいるとき
			&& event.getEventCoordinate(
				objectName[(i * EVENT_INFORMATION_SIZE) + MAP_X_],
				objectName[(i * EVENT_INFORMATION_SIZE) + MAP_Y_],
				objectName[(i * EVENT_INFORMATION_SIZE) + CURRENT_X_]
				+ directionSignX(objectName[(i * EVENT_INFORMATION_SIZE) + DIRECTION_]),
				objectName[(i * EVENT_INFORMATION_SIZE) + CURRENT_Y_]
				+ directionSignY(objectName[(i * EVENT_INFORMATION_SIZE) + DIRECTION_]))))
			continue; //条件以外のとき、処理をスキップする
		{
			eventFlag[objectName[(i * EVENT_INFORMATION_SIZE) + EVENT_NO_]] = true; //入手した場所のイベントを済み状態(true)にする

			/* コインのときのみ、保存する条件を変更する */
			if (objectName == coin)
				saveLocation[coinTypeDecision(objectName[(i * EVENT_INFORMATION_SIZE) + ITEM_TYPE_])]
					+= coinQuantityDecision(objectName[(i * EVENT_INFORMATION_SIZE) + ITEM_TYPE_]); //コインの入手（種類別に追加）
			else
				saveLocation[objectName[(i * EVENT_INFORMATION_SIZE) + ITEM_TYPE_]]++; //その他のアイテムの入手
		}
	}
}

/// <summary>
/// オブジェクト量を保存先に格納する
/// </summary>
/// <param name="saveLocation">データ保存先</param>
/// <param name="objectVolume">データ量</param>
void EventField::storingObject(int* saveLocation, const int& objectVolume) {
	if (saveLocation == nullptr) { return; } //nullチェック
	*saveLocation += objectVolume;
}

/// <summary>
/// フィールドアクション
/// </summary>
void EventField::fieldAction() {
	if (input.X) {
		getFieldObject(coin, coinFlag, player.status); //フィールドコインを入手
		getFieldObject(item, itemFlag, player.possessionItem); //フィールドアイテムを入手
		getFieldObject(accessory, accessoryFlag, player.possessionAccessory); //フィールドアクセサリーを入手
		getFieldObject(jewel, jewelFlag, player.possessionJewel); //フィールドジュエルを入手
		getFieldObject(mineral, mineralFlag, player.possessionMineral); //フィールド鉱物を入手

		actionFlagX = true; //ボタンを押しているときはアクションフラグをtrue
	}
	else actionFlagX = false; //ボタンを押していないときはアクションフラグをfalse
}

/// <summary>
/// x方向によって、-1か1を返す
/// </summary>
/// <param name="direction">イベント発生場所と隣接している方向</param>
int EventField::directionSignX(const int& direction) {
	if (direction == LEFT) return -1;
	if (direction == RIGHT) return 1;
	return 0;
}

/// <summary>
///	y方向によって、-1か1を返す
/// </summary>
/// <param name="direction">イベント発生場所と隣接している方向</param>
int EventField::directionSignY(const int& direction) {
	if (direction == UP) return -1;
	if (direction == DOWN) return 1;
	return 0;
}

/// <summary>
/// コインの種類によって、適切な量を返す
/// </summary>
/// <param name="coinType">コインの種類</param>
int EventField::coinQuantityDecision(const int& coinType) {
	return coinQuantity[coinType];
}

/// <summary>
/// コインの種類によって、適切な色のコイン情報を返す
/// </summary>
/// <param name="coinType">コインの種類</param>
int EventField::coinTypeDecision(const int& coinType) {
	if (coinType >= 0 && coinType <= 3) return GREEN_COIN; //花萌葱のコイン
	if (coinType >= 4 && coinType <= 7) return YELLOW_COIN; //金糸雀のコイン
	if (coinType >= 8 && coinType <= 11) return PURPLE_COIN; //葡萄染のコイン
	if (coinType >= 12 && coinType <= 15) return WHITE_COIN; //白百合のコイン
	return 0;
}

/// <summary>
/// 方向を反転させる
/// </summary>
/// <param name="direction"></param>
int EventField::directionReverse(const int& direction) {
	if (direction == LEFT) return RIGHT;
	if (direction == RIGHT) return LEFT;
	if (direction == UP) return DOWN;
	if (direction == DOWN) return UP;
	return 0;
}

/// <summary>
/// 更新処理
/// </summary>
void EventField::update() {
	fieldAction(); //フィールドアクション

	DrawFormatString(300, 0, GetColor(130, 130, 255), "イベント:%d, 向き:%d, T%d",
	                 this->actionFlagX, input.moveDirection,
	                 event.getEventCoordinate(8, 7, 12, 24), false);
	DrawFormatString(100, 0, GetColor(255, 0, 0), "cx:%d, cy:%d,",
	                 event.centralPlayerPosition(MAP_X), event.centralPlayerPosition(MAP_Y), false);
	DrawFormatString(WIN_WIDTH - 100, WIN_HEIGHT - 15, GetColor(255, 0, 0), "TIME:%d",
	                 EventBase::gameTime, false);
}
