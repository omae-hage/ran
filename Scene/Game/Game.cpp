#include "Game.h"
#include "../../Utility/ResourceManager.h"
#include "../../Stage/Block.h"
#include "../../Utility/ProjectConfig.h"
#include"../../Object/Item/Brick.h"
#include"../../Object/Item/ItemBox.h"
#include"../../Utility/Vector2D.h"
#include"../../Stage/Mountain.h"
#include"../../Stage/Kumo.h"
#include"../../Stage/Kumo2.h"
#include"../../Stage/Kumo3.h"
#include"../../Object/Goal/Goal.h"
#include"../../Object/Goal/Goal2.h"
#include"../../Object/Goal/Goal3.h"
#include "../../Object/Dokan/dokan.h"
#include "../../Object/Dokan/dokan1.h"
#include "../../Object/Dokan/dokan2.h"
#include "../../Object/Dokan/dokan3.h"
#include "../../Object/block/kai_block.h"
#include "../../Object/Goal/Siro.h"
#include "../../Stage/Kusa1.h"
#include "DxLib.h"



int scof;
int kazu = 0;
std::string hage;
std::string R1;
std::string R2;
std::string R3;
char Set_OB;

int Set_Iti_X;
int Set_Iti_Y;

Game::Game()
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
	, itembox(nullptr)
	, IM(nullptr)
	, FM(nullptr)
	, enemy(nullptr)
	, brick(nullptr)
	, block(nullptr)
	, goal(nullptr)
	, kai(nullptr)
	

{

}

Game::~Game()
{
}

void Game::Initialize()
{

	rm = ResourceManager::GetInstance();
	SM = StringManager::GetInstance();
	FM = FileManager::GetInstance();


	player = CreateObject<Player>(0);

	
	SetStartMapObject();
	SetMapObject();


	//�C���X�^���X�̓ǂݍ���
	IM = InputManager::GetInstance();
	ResourceManager* rm = ResourceManager::GetInstance();

	// �X�N���[���I�t�Z�b�g��ݒ�
	screen_offset.y = D_OBJECT_SIZE * 3.0f;



	// �w�i�摜�̓ǂݍ���
	back_ground_image = LoadGraph("Resource/Images/sora.png");
	back_ground_image = LoadGraph("Resource/Images/sora.png");
	time = LoadGraph("Resource/Images/UI/time.png");
	world = LoadGraph("Resource/Images/UI/world.png");
	one = LoadGraph("Resource/Images/UI/1-1.png");
	coin = LoadGraph("Resource/Images/UI/coin.png");
	score = LoadGraph("Resource/Images/UI/score.png");
	lives = LoadGraph("Resource/Images/UI/lives.png");
	kazuu = LoadGraph("Resource/Images/UI/13000.png");
	sann = LoadGraph("Resource/Images/UI/3.png");
	yonn = LoadGraph("Resource/Images/UI/yonn.png");
	// BGM�̓ǂݍ���;
	back_ground_sound = rm->GetSounds("Resource/Sounds/BGM_MarioGround.wav");
#ifdef _DEBUG

#else //���߂񂤂邳��
	PlaySoundMem(back_ground_sound, DX_PLAYTYPE_BACK);
#endif  //DEBUG_ON

}


eSceneType Game::Update(const float& delta_second)
{
	__super::Update(delta_second);

	//��ʂ̉E���Ƀ}���I������ƃX�N���[���o�b�N
	if (player->GetLocation().x + screen_offset.x > D_WIN_MAX_X / 2 + 1)
	{
		ScRoll = player->GetLocation().x - D_WIN_MAX_X / 2;
		screen_offset.x = -ScRoll;
		player->SetLocation(Vector2D(player->GetLocation().x, player->GetLocation().y));
	}
	if (player->GetLocation().x - player->GetObjectSize().x / 2 < 0 && FileEnd != true)
	{
		player->SetLocation(Vector2D(player->GetLocation().x + (0.1f), player->GetLocation().y));
	}

	return GetNowSceneType();

}

void Game::Draw() const
{	// �I�t�Z�b�g�l����ɉ摜�̕`����s��
	Vector2D graph_location = this->location + screen_offset;

	DrawRotaGraph(336, 432, 10000, 0.0, back_ground_image, TRUE);
	/*DrawFormatString(155.0f, 300.0f, GetColor(255, 255, 255), "%d", lived);*/
	DrawRotaGraph(450, 20, 1.0, 0, time, TRUE);
	DrawRotaGraph(320, 20, 1.0, 0, world, TRUE);
	DrawRotaGraph(365, 30, 0.2, 0, one, TRUE);
	DrawRotaGraph(220, 10, 1.0, 0, coin, TRUE);
	DrawRotaGraph(70, -23, 1.0, 0, score, TRUE);
	DrawRotaGraph(560, 18, 1.0, 0, lives, TRUE);
	DrawRotaGraph(127, -18, 1.0, 0, kazuu, TRUE);
	DrawRotaGraph(250, 40, 1.0, 0, sann, TRUE);
	DrawRotaGraph(485, 40, 1.0, 0, yonn, TRUE);
	DrawRotaGraph(630, 40, 1.0, 0, sann, TRUE);

#ifdef _DEBUG
	DrawLine(D_WIN_MAX_X / 2 + 1, 0, D_WIN_MAX_X / 2 + 1, D_WIN_MAX_Y, GetColor(255, 255, 255));
#endif // DEBUG_ON

	__super::Draw();


}

