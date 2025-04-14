#pragma once
#include "../SceneBase.h"

#include"../../Utility/InputManager.h"

#define DRAW_SET_X 200
#define DRAW_SET_Y 300

#define WHITE 0xFFFFFF
#define BLACK 0x000000


enum TitleSelect {
	NEXT_STAGE,
	EXIT,
};

class TitleScene : public SceneBase
{


private:
	int back_ground_image;		// 背景画像
	int back_ground_sound;		// BGM
	TitleSelect select;
	bool end_flg;
	InputManager* IM ;

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// 現在のシーンタイプ情報を取得する
	virtual const eSceneType GetNowSceneType() const override;

	virtual bool GetEndFlag() override;

};