#pragma once
#include"../GameObject.h"
#include "../../Utility/ResourceManager.h"
#include"../Player/Player.h"

class yokodokan1 : public GameObject
{
public:
	yokodokan1();
	~yokodokan1();

public:
	class Player* player;
	ResourceManager* rm;


	virtual void Initialize()override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void OnHitCollision(GameObjectBase* hit_object) override;
	virtual void Finalize() override;
};
