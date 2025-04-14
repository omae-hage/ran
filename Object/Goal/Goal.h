#pragma once

#include"../GameObject.h"
#include"../../Utility/ResourceManager.h"

class Goal : public GameObject
{

public:

	class ResourceManager* rm;
	/*int image_Goal;	*/	// 
	Vector2D velocity;
	float IsLeft = 1.0f;
	Goal();
	~Goal();

public:
	virtual void Initialize()override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

};