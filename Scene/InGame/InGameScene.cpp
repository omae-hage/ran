#include "InGameScene.h"
#include "../../Utility/ResourceManager.h"
#include "../../Stage/Block.h"
#include "../../Utility/ProjectConfig.h"
#include "../../Object/Enemy/KEnemy.h"
#include "../../Object/Enemy/NEnemy.h"
#include"../../Object/Item/BigMash.h"
#include"../../Object/Item/Brick.h"
#include"../../Object/Item/ItemBox.h"
#include"../../Utility/Vector2D.h"
#include"../../Stage/Mountain.h"
#include"../../Stage/Kumo.h"
#include"../../Stage/Kumo2.h"
#include"../../Stage/Kumo3.h"
#include"../../Object/Goal/Goal.h"
#include"../../Object/Item/star_Box.h"
#include"../../Stage/Kusa.h"
#include"../../Stage/Kusa1.h"
#include"../../Stage/Kusa2.h" 
#include"../../Object/Item/tika_Coin.h"
#include"../../Stage/Timer.h"
#include"../../Object/Dokan/dokan.h"
#include"../../Object/Dokan/dokan1.h"
#include"../../Object/Dokan/dokan2.h"
#include"../../Object/Dokan/dokan3.h"
#include "DxLib.h"




int ScreenOffset;
int count = 0;
std::string Banana;
std::string P1;
std::string P2;
std::string P3;
char SetObject;

int SetLocation_X;
int SetLocation_Y ;

InGameScene::InGameScene() 
	: player(nullptr)
	, back_ground_image(NULL)
	, back_ground_sound(NULL)
	, pause_flag(false)
	, loadline(0)
	, FileEnd(false)
	, SM(nullptr)
	, ScRoll(NULL)
	, rm(nullptr)
	, mountain(nullptr)
	, mash(nullptr)
	, itembox(nullptr)
	, IM(nullptr)
	, enemy(nullptr)
	, brick(nullptr)
	, block(nullptr)
	, goal(nullptr)
	,Star(nullptr)
	,kai(nullptr)
	, Star_Box(nullptr)
	,lived(3)
	, BGM(NULL)
	
{
	backgroundX = 0;
	backgroundY = 0;
	
}

InGameScene::~InGameScene()
{
	
}

