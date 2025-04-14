#include"Kusa1.h"
#include "../Utility/ResourceManager.h"
#include"DxLib.h"


Kusa1::Kusa1()
{

}

Kusa1::~Kusa1()
{

}

void Kusa1::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/kusa2.png")[0];

}
void Kusa1::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}