#pragma once

const int WIN_MAGNIFICATION = 100; //ウインドウ倍率
const int WIN_WIDTH = 16 * WIN_MAGNIFICATION; //ウィンドウ横幅
const int WIN_HEIGHT = 9 * WIN_MAGNIFICATION; //ウィンドウ縦幅
const int HALF_WIN_WIDTH = WIN_WIDTH / 2; //ウィンドウ横幅の半分
const int HALF_WIN_HEIGHT = WIN_HEIGHT / 2; //ウィンドウ縦幅の半分

const int BLOCK_SIZE = 64; //ブロックサイズ（int型）
const int HALF_BLOCK_SIZE = 32; //ブロックサイズの1/2（int型）
const int QUARTER_BLOCK_SIZE = 16; //ブロックサイズの1/2（int型）

const int AREA_WIDTH = 25; //1マップ区画の横のサイズ
const int AREA_HEIGHT = 25; //1マップ区画の縦のサイズ
const int AREA_MIN = 0; //区画の最小値
const int AREA_MAX = AREA_WIDTH - 1; //区画の最大値

const double HALF_BLOCK_SIZE_D = 32.0; //ブロックサイズの1/2（double型）
const double QUARTER_BLOCK_SIZE_D = HALF_BLOCK_SIZE_D / 2.0; //ブロックサイズの1/4（double型）

const double ENEMY_COLLISION_DISTANCE = 48.0; //敵との衝突距離
const double WEAPON_COLLISION_DISTANCE = HALF_BLOCK_SIZE_D; //敵と武器との衝突距離

const int TOTAL_MAPS_X = 5; //横方向のマップ総数
const int TOTAL_MAPS_Y = 5; //縦方向のマップ総数

const int ONE_MAP_X = BLOCK_SIZE * AREA_WIDTH; //1マップの横幅
const int ONE_MAP_Y = BLOCK_SIZE * AREA_HEIGHT; //1マップの縦幅

const int HALF_MAP_X = ONE_MAP_X / 2; //1マップの半分サイズ
const int HALF_MAP_Y = ONE_MAP_Y / 2; //1マップの半分サイズ

const int KEY_BUFFER_MAX = 256; //キーのバッファの最大

const int DIRECTION_SIZE = 4; //方向の種類（配列のサイズ）

const int MOVING_DISTANCE = 8; //移動距離
const double KNIFE_SPEED = 16.0; //ナイフ速度

const int INITIAL_X = ONE_MAP_X * (TOTAL_MAPS_X - 1) + HALF_MAP_X; //初期マップのx座標
const int INITIAL_Y = ONE_MAP_Y * (TOTAL_MAPS_Y - 1) + HALF_MAP_Y / 2 + BLOCK_SIZE; //初期マップのy座標

const int MOVE_RANGE = 1000; //移動範囲（この数字のマップチップまで移動可能）

const int GAME_HOUR = 1200; //1時間あたりのgameTime

const int PLAYER_STATUS_SIZE = 9; //プレイヤーステータス(距離以外)のサイズ
const int STATUS_INFORMATION_SIZE = PLAYER_STATUS_SIZE + 2; //ステータスのサイズ
const int MAP_EVENT_SIZE = 36; //マップイベント格納サイズ

const int ALL_COIN_TYPE = 4; //コインの種類

const int TERMINAL_CHAR = 1;

//一度のみ呼び出し
#define CALL_ONCE(/*src*/function)\
     do {\
          static bool initialized = false;\
          if (!initialized){\
               /*src*/function;\
               initialized = true;\
          }\
     } while (0)

//ゲームシーン
enum GAME_SCENE {
	//タイトル
	TITLE_SCENE,
	//ロード
	ROAD_SCENE,
	//ゲーム
	GAME_SCENE,
	SAVE_SCENE,
	MENU_SCENE,
	GAME_OVER_SCENE,
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

//衝突判定を行う角部分の情報
enum CORNER_INFORMATION {
	//左上
	LEFT_UP,
	//右上
	RIGHT_UP,
	//左下
	LEFT_DOWN,
	//右下
	RIGHT_DOWN,
	//中央左1
	CENTER_LEFT1,
	//中央右1
	CENTER_RIGHT1,
	//中央上1
	CENTER_UP1,
	//中央下1
	CENTER_DOWN1,
	//中央左2
	CENTER_LEFT2,
	//中央右2
	CENTER_RIGHT2,
	//中央上2
	CENTER_UP2,
	//中央下2
	CENTER_DOWN2,
};

//全ての方向（9方向）
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

//向きを符号とする
enum DIRECTION_SIGN {
	Left = -1,
	Right = 1,
	Top = -1,
	Central = 0,
	Bottom = 1,
};

//マップチップ名称
enum MAP_INFORMATION {
	//花床
	FLOOR_FLOWER,
	//宝箱の床
	FLOOR_TREASURE,
	//床（通常道）
	FLOOR_NORMAL,
	//花1
	FLOWER1,
	//花2
	FLOWER2,
	//でこぼこ
	ROUGH,
	//浅瀬
	SHALLOW,
	//水沼
	SWAMP,
	//毒沼
	POISON,
	//氷床
	ICE,
	//ランダムマップ(森)
	RANDOM_MAP1,
	//ランダムマップ2(沼地)
	RANDOM_MAP2,
	//壁
	WALL,
	//外海
	SEA,
	//宝箱
	TREASURE_BOX,
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
	POSITION_X,
	POSITION_Y,
};

//アクションコマンド
enum ACTION_COMMAND {
	//投げナイフ
	KNIFE,
	//刃
	SLASH,
	//シールド
	SHIELD,
	//状態解消
	RECOVERY,
};

//状態異常
enum STATE_ABNORMAL {
	//猛毒
	DEADLY_POISON,
	//痙攣
	CRAMPS,
	//混乱
	CONFUSION,
	//出血
	BLOODING
};
