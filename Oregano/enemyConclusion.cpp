#include "enemyConclusion.h"
#include "enemy.h"
#include "effectBlood.h"
#include "effectSpurt.h"

/* 敵 */
vector<Enemy> enemies(20);

/* 血のエフェクト */
EffectBlood blood_; //血エフェクトクラス
vector<EffectBlood> bloods_(50);

/* 噴き出しエフェクト */
EffectSpurt spurt_; //噴き出しエフェクトクラス
vector<EffectSpurt> spurts_(100);

EnemyConclusion::EnemyConclusion(Player& player_, DataSource& source_) :
	player_(player_), source_(source_), showTime(20) {
}

/// <summary>
/// 更新処理
/// </summary>
void EnemyConclusion::update() {
	/* 敵の複製 */
	for (auto& i : enemies) {
		//生存していないかつ、死亡時間でないとき
		if (!i.activity && !i.deadFlag) {
			i.initialize(player_); //初期化
		}
		i.update(player_, source_); //更新処理

		//プレイヤーからダメージを受けたとき
		if (i.intervalFlag[KNIFE] || i.intervalFlag[SLASH])
			blood_.update(bloods_, source_, i.screenPos, i.attribute); //血のエフェクト

		//死亡時間のとき
		if (!(i.deadFlag && i.deadTime <= showTime)) continue; //条件以外のとき、処理をスキップする
		spurt_.update(spurts_, i.screenPos); //噴き出し（コイン）エフェクト
	}
}
