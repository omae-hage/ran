#pragma once

#include"../Scene/SceneBase.h"
#include"../Object/GameObject.h"


class Kusa1 : public GameObject
{

public:
	Kusa1();
	~Kusa1();

private:


public:
	virtual void Initialize()override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	/*virtual void Draw() const ;*/



};

