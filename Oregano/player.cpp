#include "DxLib.h"
#include "Player.h"
#include "constant.h"
#include "mapDraw.h"

Player::Player(int graph) :
	graph(graph), status(PLAYER_STATUS_SIZE),
	possessionItem(PLAYER_ITEM_SIZE), possessionAccessory(PLAYER_ACCESSORY_SIZE),
	possessionJewel(PLAYER_JEWEL_SIZE), possessionMineral(PLAYER_MINERAL_SIZE) {
	this->pos.dx = static_cast<int>(WIN_WIDTH / 2 - BLOCK_SIZE / 2);
	this->pos.dy = static_cast<int>(WIN_HEIGHT / 2 - BLOCK_SIZE / 2 - 2);
	center = HALF_PLAYER_SIZE + pos;
}

Player::~Player() {
}

//�v���C���[�`��
void Player::draw() {
	DrawGraph(static_cast<int>(this->pos.dx),
	          static_cast<int>(this->pos.dy), graph, TRUE);

	DrawFormatString(static_cast<int>(this->pos.dx), static_cast<int>(this->pos.dy),
	                 GetColor(255, 0, 0), "%lf, %lf, %lf, %lf",
	                 this->pos.dx, this->pos.dy, center.dx, center.dy, false);
}

void Player::initProcess() {
}

void Player::update() {
	draw();

	DrawFormatString(0, 500, GetColor(120, 0, 100), "�g���W���[�����N:%d, �ԖG�K:%d, ������:%d, ������:%d, ���S��:%d",
	                 status[TREASURE_RANK], status[GREEN_COIN], status[YELLOW_COIN],
	                 status[PURPLE_COIN], status[WHITE_COIN], false);
	DrawFormatString(0, 515, GetColor(120, 0, 100), "���ݐ�����:%d, �ő吶����:%d, �U����:%d, ����:%d",
	                 status[CURRENT_LIFE], status[MAX_LIFE],
	                 status[ATTACK], status[BARGAINING_POWER], false);
	DrawFormatString(0, 530, GetColor(120, 0, 100), "�ғőϐ�:%d, �ғő����l:%d, �ғŒ~��:%d,  ��ბϐ�:%d, ��ბ����l:%d, ��გ~��:%d",
	                 status[DEADLY_POISON_RESISTANCE], status[DEADLY_POISON_VALUE],
	                 status[DEADLY_POISON_ACCUMULATION],
	                 status[PARALYSIS_RESISTANCE], status[PARALYSIS_VALUE],
	                 status[PARALYSIS_ACCUMULATION], false);
	DrawFormatString(0, 545, GetColor(120, 0, 100), "�Ö��ϐ�:%d, �Ö������l:%d, �Ö��~��:%d, �o���ϐ�:%d, �o�������l:%d, �o���~��:%d",
	                 status[HYPNOSIS_RESISTANCE], status[HYPNOSIS_VALUE],
	                 status[HYPNOSIS_ACCUMULATION],
	                 status[BLOODING_RESISTANCE], status[BLOODING_VALUE],
	                 status[BLOODING_ACCUMULATION], false);

	DrawFormatString(0, 630, GetColor(0, 0, 0), "���H:%d, �p��:%d, ��:%d, ��:%d�A��:%d, �n�}:%d, �{�g����:%d, �{�g����:%d",
	                 possessionItem[0], possessionItem[1], possessionItem[2],
	                 possessionItem[3], possessionItem[4], possessionItem[5],
	                 possessionItem[6], possessionItem[7], false);
	DrawFormatString(0, 645, GetColor(0, 0, 0),
	                 "�s�v�c�ȃ{�g��:%d, �ő�:%d, ��ő�:%d, ���N��:%d�A�`���[���b�v:%d, �A���G:%d, �}���[�S�[���h:%d, ������:%d",
	                 possessionItem[8], possessionItem[9], possessionItem[10],
	                 possessionItem[11], possessionItem[12], possessionItem[13],
	                 possessionItem[14], possessionItem[15], false);
	DrawFormatString(0, 660, GetColor(0, 0, 0),
	                 "�K�N:%d, �Q��:%d, �X�R�b�v:%d, �s�b�P��:%d�A�i�C�t:%d, ���C:%d, �A���}�L�m�R:%d, �~����:%d",
	                 possessionItem[16], possessionItem[17], possessionItem[18],
	                 possessionItem[19], possessionItem[20], possessionItem[21],
	                 possessionItem[22], possessionItem[23], false);
	DrawFormatString(0, 675, GetColor(0, 0, 0),
	                 "���N�H:%d, �ғŖ�:%d, ������:%d, �Î���:%d�A���s�i�X:%d, �^���|�|:%d, �}�b�X���_�P:%d, �L����:%d",
	                 possessionItem[24], possessionItem[25], possessionItem[26],
	                 possessionItem[27], possessionItem[28], possessionItem[29],
	                 possessionItem[30], possessionItem[31], false);
	DrawFormatString(0, 690, GetColor(0, 0, 0),
	                 "�Ԏ�:%d, �o�[�i�[:%d, ������:%d, �V�[�p���[:%d�A�u���b�h�G�L�X:%d, �u���b�h�|�[�V����:%d�A�����_�P:%d, �X���[�v�W�F��:%d",
	                 possessionItem[32], possessionItem[33], possessionItem[34],
	                 possessionItem[35], possessionItem[36], possessionItem[37],
	                 possessionItem[38], possessionItem[39], false);

	DrawFormatString(0, 720, GetColor(0, 0, 0), "B�l�b�N:%d, B�`���[:%d, B�y���_:%d, B�����O:%d�AB�s�A�X:%d, �e���T:%d, �}�`���_:%d, �i�K�^��:%d",
	                 possessionAccessory[0], possessionAccessory[1], possessionAccessory[2],
	                 possessionAccessory[3], possessionAccessory[4], possessionAccessory[5],
	                 possessionAccessory[6], possessionAccessory[7], false);
	DrawFormatString(0, 735, GetColor(0, 0, 0), "S�l�b�N:%d, S�`���[:%d, S�y���_:%d, S�����O:%d�AS�s�A�X:%d, �������:%d, G�l�b�N:%d, G�y���_:%d",
	                 possessionAccessory[8], possessionAccessory[9], possessionAccessory[10],
	                 possessionAccessory[11], possessionAccessory[12], possessionAccessory[14],
	                 possessionAccessory[15], possessionAccessory[16], false);

	DrawFormatString(0, 770, GetColor(0, 0, 0), "�G�������h:%d, T�K�[�l�b�g:%d, C�g���}����:%d, �y��D:%d�A�ԖG�K���[�hN:%d",
	                 possessionJewel[0], possessionJewel[1], possessionJewel[2],
	                 possessionJewel[3], possessionJewel[20], false);

	DrawFormatString(0, 800, GetColor(0, 0, 0), "�y��:%d, ���h��:%d, ��h��:%d, ���h��:%d�A�k�h��:%d, ��������:%d",
	                 possessionMineral[0], possessionMineral[1], possessionMineral[2],
	                 possessionMineral[3], possessionMineral[4], possessionMineral[4], false);
}
