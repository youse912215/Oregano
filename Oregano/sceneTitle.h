#pragma once
#include "dataSave.h"
#include "mapLoad.h"
#include <vector>

using namespace std;

class SceneTitle {
private:
	DataSave& save; //データセーブクラスから
	//MapLoad& load; //マップロードクラスから
public:
	static int gameScene;

	SceneTitle(DataSave& save);
	~SceneTitle();

	void update(); //タイトル処理
	vector<vector<vector<int>>>& roadingMap(); //タイトル画面でロードしたマップ三次元配列を返す
};
