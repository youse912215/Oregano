#include "gameUI.h"
#include "DxLib.h"
#include "constant.h"
#include "playerState.h"
#include "dataText.h"

DataText text_;
PlayerState state__;

GameUI::GameUI(Input& input, Player& player, MapDraw& map) :
	input(input), player(player), map(map), margin(16),
	/*　メニュー */
	menuLength(256, 64),
	menuSize(WIN_WIDTH - menuLength.x - margin, margin),
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
	actionSize(BLOCK_SIZE * 8 + 16 - margin, WIN_HEIGHT - actionLength.y - margin) {

	changeFlag = false;
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
/// 描画処理
/// </summary>
void GameUI::draw() {
	drawBlur(); //ぼかし

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

	drawFilter();
}

void GameUI::update() {
	draw();
	text_.drawText();
}
