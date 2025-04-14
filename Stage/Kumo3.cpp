#include"Kumo3.h"
#include "../Utility/ResourceManager.h"
#include"DxLib.h"


Kumo3::Kumo3()
{

}

Kumo3::~Kumo3()
{

}

void Kumo3::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/kumo3.png")[0];

}
void Kumo3::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}