#pragma once
#include "dataSave.h"
#include "inputProcess.h"
#include "dataSource.h"
#include "sceneGame.h"

class SceneGameOver {
private:
	DataSave& data; //セーブデータクラス
	Input& input; //入力クラス
	SceneGame& game; //ゲームクラス
	DataSource source; //データソースクラス

	Vec2 charSize; //文字サイズ
	Vec2 charPos; //文字位置
	const int charInterval; //文字間隔

public:
	bool endFlag; //終了フラグ

	SceneGameOver(DataSave& data, Input& input, SceneGame& game);

	void update(); //更新処理
};
