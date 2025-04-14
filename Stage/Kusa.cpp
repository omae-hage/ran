#include"Kusa.h"
#include "../Utility/ResourceManager.h"
#include"DxLib.h"


Kusa::Kusa()
{

}

Kusa::~Kusa()
{

}

void Kusa::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/kusa.png")[0];

}
void Kusa::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}