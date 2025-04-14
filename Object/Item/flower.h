#pragma once
#include"../GameObject.h"
#include"../../Utility/ResourceManager.h"

class flower : public GameObject
{

public:

	class ResourceManager* rm;
	std::vector<int> flower_animation;			// 
	float anime_time;
	int anime_count;

	flower();
	~flower();

public:
	virtual void Initialize()override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Update(float delta_second) override;
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

	void Animation();

};