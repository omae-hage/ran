#include "tika_Coin.h"
#include "../../Utility/Vector2D.h"
#include "DxLib.h"


tika_Coin::tika_Coin() : anime_time(), anime_count(), coin(NULL)
{
}

tika_Coin::~tika_Coin()
{

}

void tika_Coin::Initialize()
{

	// アニメーション画像の読み込み
	rm = ResourceManager::GetInstance();
	Coin_animation = rm->GetImages("Resource/Images/Item/mukidasitika_coin.png", 4, 4, 1, 32, 32);
	coin = rm->GetSounds("Resource/Sounds/SE_CoinPickUp.wav");

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::coin;
	collision.hit_object_type.push_back(eObjectType::block);
	collision.hit_object_type.push_back(eObjectType::brick);
	collision.hit_object_type.push_back(eObjectType::player);
	collision.Object_size = (D_OBJECT_SIZE - 1.0f);

	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	mobility = eMobilityType::Stationary;

	//location = Vector2D(200.0f, 200.0f);
	image = Coin_animation[0];
}

void tika_Coin::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void tika_Coin::Update(float delta_second)
{

	Animation();
	/*location.y -= 0.98f;*/
}

void tika_Coin::OnHitCollision(GameObjectBase* hit_object)
{// 当たり判定情報を取得して、カプセルがある位置を求める
	BoxCollision hc = hit_object->GetCollision();
	hc.Location += hit_object->GetLocation();

	Vector2D diffPoint = ((this->location) - (hc.Location));

	if (hit_object->GetCollision().object_type == eObjectType::player)
	{
		PlaySoundMem(coin, DX_PLAYTYPE_BACK);
		DestroyObject(this);
	}
}

void tika_Coin::Animation()
{
	anime_time += 1.0f;
	if (anime_time > 10.0f)
	{
		anime_time = 0.0f;
		anime_count++;

		if (image == Coin_animation[0])
		{
			image = Coin_animation[1];
		}
		else if (image == Coin_animation[1])
		{
			image = Coin_animation[2];
		}
		else if (image == Coin_animation[2])
		{
			image = Coin_animation[3];
		}

		else if (image == Coin_animation[3])
		{
			image = Coin_animation[0];
		}
	}
}