void InGameScene::Initialize()
{

	rm = ResourceManager::GetInstance();
	SM = StringManager::GetInstance();
	FM = FileManager::GetInstance();
	
	
	player = CreateObject<Player>(0);
	CreateObject<Mountain>(Vector2D(80.0f,278.0f));
	CreateObject<Mountain>(Vector2D(550.0f, 315.0f));
	CreateObject<Mountain>(Vector2D(1600.0f, 278.0f));
	CreateObject<Mountain>(Vector2D(2080.0f, 315.0f));
	CreateObject<Mountain>(Vector2D(3200.0f, 278.0f));
	CreateObject<Mountain>(Vector2D(3780.0f, 315.0f));
	CreateObject<Mountain>(Vector2D(4650.0f, 278.0f));
	CreateObject<Mountain>(Vector2D(5150.0f, 315.0f));
	CreateObject<Mountain>(Vector2D(5150.0f, 315.0f));
	CreateObject<Kumo>(Vector2D(400.0f, 60.0f));
	CreateObject<Kumo>(Vector2D(700.0f, 20.0f));
	CreateObject<Kumo3>(Vector2D(940.0f, 60.0f));
	CreateObject<Kumo2>(Vector2D(1200.0f, 20.0f));
	CreateObject<Kumo>(Vector2D(1950.0f, 60.0f));
	CreateObject<Kumo>(Vector2D(2200.0f, 20.0f));
	CreateObject<Kumo3>(Vector2D(2480.0f, 60.0f));
	CreateObject<Kumo2>(Vector2D(2760.0f, 20.0f));
	CreateObject<Kumo>(Vector2D(3000.0f, 20.0f));
	CreateObject<Kumo3>(Vector2D(3780.0f, 60.0f));
	CreateObject<Kumo2>(Vector2D(4060.0f, 20.0f));
	CreateObject<Kumo2>(Vector2D(4540.0f, 60.0f));
	CreateObject<Kumo3>(Vector2D(4800.0f, 60.0f));
	CreateObject<Kumo>(Vector2D(5080.0f, 20.0f));
	CreateObject<Kumo3>(Vector2D(5200.0f, 60.0f));
	CreateObject<Kumo>(Vector2D(5650.0f, 20.0f));
	CreateObject<Kusa>(Vector2D(360.0f, 297.0f));
	CreateObject<Kusa1>(Vector2D(1000.0f, 315.0f));
	CreateObject<Kusa2>(Vector2D(1400.0f, 320.0f));
	CreateObject<Kusa>(Vector2D(1800.0f, 297.0f));
	CreateObject<Kusa1>(Vector2D(2180.0f, 315.0f));
	CreateObject<Kusa2>(Vector2D(2700.0f, 320.0f));
	CreateObject<Kusa>(Vector2D(3000.0f, 297.0f));
	CreateObject<Kusa1>(Vector2D(3400.0f, 315.0f));
	CreateObject<Kusa2>(Vector2D(4200.0f, 320.0f));
	CreateObject<Kusa>(Vector2D(4800.0f, 297.0f));
	CreateObject<Kusa1>(Vector2D(5400.0f, 315.0f));
	CreateObject<Kusa2>(Vector2D(5600.0f, 320.0f));
	

	SetStartMapObject();
	SetMapObject();


	// C   X ^   X ̓ǂݍ   
	IM = InputManager::GetInstance();
	ResourceManager* rm = ResourceManager::GetInstance();

	//  X N   [   I t Z b g  ݒ 
	screen_offset.y = D_OBJECT_SIZE * 3.0f;



	//  w i 摜 ̓ǂݍ   
	back_ground_image = LoadGraph("Resource/Images/sora.png");
	time = LoadGraph("Resource/Images/UI/time.png");
	world = LoadGraph("Resource/Images/UI/world.png");
	one = LoadGraph("Resource/Images/UI/1-1.png");
	coin = LoadGraph("Resource/Images/UI/coin.png");
	score = LoadGraph("Resource/Images/UI/score.png");
	lives = LoadGraph("Resource/Images/UI/lives.png");
	kazu = LoadGraph("Resource/Images/UI/13000.png");
	sann= LoadGraph("Resource/Images/UI/3.png");
	yonn = LoadGraph("Resource/Images/UI/yonn.png");
	// BGM ̓ǂݍ   ;
	back_ground_sound = rm->GetSounds("Resource/Sounds/BGM_MarioGround.wav");
	BGM = rm->GetSounds("Resource/Sounds/SE_GameOver.wav");

#ifdef _DEBUG

#else //   ߂񂤂邳  
	PlaySoundMem(back_ground_sound, DX_PLAYTYPE_BACK);
#endif  //DEBUG_ON

}


eSceneType InGameScene::Update(const float& delta_second)
{
	__super::Update(delta_second);

	//  ʂ̉E   Ƀ}   I      ƃX N   [   o b N
	if (player->GetLocation().x + screen_offset.x > 120)
	{
		ScRoll = player->GetLocation().x - 120 ;
		screen_offset.x = -ScRoll;
		player->SetLocation(Vector2D(player->GetLocation().x , player->GetLocation().y));
	}
	if (player->GetLocation().x - player->GetObjectSize().x / 2 < 0 && FileEnd != true)
	{
		player->SetLocation(Vector2D(player->GetLocation().x + (0.1f), player->GetLocation().y));
	}

	//  ʂ̍  [   z      폜
	if (DeleteCheck(player->GetLocation().x - 300 ))
	{

	}

	if (IM->GetKeyDown(KEY_INPUT_T))
	{
		return eSceneType::tika;
	}
	
    //SPACE L [ Ń  U   g  ʂɑJ ڂ   
	if (player->GetDeath())
	{
		StopSoundMem(back_ground_sound);
		PlaySoundMem(BGM, DX_PLAYTYPE_BACK);
		return eSceneType::eResult;
	}

	return GetNowSceneType();

	
}

