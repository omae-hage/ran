#pragma once

#include"../Scene/SceneBase.h"
#include"../Object/GameObject.h"


class Kumo : public GameObject
{

public:
	Kumo();
	~Kumo();

private:


public:
	virtual void Initialize()override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	/*virtual void Draw() const ;*/



};

