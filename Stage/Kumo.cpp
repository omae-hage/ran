#include"Kumo.h"
#include "../Utility/ResourceManager.h"
#include"DxLib.h"


Kumo::Kumo()
{

}

Kumo::~Kumo()
{

}

void Kumo::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/kumo.png")[0];
	
}
void Kumo::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}