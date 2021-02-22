#include "dataSave.h"
#include "mapDraw.h"
#include "constant.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cmath>
#include "DxLib.h"

DataSave::DataSave(Player& player, EventField& field)
	: player(player), field(field),
	  currentStatus(STATUS_INFORMATION_SIZE), //�X�e�[�^�X
	  /* �����i */
	  currentPossessionItem(PLAYER_ITEM_SIZE), currentPossessionAccessory(PLAYER_ACCESSORY_SIZE),
	  currentPossessionJewel(PLAYER_JEWEL_SIZE), currentPossessionMineral(PLAYER_MINERAL_SIZE),
	  /* �t�B�[���h */
	  currentCoin(COIN_INFORMATION_SIZE), currentItem(ITEM_INFORMATION_SIZE),
	  currentAccessory(ACCESSORY_INFORMATION_SIZE), currentJewel(JEWEL_INFORMATION_SIZE),
	  currentMineral(MINERAL_INFORMATION_SIZE) {
	statusData = "resource\\Data\\statusData.bin"; //�X�e�[�^�X
	/* �����i */
	possessionItemData = "resource\\Data\\possessionItemData.bin";
	possessionAccessoryData = "resource\\Data\\possessionAccessoryData.bin";
	possessionJewelData = "resource\\Data\\possessionJewelData.bin";
	possessionMineralData = "resource\\Data\\possessionMineralData.bin";
	/*�@�t�B�[���h */
	coinData = "resource\\Data\\coinData.bin";
	itemData = "resource\\Data\\itemData.bin";
	accessoryData = "resource\\Data\\accessoryData.bin";
	jewelData = "resource\\Data\\jewelData.bin";
	mineralData = "resource\\Data\\mineralData.bin";
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
	for (unsigned int i = 0; i <= BARGAINING_POWER; ++i)
		currentStatus[i] = player.status[i];
	currentStatus[CURRENT_MAP_X] = MapDraw::mapX; //���݂̃}�b�vx���W����
	currentStatus[CURRENT_MAP_Y] = MapDraw::mapY; //���݂̃}�b�vy���W����
}

/// <summary>
/// �O��܂ł̃v���C���[�̃X�e�[�^�X���擾
/// </summary>
void DataSave::getLastTimeStatus() {
	for (unsigned int i = 0; i <= BARGAINING_POWER; ++i)
		player.status[i] = lastTimeStatus[i];
	MapDraw::mapX = lastTimeStatus[CURRENT_MAP_X]; //�O��܂ł̃}�b�vx���W����
	MapDraw::mapY = lastTimeStatus[CURRENT_MAP_Y]; //�O��܂ł̃}�b�vy���W����
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

	/* �����A�C�e�� */
	getCurrentEvent(currentPossessionItem, player.possessionItem);
	writeBinaryFile(currentPossessionItem, lastTimePossessionItem, possessionItemData);
	/* �����A�N�Z�T���[ */
	getCurrentEvent(currentPossessionAccessory, player.possessionAccessory);
	writeBinaryFile(currentPossessionAccessory, lastTimePossessionAccessory, possessionAccessoryData);
	/* �����W���G�� */
	getCurrentEvent(currentPossessionJewel, player.possessionJewel);
	writeBinaryFile(currentPossessionJewel, lastTimePossessionJewel, possessionJewelData);
	/* �����W���G�� */
	getCurrentEvent(currentPossessionMineral, player.possessionMineral);
	writeBinaryFile(currentPossessionMineral, lastTimePossessionMineral, possessionMineralData);

	/* �t�B�[���h�R�C�� */
	getCurrentEvent(currentCoin, field.coin);
	writeBinaryFile(currentCoin, lastTimeCoin, coinData);
	/* �t�B�[���h�A�C�e�� */
	getCurrentEvent(currentItem, field.item);
	writeBinaryFile(currentItem, lastTimeItem, itemData);
	/* �t�B�[���h�A�N�Z�T���[ */
	getCurrentEvent(currentAccessory, field.accessory);
	writeBinaryFile(currentAccessory, lastTimeAccessory, accessoryData);
	/* �t�B�[���h�W���G�� */
	getCurrentEvent(currentJewel, field.jewel);
	writeBinaryFile(currentJewel, lastTimeJewel, jewelData);
	/* �t�B�[���h�z�� */
	getCurrentEvent(currentMineral, field.mineral);
	writeBinaryFile(currentMineral, lastTimeMineral, mineralData);
}

