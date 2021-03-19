#include "enemyConclusion.h"
#include "enemy.h"
#include "effectBlood.h"
#include "effectSpurt.h"

/* �G */
vector<Enemy> enemies(20);

/* ���̃G�t�F�N�g */
EffectBlood blood_; //���G�t�F�N�g�N���X
vector<EffectBlood> bloods_(50);

/* �����o���G�t�F�N�g */
EffectSpurt spurt_; //�����o���G�t�F�N�g�N���X
vector<EffectSpurt> spurts_(100);

EnemyConclusion::EnemyConclusion(Player& player_, DataSource& source_) :
	player_(player_), source_(source_), showTime(20) {
}

/// <summary>
/// �X�V����
/// </summary>
void EnemyConclusion::update() {
	/* �G�̕��� */
	for (auto& i : enemies) {
		//�������Ă��Ȃ����A���S���ԂłȂ��Ƃ�
		if (!i.activity && !i.deadFlag) {
			i.initialize(player_); //������
		}
		i.update(player_, source_); //�X�V����

		//�v���C���[����_���[�W���󂯂��Ƃ�
		if (i.intervalFlag[KNIFE] || i.intervalFlag[SLASH])
			blood_.update(bloods_, source_, i.screenPos, i.attribute); //���̃G�t�F�N�g

		//���S���Ԃ̂Ƃ�
		if (!(i.deadFlag && i.deadTime <= showTime)) continue; //�����ȊO�̂Ƃ��A�������X�L�b�v����
		spurt_.update(spurts_, i.screenPos); //�����o���i�R�C���j�G�t�F�N�g
	}
}
