#include "enemyConclusion.h"

void EnemyConclusion::enemyProcess(vector<Enemy*> enemies) {
	for (unsigned int i = 0; i != enemies.size(); ++i)
		if (enemies[i] == nullptr) { return; }


}
