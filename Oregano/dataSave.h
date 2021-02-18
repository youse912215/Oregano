#pragma once
#include "eventBase.h"
#include "player.h"
#include <vector>
#include <string>

using namespace std;

class DataSave {
private:
	EventBase& position;
	Player& player;

	vector<int> statusData; //�X�e�[�^�X�i�[
	vector<int> vecOut; //�i�[��̔z��
	string saveDataFile; //�Z�[�u�f�[�^�̃o�C�i���t�@�C��
	string eventFieldData;

	int getFileSize(string fName);
	void getCurrentStatus();

public:
	DataSave(EventBase& event, Player& player);
	~DataSave();

	void writeBinaryFile();
	void roadBinaryFile();
	void update();
};