void Game::Finalize()
{
	FM->File(FCLOSE);
}


const eSceneType Game::GetNowSceneType() const
{
	return eSceneType::game;
}

void Game::CheckCollision(GameObjectBase* target, GameObjectBase* partner)
{
	// �k���|�`�F�b�N
	if (target == nullptr || partner == nullptr)
	{
		return;
	}

	// �����蔻������擾
	BoxCollision tc = target->GetCollision();
	BoxCollision pc = partner->GetCollision();

	// �����蔻�肪�L�����m�F����
	if (tc.IsCheckHitTarget(pc.object_type) || pc.IsCheckHitTarget(tc.object_type))
	{

		// �����̎n�_�ƏI�_��ݒ肷��
		tc.Location += target->GetLocation();
		pc.Location += partner->GetLocation();

		// �J�v�Z�����m�̓����蔻��
		if (IsCheckCollision(tc, pc))
		{
			// �������Ă��邱�Ƃ�ʒm����
			target->OnHitCollision(partner);
			partner->OnHitCollision(target);
		}
	}
}

void Game::SetStartMapObject()
{
	FM->File(FOPEN, 7, "Resource/Stage.txt");

	hage = FM->Const_GetsFile(7);
	R1 = SM->forgh(hage, 1);
	R2 = SM->forgh(hage, 2);
	R3 = SM->forgh(hage, 3);

	Set_Iti_X = stoi(R1) * (int)D_OBJECT_SIZE;
	Set_Iti_Y = stoi(R2) * (int)D_OBJECT_SIZE;

	Set_OB = R3[0];
	for (int i = 0; i < 211; i++)
	{
		if ((D_OBJECT_SIZE * i != Set_Iti_X) && (Set_OB == '#'))
		{
			block = CreateObject<Block>(0);
			block->SetLocation(Vector2D(D_OBJECT_SIZE * i, (float)Set_Iti_Y));
			block->player = player;
			block = CreateObject<Block>(0);
			block->SetLocation(Vector2D(D_OBJECT_SIZE * i, Set_Iti_Y - D_OBJECT_SIZE));
			block->player = player;

		}
		else if (i < 154)
		{

			FM->File(FSEEK, 2);

			hage = FM->Const_GetsFile(7);
			R1 = SM->forgh(hage, 1);
			R2 = SM->forgh(hage, 2);
			R3 = SM->forgh(hage, 3);

			Set_Iti_X = stoi(R1) * (int)D_OBJECT_SIZE;
			Set_Iti_Y = stoi(R2) * (int)D_OBJECT_SIZE;
			Set_OB = R3[0];
		}
	}
	FM->File(FCLOSE);

	FM->File(FOPEN);
	for (int i = 0; i < 2; i++)
	{
		hage = FM->Const_GetsFile(7);
		R1 = SM->forgh(hage, 1);
		R2 = SM->forgh(hage, 2);
		R3 = SM->forgh(hage, 3);

		Set_Iti_X = stoi(R1) * (int)D_OBJECT_SIZE;
		Set_Iti_Y = stoi(R2) * (int)D_OBJECT_SIZE;
		Set_OB = R3[0];

		if (Set_OB == 'P')//�v���C���[
		{
			player->SetLocation(Vector2D((float)32.0, (float)256.0));
			player->velocity.y++;
		}
		


		FM->File(FSEEK, 2);
		loadline += 7;
	}
}

