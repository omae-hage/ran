#pragma once
#include"../GameObject.h"
#include "../../Utility/ResourceManager.h"
#include"../Player/Player.h"

class Brick  : public GameObject
{
public:
	Brick();
	~Brick();

public:
	ResourceManager* rm;
	std::vector<int> animation;														// アニメーション画像
	int DeadSE;														// アニメーション画像

	virtual void Initialize()override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void OnHitCollision(GameObjectBase* hit_object) override;
	virtual void Finalize() override;
};