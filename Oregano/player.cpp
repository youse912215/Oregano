#include "DxLib.h"
#include "Player.h"
#include "constant.h"
#include "mapDraw.h"

Player::Player(Input& input, DataSource& source) :
	input(input), source(source), cooldown(3), cooldownFlag(3),

	/* �f�[�^�� */
	status(PLAYER_STATUS_SIZE), possessionItem(PLAYER_ITEM_SIZE),
	possessionAccessory(PLAYER_ACCESSORY_SIZE), possessionJewel(PLAYER_JEWEL_SIZE),
	possessionMineral(PLAYER_MINERAL_SIZE) {

	this->pos.dx = static_cast<int>(WIN_WIDTH / 2 - BLOCK_SIZE / 2); //�v���C���[x���W
	this->pos.dy = static_cast<int>(WIN_HEIGHT / 2 - BLOCK_SIZE / 2 - 2); //�v���C���[y���W
	center = HALF_BLOCK_SIZE + pos; //�v���C���[�̒��S���W

	knifePos = 0; //�i�C�t���W
	knifeAddPos = 0; //�i�C�t�̉��Z���̍��W
	knifeCenter = 0; //�i�C�t�̒��S���W
	knife = false; //�i�C�t�t���O

	slashPos = 0; //�n���W
	slashCenter = 0; //�n�̒��S���W
	slash = false; //�n�t���O
}

Player::~Player() {
}

/// <summary>
/// �`�揈��
/// </summary>
void Player::draw() {
	//�i�C�t
	if (knife)
		DrawGraph(static_cast<int>(knifePos.dx), static_cast<int>(knifePos.dy), source.knifeGraph, true);

	//�n
	if (slash)
		DrawGraph(static_cast<int>(slashPos.dx), static_cast<int>(slashPos.dy), source.slashGraph, true);

	//�v���C���[
	DrawGraph(static_cast<int>(this->pos.dx), static_cast<int>(this->pos.dy), source.player, true);


	DrawFormatString(static_cast<int>(this->pos.dx), static_cast<int>(this->pos.dy),
	                 GetColor(255, 0, 0), "%lf, %lf, %lf, %lf",
	                 this->pos.dx, this->pos.dy, center.dx, center.dy, false);
	DrawFormatString(static_cast<int>(this->pos.dx), static_cast<int>(this->pos.dy) - 15,
	                 GetColor(255, 0, 0), "X%lf, Y%lf",
	                 knifePos.dx, knifePos.dy, false);
	DrawFormatString(static_cast<int>(this->pos.dx), static_cast<int>(this->pos.dy) - 30,
	                 GetColor(255, 0, 0), "X%lf, Y%lf",
	                 slashPos.dx, slashPos.dy, false);
}

/// <summary>
/// �A�N�V�����R�}���h����
/// </summary>
void Player::actionCommand() {
	/* �i�C�t���� */
	if (input.A && cooldown[KNIFE] == 0 && input.anySTICK()) {
		knife = true; //�i�C�t����
		cooldownFlag[KNIFE] = true; //�N�[���_�E���t���O��true
	}
	/* �n���� */
	if (input.B && cooldown[SLASH] == 0) {
		slash = true; //�n����]
		cooldownFlag[SLASH] = true; //�N�[���_�E���t���O��true
	}
}

/// <summary>
/// �i�C�t�̃N�[���_�E������
/// </summary>
void Player::knifeCooldown() {
	if (cooldownFlag[KNIFE]) cooldown[KNIFE]++; //�N�[���_�E���J�n

	//�N�[���_�E����30�b
	if (cooldown[KNIFE] >= 30) {
		cooldown[KNIFE] = 0; //�N�[���_�E�������Z�b�g
		cooldownFlag[KNIFE] = false; //�N�[���_�E���t���O��false
	}
}

