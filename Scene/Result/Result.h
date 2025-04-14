#pragma once

#include "../SceneBase.h"

#include"../../Utility/InputManager.h"

class Result : public SceneBase
{
private:
	int font[25];
	InputManager* IM;
	int gameover;
	int starttime;
	int endtime;
public:
	//コンストラクタ
	Result();
	//デストラクタ
	virtual ~Result();

	//初期化処理
	virtual void Initialize() override;

	//更新処理
	//引数：１フレーム当たりの時間
	//戻り値：次のシーンタイプ
	virtual eSceneType Update(const float& delta_second) override;

	//描画処理
	virtual void Draw() const override;

	//終了時処理
	virtual void Finalize() override;

	// 現在のシーンタイプ情報を取得する
	virtual const eSceneType GetNowSceneType() const override;

};

