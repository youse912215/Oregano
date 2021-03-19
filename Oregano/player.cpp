#include "DxLib.h"
#include "player.h"
#include "constant.h"
#include "playerKnife.h"
#include "playerShield.h"
#include "playerSlash.h"
#include "playerState.h"

PlayerKnife knifeAct; //�i�C�t�N���X
PlayerSlash slashAct; //�n�N���X
PlayerShield shieldAct; //�V�[���h�N���X
PlayerState stateAct; //�v���C���[��ԃN���X

Player::Player(Input& input, MapDraw& draw_, DataSource& source) :
	input(input), draw_(draw_), source(source),

	pos(static_cast<int>(WIN_WIDTH / 2 - BLOCK_SIZE / 2), static_cast<int>(WIN_HEIGHT / 2 - BLOCK_SIZE / 2 - 2)),

	cooldown(4), damageFlag(false), center(HALF_BLOCK_SIZE_D + pos),

	knifeCenter(0.0, 0.0), slashCenter(0.0, 0.0),

	actionFlag{false, false, false, false}, cooldownFlag(4) {
}

Player::~Player() {
}

/// <summary>
/// �`�揈��
/// </summary>
void Player::draw() {
	//�e�_���[�W�t���O��false�̂Ƃ�
	if (!(stateAct.poisonDamageFlag || stateAct.roughDamageFlag || damageFlag)) {
		//�ʏ펞�̃v���C���[�摜
		DrawRectGraph(static_cast<int>(this->pos.dx), static_cast<int>(this->pos.dy),
		              BLOCK_SIZE * input.moveDirection, BLOCK_SIZE * PlayerState::battleStyle,
		              BLOCK_SIZE, BLOCK_SIZE,
		              source.player, true, false);
	}
	else {
		//�_���[�W�󂯂��Ƃ��̃v���C���[�摜
		DrawRectGraph(static_cast<int>(this->pos.dx), static_cast<int>(this->pos.dy),
		              BLOCK_SIZE * input.moveDirection, BLOCK_SIZE * PlayerState::battleStyle,
		              BLOCK_SIZE, BLOCK_SIZE,
		              source.playerDamage, true, false);
	}
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

		damageFlag = true; //�_���[�W�t���O��true
		source.playSe(source.seDamage); //�_���[�WSE

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
		knifeAct.calculateRadian(this->pos); //���W�A���v�Z
		knifeAct.draw(source); //�`�揈��
	}
}

/// <summary>
/// �n�X�V����
/// </summary>
void Player::slashUpdate() {
	slashAct.initialize(this->pos); //�n�̏�����
	slashAct.countCooldown(cooldown, cooldownFlag, actionFlag); //�N�[���_�E������

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
	stateAct.conditionUpdate(draw_, source); //��Ԉُ�X�V����
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

	/* �_���[�W�t���O�����Z�b�g */
	damageFlag = false;
	stateAct.resetDamageFlag();

	knifeUpdate(); //�i�C�t�X�V����
	slashUpdate(); //�n�X�V����
	shieldUpdate(); //�V�[���h�X�V����
	stateUpdate(); //��ԍX�V����
}
