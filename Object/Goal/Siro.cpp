#include "Siro.h"
#include"DxLib.h"

Siro::Siro()
{

}

Siro::~Siro()
{

}

void Siro::Initialize()
{
	// アニメーション画像の読み込み
	rm = ResourceManager::GetInstance();	
	image = rm->GetImages("Resource/Images/siro1.png", 1, 1, 1, 32, 32)[0];

	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	mobility = eMobilityType::Stationary;

}

void Siro::Draw(const Vector2D& screen_offset) const
{

	__super::Draw(screen_offset);

}
