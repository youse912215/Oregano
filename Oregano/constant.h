#pragma once

const int WIN_MAGNIFICATION = 100; //ウインドウ倍率
const int WIN_WIDTH = 16 * WIN_MAGNIFICATION; //ウィンドウ横幅
const int WIN_HEIGHT = 9 * WIN_MAGNIFICATION; //ウィンドウ縦幅

const int BLOCK_SIZE = 64; //ブロックサイズ
const int AREA_WIDTH = 25; //1マップ（区画）の横のサイズ
const int AREA_HEIGHT = 25; //1マップ（区画）の縦のサイズ
const int AREA_MIN = 0;
const int AREA_MAX = AREA_WIDTH - 1;

const int HALF_MAP_X = BLOCK_SIZE * AREA_WIDTH / 2;
const int HALF_MAP_Y = BLOCK_SIZE * AREA_HEIGHT / 2;

const int DIRECTION_SIZE = 4; //方向の種類（配列のサイズ）

const int MOVING_DISTANCE = 8; //移動速度

const int INITIAL_X = /*13600*/BLOCK_SIZE * AREA_WIDTH * 8 + HALF_MAP_X; //初期マップのx座標
const int INITIAL_Y = /*13200 + BLOCK_SIZE*/BLOCK_SIZE * AREA_HEIGHT * 8 + HALF_MAP_Y / 2 + BLOCK_SIZE; //初期マップのy座標

const int MOVE_RANGE = 1000; //移動範囲（この数字のマップチップまで移動可能）

const int GAME_HOUR = 1200; //1時間あたりのgameTime

const int PLAYER_STATUS_SIZE = 21; //プレイヤーステータス(距離以外)のサイズ
const int PLAYER_ITEM_SIZE = 160; //プレイヤーのアイテムサイズ
const int PLAYER_ACCESSORY_SIZE = 80; //プレイヤーのアクセサリーサイズ
const int PLAYER_JEWEL_SIZE = 32; //プレイヤーのジュエルサイズ
const int PLAYER_MINERAL_SIZE = 8; //プレイヤーの鉱物サイズ

const int STATUS_INFORMATION_SIZE = PLAYER_STATUS_SIZE + 2; //ステータスのサイズ
const int COIN_INFORMATION_SIZE = 4312; //コイン情報のサイズ
const int ITEM_INFORMATION_SIZE = 2120; //アイテム情報のサイズ
const int ACCESSORY_INFORMATION_SIZE = 128; //アクセサリー情報のサイズ
const int JEWEL_INFORMATION_SIZE = 72; //ジュエル情報のサイズ
const int MINERAL_INFORMATION_SIZE = 128; //鉱物情報のサイズ 
const int EVENT_INFORMATION_SIZE = 8; //1イベントあたりの情報のサイズ

const int COIN_EVENT_SIZE = 250; //コインイベントのサイズ
const int ITEM_EVENT_SIZE = 120; //アイテムイベントのサイズ
const int ACCESSORY_EVENT_SIZE = 20; //アクセサリーイベントのサイズ
const int JEWEL_EVENT_SIZE = 5; //ジュエルイベントのサイズ
const int MINERAL_EVENT_SIZE = 20; //鉱物イベントのサイズ

const int ALL_COIN_TYPE = 4; //コインの種類

const int TERMINAL_CHAR = 1;

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
	ROAD_SCENE,
	GAME_SCENE,
	MENU_ITEM_SCENE,
	MENU_STATUS_SCENE,
	MENU_EQUIPMENT_SCENE,
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
	////床
	//FLOOR,
	////縦橋
	//BRIDGE_HEIGHT = 4,
	////横橋
	//BRIDGE_WIDTH = 6,
	////草花
	//FLOWER = 8,
	////キノコ類
	//MUSHROOM,
	////浜
	//BEACH,
	////浅瀬
	//SHALLOW = 20,
	////潮
	//TIDE = 30,
	////クリスタル
	//CRYSTAL = 40,
	////木々
	//WOODS = 90,
	////家
	//HOUSE = 119,
	////海
	//WATER = 120,
	////岩山
	//STONE = 160,
	////鉱石系
	//MINERAL = 190,
	////宝箱
	//TREASURE_BOX = 199,
	//横橋
	BRIDGE_WIDTH,
	//縦橋
	BRIDGE_HEIGHT,
	//床（通常道）
	FLOOR,
	//花類
	FLOWER,
	//キノコ類
	MUSHROOM,
	//浜
	BEACH,
	//浅瀬
	SHALLOW,
	//潮
	TIDE,
	//毒沼
	POISON,
	//氷床
	ICE,
	//ランダムマップ(森)
	RANDOM_MAP1,
	//海
	SEA,
	//木々
	WOODS,
	//溶岩
	LAVA,
	//枯れた木々
	WITHERED_WOODS,
	//凍った木々
	FROZEN_WOODS,
	//氷山
	ICE_MOUNTAIN,
	//岩山
	STONE_MOUNTAIN,
	//鉱物
	MINERAL,
	//宝箱
	TREASURE_BOX,
	//ランダムマップ2(沼地)
	RANDOM_MAP2,
	//ランダムマップ3(火山)
	RANDOM_MAP3,
	//ランダムマップ4(氷山)
	RANDOM_MAP4,
};

//ボタン種類
enum BUTTON {
	A_BUTTON,
	B_BUTTON,
	X_BUTTON,
	Y_BUTTON,
	L_BUTTON,
	R_BUTTON,
	VIEW_BUTTON,
	MENU_BUTTON,
	STICK_L_BUTTON,
	STICK_R_BUTTON,
	STICK_LEFT,
	STICK_RIGHT,
	STICK_UP,
	STICK_DOWN
};

enum POSITION_INFORMATION {
	MAP_X,
	MAP_Y,
};

enum STATUS {
	//トレジャーランク
	TREASURE_RANK,
	//花萌葱のコイン
	GREEN_COIN,
	//金糸雀のコイン
	YELLOW_COIN,
	//葡萄染のコイン
	PURPLE_COIN,
	//白百合のコイン
	WHITE_COIN,
	//生命力
	CURRENT_LIFE,
	//最大生命力
	MAX_LIFE,
	//攻撃力
	ATTACK,
	//猛毒耐性
	DEADLY_POISON_RESISTANCE,
	//猛毒属性値
	DEADLY_POISON_VALUE,
	//猛毒蓄積
	DEADLY_POISON_ACCUMULATION,
	//麻痺耐性
	PARALYSIS_RESISTANCE,
	//麻痺属性値
	PARALYSIS_VALUE,
	//麻痺蓄積
	PARALYSIS_ACCUMULATION,
	//催眠耐性
	HYPNOSIS_RESISTANCE,
	//催眠耐性
	HYPNOSIS_VALUE,
	//催眠蓄積
	HYPNOSIS_ACCUMULATION,
	//出血耐性
	BLOODING_RESISTANCE,
	//出血属性値
	BLOODING_VALUE,
	//出血蓄積
	BLOODING_ACCUMULATION,
	//交渉力
	BARGAINING_POWER,
	//現在のマップ座標
	CURRENT_MAP_X,
	CURRENT_MAP_Y,
};

enum ITEM_INFORMATION {
	MAP_X_,
	MAP_Y_,
	CURRENT_X_,
	CURRENT_Y_,
	DIRECTION_,
	EVENT_NO_,
	ITEM_TYPE_,
};
