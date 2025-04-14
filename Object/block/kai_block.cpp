#include "kai_block.h"
#include"DxLib.h"

kai_block::kai_block()
{
}

kai_block::~kai_block()
{
}

void kai_block::Initialize()
{
	rm = ResourceManager::GetInstance();
	IsDead = false;

	animation = rm->GetImages("Resource/Images/Block/kai_block.png", 1, 1, 1, 32, 32);
	image = animation[0];


	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::block;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.Object_size = (D_OBJECT_SIZE);


	// レイヤーの設定
	z_layer = 5;

	mobility = eMobilityType::Stationary;
}

void kai_block::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void kai_block::OnHitCollision(GameObjectBase* hit_object)
{
	// 当たり判定情報を取得して、カプセルがある位置を求める
	BoxCollision hc = hit_object->GetCollision();
	hc.Location += hit_object->GetLocation();

	Vector2D diffPoint = ((this->location) - (hc.Location));
}

void kai_block::Finalize()
{
	
}
