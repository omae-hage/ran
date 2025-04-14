#pragma once
#include"../GameObject.h"
#include "../../Utility/ResourceManager.h"
#include"../Player/Player.h"

class ItemBox : public GameObject
{
public:
	ItemBox();
	~ItemBox();

public:

	int anim_box;
	float anim_count;
	int anim_time;
	ResourceManager* rm;
	std::vector<int> animation;			
	std::vector<int> EndImage;
	int DeadSE;														// アニメーション画像
	bool IsEnd;
	bool InBox;
	bool InCoin;
	Vector2D Now_screen_offset;

	virtual void Initialize()override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Update(float delta_second) override;
	virtual void OnHitCollision(GameObjectBase* hit_object) override;
	virtual void Finalize() override;

	void CreateItem();
	void Animation();
	void CreateCoin();
};