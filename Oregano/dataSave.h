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

	vector<int> currentPossessionItem; //���݂܂ł̏����A�C�e���i�[�p
	vector<int> lastTimePossessionItem; //�O��܂ł̏����A�C�e���i�[�p
	string possessionItemData; //�����A�C�e���f�[�^�̃o�C�i���t�@�C��

	vector<int> currentPossessionAccessory; //���݂܂ł̏����A�N�Z�T���[�i�[�p
	vector<int> lastTimePossessionAccessory; //�O��܂ł̏����A�N�Z�T���[�i�[�p
	string possessionAccessoryData; //�����A�N�Z�T���[�f�[�^�̃o�C�i���t�@�C��

	vector<int> currentPossessionJewel; //���݂܂ł̏����W���G���i�[�p
	vector<int> lastTimePossessionJewel; //�O��܂ł̏����W���G���i�[�p
	string possessionJewelData; //�����W���G���f�[�^�̃o�C�i���t�@�C��

	vector<int> currentPossessionMineral; //���݂܂ł̏����z���i�[�p
	vector<int> lastTimePossessionMineral; //�O��܂ł̏����z���i�[�p
	string possessionMineralData; //�����z���f�[�^�̃o�C�i���t�@�C��

	vector<int> currentCoin; //���݂܂ł̃t�B�[���h�R�C���i�[�p
	vector<int> lastTimeCoin; //�O��܂ł̃t�B�[���h�R�C���i�[�p
	string coinData; //�t�B�[���h�R�C���f�[�^�̃o�C�i���t�@�C��

	vector<int> currentItem; //���݂܂ł̃t�B�[���h�A�C�e���i�[�p
	vector<int> lastTimeItem; //�O��܂ł̃t�B�[���h�A�C�e���i�[�p
	string itemData; //�t�B�[���h�A�C�e���f�[�^�̃o�C�i���t�@�C��

	vector<int> currentAccessory; //���݂܂ł̃t�B�[���h�A�N�Z�T���[�i�[�p
	vector<int> lastTimeAccessory; //�O��܂ł̃t�B�[���h�A�N�Z�T���[�i�[�p
	string accessoryData; //�t�B�[���h�A�N�Z�T���[�f�[�^�̃o�C�i���t�@�C��

	vector<int> currentJewel; //���݂܂ł̃t�B�[���h�W���G���i�[�p
	vector<int> lastTimeJewel; //�O��܂ł̃t�B�[���h�W���G���i�[�p
	string jewelData; //�t�B�[���h�W���G���f�[�^�̃o�C�i���t�@�C��

	vector<int> currentMineral; //���݂܂ł̃t�B�[���h�z���i�[�p
	vector<int> lastTimeMineral; //�O��܂ł̃t�B�[���h�z���i�[�p
	string mineralData; //�t�B�[���h�z���f�[�^�̃o�C�i���t�@�C��

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
