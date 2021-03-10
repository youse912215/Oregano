#pragma once
#include "vec2.h"
#include "inputProcess.h"
#include "dataSource.h"
#include "mapDraw.h"
#include "player.h"
#include <vector>

class GameUI {
private:
	Input& input; //入力クラス
	Player& player;
	MapDraw& map; //マップ描画クラス
	DataSource& source; //ソースクラス

	const int margin; //余白サイズ
	const int eventSize; //イベント数
	const int eventLength; //1イベントあたりの情報サイズ長

	Vec2 menuLength; //メニュー長
	Vec2 menuSize; //メニューサイズ
	Vec2 passiveLength; //パッシブ長
	Vec2 passiveSize; //パッシブサイズ
	Vec2 conditionSize; //状態異常サイズ
	Vec2 actionLength; //アクション長
	Vec2 actionSize; //アクションサイズ
	Vec2 speechBalloonLength; //噴き出し長
	Vec2 speechBalloonPos; //噴き出し位置

	bool positionMatchDecision(const int& i); //プレイヤーとイベント位置の一致条件

	void drawBlur(); //ぼかしの描画
	void drawFilter(); //UIのフィルタの描画
	void drawSpeechBalloon(); //イベント用噴き出しの描画
	void draw(); //描画処理

public:
	vector<int> mapEventPos; //イベント座標

	int eventNum; //セーブフラグ

	GameUI(Input& input, Player& player, MapDraw& map, DataSource& source);
	~GameUI();


	void update(); //更新処理
};
