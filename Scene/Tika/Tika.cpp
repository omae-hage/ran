#include "Tika.h"
#include "../../Utility/ResourceManager.h"
#include"../../Utility/Vector2D.h"
#include "../../Utility/InputManager.h"
#include "../../Object/block/tika_floor.h"
#include "../../Object/block/blackblock.h"
#include "../../Object/Dokan_Y/yokodokan.h"
#include "../../Object/Dokan_Y/yokodokan1.h"
#include "../../Object/Dokan_Y/yokodokan2.h"
#include "../../Object/Dokan_Y/yokodokan3.h"
#include "../../Object/Dokan_Y/yokodokan4.h"
#include "../../Object/Dokan_Y/yokodokan5.h"
#include "../../Object/Dokan/dokan.h"
#include "../../Object/Item/tika_Coin.h"
#include "../../Utility/BOXCollision.h"
#include "DxLib.h"


int screen;
int count_set = 0;
std::string hige;
std::string T1;
std::string T2;
std::string T3;
char set_object;

int Set_L_X;
int Set_L_Y;
;

Tika::Tika()
	: player(nullptr)
	, pause_flag(false)
	, loadline(0)
	, FileEnd(false)
	, SM(nullptr)
	, rm(nullptr)
	, IM(nullptr)
	, FM(nullptr)
	,block_tika(nullptr)
	,hanya(nullptr)

{
}

Tika::~Tika()
{
}

void Tika::Initialize()
{

	rm = ResourceManager::GetInstance();
	SM = StringManager::GetInstance();
	FM = FileManager::GetInstance();


	player = CreateObject<Player>(0);


	SetStartMapObject();
	SetMapObject();

	time = LoadGraph("Resource/Images/UI/time.png");
	world = LoadGraph("Resource/Images/UI/world.png");
	one = LoadGraph("Resource/Images/UI/1-1.png");
	coin = LoadGraph("Resource/Images/UI/coin.png");
	score = LoadGraph("Resource/Images/UI/score.png");
	lives = LoadGraph("Resource/Images/UI/lives.png");
	kazu = LoadGraph("Resource/Images/UI/13000.png");
	sann = LoadGraph("Resource/Images/UI/3.png");
	yonn = LoadGraph("Resource/Images/UI/yonn.png");

	//�C���X�^���X�̓ǂݍ���
	IM = InputManager::GetInstance();
	ResourceManager* rm = ResourceManager::GetInstance();

	// �X�N���[���I�t�Z�b�g��ݒ�
	screen_offset.y = D_OBJECT_SIZE * 3.0f;

}


eSceneType Tika::Update(const float& delta_second)
{
	__super::Update(delta_second);

	if (IM->GetKeyDown(KEY_INPUT_G))
	{
		return eSceneType::game;
	}
	return GetNowSceneType();

}

void Tika::Draw() const
{	
	// �I�t�Z�b�g�l����ɉ摜�̕`����s��
	Vector2D graph_location = this->location + screen_offset;

	DrawString(200, 150, "Gキーで次のステージに遷移", 0xFFFFFF);

	DrawRotaGraph(450, 20, 1.0, 0, time, TRUE);
	DrawRotaGraph(320, 20, 1.0, 0, world, TRUE);
	DrawRotaGraph(365, 30, 0.2, 0, one, TRUE);
	DrawRotaGraph(220, 10, 1.0, 0, coin, TRUE);
	DrawRotaGraph(70, -23, 1.0, 0, score, TRUE);
	DrawRotaGraph(560, 18, 1.0, 0, lives, TRUE);
	DrawRotaGraph(127, -18, 1.0, 0, kazu, TRUE);
	DrawRotaGraph(250, 40, 1.0, 0, sann, TRUE);
	DrawRotaGraph(485, 40, 1.0, 0, yonn, TRUE);
	DrawRotaGraph(630, 40, 1.0, 0, sann, TRUE);
	
	__super::Draw();


}

void Tika::Finalize()
{
	FM->File(FCLOSE);
}


const eSceneType Tika::GetNowSceneType() const
{
	return eSceneType::tika;
}

