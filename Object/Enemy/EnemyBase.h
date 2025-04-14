#pragma once

#include "../GameObject.h"
#include"../Player/Player.h"
#include "../../Utility/ResourceManager.h"


class EnemyBase : public GameObject
{
public:
	
	class Player* player;
	class ResourceManager* rm;				//	リソースマネージャーのインスタンス
	std::vector<int> move_animation;		//	アニメーション画像
	std::vector<int> dying_animation;		//	死亡のアニメーション画像

	float IsLeft;


	float anim_count;						//フレーム換算
	int anim_time;							//実時間換算
	int DeadSE;
};