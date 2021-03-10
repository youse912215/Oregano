#pragma once
#include "inputProcess.h"
#include "dataSource.h"
#include "vec2.h"

class SceneTitle : public DataSource {
private:
	Input& input; //入力クラス

	Vec2 deviceSize; //デバイス文字サイズ
	Vec2 startSize; //スタート文字サイズ
	Vec2 startPos; //スタート文字位置

public:
	SceneTitle(Input& input);

	void update(); //更新処理
};
