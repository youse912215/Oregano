#pragma once
#include "mapDraw.h"
#include <vector>

class PlayerState {
private:
	int poisonTime; //猛毒時間
	int roughTime; //凸凹時間
	const int attributeMax; //最大耐久値
	const int timeMax; //最大時間
	const int cooldownMax; //最大クールダウン
	const int poisonDamage; //猛毒によるダメージ(減少コイン量)
	const int roughDamage; //凸凹によるダメージ(減少コイン量)
	const int eliminateCoin; //解消必要コイン

	void getStateAbnormal(); //状態異常を取得
	void getFloorState(MapDraw& draw_); //床上での状態を取得
	void countStateTime(); //猛毒時間をカウント
	void continuousDamage(const int& time, const int& value); //継続ダメージを付与

public:
	vector<bool> stateAbnormal; //状態異常（0:猛毒、1:痙攣、2:混乱、3:出血）
	vector<int> attributeAccumulation; //属性耐久値
	vector<int> coin; //コイン（HP、攻撃の役割）

	/*（0:花萌葱(対猛毒), 1:深支子(対痙攣), 2:燕子花(対混乱), 3:中紅花(対出血)）*/
	int battleStyle; //戦闘スタイル(0~3)

	void changeBattleStyle(const int& dir); //戦闘スタイルを切り替える

	void switchStyleAutomatically(); //現在の戦闘スタイルを変更
	void calculateValue(const int& attribute, const int& attributeValue); //属性蓄積値の計算
	void valueReset(bool& elimination, vector<bool>& cooldownFlag); //属性耐久値等のリセット
	void countCooldown(vector<int>& cooldown, vector<bool>& cooldownFlag); //状態のクールダウン処理
	void stateAbnormalUpdate(MapDraw& draw_); //状態異常更新処理

	PlayerState();
};
