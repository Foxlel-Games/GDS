#include <iostream>
#include <Krawler.h>
#include <KApplication.h>
#include <stdexcept>

#include "GameBlackboard.h"
#include "LevelSetup.h"

using namespace std;

using namespace Krawler;


#ifndef _DEBUG
#include <Windows.h>
int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
#else
int main(void)
#endif
{
	KScene* mainScene = new KScene(KTEXT("play scene"), SCENE_BOUNDS);

	KApplicationInitialise appInit(false);
	appInit.width = 1024;
	appInit.height = 576;
	appInit.gameFps = 30;
	appInit.physicsFps = 60;
	appInit.windowTitle = KTEXT("GDS - Prototype");
	appInit.windowStyle = KWindowStyle::Windowed_Fixed_Size;
	StartupEngine(&appInit);

	KApplication::getApp()->getSceneDirector().addScene(mainScene);
	KApplication::getApp()->getSceneDirector().setCurrentScene(KTEXT("play scene"));

	KEntity* const pEntity = mainScene->addEntityToScene();
	if (!pEntity)
	{
		KPrintf(KTEXT("Unable to create level management entity!\n"));
		return -1;
	}

	pEntity->setEntityTag(KTEXT("level setup"));
	pEntity->addComponent(new LevelSetup(pEntity));

	const KInitStatus initResult = InitialiseSubmodules();
	if (initResult != KInitStatus::Success)
	{
		system("pause");
		return -1;
	}
	RunApplication();

	ShutdownEngine();

	return 0;
}