void Game::SetMapObject()
{
	//土管
	CreateObject<dokan>(Vector2D(16.0f, 320.0f));
	CreateObject<dokan2>(Vector2D(48.0f, 320.0f));
	CreateObject<dokan1>(Vector2D(16.0f, 288.0f));
	CreateObject<dokan3>(Vector2D(48.0f, 288.0f));

	CreateObject<dokan>(Vector2D(586.0f, 320.0f));
	CreateObject<dokan2>(Vector2D(618.0f, 320.0f));
	CreateObject<dokan1>(Vector2D(586.0f, 288.0f));
	CreateObject<dokan3>(Vector2D(618.0f, 288.0f));

	//雲
	CreateObject<Kumo>(Vector2D(120.0f, 20.0f));
	CreateObject<Kumo3>(Vector2D(340.0f, 40.0f));
	CreateObject<Kumo2>(Vector2D(650.0f, 20.0f));
	CreateObject<Kumo>(Vector2D(1400.0f, 20.0f));

	//階段
	CreateObject<kai_block>(Vector2D(650.0f, 320.0f));
	CreateObject<kai_block>(Vector2D(682.0f, 320.0f));
	CreateObject<kai_block>(Vector2D(682.0f, 288.0f));
	CreateObject<kai_block>(Vector2D(714.0f, 320.0f));
	CreateObject<kai_block>(Vector2D(714.0f, 288.0f));
	CreateObject<kai_block>(Vector2D(714.0f, 256.0f));
	CreateObject<kai_block>(Vector2D(746.0f, 320.0f));
	CreateObject<kai_block>(Vector2D(746.0f, 288.0f));
	CreateObject<kai_block>(Vector2D(746.0f, 256.0f));
	CreateObject<kai_block>(Vector2D(746.0f, 224.0f));
	CreateObject<kai_block>(Vector2D(778.0f, 320.0f));
	CreateObject<kai_block>(Vector2D(778.0f, 288.0f));
	CreateObject<kai_block>(Vector2D(778.0f, 256.0f));
	CreateObject<kai_block>(Vector2D(778.0f, 224.0f));
	CreateObject<kai_block>(Vector2D(778.0f, 192.0f));
	CreateObject<kai_block>(Vector2D(810.0f, 320.0f));
	CreateObject<kai_block>(Vector2D(810.0f, 288.0f));
	CreateObject<kai_block>(Vector2D(810.0f, 256.0f));
	CreateObject<kai_block>(Vector2D(810.0f, 224.0f));
	CreateObject<kai_block>(Vector2D(810.0f, 192.0f));
	CreateObject<kai_block>(Vector2D(810.0f, 160.0f));
	CreateObject<kai_block>(Vector2D(842.0f, 320.0f));
	CreateObject<kai_block>(Vector2D(842.0f, 288.0f));
	CreateObject<kai_block>(Vector2D(842.0f, 256.0f));
	CreateObject<kai_block>(Vector2D(842.0f, 224.0f));
	CreateObject<kai_block>(Vector2D(842.0f, 192.0f));
	CreateObject<kai_block>(Vector2D(842.0f, 160.0f));
	CreateObject<kai_block>(Vector2D(842.0f, 128.0f));
	CreateObject<kai_block>(Vector2D(874.0f, 320.0f));
	CreateObject<kai_block>(Vector2D(874.0f, 288.0f));
	CreateObject<kai_block>(Vector2D(874.0f, 256.0f));
	CreateObject<kai_block>(Vector2D(874.0f, 224.0f));
	CreateObject<kai_block>(Vector2D(874.0f, 192.0f));
	CreateObject<kai_block>(Vector2D(874.0f, 160.0f));
	CreateObject<kai_block>(Vector2D(874.0f, 128.0f));
	CreateObject<kai_block>(Vector2D(874.0f, 96.0f));
	CreateObject<kai_block>(Vector2D(906.0f, 320.0f));
	CreateObject<kai_block>(Vector2D(906.0f, 288.0f));
	CreateObject<kai_block>(Vector2D(906.0f, 256.0f));
	CreateObject<kai_block>(Vector2D(906.0f, 224.0f));
	CreateObject<kai_block>(Vector2D(906.0f, 192.0f));
	CreateObject<kai_block>(Vector2D(906.0f, 160.0f));
	CreateObject<kai_block>(Vector2D(906.0f, 128.0f));
	CreateObject<kai_block>(Vector2D(906.0f, 96.0f));

	//ゴール
	CreateObject<kai_block>(Vector2D(1194.0f, 320.0f));
	CreateObject<Goal>(Vector2D(1194.0f, 288.0f));
	CreateObject<Goal>(Vector2D(1194.0f, 256.0f));
	CreateObject<Goal>(Vector2D(1194.0f, 224.0f));
	CreateObject<Goal>(Vector2D(1194.0f, 192.0f));
	CreateObject<Goal>(Vector2D(1194.0f, 160.0f));
	CreateObject<Goal>(Vector2D(1194.0f, 128.0f));
	CreateObject<Goal>(Vector2D(1194.0f, 96.0f));
	CreateObject<Goal>(Vector2D(1194.0f, 64.0f));
	CreateObject<Goal>(Vector2D(1194.0f, 32.0f));
	CreateObject<Goal3>(Vector2D(1175.0f, 32.0f));
	CreateObject<Goal2>(Vector2D(1194.0f, 0.0f));

	CreateObject<Siro>(Vector2D(1460.0f, 256.0f));

	CreateObject<Kusa1>(Vector2D(180.0f, 315.0f));
	CreateObject<Mountain>(Vector2D(1080.0f, 278.0f));
	CreateObject<Mountain>(Vector2D(1650.0f, 315.0f));
}

