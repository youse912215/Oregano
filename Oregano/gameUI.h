#pragma once
#include "vec2.h"
#include "inputProcess.h"
#include "dataSource.h"
#include "mapDraw.h"
#include "player.h"
#include <vector>

class GameUI : public DataSource {
private:
	Input& input; //入力クラス
	Player& player;
	MapDraw& map; //マップ描画クラス
	DataSource source; //ソースクラス

	const int margin; //余白サイズ

	Vec2 menuLength; //メニュー長
	Vec2 menuSize; //メニューサイズ
	Vec2 passiveSize; //パッシブサイズ
	Vec2 conditionSize; //状態異常サイズ
	Vec2 modeLeftSize; //Lモードサイズ
	Vec2 modeLength; //モード長
	Vec2 modeRightSize; //Rモードサイズ
	Vec2 actionLength; //アクション長
	Vec2 actionSize; //アクションサイズ

	bool changeFlag; //切替フラグ

	void drawBlur(); //ぼかしの描画
	void drawFilter(); //UIのフィルタの描画
	void draw(); //描画処理

public:
	vector<int> mapEventPos;

	GameUI(Input& input, Player& player, MapDraw& map);
	~GameUI();


	void update(); //更新処理
};
