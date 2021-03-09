#include "DxLib.h"
#include "constant.h"
#include "mapDraw.h"
#include "inputProcess.h"
#include "sceneLoad.h"

char Input::oldkeys[KEY_BUFFER_MAX] = {0};
char Input::keys[KEY_BUFFER_MAX] = {0};

Input::Input() :
	/* ボタン情報関係 */
	mode(false), padNum(14), oldPadNum(14),
	/* 入力情報数 */
	buttonFlag(10), stickFlag(4),
	/* 初期は正面向き */
	moveDirection(DOWN) {
	A = false;
	B = false;
	X = false;
	Y = false;
	LB = false;
	RB = false;
	VIEW = false;
	MENU = false;
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
	oldPad = pad; //前の入力情報を取得
	pad = GetJoypadInputState(DX_INPUT_PAD1); //入力状態取得

	/* 入力情報 */
	padNum[A_BUTTON] = pad & PAD_INPUT_1; //1(A)
	padNum[B_BUTTON] = pad & PAD_INPUT_2; //2(B)
	padNum[X_BUTTON] = pad & PAD_INPUT_3; //3(X)
	padNum[Y_BUTTON] = pad & PAD_INPUT_4; //4(Y)
	padNum[L_BUTTON] = pad & PAD_INPUT_5; //5(LB)
	padNum[R_BUTTON] = pad & PAD_INPUT_6; //6(RB)
	padNum[VIEW_BUTTON] = pad & PAD_INPUT_7; //7(MENU)
	padNum[MENU_BUTTON] = pad & PAD_INPUT_8; //8(MENU)

	padNum[STICK_LEFT] = mode && (pad & PAD_INPUT_LEFT); //左
	padNum[STICK_RIGHT] = mode && (pad & PAD_INPUT_RIGHT); //右
	padNum[STICK_UP] = mode && (pad & PAD_INPUT_UP); //上
	padNum[STICK_DOWN] = mode && (pad & PAD_INPUT_DOWN); //下

	/* 前の入力情報 */
	oldPadNum[A_BUTTON] = oldPad & PAD_INPUT_1; //1(A)
	oldPadNum[B_BUTTON] = oldPad & PAD_INPUT_2; //2(B)
	oldPadNum[X_BUTTON] = oldPad & PAD_INPUT_3; //3(X)
	oldPadNum[Y_BUTTON] = oldPad & PAD_INPUT_4; //4(Y)
	oldPadNum[L_BUTTON] = oldPad & PAD_INPUT_5; //5(LB)
	oldPadNum[R_BUTTON] = oldPad & PAD_INPUT_6; //6(RB)
	oldPadNum[VIEW_BUTTON] = oldPad & PAD_INPUT_7; //7(MENU)
	oldPadNum[MENU_BUTTON] = oldPad & PAD_INPUT_8; //8(MENU)
}

/// <summary>
/// キーボードとマウスパッドを切り替える
/// </summary>
void Input::inputModeChange() {
	if (keys[KEY_INPUT_Q] && !oldkeys[KEY_INPUT_Q]) mode = !mode ? true : false;
}

/// <summary>
/// スティック（十字キー）移動処理
/// </summary>
void Input::movement(MapCollision& collision, MapDraw& draw) {

	//左移動
	if (getInputButton(STICK_LEFT)) {
		move_.left(collision, draw); //衝突判定など
		directionProcess(move_.changeDirection(LEFT)); //方向処理
	}
	else stickFlag[move_.changeDirection(LEFT)] = false; //スティック状態をfalse
	//右移動
	if (getInputButton(STICK_RIGHT)) {
		move_.right(collision, draw); //衝突判定など
		directionProcess(move_.changeDirection(RIGHT)); //方向処理
	}
	else stickFlag[move_.changeDirection(RIGHT)] = false; //スティック状態をfalse
	//上移動
	if (getInputButton(STICK_UP)) {
		move_.up(collision, draw); //衝突判定など
		directionProcess(move_.changeDirection(UP)); //方向処理
	}
	else stickFlag[move_.changeDirection(UP)] = false; //スティック状態をfalse
	//下移動
	if (getInputButton(STICK_DOWN)) {
		move_.down(collision, draw); //衝突判定など
		directionProcess(move_.changeDirection(DOWN)); //方向処理
	}
	else stickFlag[move_.changeDirection(DOWN)] = false; //スティック状態をfalse
}

