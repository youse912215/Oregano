#pragma once
#include "player.h"
#include "eventField.h"
#include <vector>
#include <string>

using namespace std;

class DataSave {
private:
	Player& player;
	EventField& field;

	vector<int> currentStatus; //���݂܂ł̃X�e�[�^�X�i�[�p
	vector<int> lastTimeStatus; //�O��܂ł̃X�e�[�^�X�i�[�p
	vector<int> currentCoin; //���݂܂ł̃R�C���i�[�p
	vector<int> lastTimeCoin; //�O��܂ł̃R�C���i�[�p

	string statusData; //�Z�[�u�f�[�^�̃o�C�i���t�@�C��
	string coinData; //�R�C���f�[�^�̃o�C�i���t�@�C��

	int getFileSize(string fileName);

	void writeBinaryFile(vector<int>& currentData, vector<int>& lastTimeData, string fileName);
	void roadBinaryFile(vector<int>& currentData, vector<int>& lastTimeData, string fileName);

	void getCurrentStatus();
	void getLastTimeStatus();

	void getCurrentCoin();
	void getLastTimeCoin();

public:
	DataSave(Player& player, EventField& field);
	~DataSave();


	void writeSaveData();
	void roadSaveData();


	void update();
};
