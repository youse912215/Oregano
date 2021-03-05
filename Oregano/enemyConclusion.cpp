#include "enemyConclusion.h"
#include "enemy.h"
#include "effectBlood.h"
#include "effectSpurt.h"

/* �G */
vector<Enemy> enemies(1);

/* ���̃G�t�F�N�g */
EffectBlood blood_;
vector<EffectBlood> bloods_(100);

/* �����o���G�t�F�N�g */
EffectSpurt spurt_;
vector<EffectSpurt> spurts_(150);

EnemyConclusion::EnemyConclusion(Player& player_) : player_(player_), showTime(15) {
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
		if (i.deadFlag && i.deadTime <= showTime)
			spurt_.update(spurts_, i.screenPos); //�����o���i�R�C���j�G�t�F�N�g
	}
}
