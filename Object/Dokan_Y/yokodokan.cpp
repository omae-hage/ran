#include "yokodokan.h"
#include"DxLib.h"

yokodokan::yokodokan()
{
}

yokodokan::~yokodokan()
{
}

void yokodokan::Initialize()
{
	rm = ResourceManager::GetInstance();
	IsDead = false;

	image = rm->GetImages("Resource/Images/yokodokan_left_down.png", 1, 1, 1, 32, 32)[0];



	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::dokan;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::enemy);
	collision.Object_size = (D_OBJECT_SIZE);


	// レイヤーの設定
	z_layer = 10;

	mobility = eMobilityType::Stationary;
}

void yokodokan::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void yokodokan::OnHitCollision(GameObjectBase* hit_object)
{
	// 当たり判定情報を取得して、カプセルがある位置を求める
	BoxCollision hc = hit_object->GetCollision();
	hc.Location += hit_object->GetLocation();

	Vector2D diffPoint = ((this->location) - (hc.Location));
}

void yokodokan::Finalize()
{

}