void InGameScene::Draw() const
{	//  I t Z b g l    ɉ摜 ̕`    s  
	Vector2D graph_location = this->location + screen_offset;
	
	DrawRotaGraph(336, 432, 10000, 0.0, back_ground_image, TRUE);
	DrawString(200, 100, "Tキーで地下に遷移", 0xFFFFFF);
	/*DrawFormatString(155.0f, 300.0f, GetColor(255, 255, 255), "%d", lived);*/

	if (player->GetDeath())
	{
		DrawString(200, 100, " }   I   S    [", 0xFFFFFF);
	}

	DrawRotaGraph(450,20,1.0,0,time,TRUE);
	DrawRotaGraph(320, 20, 1.0, 0, world, TRUE);
	DrawRotaGraph(365, 30, 0.2, 0, one, TRUE);
	DrawRotaGraph(220, 10, 1.0, 0, coin, TRUE);
	DrawRotaGraph(70, -23, 1.0, 0, score, TRUE);
	DrawRotaGraph(560, 18, 1.0, 0, lives, TRUE);
	DrawRotaGraph(127, -18, 1.0, 0, kazu, TRUE);
	DrawRotaGraph(250, 40, 1.0, 0, sann, TRUE);
	DrawRotaGraph(485, 40, 1.0, 0, yonn, TRUE);
	DrawRotaGraph(630, 40, 1.0, 0, sann, TRUE);
		
#ifdef _DEBUG
	DrawLine(D_WIN_MAX_X -, 0, D_WIN_MAX_X /2 , D_WIN_MAX_Y, GetColor(255, 255, 255));
#endif // DEBUG_ON

	__super::Draw();

	
}

void InGameScene::Finalize()
{
	FM->File(FCLOSE);


}



const eSceneType InGameScene::GetNowSceneType() const
{
    return eSceneType::eInGame;
}

void InGameScene::CheckCollision(GameObjectBase* target, GameObjectBase* partner)
{
	//  k   | ` F b N
	if (target == nullptr || partner == nullptr)
	{
		return;
	}

	//      蔻      擾
	BoxCollision tc = target->GetCollision();
	BoxCollision pc = partner->GetCollision();

	//      蔻 肪 L     m F    
	if (tc.IsCheckHitTarget(pc.object_type) || pc.IsCheckHitTarget(tc.object_type))
	{

		//      ̎n _ ƏI _  ݒ肷  
		tc.Location += target->GetLocation();
		pc.Location += partner->GetLocation();

		//  J v Z     m ̓    蔻  
		if (IsCheckCollision(tc, pc))
		{
			//        Ă  邱 Ƃ ʒm    
			target->OnHitCollision(partner);
			partner->OnHitCollision(target);
		}
	}
}

void InGameScene::SetStartMapObject()
{
		FM->File(FOPEN,7,"Resource/Stage.txt");

		Banana = FM->Const_GetsFile(7);
		P1 = SM->forgh(Banana, 1);
		P2 = SM->forgh(Banana, 2);
		P3 = SM->forgh(Banana, 3);

		SetLocation_X = stoi(P1) * (int)D_OBJECT_SIZE;
		SetLocation_Y = stoi(P2) * (int)D_OBJECT_SIZE;

		SetObject = P3[0];
	for (int i = 0; i < 211; i++)
	{
		if ((D_OBJECT_SIZE * i != SetLocation_X) && (SetObject == '#'))
		{
			block = CreateObject<Block>(0);
			block->SetLocation(Vector2D(D_OBJECT_SIZE * i, (float)SetLocation_Y));
			block->player = player;
			block = CreateObject<Block>(0);
			block->SetLocation(Vector2D(D_OBJECT_SIZE * i, SetLocation_Y-D_OBJECT_SIZE));
			block->player = player;

		}
		else if(i < 154)
		{

			FM->File(FSEEK, 2);

			Banana = FM->Const_GetsFile(7);
			P1 = SM->forgh(Banana, 1);
			P2 = SM->forgh(Banana, 2);
			P3 = SM->forgh(Banana, 3);

			SetLocation_X = stoi(P1) * (int)D_OBJECT_SIZE;
			SetLocation_Y = stoi(P2) * (int)D_OBJECT_SIZE;
			SetObject = P3[0];
		}
	}
	FM->File(FCLOSE);

	FM->File(FOPEN);
	for (int i = 0; i < 2; i++)
	{
		Banana = FM->Const_GetsFile(7);
		P1 = SM->forgh(Banana, 1);
		P2 = SM->forgh(Banana, 2);
		P3 = SM->forgh(Banana, 3);

		SetLocation_X = stoi(P1) * (int)D_OBJECT_SIZE;
		SetLocation_Y = stoi(P2) * (int)D_OBJECT_SIZE;
		SetObject = P3[0];

		if (SetObject == 'P')// v   C   [
		{
			player->SetLocation(Vector2D((float)SetLocation_X, (float)SetLocation_Y));
		}
		else if (SetObject == 'E')
		{
			enemy = CreateObject<KEnemy>(0);
			enemy->SetLocation(Vector2D((float)SetLocation_X, (float)SetLocation_Y));
			enemy->player = player;
		}
		else if (SetObject == 'N')// m R m R
		{
			enemy = CreateObject<NEnemy>(0);
			enemy->SetLocation(Vector2D((float)SetLocation_X, (float)SetLocation_Y));
			enemy->player = player;
		}
		else if (SetObject == 'K')// L m R
		{
			mash = CreateObject<BigMash>(0);
			mash->SetLocation(Vector2D((float)SetLocation_X, (float)SetLocation_Y));
		}


		FM->File(FSEEK, 2);
		loadline += 7;
	}
}

