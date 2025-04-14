#pragma once

#include"../GameObject.h"
#include"../../Utility/ResourceManager.h"

class Coin : public GameObject
{

public:

	class ResourceManager* rm;
	std::vector<int> Coin_animation;			// チビマリオのアニメーション画像

	Vector2D velocity;
	
	float anime_time;
	int anime_count;
	float g_velocity;
	int coin;

	Coin();
	~Coin();

public:
	virtual void Initialize()override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Update(float delta_second) override;
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

	void Animation();
	void Movement();

};