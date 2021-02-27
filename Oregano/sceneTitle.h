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
	SceneTitle(DataSave& save);
	~SceneTitle();

	void titleProcess(); //タイトル処理
	vector<vector<vector<int>>>& returnMapAll(); //タイトル画面でロードしたマップ三次元配列を返す
};