/// <summary>
/// �Z�[�u�f�[�^�̓ǂݍ���
/// </summary>
void DataSave::roadSaveData() {
	/* �X�e�[�^�X */
	roadBinaryFile(currentStatus, lastTimeStatus, statusData);
	getLastTimeStatus();

	/* �����A�C�e�� */
	roadBinaryFile(currentPossessionItem, lastTimePossessionItem, possessionItemData);
	getLastTimeEvent(lastTimePossessionItem, player.possessionItem);
	/* �����A�N�Z�T���[ */
	roadBinaryFile(currentPossessionAccessory, lastTimePossessionAccessory, possessionAccessoryData);
	getLastTimeEvent(lastTimePossessionAccessory, player.possessionAccessory);
	/* �����W���G�� */
	roadBinaryFile(currentPossessionJewel, lastTimePossessionJewel, possessionJewelData);
	getLastTimeEvent(lastTimePossessionJewel, player.possessionJewel);
	/* �����z�� */
	roadBinaryFile(currentPossessionMineral, lastTimePossessionMineral, possessionMineralData);
	getLastTimeEvent(lastTimePossessionMineral, player.possessionMineral);

	/* �t�B�[���h�R�C�� */
	roadBinaryFile(currentCoin, lastTimeCoin, coinData);
	getLastTimeEvent(lastTimeCoin, field.coin);
	/* �t�B�[���h�A�C�e�� */
	roadBinaryFile(currentItem, lastTimeItem, itemData);
	getLastTimeEvent(lastTimeItem, field.item);
	/* �t�B�[���h�A�N�Z�T���[ */
	roadBinaryFile(currentAccessory, lastTimeAccessory, accessoryData);
	getLastTimeEvent(lastTimeAccessory, field.accessory);
	/* �t�B�[���h�W���G�� */
	roadBinaryFile(currentJewel, lastTimeJewel, jewelData);
	getLastTimeEvent(lastTimeJewel, field.jewel);
	/* �t�B�[���h�z�� */
	roadBinaryFile(currentMineral, lastTimeMineral, mineralData);
	getLastTimeEvent(lastTimeMineral, field.mineral);
}

