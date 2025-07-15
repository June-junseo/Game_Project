#include "stdafx.h"
#include "Scene1.h"
#include "Scene2.h"
#include "ArrowButton.h"
#include "ZoomUI.h"
#include "Inventory.h"
#include "SceneUiMgr.h"

Scene2::Scene2() : Scene(SceneIds::Scene2) {}

void Scene2::Init()
{
	Inventory::Instance().Init();
	ResourceLoad();
	TEXTURE_MGR.Load(texIds);
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	background2.setPosition(0.f, 0.f);
	background2.setTexture(TEXTURE_MGR.Get(texId2), true);

	sceneUiMgr.Init(FRAMEWORK.GetWindow(), windowSize);
	sceneUiMgr.CreateArrowButtons(windowSize);

	ArrowButton* leftArrow = sceneUiMgr.GetLeftArrow();
	ArrowButton* rightArrow = sceneUiMgr.GetRightArrow();
	sceneUiMgr.AddArrowButtons(leftArrow, rightArrow);

	sf::Vector2f center = windowSize * 0.5f;
	sf::Vector2f tvSize(270.f, 250.f);
	sf::FloatRect tvArea(center.x - tvSize.x * 0.5f, center.y - tvSize.y * 0.5f, tvSize.x, tvSize.y);
	tvUi.Init(TEXTURE_MGR.Get("graphics/tv_ui.png"), center);
	tvUi.SetClickableArea(tvArea);

	leftArrow->SetCallBack([this]() {
		if (tvUi.IsVisible()) tvUi.Hide();
		});
	rightArrow->SetCallBack([this]() {
		if (tvUi.IsVisible()) tvUi.Hide();
		SCENE_MGR.ChangeScene(SceneIds::Scene1);
		});
	Scene::Init();
}

void Scene2::Enter()
{
	Scene::Enter();
	ResourceLoad();
	TEXTURE_MGR.Load(texIds);
	background2.setTexture(TEXTURE_MGR.Get(texId2), true);
	tvUi.ChangeTexture(TEXTURE_MGR.Get("graphics/tv_ui.png"));
}

void Scene2::Exit()
{
	Scene::Exit();
}

void Scene2::Update(float dt)
{
	Scene::Update(dt);
	sceneUiMgr.Update(dt);
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left)) {
		sf::Vector2f mousePos = FRAMEWORK.GetWindow().mapPixelToCoords(InputMgr::GetMousePosition());
		if (tvUi.CheckClick(mousePos)) tvUi.Show();
		Inventory::Instance().HandleClick(mousePos);
	}
}

void Scene2::HandleEvent(const sf::Event& event)
{
	sceneUiMgr.HandleEvent(event, FRAMEWORK.GetWindow());
}

void Scene2::Draw(sf::RenderWindow& window)
{
	window.setView(uiView);
	window.draw(background2);
	if (tvUi.IsVisible()) tvUi.Draw(window);
	sceneUiMgr.Draw(window);
}

void Scene2::ResourceLoad()
{
	texIds = { texId2, "graphics/tv_ui.png" };
}

void Scene2::SetUpViews()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	background2.setTexture(TEXTURE_MGR.Get(texId2), true);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);
}