/// <summary>
/// 方向処理
/// </summary>
/// <param name="dir">移動方向</param>
void Input::directionProcess(const int& dir) {
	moveDirection = dir; //移動方向をdirにする
	stickFlag[dir] = true; //スティックの方向dirをtrue
}

/// <summary>
/// いずれかのスティックが押されているかを返す
/// </summary>
bool Input::anySTICK() {
	return stickFlag[LEFT] || stickFlag[RIGHT] || stickFlag[UP] || stickFlag[DOWN];
}

/// <summary>
/// ボタン入力処理
/// </summary>
void Input::eventProcess() {
	//A入力
	if (getInputButton(A_BUTTON)) A = true;
	else A = false;

	//B入力
	if (getInputButton(B_BUTTON)) B = true;
	else B = false;

	//X入力
	if (getInputButton(X_BUTTON)) X = true;
	else X = false;

	//Y入力
	if (getInputButton(Y_BUTTON)) Y = true;
	else Y = false;

	//L入力
	if (getInputButton(L_BUTTON)) LB = true;
	else LB = false;

	//R入力
	if (getInputButton(R_BUTTON)) RB = true;
	else RB = false;

	//VIEW入力
	if (getInputButton(VIEW_BUTTON)) VIEW = true;
	else VIEW = false;

	//MENU入力
	if (getInputButton(MENU_BUTTON)) MENU = true;
	else MENU = false;
}

/// <summary>
/// メニュー処理
/// </summary>
void Input::menuProcess() {
	if (MENU) {
		SceneLoad::gameScene = MENU_SCENE;
	}
}

/// <summary>
/// 指定のボタン入力を返す
/// </summary>
/// <param name="buttonName">ボタン名</param>
bool Input::getInputButton(const int& buttonName) {
	switch (buttonName) {
	case A_BUTTON: //Aボタン
		return mode && padNum[A_BUTTON] && !oldPadNum[A_BUTTON]
			|| !mode && keys[KEY_INPUT_1] && !oldkeys[KEY_INPUT_1];
	case B_BUTTON: //Bボタン
		return mode && padNum[B_BUTTON] && !oldPadNum[B_BUTTON]
			|| !mode && keys[KEY_INPUT_2] && !oldkeys[KEY_INPUT_2];
	case X_BUTTON: //Xボタン
		return mode && padNum[X_BUTTON] && !oldPadNum[X_BUTTON]
			|| !mode && keys[KEY_INPUT_3] && !oldkeys[KEY_INPUT_3];
	case Y_BUTTON: //Yボタン
		return mode && padNum[Y_BUTTON] && !oldPadNum[Y_BUTTON]
			|| !mode && keys[KEY_INPUT_4] && !oldkeys[KEY_INPUT_4];
	case L_BUTTON: //Lボタン
		return mode && padNum[L_BUTTON] && !oldPadNum[L_BUTTON]
			|| !mode && keys[KEY_INPUT_5] && !oldkeys[KEY_INPUT_5];
	case R_BUTTON: //Rボタン
		return mode && padNum[R_BUTTON] && !oldPadNum[R_BUTTON]
			|| !mode && keys[KEY_INPUT_6] && !oldkeys[KEY_INPUT_6];
	case VIEW_BUTTON: //VIEWボタン
		return mode && padNum[VIEW_BUTTON] && !oldPadNum[VIEW_BUTTON]
			|| !mode && keys[KEY_INPUT_TAB] && !oldkeys[KEY_INPUT_TAB];
	case MENU_BUTTON: //MENUボタン
		return mode && padNum[MENU_BUTTON] && !oldPadNum[MENU_BUTTON]
			|| !mode && keys[KEY_INPUT_ESCAPE] && !oldkeys[KEY_INPUT_ESCAPE];
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
}
