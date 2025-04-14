#pragma once

#include"EnemyBase.h"
#include"DxLib.h"

class KEnemy : public EnemyBase
{
public:
	KEnemy();
	~KEnemy();

public:
	virtual void Initialize()override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Update(float delta_second) override;
	virtual void OnHitCollision(GameObjectBase* hit_object) override;
	virtual void Finalize() override;

	void Moveanim();
};

