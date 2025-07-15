#include "stdafx.h"
#include "Scene1.h"
#include "Scene2.h"
#include "ArrowButton.h"
#include "ZoomUI.h"
#include "Inventory.h"
#include "SceneUiMgr.h"

Scene1::Scene1() 
	: Scene(SceneIds::Scene1)
{
}

void Scene1::Init()
{
	Inventory::Instance().Init();
	ResourceLoad();
	TEXTURE_MGR.Load(texIds);
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	shadowBg.setSize({ 1920, 1080 });
	shadowBg.setFillColor(sf::Color(0, 0, 0, 150));

	sceneUiMgr.Init(FRAMEWORK.GetWindow(), windowSize);
	sceneUiMgr.CreateArrowButtons(windowSize);

	ArrowButton* leftArrow = sceneUiMgr.GetLeftArrow();
	ArrowButton* rightArrow = sceneUiMgr.GetRightArrow();

	sceneUiMgr.AddArrowButtons(leftArrow, rightArrow);

	background1.setPosition(0.f, 0.f);
	background1.setTexture(TEXTURE_MGR.Get(texId), true);
	light.setPosition(0.f, 0.f);
	light.setTexture(TEXTURE_MGR.Get(texId1), true);

	sf::FloatRect shelfArea(windowSize.x / 10.f + 165.f, windowSize.y / 2.f - 180.f, 270.f, 250.f);
	sf::FloatRect boxArea(windowSize.x / 10.f + 750, windowSize.y / 2.f - 10.f + 130.f, 270.f, 250.f);
	sf::Vector2f center = uiView.getCenter();
	sf::FloatRect albumArea(center.x - 75.f, center.y + 30.f, 60.f, 60.f);
	albumRect.setPosition(albumArea.left, albumArea.top);

	numPad.Init(center + sf::Vector2f(-35.f, -25.f), { 50.f, 50.f });
	numPad.SetPassword("1234");

	shelfUi.Init(TEXTURE_MGR.Get("graphics/shelf_ui.png"), center);
	shelfUi.SetClickableArea(shelfArea);
	boxUi.Init(TEXTURE_MGR.Get("graphics/box_ui.png"), center);
	boxUi.SetClickableArea(boxArea);
	albumUi.Init(TEXTURE_MGR.Get("graphics/album_ui.png"), center);
	albumUi.SetClickableArea(albumArea);

	leftArrow->SetCallBack([this]() {
		if (albumUi.IsVisible()) albumUi.Hide();
		else if (shelfUi.IsVisible()) shelfUi.Hide();
		else if (boxUi.IsVisible()) boxUi.Hide();
		else SCENE_MGR.ChangeScene(SceneIds::Scene2);
		});
	rightArrow->SetCallBack([this]() {
		if (shelfUi.IsVisible()) shelfUi.Hide();
		if (boxUi.IsVisible()) boxUi.Hide();
		});
	numPad.SetOnOkPressed([this]() {
		if (numPad.IsPasswordCorrect()) {
			boxUi.ChangeTexture(TEXTURE_MGR.Get("graphics/box_open_ui.png"));
			boxUi.SetOpened(true);
			numPad.SetActive(false);
			isBatteryVisible = true;
		}
		});
	batterySprite.setTexture(TEXTURE_MGR.Get("graphics/battery_ui.png"));
	batterySprite.setPosition(boxUi.GetPosition() + sf::Vector2f(800.f, 650.f));
	batterySprite.setScale(0.5f, 0.5f);
	Scene::Init();
}

void Scene1::Enter()
{
	Scene::Enter();
	ResourceLoad();
	TEXTURE_MGR.Load(texIds);
	background1.setTexture(TEXTURE_MGR.Get(texId), true);
	light.setTexture(TEXTURE_MGR.Get(texId1), true);
	boxUi.ChangeTexture(TEXTURE_MGR.Get(boxUi.IsOpened() ? "graphics/box_open_ui.png" : "graphics/box_ui.png")); //***
	isBatteryVisible = boxUi.IsOpened() && !Inventory::Instance().HasItem("battery");
}

void Scene1::Exit()
{
	Scene::Exit();
}

void Scene1::Update(float dt)
{
	Scene::Update(dt);
	sceneUiMgr.Update(dt);
	numPad.Update(dt);
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left)) {
		sf::Vector2f mousePos = FRAMEWORK.GetWindow().mapPixelToCoords(InputMgr::GetMousePosition());
		Inventory::Instance().HandleClick(mousePos);
		if (boxUi.IsVisible() && boxUi.IsOpened() && isBatteryVisible && batterySprite.getGlobalBounds().contains(mousePos)) {
			if (!Inventory::Instance().HasItem("battery")) {
				Item* battery = new Item("battery", "graphics/battery_ui.png");
				battery->Init();
				Inventory::Instance().AddItem(battery);
			}
			isBatteryVisible = false;
		}
		if (shelfUi.IsVisible() && albumUi.CheckClick(mousePos)) albumUi.Show();
		else if (shelfUi.CheckClick(mousePos)) { shelfUi.Show(); boxUi.Hide(); albumUi.Hide(); numPad.SetActive(false); }
		else if (boxUi.CheckClick(mousePos)) { boxUi.Show(); shelfUi.Hide(); albumUi.Hide(); numPad.SetActive(true); }
	}
	blinkTimer += dt;
	if (blinkTimer >= blinkInterval) {
		blinkTimer = 0.f;
		light.setColor(sf::Color(255, 255, 255, rand() % 176 + 80));
	}
}

void Scene1::HandleEvent(const sf::Event& event)
{
	sceneUiMgr.HandleEvent(event, FRAMEWORK.GetWindow());
}

void Scene1::Draw(sf::RenderWindow& window)
{
	window.setView(uiView);
	window.draw(background1);
	window.draw(light);
	shelfUi.Draw(window, &albumRect);
	if (albumUi.IsVisible()) window.draw(shadowBg);
	albumUi.Draw(window);
	boxUi.Draw(window);
	if (boxUi.IsVisible() && !boxUi.IsOpened() && numPad.GetActive()) numPad.Draw(window);
	if (isBatteryVisible) window.draw(batterySprite);
	sceneUiMgr.Draw(window);
}

void Scene1::SetUpViews()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	background1.setTexture(TEXTURE_MGR.Get(texId), true);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);
}

void Scene1::ResourceLoad()
{
	texIds = { 
		texId, 
		texId1, 
		"graphics/shelf_ui.png", 
		"graphics/box_ui.png", 
		"graphics/album_ui.png", 
		"graphics/box_open_ui.png", 
		"graphics/battery_ui.png" };
}