#include "dataSave.h"
#include "mapDraw.h"
#include "constant.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cmath>
#include "DxLib.h"

DataSave::DataSave(PlayerState& player, GameUI& UI) :
	player(player), UI(UI),

	/* �T�C�Y�m�� */
	currentStatus(STATUS_INFORMATION_SIZE),
	roadMap(MAP_EVENT_SIZE),

	/* �o�C�i���f�[�^�t�@�C�� */
	statusData("resource\\Data\\statusData.bin"),
	mapData("resource\\Data\\mapData.bin"),
	initStatusData("resource\\Data\\initStatusData.bin") {
}

DataSave::~DataSave() {
}

/// <summary>
/// �t�@�C���T�C�Y���擾
/// </summary>
/// <param name="fName">�t�@�C���̖��O</param>
int DataSave::getFileSize(string fileName) {
	ifstream fileRoad(fileName, ifstream::ate);
	size_t fileSize = static_cast<size_t>(fileRoad.tellg());
	return fileSize;
}

/// <summary>
/// �o�C�i���t�@�C���̏�������
/// </summary>
void DataSave::writeBinaryFile(vector<int>& currentData, vector<int>& lastTimeData, string fileName) {
	lastTimeData.clear(); //�O��܂ł̃f�[�^�̃N���A

	for (auto& i : currentData)
		lastTimeData.push_back(i); //�X�e�[�^�X�����ԂɊi�[

	int sizeOut = lastTimeData.size(); //�x�N�^�[�z��̃T�C�Y�����i�[

	/* �o�C�i���t�@�C���������� */
	ofstream fileWrite(fileName, ios::binary);
	if (!fileWrite) return;

	fileWrite.write(reinterpret_cast<char*>(&lastTimeData[0]),
	                static_cast<std::streamsize>(sizeof(int)) * sizeOut);
	fileWrite.close(); //����
}

/// <summary>
/// �o�C�i���t�@�C���̓ǂݍ���
/// </summary>
void DataSave::loadBinaryFile(vector<int>& currentData, vector<int>& lastTimeData, string fileName) {
	/* �o�C�i���t�@�C���ǂݍ��� */
	ifstream fileRead(fileName, ios::binary);
	if (!fileRead) return;

	vector<char> binChar(getFileSize(fileName)); //�T�C�Y���擾
	if (!fileRead.read(&binChar[0], getFileSize(fileName))) return;
	fileRead.close(); //����

	/* 16�i����10�i���ɕϊ����A�o�͔z��Ɋi�[ */
	for (unsigned int i = 0; i < currentData.size(); ++i)
		lastTimeData.push_back((binChar[i * 4] & 0xff)
			+ static_cast<int>((binChar[i * 4 + 1] & 0xff) * pow(16, 2)));
}

/// <summary>
/// ���݂܂ł̃v���C���[�̃X�e�[�^�X���擾
/// </summary>
void DataSave::getCurrentStatus() {
	//���݂̊e�R�C������
	for (unsigned int i = 0; i != PlayerState::coin.size(); ++i)
		currentStatus[i] = PlayerState::coin[i];

	//���݂̑����ϋv�l����
	for (unsigned int i = 0; i != PlayerState::attributeAccumulation.size(); ++i)
		currentStatus[i + PlayerState::coin.size()] = PlayerState::attributeAccumulation[i];

	//���݂̐퓬�X�^�C������
	currentStatus[PlayerState::coin.size() + PlayerState::attributeAccumulation.size()] = PlayerState::battleStyle;

	//�e�}�b�v���W
	currentStatus[9] = MapDraw::mapX; //���݂̃}�b�vx���W����
	currentStatus[10] = MapDraw::mapY; //���݂̃}�b�vy���W����
}

/// <summary>
/// �O��܂ł̃v���C���[�̃X�e�[�^�X���擾
/// </summary>
void DataSave::getLastTimeStatus() {
	//�O��܂ł̊e�R�C������
	for (unsigned int i = 0; i != PlayerState::coin.size(); ++i)
		PlayerState::coin[i] = lastTimeStatus[i];

	//�O��܂ł̑����ϋv�l����
	for (unsigned int i = 0; i != PlayerState::attributeAccumulation.size(); ++i)
		PlayerState::attributeAccumulation[i] = lastTimeStatus[i + PlayerState::coin.size()];

	//�O��܂ł̐퓬�X�^�C������
	PlayerState::battleStyle = lastTimeStatus[PlayerState::coin.size() + PlayerState::attributeAccumulation.size()];

	//�e�}�b�v���W
	MapDraw::mapX = lastTimeStatus[9]; //�O��܂ł̃}�b�vx���W����
	MapDraw::mapY = lastTimeStatus[10]; //�O��܂ł̃}�b�vy���W����
}

/// <summary>
/// �C�x���g���W���i�[
/// </summary>
/// <param name="lastTimeEvent">�O��܂ł̃C�x���g</param>
/// <param name="saveLocation">�t�B�[���h�C�x���g</param>
void DataSave::storingEvent(vector<int>& roadData, vector<int>& saveLocation) {
	for (unsigned int i = 0; i < roadData.size(); ++i)
		saveLocation[i] = roadData[i];
}

/// <summary>
/// �Z�[�u�f�[�^�̏�������
/// </summary>
void DataSave::writeSaveData() {
	/* �X�e�[�^�X */
	getCurrentStatus();
	writeBinaryFile(currentStatus, lastTimeStatus, statusData);
}

/// <summary>
/// �Z�[�u�f�[�^�̓ǂݍ���
/// </summary>
void DataSave::loadSaveData() {
	/* �X�e�[�^�X */
	loadBinaryFile(currentStatus, lastTimeStatus, statusData);
	getLastTimeStatus();
}

/// <summary>
/// �����Z�[�u�f�[�^�̓ǂݍ���
/// </summary>
void DataSave::loadInitSaveData() {
	/* �X�e�[�^�X */
	loadBinaryFile(currentStatus, lastTimeStatus, initStatusData);
	getLastTimeStatus();
}

/// <summary>
/// �}�b�v�f�[�^�̓ǂݍ���
/// </summary>
void DataSave::loadMapData() {
	/* �}�b�v�C�x���g���W�̊i�[ */
	loadBinaryFile(roadMap, storeMap, mapData);
	storingEvent(storeMap, UI.mapEventPos);
}
