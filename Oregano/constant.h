#pragma once

const int WIN_MAGNIFICATION = 100; //ウインドウ倍率
const int WIN_WIDTH = 16 * WIN_MAGNIFICATION; //ウィンドウ横幅
const int WIN_HEIGHT = 9 * WIN_MAGNIFICATION; //ウィンドウ縦幅

const int BLOCK_SIZE = 64; //ブロックサイズ
const int AREA_WIDTH = 25; //1マップ（区画）の横のサイズ
const int AREA_HEIGHT = 25; //1マップ（区画）の縦のサイズ
const int AREA_MIN = 0;
const int AREA_MAX = AREA_WIDTH - 1;

const int DIRECTION_SIZE = 4; //方向の種類（配列のサイズ）

const int MOVING_DISTANCE = 8; //移動速度

const int INITIAL_X = 13600; //初期マップのx座標
const int INITIAL_Y = 13200 + BLOCK_SIZE; //初期マップのy座標

//方向の情報
enum direction {
	LEFT,
	//左　
	RIGHT,
	//右
	UP,
	//上
	DOWN,
	//下
	CENTER_X1,
	CENTER_X2,
	CENTER_Y1,
	CENTER_Y2,
	//中央
	CROSS,
	//特殊
};

enum corner {
	LEFT_UP,
	RIGHT_UP,
	LEFT_DOWN,
	RIGHT_DOWN,
	CENTER_LEFT1,
	CENTER_RIGHT1,
	CENTER_UP1,
	CENTER_DOWN1,
	CENTER_LEFT2,
	CENTER_RIGHT2,
	CENTER_UP2,
	CENTER_DOWN2,
};

enum dirction_sign {
	Left = -1,
	Right = 1,
	Top = -1,
	Central = 0,
	Bottom = 1,
};

//--- マップチップ名称 ---//
enum map_info {
	//床
	FLOOR,
	//家
	HOUSE,
	//浅瀬
	SHALLOW,
	//潮
	TIDE,
	//水辺
	WATER = 21,
	//岩山
	STONE = 31,
	//木々
	WOODS = 41,
	//縦橋
	BRIDGE_HEIGHT = 101,
	//横橋
	BRIDGE_WIDTH = 102
};
