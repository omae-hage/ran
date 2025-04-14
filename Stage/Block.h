#pragma once

#include"../Object/GameObject.h"

class Block : public GameObject
{
public:
	Block();
	~Block();
public:	
	virtual	void Initialize()override;
	virtual void Draw(const Vector2D& screen_offset) const override;
};