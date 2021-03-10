#pragma once

class DataSource {
private:

protected:
	int actionUI; //アクションUI画像ファイルの読み込み

public:
	int enemyGraph;
	int player; //プレイヤー
	int playerDamage; //プレイヤーダメージ
	int mapChip; //マップチップ
	int knifeGraph; //ナイフ
	int slashGraph; //刃
	int shieldGraph; //シールド
	int red; //赤色の血
	int blue; //青色の血
	int green; //緑色の血
	int yellow; //黄色の血
	int blurGraph1; //ぼかし1
	int blurGraph2; //ぼかし2
	int enemyLife; //敵のライフ
	int coinGraph; //コインUI
	int conditionGraph; //状態UI
	int passiveGraph; //パッシブUI
	int menuGraph; //メニューUI
	int actionGraph; //アクションUI
	int filterGraph1; //アクション以外のフィルターUI
	int filterGraph2; //アクションのフィルターUI
	int shieldGauge; //シールドゲージ
	int eventGraph; //イベントUI
	int title; //タイトル画面
	int menu; //メニュー画面
	int gameover; //ゲームオーバー画面
	int clear; //クリア画面
	int event1; //イベント画面1
	int event2; //イベント画面2
	int event3; //イベント画面3
	int titleStart; //タイトルボタン文字
	int deviceChange1; //デバイス切替文字1
	int deviceChange2; //デバイス切替文字2
	int gameOverEnd; //ゲームオーバーボタン文字

	DataSource();
	~DataSource();
};
