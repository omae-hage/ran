#include "Mountain.h"
#include "../Utility/ResourceManager.h"
#include"DxLib.h"





Mountain::Mountain()
{

}

Mountain::~Mountain()
{

}

void Mountain::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/yama.png")[0];

	// ‰Â“®«‚ÌÝ’è
	mobility = eMobilityType::Stationary;

	/*yama = LoadGraph("C:\\PG\\Mario_team\\Resource\\Images\\yama.png");*/
}
void Mountain::Draw(const Vector2D& screen_offset) const
{
	/*Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 0.2, 0.0, yama, TRUE);*/
	__super::Draw(screen_offset);
}
//void Mountain::Draw(const Vector2D& screen_offset) const
//{
//	DrawRotaGraphF(80, 374, 1.0, 0.0, yama, TRUE);
//}

// void Mountain::Draw() const
//{
//	 __super::Draw(screen_offset);
//}
