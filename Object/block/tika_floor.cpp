#include "tika_floor.h"
#include"DxLib.h"

tika_floor::tika_floor()
{
}

tika_floor::~tika_floor()
{
}

void tika_floor::Initialize()
{
	rm = ResourceManager::GetInstance();
	IsDead = false;

	animation = rm->GetImages("Resource/Images/Block/tika_floor.png", 1, 1, 1, 32, 32);
	image = animation[0];


	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::brick;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.Object_size = (D_OBJECT_SIZE);


	// レイヤーの設定
	z_layer = 5;

	mobility = eMobilityType::Stationary;
}

void tika_floor::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void tika_floor::OnHitCollision(GameObjectBase* hit_object)
{
	// 当たり判定情報を取得して、カプセルがある位置を求める
	BoxCollision hc = hit_object->GetCollision();
	hc.Location += hit_object->GetLocation();

	Vector2D diffPoint = ((this->location) - (hc.Location));
}

void tika_floor::Finalize()
{

}
