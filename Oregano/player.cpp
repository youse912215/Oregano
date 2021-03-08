#include "DxLib.h"
#include "player.h"
#include "constant.h"
#include "playerKnife.h"
#include "playerShield.h"
#include "playerSlash.h"
#include "playerState.h"

PlayerKnife knifeAct;
PlayerSlash slashAct;
PlayerShield shieldAct;
PlayerState stateAct;

Player::Player(Input& input, MapDraw& draw_) : input(input),
                                               draw_(draw_), cooldown(4),

                                               cooldownFlag(4),

                                               knifeCenter(0.0, 0.0), slashCenter(0.0, 0.0),

                                               actionFlag{false, false, false, false} {

	this->pos.dx = static_cast<int>(WIN_WIDTH / 2 - BLOCK_SIZE / 2); //�v���C���[x���W
	this->pos.dy = static_cast<int>(WIN_HEIGHT / 2 - BLOCK_SIZE / 2 - 2); //�v���C���[y���W
	center = HALF_BLOCK_SIZE_D + pos; //�v���C���[�̒��S���W
}

Player::~Player() {
}

/// <summary>
/// �`�揈��
/// </summary>
void Player::draw() {
	//�v���C���[
	DrawRectGraph(static_cast<int>(this->pos.dx), static_cast<int>(this->pos.dy),
	              BLOCK_SIZE * input.moveDirection, BLOCK_SIZE * PlayerState::battleStyle,
	              BLOCK_SIZE, BLOCK_SIZE,
	              source.player, true, false);
}

/// <summary>
/// �A�N�V�����R�}���h����
/// </summary>
void Player::actionCommand() {
	/* �i�C�t���� */
	if (input.A && cooldown[KNIFE] == 0 && input.anySTICK()) {
		actionFlag[KNIFE] = true; //�i�C�t����
		cooldownFlag[KNIFE] = true; //�N�[���_�E���t���O��true
	}
	/* �n���� */
	if (input.B && cooldown[SLASH] == 0) {
		actionFlag[SLASH] = true; //�n����]
		cooldownFlag[SLASH] = true; //�N�[���_�E���t���O��true
	}
	/* �V�[���h */
	if (input.X && !cooldownFlag[SHIELD]) {
		actionFlag[SHIELD] = true; //�V�[���h��t�^
		shieldAct.giveShield(PlayerState::battleStyle); //�V�[���h�ʂ�ǉ�
		cooldownFlag[SHIELD] = true; //�N�[���_�E���t���O��true
	}
	/* �����ꂩ�̏�Ԉُ�̂Ƃ��A��Ԃ����� */
	if (input.Y && !cooldownFlag[RECOVERY] && stateAct.anyCondition()) {
		actionFlag[RECOVERY] = true; //��Ԃ�����
	}
	/* �퓬�X�^�C���ؑ� */
	//L�{�^��
	if (input.LB)
		stateAct.changeBattleStyle(LEFT); //���̃X�^�C����
	//R�{�^��
	if (input.RB)
		stateAct.changeBattleStyle(RIGHT); //�E�̃X�^�C����
}

/// <summary>
/// �R�C���̑�������
/// </summary>
/// <param name="attackPower">�G�̍U����</param>
void Player::lostPlayerCoin(const int& attackPower) {
	if (!actionFlag[SHIELD]) {
		PlayerState::coin[PlayerState::battleStyle]
			-= attackPower * stateAct.addConditionDamage(); //�R�C������
		//�R�C����0�ȉ��Ȃ�΁A
		if (PlayerState::coin[PlayerState::battleStyle] <= 0)
			PlayerState::coin[PlayerState::battleStyle] = 0; //0�ȉ��ɂȂ�����0�ɖ߂�
	}
	else {
		shieldAct.value -= attackPower; //�V�[���h�ʌ���
		shieldAct.zeroOut(); //0�ȉ��ɂȂ����Ƃ�0�ɖ߂�
	}
}

/// <summary>
/// �R�C���̒ǉ�����
/// </summary>
/// <param name="enemyCoin">�G�̏����R�C��</param>
/// <param name="attribute">�G�̑���</param>
void Player::addPlayerCoin(const int& attribute, const int& enemyCoin) {
	PlayerState::coin[attribute] += enemyCoin;
}

/// <summary>
/// �����l�̒~�Ϗ���
/// �����~�ϒl���ő�l�ł͂Ȃ��Ƃ��A���Z����
/// </summary>
/// <param name="attribute">�G�̑���</param>
/// <param name="attributeValue">�G�̑����l</param>
void Player::addAttributeAccumulation(const int& attribute, const int& attributeValue) {
	//�V�[���h���Ȃ��Ƃ�
	if (!actionFlag[SHIELD])
		stateAct.calculateValue(attribute, attributeValue); //�����~�ϒl�̌v�Z

}

/// <summary>
/// �G�ւ̃_���[�W
/// </summary>
/// <param name="act">�v���C���[�̃A�N�V����</param>
int Player::addDamage(const int& act) {
	if (stateAct.battleStyle != BLOODING)
		return act + 1; //�ʏ��act+1�_���[�W
	return (act + 1) * 2; //�퓬�X�^�C�������g��(�Ώo��)�̂Ƃ�2�{
}

