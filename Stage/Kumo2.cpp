#include"Kumo2.h"
#include "../Utility/ResourceManager.h"
#include"DxLib.h"


Kumo2::Kumo2()
{

}

Kumo2::~Kumo2()
{

}

void Kumo2::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/kumo2.png")[0];

}
void Kumo2::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}