#pragma once

#include"../GameObject.h"
#include "../../Scene/SceneBase.h"
#include <vector>

enum eMarioState :unsigned char
{
	DEATH,
	SMALL,
	TOLL,
	FIRE,
	STAR,
};

enum eDirectionState :unsigned char
{
	NONE,
	RIGHT,
	LEFT,
	JUMP,
	CROUCH,
};

class Player : public GameObject
{
public:
	std::vector<int> Mario_animation;			// チビマリオのアニメーション画像
	std::vector<int> dekaMario_animation;
	std::vector<int> fiyaMario_animation;
	std::vector<int> Mario_Bigger_animation;
	std::vector<int> dying_animation;		// 死亡のアニメーション画像
	Vector2D velocity;						// 移動量
	float animation_time;					// アニメーション時間
	int animation_count;					// アニメーション添字
	float jumpHigh;
	bool IsJump;
	bool HighJump;
	bool animnow = false;
	bool Isleft = false;
	int	 Life;
	int fire;
	int Big;
	class Fire_ball* fire_ball;


	eMarioState old_MarioState;				// 古いマリオの状態
	eMarioState MarioState;					// マリオの状態
	eDirectionState MoveState;				// マリオの行動状態

	float Dash_time;					// アニメーション時間
	int	  Dash_count;					// アニメーション

public:
	Player();
	virtual ~Player();

public:
	virtual void Initialize()override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Update(float delta_second) override;
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

	void ShotFire();
	void animation();
	void Tollanimation();
	void Fireanimation();
	void MarioBiggerStep();
	bool GetDeath() const;

	/*eDirectionState GetPlayerDirection() const;*/


};