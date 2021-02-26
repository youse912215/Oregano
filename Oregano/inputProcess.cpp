#include "DxLib.h"
#include "eventBase.h"
#include "mapDraw.h"
#include "inputProcess.h"

char Input::oldkeys[256] = {0};
char Input::keys[256] = {0};

Input::Input() : padNum(14), buttonFlag(10) {
	A = false;
	B = false;
	X = false;
	Y = false;
	LB = false;
	RB = false;
	moveDirection = UP;
	mode = false;
}

/// <summary>
/// キーボード情報
/// </summary>
void Input::keyboardInformation() {
	// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
	for (unsigned int i = 0; i < 256; ++i) {
		oldkeys[i] = keys[i];
	}
	// 最新のキーボード情報を取得
	GetHitKeyStateAll(keys);
}

/// <summary>
/// ジョイパッド情報
/// </summary>
void Input::padsInformation() {
	oldPad = pad;
	pad = GetJoypadInputState(DX_INPUT_PAD1); //入力状態取得
	padNum[A_BUTTON] = mode && (pad & PAD_INPUT_1); //1(A)
	padNum[B_BUTTON] = mode && (pad & PAD_INPUT_2); //2(B)
	padNum[X_BUTTON] = mode && (pad & PAD_INPUT_3); //3(X)
	padNum[Y_BUTTON] = mode && (pad & PAD_INPUT_4); //4(Y)
	padNum[L_BUTTON] = mode && (pad & PAD_INPUT_5); //5(LB)
	padNum[R_BUTTON] = mode && (pad & PAD_INPUT_6); //6(RB)
	padNum[VIEW_BUTTON] = mode && (pad & PAD_INPUT_7); //7(MENU)
	padNum[MENU_BUTTON] = mode && (pad & PAD_INPUT_8); //8(MENU)

	padNum[STICK_LEFT] = mode && (pad & PAD_INPUT_LEFT); //左
	padNum[STICK_RIGHT] = mode && (pad & PAD_INPUT_RIGHT); //右
	padNum[STICK_UP] = mode && (pad & PAD_INPUT_UP); //上
	padNum[STICK_DOWN] = mode && (pad & PAD_INPUT_DOWN); //下
}

/// <summary>
/// キーボードとマウスパッドを切り替える
/// </summary>
void Input::inputModeChange() {
	if (keys[KEY_INPUT_TAB] && !oldkeys[KEY_INPUT_TAB]) mode = !mode ? true : false;
}

/// <summary>
/// スティック（十字キー）移動処理
/// </summary>
void Input::moveProcess(MapCollision& collision) {

	//左移動
	if (getInputButton(STICK_LEFT)) {
		MapDraw::mapX -= MOVING_DISTANCE;
		if (collision.leftCollisionFlag()) MapDraw::mapX += MOVING_DISTANCE;
		moveDirection = LEFT;
	}
	//右移動
	if (getInputButton(STICK_RIGHT)) {
		MapDraw::mapX += MOVING_DISTANCE;
		if (collision.rightCollisionFlag()) MapDraw::mapX -= MOVING_DISTANCE;
		moveDirection = RIGHT;
	}
	//上移動
	if (getInputButton(STICK_UP)) {
		MapDraw::mapY -= MOVING_DISTANCE;
		if (collision.upCollisionFlag()) MapDraw::mapY += MOVING_DISTANCE;
		moveDirection = UP;
	}
	//下移動
	if (getInputButton(STICK_DOWN)) {
		MapDraw::mapY += MOVING_DISTANCE;
		if (collision.downCollisionFlag()) MapDraw::mapY -= MOVING_DISTANCE;
		moveDirection = DOWN;
	}

	DrawFormatString(0, 150, GetColor(255, 255, 120), "%d   %d",
	                 collision.leftCollisionFlag(), collision.rightCollisionFlag(), false);
	DrawFormatString(0, 135, GetColor(255, 255, 120), "  %d",
	                 collision.upCollisionFlag(), false);
	DrawFormatString(0, 165, GetColor(255, 255, 120), "  %d",
	                 collision.downCollisionFlag(), false);

	DrawFormatString(0, 200, GetColor(255, 255, 120), "  %d",
	                 getInputButton(STICK_UP), false);
	DrawFormatString(0, 215, GetColor(255, 255, 120), "%d   %d",
	                 getInputButton(STICK_LEFT), getInputButton(STICK_RIGHT), false);
	DrawFormatString(0, 230, GetColor(255, 255, 120), "  %d",
	                 getInputButton(STICK_DOWN), false);


}

