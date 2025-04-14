#pragma once

#include "../SceneBase.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/EnemyBase.h"
#include"../../Object/block/kai_block.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/FileManager.h"
#include "../../Utility/StringManager.h"
#include"../../Utility/ResourceManager.h"
#include"../../Utility/Vector2D.h"
#include"../../Stage/Mountain.h"

class Game : public SceneBase
{
private:

	class Brick* brick;
	class ItemBox* itembox;
	class EnemyBase* enemy;
	class Mountain* mountain;
	class Block* block;			// 地面情報
	class Player* player;		// プレイヤー情報
	class Goal* goal;           //　ゴールの情報
	class kai_block* kai;
	int back_ground_image;		// 背景画像
	int back_ground_sound;		// BGM
	bool pause_flag;			// 一時停止フラグ
	class InputManager* IM;		//入力インスタンス
	class FileManager* FM;		//
	class StringManager* SM;	//
	float ScRoll;				//スクリーンバック数	
	std::vector<Block*>	Block_obj;	// 生成を行うオブジェクトリスト
	int loadline;
	bool FileEnd;
	int time;
	int world;
	int one;
	int coin;
	int score;
	int	lives;
	int kazuu;
	int sann;
	int yonn;

	int scof;
	int kazu = 0;
	std::string hage;
	std::string R1;
	std::string R2;
	std::string R3;
	char Set_OB;

public:
	Game();
	virtual ~Game();
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


