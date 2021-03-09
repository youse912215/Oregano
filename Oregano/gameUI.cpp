#include "gameUI.h"
#include "DxLib.h"
#include "constant.h"
#include "playerState.h"
#include "dataText.h"
#include "sceneLoad.h"

DataText text_;
PlayerState state__;

GameUI::GameUI(Input& input, Player& player, MapDraw& map) :
	input(input), player(player), map(map), margin(16), eventSize(9), eventLength(4),
	/*　メニュー */
	menuLength(256, 64), menuSize(WIN_WIDTH - menuLength.x - margin, margin),
	/* パッシブ */
	passiveSize(margin, WIN_HEIGHT - 128 - margin),
	/* 状態異常 */
	conditionSize(WIN_WIDTH - 256 - margin, WIN_HEIGHT - 128 - margin),
	/* モード */
	modeLeftSize(BLOCK_SIZE * 7 - margin, WIN_HEIGHT - 128 - margin),
	modeLength(64, 128),
	modeRightSize(BLOCK_SIZE * 16 + 32 - margin, WIN_HEIGHT - modeLength.y - margin),
	/* アクション */
	actionLength(512, 128),
	/* マップ上イベント */
	actionSize(BLOCK_SIZE * 8 + 16 - margin, WIN_HEIGHT - actionLength.y - margin),
	speechBalloonPos(HALF_WIN_WIDTH - 32, HALF_WIN_HEIGHT - 100), mapEventPos(MAP_EVENT_SIZE),
	eventNum(0) {
}

GameUI::~GameUI() {
}

/// <summary>
/// ぼかしの描画
/// </summary>
void GameUI::drawBlur() {
	//マップ座標（3, 2）より右上以外は通常ぼかし
	if (!(map.currentMap.x >= 3 && map.currentMap.y <= 2))
		DrawGraph(0, 0, blurGraph1, true);
		//さらに視界を狭めるぼかし
	else
		DrawGraph(0, 0, blurGraph2, true);
}

/// <summary>
/// フィルター描画
/// </summary>
void GameUI::drawFilter() {
	/* 現在の戦闘スタイル以外のパッシブUIをフィルターで隠す */
	for (int i = 0; i <= BLOODING; ++i) {
		if (PlayerState::battleStyle != i)
			DrawGraph(passiveSize.x + BLOCK_SIZE * i,
			          passiveSize.y + BLOCK_SIZE, filterGraph1, true);
	}
	/* 現在の状態異常以外をフィルターで隠す */
	for (int i = 0; i <= BLOODING; ++i) {
		if (!PlayerState::condition[i])
			DrawGraph(conditionSize.x + BLOCK_SIZE * i, conditionSize.y + BLOCK_SIZE,
			          filterGraph1, true);
	}
	/* 現在出来ないアクションをフィルターで隠す */
	for (int i = 0; i < 3; ++i) {
		if (player.actionFlag[i])
			DrawGraph(actionSize.x + BLOCK_SIZE * 2 * i, actionSize.y, filterGraph2, true);
	}
	if (!state__.anyCondition())
		DrawGraph(actionSize.x + BLOCK_SIZE * 6, actionSize.y, filterGraph2, true);
}

/// <summary>
/// プレイヤーとイベント位置の一致条件
/// </summary>
/// <param name="i">イベント番号</param>
bool GameUI::positionMatchDecision(const int& i) {
	return map.currentMap.x == mapEventPos[i * eventLength] //マップx座標
		&& map.currentMap.y == mapEventPos[i * eventLength + 1] //マップy座標
		&& abs(map.blockArea.x - mapEventPos[i * eventLength + 2]) <= 1 //区画x座標
		&& abs(map.blockArea.y - mapEventPos[i * eventLength + 3]) <= 1; //区画y座標
}

/// <summary>
/// イベント用噴き出しの描画
/// </summary>
void GameUI::drawSpeechBalloon() {
	//イベント数分繰り返す
	for (int i = 0; i < eventSize; ++i) {
		//プレイヤーとイベント位置が一致
		if (!positionMatchDecision(i))
			continue; //条件以外のとき、処理をスキップする
		DrawGraph(speechBalloonPos.x, speechBalloonPos.y, source.eventGraph, true); //噴き出し

		eventNum = i; //今いる位置のイベント番号を代入

		if (input.VIEW) {
			//目的地点のイベント番号(eventSize - 1)以外なら
			if (eventNum != eventSize - 1) {
				SceneLoad::gameScene = SAVE_SCENE; //VIEWボタンを押したとき、セーブシーンへ
			}
			else SceneLoad::gameScene = END_SCENE; //VIEWボタンを押したとき、エンドシーンへ
		}
	}
}

/// <summary>
/// 描画処理
/// </summary>
void GameUI::draw() {
	DrawGraph(margin, margin, coinGraph, true); //コイン

	DrawRectGraph(menuSize.x, menuSize.y,
	              0, 0, menuLength.x, menuLength.y,
	              menuGraph, true, false, false); //メニュー

	DrawGraph(passiveSize.x, passiveSize.y, passiveGraph, true); //パッシブ

	DrawGraph(conditionSize.x, conditionSize.y, conditionGraph, true); //状態異常

	DrawRectGraph(modeLeftSize.x, modeLeftSize.y,
	              0, 0, modeLength.x, modeLength.y, modeGraph,
	              true, false, false); //Lモード

	DrawRectGraph(modeRightSize.x, modeRightSize.y,
	              modeLength.x, 0, modeLength.x, modeLength.y, modeGraph,
	              true, false, false); //Rモード

	DrawRectGraph(actionSize.x, actionSize.y,
	              0, 0, actionLength.x, actionLength.y, actionGraph,
	              true, false, false); //アクション
	drawFilter(); //フィルター描画
}

void GameUI::update() {
	drawBlur(); //ぼかし
	draw();
	text_.drawText();
	drawSpeechBalloon(); //イベント用噴き出し描画

	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d, %d, %d, %d",
	                 mapEventPos[0], mapEventPos[1], mapEventPos[2], mapEventPos[3], false);
}
