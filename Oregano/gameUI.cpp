#include "gameUI.h"
#include "DxLib.h"
#include "constant.h"

GameUI::GameUI(Input& input) : input(input) {
	pos.x = WIN_WIDTH - BLOCK_SIZE * 2;
	pos.y = WIN_HEIGHT - BLOCK_SIZE * 2;
	graphPos = 0;
	changeFlag = false;
}

GameUI::~GameUI() {
}

void GameUI::draw() {
	DrawRectGraph(pos.x, pos.y, graphPos, 0,
	              BLOCK_SIZE, BLOCK_SIZE, actionUI, true, false);
}

void GameUI::actionModeChange() {
	if (input.B) {
		changeFlag = !changeFlag ? true : false;
	}

	if (input.LB && graphPos != 0 && changeFlag) graphPos -= BLOCK_SIZE;

	if (input.RB && graphPos != BLOCK_SIZE * 2 && changeFlag) graphPos += BLOCK_SIZE;
}

void GameUI::update() {
	actionModeChange();
	//stopIntervalTime();
	draw();

	DrawFormatString(pos.x - BLOCK_SIZE, pos.y + BLOCK_SIZE, GetColor(255, 0, 0), "TF:%d, mode:%d",
	                 changeFlag, graphPos, false);
}
