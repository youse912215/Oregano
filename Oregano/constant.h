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

const int MOVE_RANGE = 160;

#define CALL_ONCE(src)\
     do {\
          static bool initialized = false;\
          if (!initialized){\
               src;\
               initialized = true;\
          }\
     } while (0)

//ゲームシーン
enum GAME_SCENE {
	TITLE_SCENE,
	GAME_SCENE,
	MENU_SCENE,
	END_SCENE,
};

//方向の情報
enum DIRECTION_INFORMATION {
	//左
	LEFT,
	//右
	RIGHT,
	//上
	UP,
	//下
	DOWN,
	//中央左
	CENTER_X1,
	//中央右
	CENTER_X2,
	//中央上
	CENTER_Y1,
	//中央下
	CENTER_Y2,
	//交差
	CROSS,
};

enum CORNER_INFORMATION {
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

enum DIRECTION_MAP {
	MAP_TOP_LEFT,
	MAP_TOP_CENTRAL,
	MAP_TOP_RIGHT,
	MAP_LEFT_CENTRAL,
	MAP_CENTRAL,
	MAP_RIGHT_CENTRAL,
	MAP_BOTTOM_LEFT,
	MAP_BOTTOM_CENTRAL,
	MAP_BOTTOM_RIGHT
};

enum DIRECTION_SIGN {
	Left = -1,
	Right = 1,
	Top = -1,
	Central = 0,
	Bottom = 1,
};

//マップチップ名称
enum MAP_INFORMATION {
	//床
	FLOOR,
	//縦橋
	BRIDGE_HEIGHT = 4,
	//横橋
	BRIDGE_WIDTH = 6,
	//草花
	FLOWER = 8,
	//キノコ類
	MUSHROOM,
	//浜
	BEACH,
	//浅瀬
	SHALLOW = 20,
	//潮
	TIDE = 30,
	//クリスタル
	CRYSTAL = 40,
	//木々
	WOODS = 90,
	//家
	HOUSE = 119,
	//海
	WATER = 120,
	//岩山
	STONE = 160,
	//鉱石系
	MINERAL = 190,
	//宝箱
	TREASURE_BOX = 300,
};

//ボタン種類
enum BUTTON {
	A,
	B,
	X,
	Y,
	LB,
	RB,
	VIEW,
	MENU,
	STICK_L,
	STICK_R
};

enum POSITION_INFORMATION {
	MAP_X,
	MAP_Y,
};

enum STATUS {
	//トレジャーランク
	TREASURE_RANK,
	//生命力
	LIFE,
	//攻撃力
	ATTACK,
	//守備力
	DEFENSE,
	//猛毒耐性
	DEADLY_POISON_RESISTANCE,
	//猛毒属性値
	DEADLY_POISON_VALUE,
	//麻痺耐性
	PARALYSIS_RESISTANCE,
	//麻痺属性値
	PARALYSIS_VALUE,
	//催眠耐性
	HYPNOSIS_RESISTANCE,
	//催眠耐性
	HYPNOSIS_VALUE,
	//優先度
	BLOODING_RESISTANCE,
	BLOODING_VALUE,
	PRIORITY,
	//現在のマップ座標
	CURRENT_MAP_X,
	CURRENT_MAP_Y,
};
