#pragma once

#include"../GameObject.h"
#include"../../Utility/ResourceManager.h"

class BigMash : public GameObject
{

public:

	class ResourceManager* rm;
	std::vector<int> mash_animation;			// チビマリオのアニメーション画像

	Vector2D velocity;
	float IsLeft = 1.0f;
	BigMash();
	~BigMash();

public:
	virtual void Initialize()override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Update(float delta_second) override;
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

};