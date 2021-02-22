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
	string statusData; //�Z�[�u�f�[�^�̃o�C�i���t�@�C��

	vector<int> currentPossession; //���݂܂ł̏����i�i�[�p
	vector<int> lastTimePossession; //�O��܂ł̏����i�i�[�p
	string possessionData; //�����i�f�[�^�̃o�C�i���t�@�C��

	vector<int> currentCoin; //���݂܂ł̃R�C���i�[�p
	vector<int> lastTimeCoin; //�O��܂ł̃R�C���i�[�p
	string coinData; //�R�C���f�[�^�̃o�C�i���t�@�C��

	vector<int> currentItem; //���݂܂ł̃A�C�e���i�[�p
	vector<int> lastTimeItem; //�O��܂ł̃A�C�e���i�[�p
	string itemData; //�A�C�e���f�[�^�̃o�C�i���t�@�C��

	vector<int> currentAccessory; //���݂܂ł̃A�N�Z�T���[�i�[�p
	vector<int> lastTimeAccessory; //�O��܂ł̃A�N�Z�T���[�i�[�p
	string accessoryData; //�A�N�Z�T���[�f�[�^�̃o�C�i���t�@�C��

	vector<int> currentJewel; //���݂܂ł̃W���G���i�[�p
	vector<int> lastTimeJewel; //�O��܂ł̃W���G���i�[�p
	string jewelData; //�W���G���f�[�^�̃o�C�i���t�@�C��

	vector<int> currentMineral; //���݂܂ł̍z���i�[�p
	vector<int> lastTimeMineral; //�O��܂ł̍z���i�[�p
	string mineralData; //�z���f�[�^�̃o�C�i���t�@�C��

	int getFileSize(string fileName);

	void writeBinaryFile(vector<int>& currentData, vector<int>& lastTimeData, string fileName);
	void roadBinaryFile(vector<int>& currentData, vector<int>& lastTimeData, string fileName);

	void getCurrentStatus();
	void getLastTimeStatus();

	void getCurrentEvent(vector<int>& currentEvent, vector<int>& saveLocation);
	void getLastTimeEvent(vector<int>& lastTimeEvent, vector<int>& saveLocation);

public:
	DataSave(Player& player, EventField& field);
	~DataSave();


	void writeSaveData();
	void roadSaveData();


	void update();
};
