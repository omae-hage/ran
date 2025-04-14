#include "blackblock.h"
#include"DxLib.h"

blackblock::blackblock()
{
}

blackblock::~blackblock()
{
}

void blackblock::Initialize()
{
	rm = ResourceManager::GetInstance();
	IsDead = false;

	animation = rm->GetImages("Resource/Images/Block/blackblock.png", 1, 1, 1, 32, 32);
	image = animation[0];
	

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::block;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.Object_size = (D_OBJECT_SIZE);


	// 可動性の設定
	mobility = eMobilityType::Stationary;
}

void blackblock::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}


void blackblock::OnHitCollision(GameObjectBase* hit_object)
{
	// 当たり判定情報を取得して、カプセルがある位置を求める
	BoxCollision hc = hit_object->GetCollision();
	hc.Location += hit_object->GetLocation();

	Vector2D diffPoint = ((this->location) - (hc.Location));
}

void blackblock::Finalize()
{
	
}
