#pragma once
#include "playerState.h"
#include "player.h"
#include <vector>
#include <string>

using namespace std;

class DataSave {
private:
	PlayerState& player;

	vector<int> currentStatus; //���݂܂ł̃X�e�[�^�X�i�[�p
	vector<int> lastTimeStatus; //�O��܂ł̃X�e�[�^�X�i�[�p
	string statusData; //�Z�[�u�f�[�^�̃o�C�i���t�@�C��

	int getFileSize(string fileName);

	void writeBinaryFile(vector<int>& currentData, vector<int>& lastTimeData, string fileName);
	void roadBinaryFile(vector<int>& currentData, vector<int>& lastTimeData, string fileName);

	void getCurrentStatus();
	void getLastTimeStatus();

	void getCurrentEvent(vector<int>& currentEvent, vector<int>& saveLocation);
	void getLastTimeEvent(vector<int>& lastTimeEvent, vector<int>& saveLocation);

public:
	DataSave(PlayerState& player);
	~DataSave();

	vector<int> roadItemText;
	vector<int> OutputItemText;

	void writeSaveData();
	void roadSaveData();


	void update();
};