/// <summary>
/// �i�C�t�̃|�W�W�������Z�b�g����
/// </summary>
void Player::knifePositionSet() {
	/* x���� */
	if (knifePos.dx < pos.dx) knifeAddPos.dx -= KNIFE_SPEED;
	else if (knifePos.dx > pos.dx) knifeAddPos.dx += KNIFE_SPEED;
	else knifeAddPos.dx = 0;
	/* y���� */
	if (knifePos.dy < pos.dy) knifeAddPos.dy -= KNIFE_SPEED;
	else if (knifePos.dy > pos.dy)knifeAddPos.dy += KNIFE_SPEED;
	else knifeAddPos.dy = 0;
}

/// <summary>
/// �i�C�t�̃|�W�W���������Z�b�g����
/// </summary>
void Player::knifePositionReset() {
	if (deleteKnife()) {
		knife = false;
		knifeAddPos.dx = 0.0;
		knifeAddPos.dy = 0.0;
	}
}

/// <summary>
/// �i�C�t�̉����i�W���C�p�b�h���ƋȂ��邱�Ƃ��\�j
/// </summary>
void Player::accelKnife() {
	/* x���� */
	if (input.STICK[LEFT]) knifeAddPos.dx -= KNIFE_SPEED / 2.0;
	else if (input.STICK[RIGHT]) knifeAddPos.dx += KNIFE_SPEED / 2.0;
	/* y���� */
	if (input.STICK[UP]) knifeAddPos.dy -= KNIFE_SPEED / 2.0;
	else if (input.STICK[DOWN]) knifeAddPos.dy += KNIFE_SPEED / 2.0;
}

/// <summary>
/// �i�C�t�̍X�V����
/// </summary>
void Player::knifeUpdate() {
	knifePos = pos + knifeAddPos; //�i�C�t�̍��W�̍X�V
	knifeCenter = HALF_BLOCK_SIZE + knifePos; //�i�C�t�̒��S�ʒu�̍X�V

	//�i�C�t���͂��������Ƃ�
	if (knife) {
		knifePositionSet(); //�i�C�t�̃|�W�W�����Z�b�g
		accelKnife(); //�i�C�t�̉���
		knifePositionReset(); //�i�C�t�̃|�W�W�������Z�b�g
	}
}

/// <summary>
/// �i�C�t�̍폜����
/// </summary>
/// <returns></returns>
bool Player::deleteKnife() {
	//�v���C���[����̋�����3�}�X������Ă��邩
	return abs(knifePos.dx + HALF_BLOCK_SIZE - center.dx) >= BLOCK_SIZE * 3.0
		|| abs(knifePos.dy + HALF_BLOCK_SIZE - center.dy) >= BLOCK_SIZE * 3.0;
}

/// <summary>
/// �n�̃N�[���_�E������
/// </summary>
void Player::slashCooldown() {
	if (cooldownFlag[SLASH]) cooldown[SLASH]++; //�N�[���_�E���J�n

	if (cooldown[SLASH] >= 20 && cooldown[SLASH] < 60) {
		slash = false; //�n�����߂�
	}
		//�N�[���_�E����60�b
	else if (cooldown[SLASH] >= 60) {
		cooldown[SLASH] = 0; //�N�[���_�E�������Z�b�g
		cooldownFlag[SLASH] = false; //�N�[���_�E���t���O��false
	}
}

void Player::slashUpdate() {
	slashPos = this->pos - HALF_BLOCK_SIZE;
}

/// <summary>
/// �X�V����
/// </summary>
void Player::update() {
	knifeCooldown(); //�i�C�t�̃N�[���_�E������
	slashCooldown(); //�n�̃N�[���_�E������

	actionCommand(); //�A�N�V�����R�}���h����

	knifeUpdate(); //�i�C�t�X�V����
	slashUpdate(); //�n�̍X�V����

	draw(); //�`�揈��

	DrawFormatString(0, 450, GetColor(0, 255, 0), "TF:%d, CDR:%d", knife, cooldown[0], false);
	DrawFormatString(0, 465, GetColor(0, 255, 0), "TF:%d, CDR:%d", slash, cooldown[1], false);

	/*DrawFormatString(0, 500, GetColor(120, 0, 100), "�g���W���[�����N:%d, �ԖG�K:%d, ������:%d, ������:%d, ���S��:%d",
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
	                 possessionMineral[3], possessionMineral[4], possessionMineral[4], false);*/
}
