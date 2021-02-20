#include "eventField.h"
#include "constant.h"
#include "mapDraw.h"
#include "DxLib.h"

EventField::EventField(Input& input, EventBase& event, Player& player)
	: input(input), event(event), player(player), coinFlag(250),
	  coinQuantity{5, 10, 50, 100}, coin(COIN_INFORMATION_QUANTITY) {
	eventFlag = false;
}

EventField::~EventField() {
}

/// <summary>
/// Xボタンを押したとき、フィールド上の指定の場所でアイテムを入手可能にする
/// </summary>
void EventField::getFieldItem() {
	if (input.X) {
		for (unsigned int i = 0; i < coin.size() / INFORMATION_SIZE; ++i) {
			if (!( //イベント発生場所の方向を向いているとき
				input.moveDirection == directionReverse(coin[(i * INFORMATION_SIZE) + DIRECTION_])
				//コインフラグがfalseのとき
				&& !coinFlag[coin[(i * INFORMATION_SIZE) + EVENT_NO_]]
				//イベント発生場所の周辺にいるとき
				&& event.getEventCoordinate(
					coin[(i * INFORMATION_SIZE) + MAP_X_],
					coin[(i * INFORMATION_SIZE) + MAP_Y_],
					coin[(i * INFORMATION_SIZE) + CURRENT_X_]
					+ directionSignX(coin[(i * INFORMATION_SIZE) + DIRECTION_]),
					coin[(i * INFORMATION_SIZE) + CURRENT_Y_]
					+ directionSignY(coin[(i * INFORMATION_SIZE) + DIRECTION_]))))
				continue; //条件以外のとき、処理をスキップする
			{
				player.status[coinTypeDecision(coin[(i * INFORMATION_SIZE) + ITEM_TYPE_])]
					+= coinQuantityDecision(coin[(i * INFORMATION_SIZE) + ITEM_TYPE_]); //コインの入手（種類別に追加）
				coinFlag[coin[(i * INFORMATION_SIZE) + EVENT_NO_]] = true; //入手した場所のコインイベントを済み状態(true)にする
			}
		}
		eventFlag = true; //ボタンを押しているときはイベントフラグをtrue
	}
	else eventFlag = false; //ボタンを押していないときはイベントフラグをfalse
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
/// <param name="coinTypeDecision">コインの種類</param>
int EventField::coinQuantityDecision(const int& coinType) {
	return coinQuantity[coinType];
}

/// <summary>
/// コインの種類によって、適切な色のコイン情報を返す
/// </summary>
/// <param name="coinTypeDecision">コインの種類</param>
int EventField::coinTypeDecision(const int& coinType) {
	if (coinType >= 0 && coinType <= 3) return GREEN_COIN;
	if (coinType >= 4 && coinType <= 7) return YELLOW_COIN;
	if (coinType >= 8 && coinType <= 11) return PURPLE_COIN;
	if (coinType >= 12 && coinType <= 15) return WHITE_COIN;
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
	getFieldItem();
	DrawFormatString(300, 0, GetColor(130, 130, 255), "イベント:%d, 向き:%d, T%d",
	                 this->eventFlag, input.moveDirection,
	                 event.getEventCoordinate(8, 7, 12, 24), false);
	DrawFormatString(100, 0, GetColor(255, 0, 0), "cx:%d, cy:%d",
	                 event.centralPlayerPosition(MAP_X), event.centralPlayerPosition(MAP_Y), false);
}
