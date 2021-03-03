#include "enemyConclusion.h"
#include "enemy.h"
#include "effectBlood.h"
#include "effectSpurt.h"

/* �G */
vector<Enemy> enemies(30);

/* ���̃G�t�F�N�g */
EffectBlood blood_;
vector<EffectBlood> bloods_(100);

/* �����o���G�t�F�N�g */
EffectSpurt spurt_;
vector<EffectSpurt> spurts_(150);

EnemyConclusion::EnemyConclusion(Player& player_) : player_(player_) {
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
		//���S���Ԃ̂Ƃ�
		if (i.deadFlag) {
			blood_.update(bloods_, source_, i.screenPos, i.attribute); //���̃G�t�F�N�g
			if (i.deadTime <= 15) spurt_.update(spurts_, i.screenPos); //�����o���i�R�C���j�G�t�F�N�g
		}
	}
}
