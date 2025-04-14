#include"DxLib.h"
#include"Scene/SceneManager.h"
#include <string>
#include "Utility/ProjectConfig.h"
#include <iostream>
#include <chrono>
#include <thread>
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	try 
	{
		SceneManager manager;

		manager.WakeUp();

		manager.Run();

		manager.Shutdown();
	}
	catch (std::string error_log)
	{
		return ErrorThrow(error_log);
	}

	return ERROR_SUCCESS;
}