/// <summary>
/// ボタン入力処理
/// </summary>
void Input::eventProcess() {
	//キャンセル入力
	if (getInputButton(A_BUTTON)) A = true;
	else A = false;

	//入力
	if (getInputButton(B_BUTTON)) B = true;
	else B = false;

	//決定入力
	if (getInputButton(X_BUTTON)) X = true;
	else X = false;

	//入力
	if (getInputButton(Y_BUTTON)) Y = true;
	else Y = false;

	//入力
	if (getInputButton(L_BUTTON)) LB = true;
	else LB = false;

	//入力
	if (getInputButton(R_BUTTON)) RB = true;
	else RB = false;

	DrawFormatString(150, 150, GetColor(0, 255, 120), "%d   %d",
	                 X, B, false);
	DrawFormatString(150, 135, GetColor(0, 255, 120), "  %d",
	                 Y, false);
	DrawFormatString(150, 165, GetColor(0, 255, 120), "  %d",
	                 A, false);
	DrawFormatString(150, 180, GetColor(0, 255, 120), "%d   %d",
	                 LB, RB, false);
}

/// <summary>
/// 終了処理
/// </summary>
void Input::endProcess() {
	if (getInputButton(VIEW_BUTTON)) {
		EventBase::gameScene = END_SCENE;
	}
}

/// <summary>
/// 指定のボタン入力を返す
/// </summary>
/// <param name="buttonName">ボタン名</param>
bool Input::getInputButton(const int& buttonName) {
	switch (buttonName) {
	case A_BUTTON: //Aボタン
		return mode && padNum[A_BUTTON] && !oldPad || !mode && keys[KEY_INPUT_1] && !oldkeys[KEY_INPUT_1];
	case B_BUTTON: //Bボタン
		return mode && padNum[B_BUTTON] && !oldPad || !mode && keys[KEY_INPUT_2] && !oldkeys[KEY_INPUT_2];
	case X_BUTTON: //Xボタン
		return mode && padNum[X_BUTTON] && !oldPad || !mode && keys[KEY_INPUT_3] && !oldkeys[KEY_INPUT_3];
	case Y_BUTTON: //Yボタン
		return mode && padNum[Y_BUTTON] && !oldPad || !mode && keys[KEY_INPUT_4] && !oldkeys[KEY_INPUT_4];
	case L_BUTTON: //Lボタン
		return mode && padNum[L_BUTTON] && !oldPad || !mode && keys[KEY_INPUT_5] && !oldkeys[KEY_INPUT_5];
	case R_BUTTON: //Rボタン
		return mode && padNum[R_BUTTON] && !oldPad || !mode && keys[KEY_INPUT_6] && !oldkeys[KEY_INPUT_6];
	case VIEW_BUTTON: //VIEWボタン
		return mode && padNum[VIEW_BUTTON] && !oldPad || !mode && keys[KEY_INPUT_ESCAPE] && !oldkeys[KEY_INPUT_ESCAPE];
	case MENU_BUTTON: //MENUボタン
		return mode && padNum[MENU_BUTTON] && !oldPad || !mode && keys[KEY_INPUT_8] && !oldkeys[KEY_INPUT_8];
	case STICK_LEFT: //左スティック
		return mode && padNum[STICK_LEFT] || !mode && keys[KEY_INPUT_LEFT];
	case STICK_RIGHT: //右スティック
		return mode && padNum[STICK_RIGHT] || !mode && keys[KEY_INPUT_RIGHT];
	case STICK_UP: //上スティック
		return mode && padNum[STICK_UP] || !mode && keys[KEY_INPUT_UP];
	case STICK_DOWN: //下スティック
		return mode && padNum[STICK_DOWN] || !mode && keys[KEY_INPUT_DOWN];
	default: return false;
	}
}


/// <summary>
/// 更新処理
/// </summary>
void Input::update() {
	keyboardInformation(); //キーボード情報
	padsInformation(); //ジョイパッド情報
	inputModeChange(); //モードチェンジ
	eventProcess(); //イベント入力処理
	endProcess(); //終了入力処理
}
