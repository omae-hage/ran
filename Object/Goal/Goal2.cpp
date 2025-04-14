#include "Goal2.h"
#include"DxLib.h"

Goal2::Goal2()
{
}

Goal2::~Goal2()
{

}

void Goal2::Initialize()
{
	// アニメーション画像の読み込み
	rm = ResourceManager::GetInstance();	
	image = rm->GetImages("Resource/Images/pole.png", 1, 1, 1, 32, 32)[0];



	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::goal;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.Object_size = (D_OBJECT_SIZE - 1.0f);


	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	mobility = eMobilityType::Stationary;

}

void Goal2::Draw(const Vector2D& screen_offset) const
{

	__super::Draw(screen_offset);

}

void Goal2::OnHitCollision(GameObjectBase* hit_object)
{// 当たり判定情報を取得して、カプセルがある位置を求める
	BoxCollision hc = hit_object->GetCollision();
	hc.Location += hit_object->GetLocation();

	Vector2D diffPoint = ((this->location) - (hc.Location));

	if (hit_object->GetCollision().object_type == eObjectType::player)
	{
		DrawString(200, 100, "ゴールしたかも？", 0xFFFFFF);
	}

}