void Tika::CheckCollision(GameObjectBase* target, GameObjectBase* partner)
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

void Tika::SetStartMapObject()
{
	FM->File(FOPEN, 7, "Resource/tika.txt");

	hige = FM->Const_GetsFile(7);
	T1 = SM->forgh(hige, 1);
	T2 = SM->forgh(hige, 2);
	T3 = SM->forgh(hige, 3);

	Set_L_X = stoi(T1) * (int)D_OBJECT_SIZE;
	Set_L_Y = stoi(T2) * (int)D_OBJECT_SIZE;

	set_object = T3[0];
	for (int i = 0; i < 211; i++)
	{
		if ((D_OBJECT_SIZE * i != Set_L_X) && (set_object == '#'))
		{
			block_tika = CreateObject<tika_floor>(0);
			block_tika->SetLocation(Vector2D(D_OBJECT_SIZE * i, (float)Set_L_Y));
			block_tika->player = player;
			block_tika = CreateObject<tika_floor>(0);
			block_tika->SetLocation(Vector2D(D_OBJECT_SIZE * i, Set_L_Y - D_OBJECT_SIZE));
			block_tika->player = player;
		}
		else if (i < 154)
		{

			FM->File(FSEEK, 2);

			hige = FM->Const_GetsFile(7);
			T1 = SM->forgh(hige, 1);
			T2 = SM->forgh(hige, 2);
			T3 = SM->forgh(hige, 3);

			Set_L_X = stoi(T1) * (int)D_OBJECT_SIZE;
			Set_L_Y = stoi(T2) * (int)D_OBJECT_SIZE;
			set_object = T3[0];
		}
	}
	FM->File(FCLOSE);

	FM->File(FOPEN);
	for (int i = 0; i < 2; i++)
	{
		hige = FM->Const_GetsFile(7);
		T1 = SM->forgh(hige, 1);
		T2 = SM->forgh(hige, 2);
		T3 = SM->forgh(hige, 3);

		Set_L_X = stoi(T1) * (int)D_OBJECT_SIZE;
		Set_L_Y = stoi(T2) * (int)D_OBJECT_SIZE;
		set_object = T3[0];

		if (set_object == 'P')//�v���C���[
		{
			player->SetLocation(Vector2D((float)96.0, (float)0.0));
			player->velocity.y++;
		}


		FM->File(FSEEK, 2);
		loadline += 7;
	}
}

