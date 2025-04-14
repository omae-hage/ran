#pragma once
#include"../GameObject.h"
#include "../../Utility/ResourceManager.h"
#include"../Player/Player.h"

class blackblock : public GameObject
{
public:
	blackblock();
	~blackblock();

public:
	class Player* player;
	ResourceManager* rm;
	std::vector<int> animation;														// アニメーション画像

	virtual void Initialize()override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void OnHitCollision(GameObjectBase* hit_object) override;
	virtual void Finalize() override;
};