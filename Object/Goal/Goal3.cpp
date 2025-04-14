#include "Goal3.h"
#include"DxLib.h"

Goal3::Goal3()
{
}

Goal3::~Goal3()
{

}

void Goal3::Initialize()
{
	// アニメーション画像の読み込み
	rm = ResourceManager::GetInstance();	
	image = rm->GetImages("Resource/Images/flag.png", 1, 1, 1, 32, 32)[0];

	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	mobility = eMobilityType::Stationary;

	
}

void Goal3::Draw(const Vector2D& screen_offset) const
{

	__super::Draw(screen_offset);

}


