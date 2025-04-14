#include "Block.h"
#include "../Utility/ResourceManager.h"
#include "DxLib.h"
#include "../Object/Player/Player.h"

Block::Block()
{
}

Block::~Block()
{
	
}

void Block::Initialize()
{
	// “–‚½‚è”»’è‚ÌÝ’è
	collision.is_blocking = true;
	collision.object_type = eObjectType::block;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::enemy);
	collision.hit_object_type.push_back(eObjectType::special);


	collision.Object_size = D_OBJECT_SIZE;


	// ‰Â“®«‚ÌÝ’è
	mobility = eMobilityType::Stationary;

	ResourceManager* rm = ResourceManager::GetInstance();
	
	image =	rm->GetImages("Resource/Images/Block/floor.png")[0];

	z_layer = 1;

}

void Block::Draw(const Vector2D& screen_offset) const
{
	if (player->GetLocation().x - this->GetLocation().x < 330)
	{
		__super::Draw(screen_offset);

#ifdef _DEBUG
		Vector2D size = this->collision.Object_size;
		DrawBoxAA(location.x + screen_offset.x - size.x / 2, location.y + screen_offset.y - size.y / 2, location.x + screen_offset.x + size.x / 2, location.y + screen_offset.y + size.y / 2, GetColor(255, 0, 0), false);
#endif
	}
}

