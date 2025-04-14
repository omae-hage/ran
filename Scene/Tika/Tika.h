#pragma once

#include "../SceneBase.h"
#include "../../Object/Player/Player.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/FileManager.h"
#include "../../Utility/StringManager.h"
#include"../../Utility/ResourceManager.h"
#include"../../Utility/Vector2D.h"

class Tika : public SceneBase
{
private:

	class Player* player;		// プレイヤー情報
	class tika_floor* block_tika;
	class blackblock* hanya;
	bool pause_flag;			// 一時停止フラグ
	class InputManager* IM;		//入力インスタンス
	class FileManager* FM;		//
	class StringManager* SM;	//	
	int loadline;
	bool FileEnd;


	int screen;
	int count_set = 0;
	std::string hige;
	std::string T1;
	std::string T2;
	std::string T3;
	char set_object;
	int time;
	int world;
	int one;
	int coin;
	int score;
	int	lives;
	int kazu;
	int sann;
	int yonn;

public:
	Tika();
	virtual ~Tika();
	ResourceManager* rm;
	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;
	/*virtual void Draw(const Vector2D& screen_offset) const override;*/

	// 現在のシーンタイプ情報を取得する
	virtual const eSceneType GetNowSceneType() const override;

	/// <summary>
	/// 当たり判定確認処理
	/// </summary>
	/// <param name="target">1つ目のゲームオブジェクト</param>
	/// <param name="partner">2つ目のゲームオブジェクト</param>
	virtual void CheckCollision(GameObjectBase* target, GameObjectBase* partner) override;


protected:
	Vector2D			location;		// 位置座標



private:
	void SetStartMapObject();
	void SetMapObject();



};


