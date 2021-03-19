#pragma once
#include "dataSave.h"
#include "mapAutogeneration.h"
#include <vector>

using namespace std;

class SceneLoad {
private:
	DataSave& save; //データセーブクラスから
	MapAutoGeneration& mapAuto;

public:
	static int gameScene; //ゲームシーン

	SceneLoad(DataSave& save, MapAutoGeneration& mapAuto);
	~SceneLoad();

	void update(); //タイトル処理
	vector<vector<vector<int>>>& roadingMap(); //タイトル画面でロードしたマップ三次元配列を返す
};