void InGameScene::SetMapObject()
{

	while (1)
	{
		Banana = FM->Const_GetsFile(7);
		P1 = SM->forgh(Banana, 1);
		P2 = SM->forgh(Banana, 2);
		P3 = SM->forgh(Banana, 3);

		SetLocation_X = stoi(P1) * (int)D_OBJECT_SIZE;
		SetLocation_Y = stoi(P2) * (int)D_OBJECT_SIZE;
		SetObject = P3[0];

		if (SetObject == 'E')
		{
			enemy = CreateObject<KEnemy>(0);
			enemy->SetLocation(Vector2D((float)SetLocation_X, (float)SetLocation_Y));
			enemy->player = player;

		}
		else if (SetObject == 'N')// m R m R
		{
			enemy = CreateObject<NEnemy>(0);
			enemy->SetLocation(Vector2D((float)SetLocation_X, (float)SetLocation_Y));
			enemy->player = player;

		}
		else if (SetObject == 'K')// L m R
		{
			CreateObject<BigMash>(Vector2D((float)SetLocation_X, (float)SetLocation_Y));

		}

		else if (SetObject == 'C')// R C  
		{

		}
		else if (SetObject == 'U')//1up
		{

		}

		else if (SetObject == 'B')//Brick
		{
			brick = CreateObject<Brick>(0);
			brick->SetLocation(Vector2D((float)SetLocation_X, (float)SetLocation_Y));
			brick->player = player;
		}

		else if (SetObject == '?')//ItemBox
		{
			itembox = CreateObject<ItemBox>(0);
			itembox->SetLocation(Vector2D((float)SetLocation_X, (float)SetLocation_Y));
			itembox->InCoin = true;
			itembox->player = player;
		}

		else if (SetObject == '!')//ItemBox_InMash
		{
			itembox = CreateObject<ItemBox>(0);
			itembox->SetLocation(Vector2D((float)SetLocation_X, (float)SetLocation_Y));
			itembox->InBox = true;
			itembox->player = player;
		}
		else if (SetObject == 'S')// X ^ [
		{
			Star_Box = CreateObject<star_Box>(0);
			Star_Box->SetLocation(Vector2D((float)SetLocation_X, (float)SetLocation_Y));
			Star_Box->InStar = true;
			Star_Box->player = player;
		}

		else if (SetObject == 'D')  //階段ブロック
		{
			kai = CreateObject<kai_block>(0);
			kai->SetLocation(Vector2D((float)SetLocation_X, (float)SetLocation_Y));
		}

		else if (SetObject == 'Z')  //土管1
		{
		    Dokan = CreateObject<dokan>(0);
			Dokan->SetLocation(Vector2D((float)SetLocation_X, (float)SetLocation_Y));
		}

		else if (SetObject == 'X')  //土管2
		{
			Dokan1 = CreateObject<dokan1>(0);
			Dokan1->SetLocation(Vector2D((float)SetLocation_X, (float)SetLocation_Y));
		}

		else if (SetObject == 'J')  //土管2
		{
			Dokan2 = CreateObject<dokan2>(0);
			Dokan2->SetLocation(Vector2D((float)SetLocation_X, (float)SetLocation_Y));
		}

		else if (SetObject == 'L')  //土管2
		{
			Dokan3 = CreateObject<dokan3>(0);
			Dokan3->SetLocation(Vector2D((float)SetLocation_X, (float)SetLocation_Y));
		}


		else if (SetObject == 'G') //ゴールのポール
		{
			goal = CreateObject<Goal>(0);
			goal->SetLocation(Vector2D((float)SetLocation_X, (float)SetLocation_Y));
		}

		else
		{
			FM->File(FCLOSE);
			FileEnd = true;
			break;
		}
	FM->File(FSEEK, 2);

}
	FM->File(FCLOSE);
	

}
