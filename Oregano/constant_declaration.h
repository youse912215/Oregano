#pragma once

const int WINDOW_WIDTH = 1600; //ウィンドウ横幅
const int WINDOW_HEIGHT = 900; //ウィンドウ縦幅
const int WIN_WIDTH = 800; //ウィンドウ横幅
const int WIN_HEIGHT = 450; //ウィンドウ縦幅
const int block_size = 32; //ブロックサイズ
const int area_width = 25; //1マップ（区画）の横のサイズ
const int area_height = 25; //1マップ（区画）の縦のサイズ
const int direction_size = 4; //方向の種類（配列のサイズ）
const int moving_speed = 10; //移動速度
const int initial_map_x = 6800; //初期マップのx座標
const int initial_map_y = 6625; //初期マップのy座標

//方向の情報
enum direction {
	LEFT,
	//左　
	RIGHT,
	//右
	UP,
	//上
	DOWN
	//下
};

enum dirction_sign {
	Left = -1,
	Right = 1,
	Top = -1,
	Central = 0,
	Bottom = 1,
};
