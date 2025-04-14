#include "NEnemy.h"
#include "DxLib.h"


int wakeup_count;

NEnemy::NEnemy()
{
}

NEnemy::~NEnemy()
{
}

void NEnemy::Initialize()
{
	rm = ResourceManager::GetInstance();
	IsDead = false;
	IsDown = false;
	move_animation = rm->GetImages("Resource/Images/Enemy/nokonoko.png", 2, 2, 1, 32, 64);
	down_animation = rm->GetImages("Resource/Images/Enemy/nokonoko_revival.png", 2, 2, 1, 32, 32);
	image = move_animation[0];
	DeadSE = rm->GetSounds("Resource/Sounds/SE_StepOn.wav");

	IsLeft = -1.0f;

	NowState = DEFAULT;

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);	
	collision.hit_object_type.push_back(eObjectType::enemy);
	collision.hit_object_type.push_back(eObjectType::block);
	collision.hit_object_type.push_back(eObjectType::brick);
	collision.Object_size = Vector2D(D_OBJECT_SIZE - 1.0f,64.0f);

	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	mobility = eMobilityType::Movable;
}

void NEnemy::Draw(const Vector2D& screen_offset) const
{
	if (player->GetLocation().x - this->GetLocation().x < 330)
	{
		__super::Draw(screen_offset);
	}
}

void NEnemy::Update(float delta_second)
{
	if (player->GetLocation().x - this->GetLocation().x < 330)
	{
		__super::Update(delta_second);
		if (player->animnow != true)
		{
			location.y += 0.098f;
			Moveanim();
			switch (NowState)
			{
			case DEFAULT:
				location.x += 0.01f * IsLeft;
				break;
			case DOWN:
				break;
			case SPIN:
				location.x += Velocity.x;
				break;
			default:
				break;
			}
		}
	}
}

void NEnemy::OnHitCollision(GameObjectBase* hit_object)
{
	// 当たり判定情報を取得して、カプセルがある位置を求める
	BoxCollision hc = hit_object->GetCollision();
	hc.Location += hit_object->GetLocation();

	Vector2D diffPoint = ((this->location) - (hc.Location));
	if (hit_object->GetCollision().object_type == eObjectType::block || hit_object->GetCollision().object_type == eObjectType::dokan)
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
			if ((diffPoint.y < 0))
			{
				if (image == down_animation[0] || image == down_animation[1])
				{
					diffPoint += D_OBJECT_SIZE;
				}
				else {
					diffPoint += D_OBJECT_SIZE * 1.5f;
				}
				location.y -= diffPoint.y;
			}
		}
	}
	else if (hit_object->GetCollision().object_type == eObjectType::player)
	{
		if (diffPoint.x > 0 && NowState == DOWN)
		{
			Velocity.x = 1.0f;
			NowState = SPIN;
			invincible = true;
		}
		else if (diffPoint.x < 0 && NowState == DOWN)
		{
			Velocity.x = -1.0f;
			NowState = SPIN;
			invincible = true;
		}


		if (diffPoint.y > 0&& NowState != DOWN)//上から踏んだか
		{
			image = down_animation[0]; 
			NowState = DOWN;
			anim_count = 0;
			collision.Object_size.y = D_OBJECT_SIZE;
			IsDead = true;
		}
		else//踏んでない
		{
			//...念の為置いておくけど、恐らく内容ほぼないので削除予定
		}
	}
	else if (hit_object->GetCollision().object_type == eObjectType::enemy)
	{
		if (hit_object->IsDead)
		{

		}
		else if (hit_object->getinvincible())
		{
			IsDead = true;
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
}

void NEnemy::Finalize()
{
}

void NEnemy::Moveanim()
{
	anim_count += 1.0f;
	if (anim_count > 60.0f)
	{
		anim_count = 0.0f;
		anim_time++;
	}
	if (anim_time > 5)
	{
		anim_time = NULL;

		if (NowState == DEFAULT)
		{
			if (image == move_animation[0])
			{
				image = move_animation[1];
			}
			else
			{
				image = move_animation[0];
			}
		}
		else
		{
			if (NowState == SPIN)
			{
				image = down_animation[0];

			}
			else if (image == down_animation[0])
			{
				image = down_animation[1];
			}
			else
			{
				image = down_animation[0];
				wakeup_count++;
				anim_time = 30;

				if (wakeup_count > 8 && NowState != SPIN)
				{
					IsDead = false;
					NowState = DEFAULT;
					collision.Object_size.y = D_OBJECT_SIZE * 2.0f;
					wakeup_count = 0;
				}
			}
		}
	}
}