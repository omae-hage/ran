#include "star.h"
#include"DxLib.h"

#define D_GRAVITY (100.807f) 

star::star()
{
}

star::~star()
{

}

void star::Initialize()
{
	// アニメーション画像の読み込み
	rm = ResourceManager::GetInstance();
	star_animation = rm->GetImages("Resource/Images/Item/star.png", 4, 4, 1, 32, 32);

	velocity = Vector2D(0.0f);
	g_velocity = 0.0f;

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::item;
	collision.hit_object_type.push_back(eObjectType::enemy);
	collision.hit_object_type.push_back(eObjectType::block);
	collision.hit_object_type.push_back(eObjectType::brick);
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::item_flower);
	collision.Object_size = (D_OBJECT_SIZE - 1.0f);


	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	mobility = eMobilityType::Movable;

	//location = Vector2D(200.0f, 200.0f);

	image = star_animation[0];
}

void star::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);

}

void star::Update(float delta_second)
{

	//移動領分だけ位置をずらす
	location += velocity * delta_second;

	//重力加速度の計算
	g_velocity += D_GRAVITY / 400.0f;
	velocity.y += g_velocity;
	

	Movement();


	Animation();
	



}

void star::OnHitCollision(GameObjectBase* hit_object)
{// 当たり判定情報を取得して、カプセルがある位置を求める
	// 当たり判定情報を取得して、カプセルがある位置を求める
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
	if (hit_object->GetCollision().object_type == eObjectType::block)
	{
		g_velocity = 0.0f;
		velocity.y -= 500.0f;
		
	}

	if (hit_object->GetCollision().object_type == eObjectType::player)
	{
		DestroyObject(this);
	}

}

void star::Animation()
{
	anime_time += 1.0f;
	if (anime_time > 10.0f)
	{
		anime_time = 0.0f;
		anime_count++;

		if (image == star_animation[0])
		{
			image = star_animation[1];
		}
		else if (image == star_animation[1])
		{
			image = star_animation[2];
		}
		else if (image == star_animation[2])
		{
			image = star_animation[3];
		}

		else if (image == star_animation[3])
		{
			image = star_animation[0];
		}

	}
}

void star::Movement()
{
	Vector2D velocity = 0.0f;

	velocity.x += 1.0f;
	velocity.y -= 2.8f;

	location += velocity;
}