bool Player::state(const int& num) {
	return stateAct.condition[num];
}

bool Player::cool(const int& num) {
	return cooldownFlag[num];
}

/// <summary>
/// �i�C�t�X�V����
/// </summary>
void Player::knifeUpdate() {
	knifeAct.initialize(this->pos, knifeCenter); //�i�C�t�̏�����
	knifeAct.countCooldown(cooldown, cooldownFlag); //�i�C�t�̃N�[���_�E������

	//�i�C�t���͂��������Ƃ�
	if (actionFlag[KNIFE]) {
		knifeAct.setKnifePosition(this->pos); //�i�C�t�̃|�W�W�����Z�b�g
		knifeAct.accelKnife(input); //�i�C�t�̉���
		knifeAct.resetKnifePosition(center, actionFlag); //�i�C�t�̃|�W�W�������Z�b�g
		knifeAct.calculateRadian(this->pos);
		knifeAct.draw(source); //�`�揈��
	}
}

/// <summary>
/// �n�X�V����
/// </summary>
void Player::slashUpdate() {
	slashAct.initialize(this->pos); //�n�̏�����
	slashAct.countCooldown(cooldown, cooldownFlag, actionFlag);

	//�n�̓��͂��������Ƃ�
	if (actionFlag[SLASH]) {
		slashAct.countTime(); //�`�掞�ԃJ�E���g
		slashAct.draw(source); //�`�揈��
	}
}

/// <summary>
/// �V�[���h�X�V����
/// </summary>
void Player::shieldUpdate() {
	shieldAct.initialize(this->pos); //�V�[���h�̏�����
	shieldAct.countCooldown(cooldown, cooldownFlag, actionFlag); //�V�[���h�̃N�[���_�E������

	if (shieldAct.value <= 0) actionFlag[SHIELD] = false; //�V�[���h�ʂ�0�ɂȂ�����A�V�[���h����

	//�V�[���h�̓��͂��������Ƃ�
	if (actionFlag[SHIELD]) shieldAct.draw(source); //�`�揈��
}

/// <summary>
/// ��ԍX�V����
/// </summary>
void Player::stateUpdate() {
	stateAct.valueReset(actionFlag, cooldownFlag); //��Ԉُ퓙������
	stateAct.countCooldown(cooldown, cooldownFlag); //��ԉ����̃N�[���_�E������
	stateAct.conditionUpdate(draw_); //��Ԉُ�X�V����
	stateAct.switchStyleAutomatically(); //������Ԃ��X�V
}

/// <summary>
/// ���݂̃}�b�v��Ԃ�
/// </summary>
/// <param name="pos">x�܂���y</param>
int Player::currentMapPos(const int& pos) {
	if (pos == POSITION_X) return draw_.currentMap.x; //x�}�b�v
	return draw_.currentMap.y; //y�}�b�v
}

/// <summary>
/// �X�V����
/// </summary>
void Player::update() {
	actionCommand(); //�A�N�V�����R�}���h����

	draw(); //�`�揈��

	knifeUpdate(); //�i�C�t�X�V����
	slashUpdate(); //�n�X�V����
	shieldUpdate(); //�V�[���h�X�V����
	stateUpdate(); //�X�V����

	/*DrawFormatString(0, 450, GetColor(0, 255, 0), "�i�C�t�@�@CDR:%d", cooldown[0], false);
	DrawFormatString(0, 465, GetColor(0, 255, 0), "�@�n�@�@�@CDR:%d", cooldown[1], false);
	DrawFormatString(0, 480, GetColor(0, 255, 0), "�V�[���h�@Value:%d", cooldown[2], shieldAct.value, false);
	DrawFormatString(0, 495, GetColor(0, 255, 0), "�@�����@�@CDR:%d, CDRflag:%d", cooldown[3], cool(3), false);


	DrawFormatString(0, 550, GetColor(255, 100, 100), "�X�^�C��:%d", stateAct.battleStyle, false);
	DrawFormatString(0, 565, GetColor(0x00, 0x8d, 0x56), "�ԖG�K:%d, �R�C��:%d, ���:%d",
	                 PlayerState::attributeAccumulation[0], PlayerState::coin[0], state(0), false);
	DrawFormatString(0, 580, GetColor(0xef, 0xbb, 0x2c), "�[�x�q:%d, �R�C��:%d, ���:%d",
	                 PlayerState::attributeAccumulation[1], PlayerState::coin[1], state(1), false);
	DrawFormatString(0, 595, GetColor(0x4b, 0x5e, 0xaa), "���q��:%d, �R�C��:%d, ���:%d",
	                 PlayerState::attributeAccumulation[2], PlayerState::coin[2], state(2), false);
	DrawFormatString(0, 610, GetColor(0xee, 0x86, 0x9a), "���g��:%d, �R�C��:%d, ���:%d",
	                 PlayerState::attributeAccumulation[3], PlayerState::coin[3], state(3), false);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "mX%d, mY%d", draw_.currentMap.x, draw_.currentMap.y, false);*/

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
