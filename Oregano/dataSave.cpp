#include "dataSave.h"
#include "mapDraw.h"
#include "constant.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cmath>
#include "DxLib.h"

DataSave::DataSave(Player& player, EventField& field)
	: player(player), field(field), currentStatus(STATUS_SIZE + 2), currentCoin(COIN_INFORMATION_QUANTITY) {
	statusData = "resource\\Data\\statusData.bin";
	coinData = "resource\\Data\\coinData.bin";
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
void DataSave::roadBinaryFile(vector<int>& currentData, vector<int>& lastTimeData, string fileName) {
	/* �o�C�i���t�@�C���ǂݍ��� */
	ifstream fileRead(fileName, ios::binary);
	if (!fileRead) return;

	vector<char> binChar(getFileSize(fileName));
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
	for (unsigned int i = 0; i <= PRIORITY; ++i)
		currentStatus[i] = player.status[i];
	currentStatus[CURRENT_MAP_X] = MapDraw::mapX; //���݂̃}�b�vx���W����
	currentStatus[CURRENT_MAP_Y] = MapDraw::mapY; //���݂̃}�b�vy���W����
}

/// <summary>
/// �O��܂ł̃v���C���[�̃X�e�[�^�X���擾
/// </summary>
void DataSave::getLastTimeStatus() {
	for (unsigned int i = 0; i <= PRIORITY; ++i)
		player.status[i] = lastTimeStatus[i];
	MapDraw::mapX = lastTimeStatus[CURRENT_MAP_X]; //�O��܂ł̃}�b�vx���W����
	MapDraw::mapY = lastTimeStatus[CURRENT_MAP_Y]; //�O��܂ł̃}�b�vy���W����
}

void DataSave::getCurrentCoin() {
	for (unsigned int i = 0; i < currentCoin.size(); ++i)
		currentCoin[i] = field.coin[i]; //���݂܂ł̃R�C���󋵂��擾
}

void DataSave::getLastTimeCoin() {
	for (unsigned int i = 0; i < currentCoin.size(); ++i)
		field.coin[i] = lastTimeCoin[i]; //�O��܂ł̃R�C���󋵂��擾
}

/// <summary>
/// �Z�[�u�f�[�^�̏�������
/// </summary>
void DataSave::writeSaveData() {
	getCurrentStatus();
	writeBinaryFile(currentStatus, lastTimeStatus, statusData);

	getCurrentCoin();
	writeBinaryFile(currentCoin, lastTimeCoin, coinData);
}

/// <summary>
/// �Z�[�u�f�[�^�̓ǂݍ���
/// </summary>
void DataSave::roadSaveData() {
	/* �X�e�[�^�X */
	roadBinaryFile(currentStatus, lastTimeStatus, statusData);
	getLastTimeStatus();

	/* �t�B�[���h�R�C�� */
	roadBinaryFile(currentCoin, lastTimeCoin, coinData);
	getLastTimeCoin();
}

/// <summary>
/// �X�V����
/// </summary>
void DataSave::update() {
	DrawFormatString(0, 500, GetColor(0, 0, 0), "�ԖG�K:%d, ������:%d, ������:%d, ���S��:%d",
	                 player.status[GREEN_COIN], player.status[YELLOW_COIN],
	                 player.status[PURPLE_COIN], player.status[WHITE_COIN], false);

	DrawFormatString(0, 515, GetColor(0, 0, 0), "������:%d, �U����:%d, �����:%d, �D��x:%d",
	                 player.status[LIFE], player.status[ATTACK],
	                 player.status[DEFENSE], player.status[PRIORITY], false);

	DrawFormatString(0, 530, GetColor(0, 0, 0),
	                 "mx:%d, my:%d, cx:%d, cy:%d, dir:%d, type:%d, rank:%d, TofF:%d",
	                 field.coin[0], field.coin[1], field.coin[2], field.coin[3],
	                 field.coin[4], field.coin[5], field.coin[6], field.coin[7], false);
	DrawFormatString(0, 545, GetColor(0, 0, 0),
	                 "mx:%d, my:%d, cx:%d, cy:%d, dir:%d, type:%d, rank:%d, TofF:%d",
	                 field.coin[8], field.coin[9], field.coin[10], field.coin[11],
	                 field.coin[12], field.coin[13], field.coin[14], field.coin[15], false);
}
