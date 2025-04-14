#include "flower.h"


flower::flower(): anime_time(), anime_count()
{
}

flower::~flower()
{

}

void flower::Initialize()
{
	// アニメーション画像の読み込み
	rm = ResourceManager::GetInstance();
	flower_animation = rm->GetImages("Resource/Images/Item/flower.png", 4, 4, 1, 32, 32);

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::item_flower;
	collision.hit_object_type.push_back(eObjectType::block);
	collision.hit_object_type.push_back(eObjectType::player);
	collision.Object_size = (D_OBJECT_SIZE - 1.0f);


	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	mobility = eMobilityType::Stationary;

	image = flower_animation[0];

}

void flower::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);

}

void flower::Update(float delta_second)
{
	Animation();

}

void flower::OnHitCollision(GameObjectBase* hit_object)
{// 当たり判定情報を取得して、カプセルがある位置を求める
	BoxCollision hc = hit_object->GetCollision();
	hc.Location += hit_object->GetLocation();

	Vector2D diffPoint = ((this->location) - (hc.Location));

	

	if (hit_object->GetCollision().object_type == eObjectType::player)
	{
		DestroyObject(this);
		
	}

}

void flower::Animation()
{
	anime_time += 1.0f;
	if (anime_time > 30.0f)
	{
		anime_time = 0.0f;
		anime_count++;

			if (image == flower_animation[0])
			{
				image = flower_animation[1];
			}
			else if (image == flower_animation[1])
			{
				image = flower_animation[2];
			}
			else if (image == flower_animation[2])
			{
				image = flower_animation[3];
			}

			else if (image == flower_animation[3])
			{
				image = flower_animation[0];
			}
		
	}
}