#include "Fire_ball.h"
#include"Player.h"

#define D_GRAVITY (100.807f) 


Fire_ball::Fire_ball()
{
}

Fire_ball::~Fire_ball()
{

}

void Fire_ball::Initialize()
{
	// アニメーション画像の読み込み
	rm = ResourceManager::GetInstance();
	fire_animation = rm->GetImages("Resource/Images/Mario/fireball.png", 1, 1, 1, 32, 32);
	bom_animation = rm->GetImages("Resource/Images/bakuha.png", 3, 3, 1, 32, 32);

	velocity = -1.0f;

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::ball;
	collision.hit_object_type.push_back(eObjectType::enemy);
	collision.hit_object_type.push_back(eObjectType::block);
	collision.hit_object_type.push_back(eObjectType::brick);
	collision.hit_object_type.push_back(eObjectType::item_flower);
	collision.hit_object_type.push_back(eObjectType::special);
	collision.Object_size = (D_OBJECT_SIZE - 1.0f);


	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	mobility = eMobilityType::Movable;

	//location = Vector2D(200.0f, 200.0f);

	image = fire_animation[0];

	anime_time += 1.0f;
	
}

void Fire_ball::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);


}

void Fire_ball::Update(float delta_second)
{
	//移動領分だけ位置をずらす
	location += velocity * delta_second;

	//重力加速度の計算
	g_velocity += D_GRAVITY / 400.0f;
	velocity.y += g_velocity;
	

	Movement();
	Anim();

}

void Fire_ball::OnHitCollision(GameObjectBase* hit_object)
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
		velocity.y -= 150.0f;
	}

	if (hit_object->GetCollision().object_type != eObjectType::block)
	{
		image = bom_animation[2];
		
		if (image = bom_animation[2])
		{
			DestroyObject(this);
		}
			
		
		
		
	}

}

void Fire_ball::Movement()
{
	Vector2D velocity = 0.0f;

	if (faiya == 1)
	{
		velocity.x += 3.0f;
		velocity.y += 2.8f;
	}

	if (faiya == 0)
	{
		velocity.x -= 3.0f;
		velocity.y += 2.8f;
	}
	
	
	location += velocity;


}

void Fire_ball::Anim()
{
	//anime_time += 1.0f;
	//if (anime_time > 5.0f)
	//{
	//	anime_time = 0.0f;
	//	anime_count++;

	//	if (image == bom_animation[0])
	//	{
	//		image = bom_animation[1];
	//	}
	//	else if (image == bom_animation[1])
	//	{
	//		image = bom_animation[2];
	//		

	//	
	//	}
	//	if (image == bom_animation[2])//わからんくなったからねる
	//	{
	//		DestroyObject(this);

	//	}
	//}
	
	
}
