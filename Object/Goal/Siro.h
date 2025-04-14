#pragma once

#include"../GameObject.h"
#include"../../Utility/ResourceManager.h"
class Siro : public GameObject
{
public:

	class ResourceManager* rm;
	/*int image_Goal;	*/	// 
	Vector2D velocity;
	float IsLeft = 1.0f;
	Siro();
	~Siro();

public:
	virtual void Initialize()override;
	virtual void Draw(const Vector2D& screen_offset) const override;

};

