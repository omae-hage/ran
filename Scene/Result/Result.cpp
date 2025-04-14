#include "Result.h"
#include"DxLib.h"
#include "../../Utility/ResourceManager.h"


Result::Result() :
IM(nullptr)
{
}

Result::~Result()
{
}

void Result::Initialize()
{
	//インスタンスの読み込み
	IM = InputManager::GetInstance();
	ResourceManager* rm = ResourceManager::GetInstance();

	//画像読み込み
	gameover = rm->GetImages("Resource/Images/gameover.png")[0];

	// スクリーンオフセットを設定
	screen_offset.y = D_OBJECT_SIZE * 3.0f;

	starttime = GetNowCount();
}

eSceneType Result::Update(const float& delta_second)
{
	// 親クラスの更新処理を呼び出す
	__super::Update(delta_second);

	endtime = GetNowCount() - starttime;

	if (endtime >= 5000)
	{
		return eSceneType::eTitle;
	}

	return GetNowSceneType();

}

void Result::Draw() const
{

	//親クラスのDrawを呼び出す。
	__super::Draw();

	DrawRotaGraph(320, 260, 1.5, 0.0, gameover, TRUE);
	
}

void Result::Finalize()
{
	// 親クラスの終了時処理を呼び出す
	__super::Finalize();
}

const eSceneType Result::GetNowSceneType() const
{
	return eSceneType::eResult;
}