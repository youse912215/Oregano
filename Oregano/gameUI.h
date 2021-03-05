#pragma once
#include "vec2.h"
#include "inputProcess.h"
#include "dataSource.h"
#include "mapDraw.h"
//#include "player.h"

class GameUI : public DataSource {
private:
	Input& input; //入力クラス
	MapDraw& map; //マップ描画クラス
	DataSource source; //ソースクラス

	Vec2 pos; //UI位置
	int graphPos; //画像位置

	void drawblur(); //ぼかしの描画
	void draw(); //描画処理

public:
	bool changeFlag;

	GameUI(Input& input, MapDraw& map);
	~GameUI();


	void update(); //更新処理
};
