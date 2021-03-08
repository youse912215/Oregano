#include "dataSave.h"
#include "mapDraw.h"
#include "constant.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cmath>
#include "DxLib.h"

DataSave::DataSave(PlayerState& player)
	: player(player),
	  currentStatus(STATUS_INFORMATION_SIZE) //�X�e�[�^�X
/* �����i */
/*currentPossessionItem(PLAYER_ITEM_SIZE), currentPossessionAccessory(PLAYER_ACCESSORY_SIZE),
currentPossessionJewel(PLAYER_JEWEL_SIZE), currentPossessionMineral(PLAYER_MINERAL_SIZE),*/
/* �t�B�[���h */
/*currentCoin(COIN_INFORMATION_SIZE), currentItem(ITEM_INFORMATION_SIZE),
currentAccessory(ACCESSORY_INFORMATION_SIZE), currentJewel(JEWEL_INFORMATION_SIZE),
currentMineral(MINERAL_INFORMATION_SIZE), roadItemText(120)*/ {
	statusData = "resource\\Data\\statusData.bin"; //�X�e�[�^�X
	///* �����i */
	//possessionItemData = "resource\\Data\\possessionItemData.bin";
	//possessionAccessoryData = "resource\\Data\\possessionAccessoryData.bin";
	//possessionJewelData = "resource\\Data\\possessionJewelData.bin";
	//possessionMineralData = "resource\\Data\\possessionMineralData.bin";
	///*�@�t�B�[���h */
	//coinData = "resource\\Data\\coinData.bin";
	//itemData = "resource\\Data\\itemData.bin";
	//accessoryData = "resource\\Data\\accessoryData.bin";
	//jewelData = "resource\\Data\\jewelData.bin";
	//mineralData = "resource\\Data\\mineralData.bin";

	//itemTextData = "resource\\Data\\itemTextLengthData.bin";
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
/// ���݂܂ł̃t�B�[���h�C�x���g�󋵂��擾
/// </summary>
/// <param name="currentEvent">���݂܂ł̃C�x���g</param>
/// <param name="saveLocation">�t�B�[���h�C�x���g</param>
void DataSave::getCurrentEvent(vector<int>& currentEvent, vector<int>& saveLocation) {
	for (unsigned int i = 0; i < currentEvent.size(); ++i)
		currentEvent[i] = saveLocation[i];
}

/// <summary>
/// �O��܂ł̃t�B�[���h�C�x���g�󋵂��擾
/// </summary>
/// <param name="lastTimeEvent">�O��܂ł̃C�x���g</param>
/// <param name="saveLocation">�t�B�[���h�C�x���g</param>
void DataSave::getLastTimeEvent(vector<int>& lastTimeEvent, vector<int>& saveLocation) {
	for (unsigned int i = 0; i < lastTimeEvent.size(); ++i)
		saveLocation[i] = lastTimeEvent[i];
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
void DataSave::roadSaveData() {
	/* �X�e�[�^�X */
	roadBinaryFile(currentStatus, lastTimeStatus, statusData);
	getLastTimeStatus();
}

/// <summary>
/// �X�V����
/// </summary>
void DataSave::update() {
	/*DrawFormatString(0, 700, GetColor(255, 0, 0), "%d, %d, %d, %d",
	                 player.coin[0], player.coin[1], player.coin[2], player.coin[3], false);*/
}
