#include "TitleScene.h"
#include"DxLib.h"


#include "../../Object/Player/Player.h"
#include "../../Utility/ResourceManager.h"


TitleScene::TitleScene()
	: IM(nullptr)
	, back_ground_image(NULL)
	, back_ground_sound(NULL)
	, select(TitleSelect::NEXT_STAGE)
	, end_flg(false)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	//インスタンスの読み込み
	IM = InputManager::GetInstance();
	ResourceManager* rm = ResourceManager::GetInstance();

	// スクリーンオフセットを設定
	screen_offset.y = D_OBJECT_SIZE * 3.0f;

	// 背景画像の読み込み
	back_ground_image = LoadGraph("Resource/Images/title.png");
	// BGMの読み込み;

}

eSceneType TitleScene::Update(const float& delta_second)
{

	if (IM->GetKeyDown(KEY_INPUT_DOWN))
	{
		if (select == TitleSelect::EXIT)
		{
			select = TitleSelect::NEXT_STAGE;
		}
		else
		{
		select = TitleSelect::EXIT;
		}
	}
	if (IM->GetKeyDown(KEY_INPUT_UP))
	{
		if (select == TitleSelect::NEXT_STAGE)
		{
			select = TitleSelect::EXIT;
		}
		else
		{
			select = TitleSelect::NEXT_STAGE;
		}
	}
	if (IM->GetKeyDown(KEY_INPUT_RETURN))
	{
		if (select == TitleSelect::EXIT)
		{
			end_flg = true;
		}
		else {

			return eSceneType::eInGame;
		}
	}


	return eSceneType::eTitle;
	// 親クラスの更新処理を呼び出す
	__super::Update(delta_second);
}

void TitleScene::Draw() const
{

	//親クラスのDrawを呼び出す。
	__super::Draw();

	//背景(title)_仮置き
	DrawGraph(0, 0, back_ground_image, false);


	switch (select)
	{
	case NEXT_STAGE:
	DrawString(DRAW_SET_X - 15, DRAW_SET_Y - 2,	 "→",			WHITE);
	DrawString(DRAW_SET_X,		DRAW_SET_Y,		 "・スタート",  WHITE);
	DrawString(DRAW_SET_X,		DRAW_SET_Y + 50, "・終了",		BLACK);
		break;
	case EXIT:
	DrawString(DRAW_SET_X - 15, DRAW_SET_Y + 48, "→",			WHITE);
	DrawString(DRAW_SET_X,		DRAW_SET_Y,		 "・スタート",  BLACK);
	DrawString(DRAW_SET_X,		DRAW_SET_Y + 50, "・終了",		WHITE);
		break;
	}

}

void TitleScene::Finalize()
{
	// 親クラスの終了時処理を呼び出す
	__super::Finalize();
}

const eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}

bool TitleScene::GetEndFlag()
{
	return end_flg;
}
