#pragma once
#include <vector>

using namespace std;

class MapLoad {
private:
	vector<vector<int>> vecMap; //�ǂݍ��񂾃}�b�v�f�[�^�z����i�[

public:
	vector<vector<vector<int>>> mapAll; //�S�Ẵ}�b�v�f�[�^���i�[

	MapLoad();
	~MapLoad();

	void roadMapData(); //�}�b�v�f�[�^�z���ǂݍ��݁A�O�����z��Ɋi�[
};
