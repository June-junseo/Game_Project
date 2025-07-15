#include "stdafx.h"
#include "Scene1.h"
#include "Scene2.h"
#include "ArrowButton.h"
#include "ZoomUI.h"
#include "Inventory.h"
#include "SceneUiMgr.h"
#include "Scene3.h"

Scene3::Scene3()
	:Scene(SceneIds::Scene3)
{
}

void Scene3::Init()
{
	Inventory::Instance().Init();
	ResourceLoad();
	TEXTURE_MGR.Load(texIds);
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	background3.setPosition(0.f, 0.f);
	background3.setTexture(TEXTURE_MGR.Get(texId3), true);

	sceneUiMgr.Init(FRAMEWORK.GetWindow(), windowSize);
	sceneUiMgr.CreateArrowButtons(windowSize);

	ArrowButton* leftArrow = sceneUiMgr.GetLeftArrow();
	ArrowButton* rightArrow = sceneUiMgr.GetRightArrow();
	sceneUiMgr.AddArrowButtons(leftArrow, rightArrow);

	leftArrow->SetCallBack([this]() {
		SCENE_MGR.ChangeScene(SceneIds::Scene4);
		});
	rightArrow->SetCallBack([this]() { //func
		SCENE_MGR.ChangeScene(SceneIds::Scene2);
		});
	Scene::Init();
}

void Scene3::Enter()
{
	Scene::Enter();
	ResourceLoad();
	TEXTURE_MGR.Load(texIds);
	background3.setTexture(TEXTURE_MGR.Get(texId3), true);
}

void Scene3::Exit()
{
	Scene::Exit();
}

void Scene3::Update(float dt)
{
	Scene::Update(dt);
	sceneUiMgr.Update(dt);
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left)) {
		sf::Vector2f mousePos = FRAMEWORK.GetWindow().mapPixelToCoords(InputMgr::GetMousePosition());
		Inventory::Instance().HandleClick(mousePos);
	}
}

void Scene3::HandleEvent(const sf::Event& event)
{
	sceneUiMgr.HandleEvent(event, FRAMEWORK.GetWindow());
}

void Scene3::Draw(sf::RenderWindow& window)
{
	window.setView(uiView);
	window.draw(background3);
	sceneUiMgr.Draw(window);
}

void Scene3::ResourceLoad()
{
	texIds.push_back("graphics/scene3_bg.png");
}
void Scene3::SetUpViews()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	background3.setTexture(TEXTURE_MGR.Get(texId3), true);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);
}

