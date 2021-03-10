#pragma once
#include "inputProcess.h"
#include "dataSource.h"

class SceneEnd : public DataSource {
private:
	Input& input; //入力クラス
	Vec2 startSize; //スタート文字サイズ
	Vec2 startPos; //スタート文字位置

	const int maxTime; //最大時間
	const int changeTime; //切替時間
	int interval; //間隔時間

public:
	bool endFlag; //終了フラグ

	SceneEnd(Input& input);

	void update(); //更新処理
};
