#pragma once

#include"../Scene/SceneBase.h"
#include"../Object/GameObject.h"


class Kusa2 : public GameObject
{

public:
	Kusa2();
	~Kusa2();

private:


public:
	virtual void Initialize()override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	/*virtual void Draw() const ;*/



};

