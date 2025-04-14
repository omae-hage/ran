#include "Player.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/InputManager.h"
#include"Fire_ball.h"
#include "DxLib.h"

#include <math.h>

#define GRAVITY 98.0f* delta_second			//重力加速度
#define FRICTION 0.0f			//ある程度を丸め込む
#define RUN_SPEED 2.0f
#define MAX_RUN_SPEED 20.0f
#define WALK_SPEED 1.0f
#define MAX_WALK_SPEED 10.0f

Player::Player():
dying_animation()
,velocity(0.0f)
,animation_time(0.0f)
,animation_count(0)
,IsJump(true)
,HighJump(false)
,Life(3)
,fire(NULL)
,Big(NULL)
{

}

Player::~Player()
{
}


void Player::Initialize()
{
	// アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	Mario_animation = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);
	dekaMario_animation = rm->GetImages("Resource/Images/Mario/dekamario.png", 10, 10, 1, 32, 64);
	fiyaMario_animation = rm->GetImages("Resource/Images/Mario/faiyamario.png", 9, 9, 1, 32, 64);

	Mario_Bigger_animation = rm->GetImages("Resource/Images/Mario/dekamarimation.png", 3, 3, 1, 32, 64);
	fire = rm->GetSounds("Resource/Sounds/SE_FireBall.wav");
	Big = rm->GetSounds("Resource/Sounds/SE_PowerUp.wav");
	velocity = 0.0f;

	

	MarioState = SMALL;
	old_MarioState = MarioState;

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::player;
	collision.hit_object_type.push_back(eObjectType::enemy);
	collision.hit_object_type.push_back(eObjectType::block);
	collision.hit_object_type.push_back(eObjectType::brick);
	collision.hit_object_type.push_back(eObjectType::item);
	collision.hit_object_type.push_back(eObjectType::item_flower);
	collision.hit_object_type.push_back(eObjectType::special);
	collision.hit_object_type.push_back(eObjectType::dokan); 
	collision.Object_size = (D_OBJECT_SIZE - 1.0f);


	// レイヤーの設定
	z_layer = 6;

	// 可動性の設定
	mobility = eMobilityType::Movable;
	
	image = Mario_animation[0];
}

void Player::Draw(const Vector2D& screen_offset) const
{
		Vector2D graph_location = this->location + screen_offset;
		DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, true , Isleft);
#ifdef _DEBUG
		Vector2D size = this->collision.Object_size;
		DrawBoxAA(location.x + screen_offset.x - size.x / 2, location.y + screen_offset.y - size.y / 2, location.x + screen_offset.x + size.x / 2, location.y + screen_offset.y + size.y / 2, GetColor(255, 0, 0), false);
		DrawCircleAA(location.x + screen_offset.x, location.y + screen_offset.y, 2,4, GetColor(255, 255, 0));

#endif

}

