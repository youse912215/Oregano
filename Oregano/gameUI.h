#pragma once
#include "vec2.h"
#include "inputProcess.h"
#include "dataSource.h"

class GameUI : public DataSource {
private:
	Input& input; //入力クラスから

	Vec2 pos; //UI位置
	int graphPos; //画像位置

	void draw(); //描画処理
	void actionModeChange(); //アクションモードの変更

public:
	bool changeFlag;

	GameUI(Input& input); //コンストラクタ
	~GameUI(); //デスクトラクタ

	void update(); //更新処理
};
