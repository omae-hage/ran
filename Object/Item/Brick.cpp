#include "Brick.h"
#include"DxLib.h"

Brick::Brick()
{
}

Brick::~Brick()
{
}

void Brick::Initialize()
{
	rm = ResourceManager::GetInstance();
	IsDead = false;
	
	animation = rm->GetImages("Resource/Images/Block/block.png", 1, 1, 1, 32, 32);
	image = animation[0];
	DeadSE = rm->GetSounds("Resource/Sounds/SE_BlockBreak.wav");


	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::brick;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::enemy);
	collision.hit_object_type.push_back(eObjectType::item);
	collision.hit_object_type.push_back(eObjectType::item_flower);
	collision.hit_object_type.push_back(eObjectType::special);
	collision.Object_size = (D_OBJECT_SIZE);


	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	mobility = eMobilityType::Stationary;
}

void Brick::Draw(const Vector2D& screen_offset) const
{
	if (player->GetLocation().x - this->GetLocation().x < 330)
	{
		__super::Draw(screen_offset);
	}
}

void Brick::OnHitCollision(GameObjectBase* hit_object)
{
	// 当たり判定情報を取得して、カプセルがある位置を求める
	BoxCollision hc = hit_object->GetCollision();
	hc.Location += hit_object->GetLocation();

	Vector2D diffPoint = ((this->location) - (hc.Location));
	if (hit_object->GetCollision().object_type == eObjectType::player && player->MarioState != SMALL)
	{
		if (diffPoint.y > 0)//下から当たった
		{
			IsDead = true;
			DestroyObject(this);
		}
	}
}

void Brick::Finalize()
{
	PlaySoundMem(DeadSE, DX_PLAYTYPE_BACK);
}
