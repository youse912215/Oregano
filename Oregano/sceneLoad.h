#pragma once
#include "dataSave.h"
#include "mapLoad.h"
#include <vector>

using namespace std;

class SceneLoad {
private:
	DataSave& save; //データセーブクラスから

public:
	static int gameScene; //ゲームシーン

	SceneLoad(DataSave& save);
	~SceneLoad();

	void update(); //タイトル処理
	vector<vector<vector<int>>>& roadingMap(); //タイトル画面でロードしたマップ三次元配列を返す
};