void Player::Update(float delta_second)
{
	InputManager* IM = InputManager::GetInstance();
	Fire_ball* FL;//これもテスト

	if (MarioState == eMarioState::FIRE)
	{
		//ファイヤーの弾を出す
		if (IM->GetKeyDown(KEY_INPUT_Q))
		{
			PlaySoundMem(fire, DX_PLAYTYPE_BACK);
			FL = CreateObject<Fire_ball>(Vector2D(location.x, location.y));
			FL->SetLocation(Vector2D(this->location.x, this->location.y - D_OBJECT_SIZE));

			if (Isleft == false)
			{
				FL->faiya = 1;
			}

			if (Isleft == true)
			{
				FL->faiya = 0;
			}

		}
	}
	
	//ここまで

	if (animnow)
	{
		MarioBiggerStep();

		if (image == Mario_Bigger_animation[2])
		{
			image = dekaMario_animation[0];
			animnow = false;
		}
	}

	
	else
	{
			old_MarioState = MarioState;
			//アニメーション
			switch (MarioState)
			{
			case SMALL:
				animation();
				break;
			case TOLL:
				Tollanimation();
				break;
			case FIRE:
				Fireanimation();
				break;
			case STAR:
				break;
			case DEATH:
				//作ったけど．．．いるかこれ？
				break;
			default:
				break;
		}
	}

	velocity.x += RUN_SPEED * delta_second;
       if (velocity.x > MAX_RUN_SPEED)
		{
			velocity.x = MAX_RUN_SPEED;
		}

		//if (IM->GetKey(KEY_INPUT_RIGHT) && IM->GetKey(KEY_INPUT_LSHIFT))
		//{
		//	velocity.x += RUN_SPEED * delta_second;
		//	if (velocity.x > MAX_RUN_SPEED)
		//	{
		//		velocity.x = MAX_RUN_SPEED;
		//	}

		//	Isleft = false;
		///*}*/
		//else if (IM->GetKey(KEY_INPUT_LEFT) && IM->GetKey(KEY_INPUT_LSHIFT))
		//{
		//	velocity.x -= RUN_SPEED * delta_second;
		//	if (velocity.x < -MAX_RUN_SPEED)
		//	{
		//		velocity.x = -MAX_RUN_SPEED;
		//	}
		//	

		//	MoveState = LEFT;
		//}
		//else if (IM->GetKey(KEY_INPUT_RIGHT))
		//{
		//	velocity.x += WALK_SPEED * delta_second;
		//	if (velocity.x > MAX_WALK_SPEED)
		//	{
		//		velocity.x = MAX_WALK_SPEED;
		//	}

		//	
		//	Isleft = false;
		//}
		//else if (IM->GetKey(KEY_INPUT_LEFT))
		//{
		//	velocity.x -= WALK_SPEED * delta_second;
		//	if (velocity.x < -MAX_WALK_SPEED)
		//	{
		//		velocity.x = -MAX_WALK_SPEED;
		//	}
		//	Isleft = true;
		//	MoveState = LEFT;
		//}
		//else if (IM->GetKey(KEY_INPUT_DOWN) && MarioState == TOLL)
		//{
		//	//
		//	MoveState = CROUCH;
		//}
		//else if (IM->GetKey(KEY_INPUT_RETURN) && MarioState == FIRE)
		//{
		//	ShotFire();
		//}
		//else if (IM->GetKey(KEY_INPUT_B))
		//{
		//	image = Mario_Bigger_animation[0];
		//	this->collision.Object_size = Vector2D(D_OBJECT_SIZE, 64.0f);
		//	MarioState = TOLL;

		//	MarioBiggerStep();
		//}
		else
		{
			MoveState = NONE;
		}

		if (IM->GetKey(KEY_INPUT_SPACE))
		{
			float Diff;
			if (HighJump == false)
			{
				switch (IsJump)
				{
				case(true):
					jumpHigh = location.y - D_OBJECT_SIZE * 4;
					Diff = -(location.y - jumpHigh) / 100;
					velocity.y += -200.0f * delta_second;
					IsJump = false;
					break;
				case(false):

					if (jumpHigh > location.y)
					{
						HighJump = true;
					}
					break;
				}
			}
		}
		if (IM->GetKeyUp(KEY_INPUT_SPACE))
		{
			HighJump = true;
		}

	if (velocity.x != 0.0f || velocity.y != 0.0f)
	{

		location += velocity;

		if (velocity.x > 0.0f)
		{
			velocity.x -= velocity.x/100;

			if (velocity.x < FRICTION)
			{
				velocity.x = 0.0f;
			}
		}
		else if(velocity.x < 0.0f)
		{
			velocity.x += -velocity.x / 100;

			if ( velocity.x > -FRICTION)
			{
				velocity.x = 0.0f;
			}
		}
		if (HighJump)
		{
			if (velocity.y != 0.0f)
			{
				velocity.y = GRAVITY;
			}
		}

	}
	if (GetDeath())
	{
		Life = Life - 1;
		MarioState = SMALL;
	}
	
}

//炎を吐きだす。
void Player::ShotFire()
{
	CreateObject<Fire_ball>(Vector2D(location.x, location.y));
}

//チビ状態のアニメーション
void Player::animation()
{
	animation_time += 1.0f;
	if (animation_time > 60.0f)
	{
		animation_time = 0.0f;
		animation_count++;

		if (velocity.x == 0)
		{
			image = Mario_animation[0];
		}
		else
		{
			if (image == Mario_animation[0])
			{
				image = Mario_animation[1];
			}
			else if (image == Mario_animation[1])
			{
				image = Mario_animation[2];
			}
			else if (image == Mario_animation[2])
			{
				image = Mario_animation[1];
			}
		}
	}
}

//デカ状態のアニメーション
void Player::Tollanimation()
{
	animation_time += 1.0f;
	if (animation_time > 60.0f)
	{
		animation_time = 0.0f;
		animation_count++;

		if (velocity.x == 0)
		{
			image = dekaMario_animation[0];
		}
		else
		{
			if (image == dekaMario_animation[0])
			{
				image = dekaMario_animation[2];
			}
			else if (image == dekaMario_animation[2])
			{
				image = dekaMario_animation[3];
			}
			else if (image == dekaMario_animation[3])
			{
				image = dekaMario_animation[2];
			}
		}
	}
}

