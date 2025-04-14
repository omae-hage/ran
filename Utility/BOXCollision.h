#pragma once

#define D_ApplyRectangleHitDetection
#define D_OBJECT_SIZE (32.0f)

#include "Vector2D.h"
#include <vector>

// オブジェクトタイプ
enum class eObjectType : unsigned char
{
	none,
	player,
	enemy,
	block,
	brick,
	item,
	item_flower,
	special,
	goal,
	ball,
	dokan,
	coin
};

//矩形の当たり判定クラス
class BoxCollision
{
public:
	bool						is_blocking;		// すり抜けフラグ
	eObjectType					object_type;		// 自身のオブジェクトタイプ
	std::vector<eObjectType>	hit_object_type;	// 適用するオブジェクトタイプ
	Vector2D					Object_size;		// 矩形のサイズ
	Vector2D					Location;				// 始点と終点（相対座標）

public:
	BoxCollision() :
		is_blocking(false),
		object_type(eObjectType::none),
		hit_object_type(),
		Object_size (Vector2D(D_OBJECT_SIZE, D_OBJECT_SIZE))
	{
		Location = { (0.0f),(0.0f)};
	}
	~BoxCollision()
	{
		hit_object_type.clear();
	}
	// 当たり判定有効確認処理
	 bool IsCheckHitTarget(eObjectType hit_object) const;
};

bool IsCheckCollision(const BoxCollision& c1, const BoxCollision& c2);

Vector2D NearPointCheck(const BoxCollision& cap, const Vector2D& point);
