#include "star_Box.h"
#include"star.h"


star_Box::star_Box()
{
}

star_Box::~star_Box()
{
}

void star_Box::Initialize()
{
	anim_box = 0;
	rm = ResourceManager::GetInstance();
	IsDead = false;

	animation = rm->GetImages("Resource/Images/Block/hatena.png", 4, 4, 1, 32, 32);
	EndImage = rm->GetImages("Resource/Images/Block/kara_block.png", 1, 1, 1, 32, 32);
	image = animation[0];
	DeadSE = rm->GetSounds("Resource/Sounds/SE_Block.wav");


	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::brick;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::enemy);
	collision.hit_object_type.push_back(eObjectType::item);
	collision.hit_object_type.push_back(eObjectType::item_flower);
	collision.Object_size = (D_OBJECT_SIZE);


	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	mobility = eMobilityType::Movable;
}

void star_Box::Draw(const Vector2D& screen_offset) const
{
	if (player->GetLocation().x - this->GetLocation().x < 330)
	{
		__super::Draw(screen_offset);
	}
}

void star_Box::Update(float delta_second)
{
	if (player->GetLocation().x - this->GetLocation().x < 330)
	{
		if (IsEnd == false)
		{
			Animation();
		}
	}
}

void star_Box::OnHitCollision(GameObjectBase* hit_object)
{
	// 当たり判定情報を取得して、カプセルがある位置を求める
	BoxCollision hc = hit_object->GetCollision();
	hc.Location += hit_object->GetLocation();

	Vector2D diffPoint = ((this->location) - (hc.Location));
	if (hit_object->GetCollision().object_type == eObjectType::player)
	{
		if (diffPoint.y < 0 && IsEnd == false)//下から当たった
		{
			IsEnd = true;
			image = EndImage[0];
			if (InStar)
			{
				CreateItem();
			}
		}
	}
}

void star_Box::Finalize()
{
}

void star_Box::CreateItem()
{
	star* SR;

	SR = CreateObject<star>(0);
	SR->SetLocation(Vector2D(this->location.x, this->location.y - D_OBJECT_SIZE));

}


void star_Box::Animation()
{
	anim_count += 1.0f;
	if (anim_count > 60.0f)
	{
		anim_count = 0;
		anim_time++;
	}
	if (anim_time > 3)
	{

		anim_time = 0;
		anim_box++;
		if (anim_box > 3)
		{
			anim_box = 0;
		}
		image = animation[anim_box];
	}
}