//ファイヤー状態のアニメーション
void Player::Fireanimation()
{
	animation_time += 1.0f;
	if (animation_time > 60.0f)
	{
		animation_time = 0.0f;
		animation_count++;

		if (velocity.x == 0)
		{
			image = fiyaMario_animation[0];
		}
		else
		{
			if (image == fiyaMario_animation[0])
			{
				image = fiyaMario_animation[2];
			}
			else if (image == fiyaMario_animation[2])
			{
				image = fiyaMario_animation[3];
			}
			else if (image == fiyaMario_animation[3])
			{
				image = fiyaMario_animation[2];
			}
		}
	}
}


void Player::MarioBiggerStep()
{
	animnow = true;
	animation_time += 1.0f;
	if (animation_time > 60.0f)
	{
		animation_time = 0.0f;
		animation_count++;
		if (image == Mario_Bigger_animation[0])
		{
			image = Mario_Bigger_animation[1];
		}
		else if (image == Mario_Bigger_animation[1])
		{
			image = Mario_Bigger_animation[0];
		}
	}
	if (animation_count > 5)
	{
		{
			if (image == Mario_Bigger_animation[1])
			{
				image = Mario_Bigger_animation[2];
				animnow = false;
			}
		}
	}
}

bool Player::GetDeath() const
{
	return IsDead;
}

/// <summary>
/// 当たり判定通知処理
/// </summary>
/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
void Player::OnHitCollision(GameObjectBase* hit_object)
{
	// 当たり判定情報を取得して、カプセルがある位置を求める
	BoxCollision hc = hit_object->GetCollision();
	hc.Location += hit_object->GetLocation();

	Vector2D diffPoint = ((this->location) - (hc.Location));
	if (hit_object->GetCollision().object_type == eObjectType::block || hit_object->GetCollision().object_type == eObjectType::brick || hit_object->GetCollision().object_type == eObjectType::dokan || hit_object->GetCollision().object_type == eObjectType::goal)
	{
		//if ((fabs(diffPoint.x) > fabs(diffPoint.y)))
		if ((diffPoint.x > D_OBJECT_SIZE) || -diffPoint.x > D_OBJECT_SIZE)
		{
			if ((diffPoint.x > 0))
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
		{
			if (MarioState == TOLL || MarioState == FIRE)
			{
				diffPoint += D_OBJECT_SIZE * 1.5f;
				location.y -= diffPoint.y;

				HighJump = false;
				IsJump = true;
			}
			else if ((diffPoint.y > 0))
			{
				diffPoint -= D_OBJECT_SIZE;
				location.y -= diffPoint.y;
			}
			else
			{
				diffPoint += D_OBJECT_SIZE;
				location.y -= diffPoint.y;

				HighJump = false;
				IsJump = true;
			}
		}
	}

	// 当たったオブジェクトが敵だったら
	else if (hit_object->GetCollision().object_type == eObjectType::enemy)
	{
		
		 if (diffPoint.y < 0 && diffPoint.x > diffPoint.y)//上から踏んだか
		{
			velocity.y += -3.0f;
		}
		 else if (hit_object->IsDead == true)
		{
			//相手が当たり判定を放棄してる場合(何も起きない)
		}
		
		else//踏んでない
		{
			if (MarioState == SMALL)
			{
				MarioState = DEATH;
				IsDead = true;
			}
			//else if (MarioState == STAR)
			//{
			//	//敵側での処理を描くため特に記載なし(敵を倒した処理へ飛んで大丈夫だと思われる。)
			//	return;
			//}
			else if (MarioState == TOLL)
			{
				MarioState = SMALL;
			}
			//理解しやすく"if"を記述(処理文を書き次第ifを撤去)
			else if (MarioState == FIRE)
			{
			}
		}
	}
	// 当たったオブジェクトがキノコだったら
	if (hit_object->GetCollision().object_type == eObjectType::item)
	{
		PlaySoundMem(Big, DX_PLAYTYPE_BACK);
		image = Mario_Bigger_animation[0];
		this->collision.Object_size = Vector2D(D_OBJECT_SIZE, 64.0f);
		MarioState = TOLL;

		MarioBiggerStep();
	}

	//ファイヤーフラワーとったら
	if (hit_object->GetCollision().object_type == eObjectType::item_flower)
	{
		image = fiyaMario_animation[0];
		this->collision.Object_size = Vector2D(D_OBJECT_SIZE, 64.0f);
		MarioState = FIRE;

		
	}
}

