#pragma once

#include"EnemyBase.h"

enum NokonokoState
{
	DEFAULT,
	DOWN,
	SPIN
};

class NEnemy : public EnemyBase
{
public:

	std::vector<int> down_animation;		//	アニメーション画像

	NEnemy();
	~NEnemy();

	NokonokoState NowState;

	bool IsDown;
	Vector2D Velocity;

public:
	virtual void Initialize()override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Update(float delta_second) override;
	virtual void OnHitCollision(GameObjectBase* hit_object) override;
	virtual void Finalize() override;

	void Moveanim();
};