void Tika::SetMapObject()
{
	//左壁
	CreateObject<blackblock>(Vector2D(16.0f, 320.0f));
	CreateObject<blackblock>(Vector2D(16.0f, 288.0f));
	CreateObject<blackblock>(Vector2D(16.0f, 256.0f));
	CreateObject<blackblock>(Vector2D(16.0f, 224.0f));
	CreateObject<blackblock>(Vector2D(16.0f, 192.0f));
	CreateObject<blackblock>(Vector2D(16.0f, 160.0f));
	CreateObject<blackblock>(Vector2D(16.0f, 128.0f));
	CreateObject<blackblock>(Vector2D(16.0f, 96.0f));
	CreateObject<blackblock>(Vector2D(16.0f, 64.0f));
	CreateObject<blackblock>(Vector2D(16.0f, 32.0f));
	CreateObject<blackblock>(Vector2D(16.0f, 0.0f));

	//段差
	CreateObject<blackblock>(Vector2D(192.0f, 320.0f));
	CreateObject<blackblock>(Vector2D(224.0f, 320.0f));
	CreateObject<blackblock>(Vector2D(256.0f, 320.0f));
	CreateObject<blackblock>(Vector2D(288.0f, 320.0f));
	CreateObject<blackblock>(Vector2D(320.0f, 320.0f));
	CreateObject<blackblock>(Vector2D(352.0f, 320.0f));
	CreateObject<blackblock>(Vector2D(384.0f, 320.0f));
	CreateObject<blackblock>(Vector2D(192.0f, 288.0f));
	CreateObject<blackblock>(Vector2D(224.0f, 288.0f));
	CreateObject<blackblock>(Vector2D(256.0f, 288.0f));
	CreateObject<blackblock>(Vector2D(288.0f, 288.0f));
	CreateObject<blackblock>(Vector2D(320.0f, 288.0f));
	CreateObject<blackblock>(Vector2D(352.0f, 288.0f));
	CreateObject<blackblock>(Vector2D(384.0f, 288.0f));
	CreateObject<blackblock>(Vector2D(192.0f, 256.0f));
	CreateObject<blackblock>(Vector2D(224.0f, 256.0f));
	CreateObject<blackblock>(Vector2D(256.0f, 256.0f));
	CreateObject<blackblock>(Vector2D(288.0f, 256.0f));
	CreateObject<blackblock>(Vector2D(320.0f, 256.0f));
	CreateObject<blackblock>(Vector2D(352.0f, 256.0f));
	CreateObject<blackblock>(Vector2D(384.0f, 256.0f));

	//天井
	CreateObject<blackblock>(Vector2D(192.0f, 0.0f));
	CreateObject<blackblock>(Vector2D(224.0f, 0.0f));
	CreateObject<blackblock>(Vector2D(256.0f, 0.0f));
	CreateObject<blackblock>(Vector2D(288.0f, 0.0f));
	CreateObject<blackblock>(Vector2D(320.0f, 0.0f));
	CreateObject<blackblock>(Vector2D(352.0f, 0.0f));
	CreateObject<blackblock>(Vector2D(384.0f, 0.0f));

	//土管
	CreateObject<yokodokan4>(Vector2D(624.0f, 320.0f));
	CreateObject<yokodokan5>(Vector2D(624.0f, 288.0f));
	CreateObject<yokodokan3>(Vector2D(592.0f, 320.0f));
	CreateObject<yokodokan2>(Vector2D(592.0f, 288.0f));
	CreateObject<yokodokan>(Vector2D(560.0f, 320.0f));
	CreateObject<yokodokan1>(Vector2D(560.0f, 288.0f));
	CreateObject<dokan>(Vector2D(624.0f, 256.0f));
	CreateObject<dokan>(Vector2D(624.0f, 224.0f));
	CreateObject<dokan>(Vector2D(624.0f, 192.0f));
	CreateObject<dokan>(Vector2D(624.0f, 160.0f));
	CreateObject<dokan>(Vector2D(624.0f, 128.0f));
	CreateObject<dokan>(Vector2D(624.0f, 96.0f));
	CreateObject<dokan>(Vector2D(624.0f, 64.0f));
	CreateObject<dokan>(Vector2D(624.0f, 32.0f));
	CreateObject<dokan>(Vector2D(624.0f, 0.0f));

	//コイン
	CreateObject<tika_Coin>(Vector2D(192.0f, 224.0f));
	CreateObject<tika_Coin>(Vector2D(224.0f, 224.0f));
	CreateObject<tika_Coin>(Vector2D(256.0f, 224.0f));
	CreateObject<tika_Coin>(Vector2D(288.0f, 224.0f));
	CreateObject<tika_Coin>(Vector2D(320.0f, 224.0f));
	CreateObject<tika_Coin>(Vector2D(352.0f, 224.0f));
	CreateObject<tika_Coin>(Vector2D(384.0f, 224.0f));

	CreateObject<tika_Coin>(Vector2D(192.0f, 160.0f));
	CreateObject<tika_Coin>(Vector2D(224.0f, 160.0f));
	CreateObject<tika_Coin>(Vector2D(256.0f, 160.0f));
	CreateObject<tika_Coin>(Vector2D(288.0f, 160.0f));
	CreateObject<tika_Coin>(Vector2D(320.0f, 160.0f));
	CreateObject<tika_Coin>(Vector2D(352.0f, 160.0f));
	CreateObject<tika_Coin>(Vector2D(384.0f, 160.0f));

	CreateObject<tika_Coin>(Vector2D(224.0f, 96.0f));
	CreateObject<tika_Coin>(Vector2D(256.0f, 96.0f));
	CreateObject<tika_Coin>(Vector2D(288.0f, 96.0f));
	CreateObject<tika_Coin>(Vector2D(320.0f, 96.0f));
	CreateObject<tika_Coin>(Vector2D(352.0f, 96.0f));
}

