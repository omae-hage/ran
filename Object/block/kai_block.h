#pragma once
#include"../GameObject.h"
#include "../../Utility/ResourceManager.h"
#include"../Player/Player.h"

class kai_block : public GameObject
{
public:
	kai_block();
	~kai_block();

public:
	class Player* player;
	ResourceManager* rm;
	std::vector<int> animation;														// アニメーション画像													// アニメーション画像

	virtual void Initialize()override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void OnHitCollision(GameObjectBase* hit_object) override;
	virtual void Finalize() override;
};