#pragma once
#include "inputProcess.h"
#include "dataSource.h"
#include "vec2.h"

class SceneMenu : public DataSource {
private:
	Input& input; //入力クラス

	Vec2 devicePos; //デバイス文字位置
	Vec2 deviceSize; //デバイス文字サイズ

	const int maxTime; //最大時間
	const int changeTime; //切替時間
	int interval; //間隔時間

public:
	SceneMenu(Input& input);

	void update(); //更新処理
};
