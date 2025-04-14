#pragma once

#include "../Utility/BOXCollision.h"

#define D_OBJECT_SIZE (32.0f)

//可動性の種類
enum eMobilityType
{
	Stationary,		//固定
	Movable,		//可動
};

class GameObjectBase
{

protected:
	class SceneBase* owner_scene;	// 所有するシーン情報
	Vector2D			location;		// 位置座標
	BoxCollision	collision;		// 当たり判定情報

	int					image;			// 画像情報
	int					z_layer;		// レイヤー情報
	eMobilityType		mobility;		// 可動性
public:
	GameObjectBase();
	virtual ~GameObjectBase();

	bool				IsDead;			//死亡したどうか

	bool invincible = false;


	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Initialize();
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	virtual void Update(float delta_second);
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="screen_offset">オフセット値</param>
	virtual void Draw(const Vector2D& screen_offset) const;
	/// <summary>
	/// 終了時処理
	/// </summary>
	virtual void Finalize();

	/// <param name="screen_offset">オフセット値</param>
	virtual void wow(const Vector2D& screen_offset) const;
	/// <summary>
public:
	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObjectBase* hit_object);

	virtual bool getinvincible();


public:
	/// <summary>
	/// 所有シーン情報の設定
	/// </summary>
	/// <param name="scene">所有シーン情報</param>
	void SetOwnerScene(class SceneBase* scene);

	/// <summary>
	/// 位置座標取得処理
	/// </summary>
	/// <returns>位置座標情報</returns>
	const Vector2D& GetLocation() const;

	/// <summary>
	/// 位置情報変更処理
	/// </summary>
	/// <param name="location">変更したい位置情報</param>
	void SetLocation(const Vector2D& location);

#ifdef D_ApplyRectangleHitDetection
	/// <summary>
	/// 当たり判定取得処理
	/// </summary>
	/// <returns>当たり判定情報</returns>
	BoxCollision GetCollision() const;
#else
	/// <summary>
	/// 当たり判定取得処理
	/// </summary>
	/// <returns>当たり判定情報</returns>
	CapsuleCollision GetCollision() const;
#endif
	/// <summary>
	/// Ｚレイヤー情報取得処理
	/// </summary>
	/// <returns>Ｚレイヤー情報</returns>
	const int GetZLayer() const;

	/// <summary>
	/// 可動性情報の取得処理
	/// </summary>
	/// <returns>可動性情報</returns>
	const eMobilityType GetMobility() const;

	const Vector2D GetObjectSize();

};
