#pragma once
#include "playerState.h"
#include "gameUI.h"
#include <vector>
#include <string>

using namespace std;

class DataSave {
private:
	PlayerState& player; //�v���C���[��ԃN���X
	GameUI& UI; //UI�N���X

	vector<int> currentStatus; //���݂܂ł̃X�e�[�^�X�i�[�p
	vector<int> lastTimeStatus; //�O��܂ł̃X�e�[�^�X�i�[�p
	string statusData; //�Z�[�u�f�[�^�̃o�C�i���t�@�C��

	vector<int> roadMap; //�}�b�v�o�b�t�@�m�ۗp
	vector<int> storeMap; //�}�b�v�i�[�p
	string mapData; //�Z�[�u�f�[�^�̃o�C�i���t�@�C��

	int getFileSize(string fileName); //�t�@�C���T�C�Y���擾

	void writeBinaryFile(vector<int>& currentData, vector<int>& lastTimeData,
	                     string fileName); //�o�C�i���t�@�C���̂̏�������
	void roadBinaryFile(vector<int>& currentData, vector<int>& lastTimeData,
	                    string fileName); //�o�C�i���t�@�C���̓ǂݍ���

	void getCurrentStatus(); //���݂܂ł̃v���C���[�̃X�e�[�^�X���擾
	void getLastTimeStatus(); //�O��܂ł̃v���C���[�̃X�e�[�^�X���擾

	void storingEvent(vector<int>& roadData, vector<int>& saveLocation); //�C�x���g���W���i�[

public:
	DataSave(PlayerState& player, GameUI& UI);
	~DataSave();

	void writeSaveData(); //�Z�[�u�f�[�^�̏�������
	void roadSaveData(); //�Z�[�u�f�[�^�̓ǂݍ���

	void roadMapData(); //�}�b�v�f�[�^�̓ǂݍ���
};
