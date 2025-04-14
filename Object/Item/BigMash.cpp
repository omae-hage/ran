#include "BigMash.h"

BigMash::BigMash()
{
}

BigMash::~BigMash()
{

}

void BigMash::Initialize()
{
	// アニメーション画像の読み込み
	rm = ResourceManager::GetInstance();
	mash_animation = rm->GetImages("Resource/Images/Item/mushroom.png", 1,1, 1, 32, 32);

	velocity = -1.0f;

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::item;
	collision.hit_object_type.push_back(eObjectType::enemy);
	collision.hit_object_type.push_back(eObjectType::block);
	collision.hit_object_type.push_back(eObjectType::brick);
	collision.hit_object_type.push_back(eObjectType::player);
	collision.Object_size = (D_OBJECT_SIZE - 1.0f);


	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	mobility = eMobilityType::Movable;

	//location = Vector2D(200.0f, 200.0f);

	image = mash_animation[0];
}

void BigMash::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void BigMash::Update(float delta_second)
{

	location.y += 0.98f;
	location.x += 0.3f * IsLeft;

}

void BigMash::OnHitCollision(GameObjectBase* hit_object)
{// 当たり判定情報を取得して、カプセルがある位置を求める
	BoxCollision hc = hit_object->GetCollision();
	hc.Location += hit_object->GetLocation();

	Vector2D diffPoint = ((this->location) - (hc.Location));
	if (hit_object->GetCollision().object_type == eObjectType::block || hit_object->GetCollision().object_type == eObjectType::brick)
	{
		if ((diffPoint.x > D_OBJECT_SIZE) || -diffPoint.x > D_OBJECT_SIZE)
		{
			if ((diffPoint.x < D_OBJECT_SIZE))
			{
				diffPoint += D_OBJECT_SIZE;
				location.x -= diffPoint.x;
				IsLeft = -1.0f;
			}
			else
			{
				diffPoint -= D_OBJECT_SIZE;
				location.x += diffPoint.x;
				IsLeft = 1.0f;
			}
		}
		else
		{
			if ((diffPoint.y < D_OBJECT_SIZE))
			{
				diffPoint += D_OBJECT_SIZE;
				location.y -= diffPoint.y;
			}
			else if (-diffPoint.y < D_OBJECT_SIZE)
			{
				diffPoint -= D_OBJECT_SIZE;
				location.y += diffPoint.y;
			}
		}
	}	
	if (hit_object->GetCollision().object_type == eObjectType::player)
	{
		DestroyObject(this);
	}

}
