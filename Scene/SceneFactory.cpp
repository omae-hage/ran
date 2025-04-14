#include "SceneFactory.h"
#include"../Scene/SceneBase.h"
#include"../Scene/InGame/InGameScene.h"

SceneBase* SceneFactory::CreateScene(eSceneType scene)
{
	switch (scene)
	{
	case eSceneType::eTitle:
		break;

	case eSceneType::eInGame:
		return new InGameScene();
		break;

	case eSceneType::eResult:
		break;

	case eSceneType::re_start:
		break;

	case eSceneType::tika:
		break;

	case eSceneType::game:
		break;
	default:
		break;
	}
	return nullptr;
}