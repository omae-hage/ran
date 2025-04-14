#include "BOXCollision.h"

bool BoxCollision::IsCheckHitTarget(eObjectType hit_object) const
{
	// 適用するオブジェクトタイプなら、true
	for (eObjectType type : hit_object_type)
	{

		if (type == hit_object)
		{
			return true;
		}
	}

	return false;
}

//bool IsCheckCollision(const BoxCollision& c1, const BoxCollision& c2)
//{
//
//	//x 100 y 50
//	//
//	//100,50				100+Dobject_size,Dobject_size
//	//100,50+Dobject_size	100+Dobject_size,Dobject_size*2
//	/*//ライムはバカ　←　重要な要素					go*/
//
//
//	Vector2D diff1 = c1.Location;
//	Vector2D diff2 = c2.Location;
//
//	Vector2D diff_line = diff1 - diff2;
//
//	Vector2D Box_sizeDiff =( c1.Object_size + c2.Object_size)/2.0f;
//
//	if ((fabsf(diff_line.x) < Box_sizeDiff.x) && (fabsf(diff_line.y) < Box_sizeDiff.y))
//	{
//		return true;
//	}
//	return false;
//}

bool IsCheckCollision(const BoxCollision& c1, const BoxCollision& c2)
{
	// 矩形の境界を計算
	Vector2D c1Min = c1.Location - (c1.Object_size / 2.0f);
	Vector2D c1Max = c1.Location + (c1.Object_size / 2.0f);

	Vector2D c2Min = c2.Location - (c2.Object_size / 2.0f);
	Vector2D c2Max = c2.Location + (c2.Object_size / 2.0f);

	// 矩形の軸に沿って交差判定を行う (AABB - Axis-Aligned Bounding Box 判定)
	bool isOverlappingX = (c1Min.x <= c2Max.x) && (c1Max.x >= c2Min.x);
	bool isOverlappingY = (c1Min.y <= c2Max.y) && (c1Max.y >= c2Min.y);

	return isOverlappingX && isOverlappingY;
}

/// <summary>
/// 点と矩形の最近傍点を求める処理
/// </summary>
/// <param name="cap">カプセルの情報</param>
/// <param name="point">矩形の中心点</param>
//矩形のサイズ cap.Object_size(幅と高さ)
/// <returns>最近傍点</returns>
Vector2D NearPointCheck(const BoxCollision& rect, const Vector2D& point)
{
	// 矩形の最小・最大の境界を計算
	Vector2D minBound = rect.Location - (rect.Object_size / 2.0f);
	Vector2D maxBound = rect.Location + (rect.Object_size / 2.0f);

	// 点を矩形の境界内にクランプ
	Vector2D closestPoint;
	closestPoint.x = std::max(minBound.x, std::min(point.x, maxBound.x));
	closestPoint.y = std::max(minBound.y, std::min(point.y, maxBound.y));

	// クランプ結果が入力点とほぼ一致する場合、補正を行わない
	const float epsilon = 0.05f; // 許容する微小な範囲
	if (fabsf(closestPoint.x - point.x) < epsilon && fabsf(closestPoint.y - point.y) < epsilon)
	{
		return point; // 位置補正不要
	}

	return closestPoint;
}