/// <summary>
/// �X�V����
/// </summary>
void DataSave::update() {
	DrawFormatString(0, 500, GetColor(120, 0, 100), "�g���W���[�����N:%d, �ԖG�K:%d, ������:%d, ������:%d, ���S��:%d",
	                 player.status[TREASURE_RANK], player.status[GREEN_COIN], player.status[YELLOW_COIN],
	                 player.status[PURPLE_COIN], player.status[WHITE_COIN], false);
	DrawFormatString(0, 515, GetColor(120, 0, 100), "���ݐ�����:%d, �ő吶����:%d, �U����:%d, ����:%d",
	                 player.status[CURRENT_LIFE], player.status[MAX_LIFE],
	                 player.status[ATTACK], player.status[BARGAINING_POWER], false);
	DrawFormatString(0, 530, GetColor(120, 0, 100), "�ғőϐ�:%d, �ғő����l:%d, �ғŒ~��:%d,  ��ბϐ�:%d, ��ბ����l:%d, ��გ~��:%d",
	                 player.status[DEADLY_POISON_RESISTANCE], player.status[DEADLY_POISON_VALUE],
	                 player.status[DEADLY_POISON_ACCUMULATION],
	                 player.status[PARALYSIS_RESISTANCE], player.status[PARALYSIS_VALUE],
	                 player.status[PARALYSIS_ACCUMULATION], false);
	DrawFormatString(0, 545, GetColor(120, 0, 100), "�Ö��ϐ�:%d, �Ö������l:%d, �Ö��~��:%d, �o���ϐ�:%d, �o�������l:%d, �o���~��:%d",
	                 player.status[HYPNOSIS_RESISTANCE], player.status[HYPNOSIS_VALUE],
	                 player.status[HYPNOSIS_ACCUMULATION],
	                 player.status[BLOODING_RESISTANCE], player.status[BLOODING_VALUE],
	                 player.status[BLOODING_ACCUMULATION], false);

	DrawFormatString(0, 630, GetColor(0, 0, 0), "���H:%d, �p��:%d, ��:%d, ��:%d�A��:%d, �n�}:%d, �{�g����:%d, �{�g����:%d",
	                 player.possessionItem[0], player.possessionItem[1], player.possessionItem[2],
	                 player.possessionItem[3], player.possessionItem[4], player.possessionItem[5],
	                 player.possessionItem[6], player.possessionItem[7], false);
	DrawFormatString(0, 645, GetColor(0, 0, 0),
	                 "�s�v�c�ȃ{�g��:%d, �ő�:%d, ��ő�:%d, ���N��:%d�A�`���[���b�v:%d, �A���G:%d, �}���[�S�[���h:%d, ������:%d",
	                 player.possessionItem[8], player.possessionItem[9], player.possessionItem[10],
	                 player.possessionItem[11], player.possessionItem[12], player.possessionItem[13],
	                 player.possessionItem[14], player.possessionItem[15], false);
	DrawFormatString(0, 660, GetColor(0, 0, 0),
	                 "�K�N:%d, �Q��:%d, �X�R�b�v:%d, �s�b�P��:%d�A�i�C�t:%d, ���C:%d, �A���}�L�m�R:%d, �~����:%d",
	                 player.possessionItem[16], player.possessionItem[17], player.possessionItem[18],
	                 player.possessionItem[19], player.possessionItem[20], player.possessionItem[21],
	                 player.possessionItem[22], player.possessionItem[23], false);
	DrawFormatString(0, 675, GetColor(0, 0, 0),
	                 "���N�H:%d, �ғŖ�:%d, ������:%d, �Î���:%d�A���s�i�X:%d, �^���|�|:%d, �}�b�X���_�P:%d, �L����:%d",
	                 player.possessionItem[24], player.possessionItem[25], player.possessionItem[26],
	                 player.possessionItem[27], player.possessionItem[28], player.possessionItem[29],
	                 player.possessionItem[30], player.possessionItem[31], false);
	DrawFormatString(0, 690, GetColor(0, 0, 0),
	                 "�Ԏ�:%d, �o�[�i�[:%d, ������:%d, �V�[�p���[:%d�A�u���b�h�G�L�X:%d, �u���b�h�|�[�V����:%d�A�����_�P:%d, �X���[�v�W�F��:%d",
	                 player.possessionItem[32], player.possessionItem[33], player.possessionItem[34],
	                 player.possessionItem[35], player.possessionItem[36], player.possessionItem[37],
	                 player.possessionItem[38], player.possessionItem[39], false);

	DrawFormatString(0, 720, GetColor(0, 0, 0), "B�l�b�N:%d, B�`���[:%d, B�y���_:%d, B�����O:%d�AB�s�A�X:%d, �e���T:%d, �}�`���_:%d, �i�K�^��:%d",
	                 player.possessionAccessory[0], player.possessionAccessory[1], player.possessionAccessory[2],
	                 player.possessionAccessory[3], player.possessionAccessory[4], player.possessionAccessory[5],
	                 player.possessionAccessory[6], player.possessionAccessory[7], false);
	DrawFormatString(0, 735, GetColor(0, 0, 0), "S�l�b�N:%d, S�`���[:%d, S�y���_:%d, S�����O:%d�AS�s�A�X:%d, �������:%d, G�l�b�N:%d, G�y���_:%d",
	                 player.possessionAccessory[8], player.possessionAccessory[9], player.possessionAccessory[10],
	                 player.possessionAccessory[11], player.possessionAccessory[12], player.possessionAccessory[14],
	                 player.possessionAccessory[15], player.possessionAccessory[16], false);

	DrawFormatString(0, 770, GetColor(0, 0, 0), "�G�������h:%d, T�K�[�l�b�g:%d, C�g���}����:%d, �y��D:%d�A�ԖG�K���[�hN:%d",
	                 player.possessionJewel[0], player.possessionJewel[1], player.possessionJewel[2],
	                 player.possessionJewel[3], player.possessionJewel[20], false);

	DrawFormatString(0, 800, GetColor(0, 0, 0), "�y��:%d, ���h��:%d, ��h��:%d, ���h��:%d�A�k�h��:%d, ��������:%d",
	                 player.possessionMineral[0], player.possessionMineral[1], player.possessionMineral[2],
	                 player.possessionMineral[3], player.possessionMineral[4], player.possessionMineral[4], false);
}
