#include "KEnemy.h"

KEnemy::KEnemy()
{
}

KEnemy::~KEnemy()
{
}

void KEnemy::Initialize()
{
	rm = ResourceManager::GetInstance();
	IsDead = false;
	move_animation = rm->GetImages("Resource/Images/Enemy/Kuribo.png", 3, 3, 1, 32, 32);
	image = move_animation[0];
	DeadSE = rm->GetSounds("Resource/Sounds/SE_StepOn.wav");

	IsLeft = -1.0f;

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::block);
	collision.hit_object_type.push_back(eObjectType::brick);
	collision.hit_object_type.push_back(eObjectType::dokan);
	collision.hit_object_type.push_back(eObjectType::ball);
	collision.Object_size = (D_OBJECT_SIZE - 1.0f);


	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	mobility = eMobilityType::Movable;
}

void KEnemy::Draw(const Vector2D& screen_offset) const
{
	if (player->GetLocation().x - this->GetLocation().x < 330)
	{
		__super::Draw(screen_offset);
	}
}

void KEnemy::Update(float delta_second)
{
	if (player->GetLocation().x - this->GetLocation().x < 330)
	{
		__super::Update(delta_second);
		if (player->animnow != true)
		{
			location.y += 0.098f;
			Moveanim();
			//location.x += 0.2f * IsLeft;
			if (IsDead == false)
			{
				location.x += 0.05f * IsLeft;
			}
		}
	}
}

void KEnemy::OnHitCollision(GameObjectBase* hit_object)
{
	// 当たり判定情報を取得して、カプセルがある位置を求める
	BoxCollision hc = hit_object->GetCollision();
	hc.Location += hit_object->GetLocation();

	Vector2D diffPoint = ((this->location) - (hc.Location));
	if (hit_object->GetCollision().object_type == eObjectType::block || hit_object->GetCollision().object_type == eObjectType::dokan)
	{
		//if ((fabs(diffPoint.x) > fabs(diffPoint.y)))
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
			}
		}
		else
		{

			if ((diffPoint.y < D_OBJECT_SIZE))
			{
				diffPoint += D_OBJECT_SIZE;
				location.y -= diffPoint.y;
			}
			else
			{
				diffPoint -= D_OBJECT_SIZE;
				location.y += diffPoint.y;
			}
		}
	}
	else if (hit_object->GetCollision().object_type == eObjectType::player)
	{
		if (diffPoint.y > 0)//上から踏んだか
		{
			image = move_animation[2];
			IsDead = true;
			anim_count = 0;
			PlaySoundMem(DeadSE, DX_PLAYTYPE_BACK);

		}
		else//踏んでない
		{
			//...念の為置いておくけど、恐らく内容ほぼないので削除予定
		}
	}
	else if (hit_object->GetCollision().object_type == eObjectType::enemy)
	{
		if (hit_object->getinvincible())
		{
			IsDead = true;
			image = move_animation[2];
		}
		else
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
	}
	if (hit_object->GetCollision().object_type == eObjectType::ball)
	{
		DestroyObject(this);
	}
}

void KEnemy::Finalize()
{

}

void KEnemy::Moveanim()
{
	anim_count += 1.0f;
	if (anim_count > 30.0f)
	{
		anim_count = 0.0f;
		anim_time++;
	}
	if (anim_time > 5 && image != move_animation[2])
	{

		if (image == move_animation[0])
		{
			image = move_animation[1];
		}
		else
		{
			image = move_animation[0];
		}
		anim_time = NULL;
	}
	else if (anim_time > 6 && image == move_animation[2])
	{
		DestroyObject(this);
	}
}
