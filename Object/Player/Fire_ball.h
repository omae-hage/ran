#pragma once

#include"../GameObject.h"
#include"../../Utility/ResourceManager.h"

class Fire_ball : public GameObject
{

public:

	class ResourceManager* rm;
	//class Player* player;
	std::vector<int> fire_animation;			// チビマリオのアニメーション画像
	std::vector<int> bom_animation;
	Vector2D velocity;
	float IsLeft = 1.0f;
	float g_velocity;
	bool faiya;
	float anime_time;
	int anime_count;

	Fire_ball();
	~Fire_ball();

public:
	virtual void Initialize()override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Update(float delta_second) override;
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

	void Movement();

	void Anim();

};