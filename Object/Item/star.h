#pragma once

#include"../GameObject.h"
#include"../../Utility/ResourceManager.h"

class star : public GameObject
{

public:

	class ResourceManager* rm;
	std::vector<int> star_animation;			// ÉXÉ^Å[ÇÃâÊëú

	Vector2D velocity;
	float IsLeft = 1.0f;
	float g_velocity;

	float anime_time;
	int anime_count;

	star();
	~star();

public:
	virtual void Initialize()override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Update(float delta_second) override;
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

	void Animation();
	void Movement();

};