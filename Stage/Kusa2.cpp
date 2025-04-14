#include"Kusa2.h"
#include "../Utility/ResourceManager.h"
#include"DxLib.h"


Kusa2::Kusa2()
{

}

Kusa2::~Kusa2()
{

}

void Kusa2::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/kusa3.png")[0];

}
void Kusa2::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}