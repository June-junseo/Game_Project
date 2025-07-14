#include "stdafx.h"
#include "Scene1.h"
#include "ArrowButton.h"
#include "ZoomUI.h"

Scene1::Scene1()
	: Scene(SceneIds::Scene1)
{
}

void Scene1::Init()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f size(25.f, 30.f);

	numPad.SetActive(false);

	shadowBg.setSize({ 1920, 1080 });
	shadowBg.setFillColor(sf::Color(0, 0, 0, 150));

	leftArrow = new ArrowButton(ArrowDirection::Left, { 150, windowSize.y / 2 - 20 }, size);
	rightArrow = new ArrowButton(ArrowDirection::Right, { windowSize.x - 370, windowSize.y / 2 - 20 }, size);

	// Resource loading
	ResourceLoad();
	TEXTURE_MGR.Load(texIds);

	// Background setting
	background1.setPosition(0.f, 0.f);
	background1.setTexture(TEXTURE_MGR.Get(texId), true);

	// Light setup
	light.setPosition(0.f, 0.f);
	light.setTexture(TEXTURE_MGR.Get(texId1), true);

	// View setup
	SetUpViews();

	// Define clickable areas
	sf::FloatRect shelfClickableArea(windowSize.x / 10.f + 165.f, windowSize.y / 2.f - 180.f, 270.f, 250.f);
	sf::FloatRect boxClickableArea(windowSize.x / 10.f + 750, windowSize.y / 2.f - 10.f + 130.f, 270.f, 250.f);

	sf::Vector2f shelfCenter = uiView.getCenter();
	sf::FloatRect albumClickableArea(shelfCenter.x - 75.f, shelfCenter.y + 30.f, 60.f, 60.f);
	albumRect.setPosition(albumClickableArea.left, albumClickableArea.top);

	sf::Vector2f numPadPos = uiView.getCenter() + sf::Vector2f(-35.f, -25.f);
	numPad.Init(numPadPos, { 50.f, 50.f });
	numPad.SetPassword("1234");

	// Load textures for UI elements
	sf::Texture& shelfTex = TEXTURE_MGR.Get("graphics/shelf_ui.png");
	sf::Texture& boxTex = TEXTURE_MGR.Get("graphics/box_ui.png");
	sf::Texture& albumTex = TEXTURE_MGR.Get("graphics/album_ui.png");

	// Initialize UI elements
	shelfUi.Init(shelfTex, uiView.getCenter());
	shelfUi.SetClickableArea(shelfClickableArea);

	boxUi.Init(boxTex, uiView.getCenter());
	boxUi.SetClickableArea(boxClickableArea);

	albumUi.Init(albumTex, uiView.getCenter());
	albumUi.SetClickableArea(albumClickableArea);

	// Setup debug rectangles for clickable areas
	shelfRect.setSize({ 270.f, 250.f });
	shelfRect.setPosition(shelfClickableArea.left, shelfClickableArea.top);
	shelfRect.setFillColor(sf::Color(255, 0, 0, 100));
	shelfRect.setOutlineThickness(3.f);
	shelfRect.setOutlineColor(sf::Color::Red);

	boxRect.setSize({ 340.f, 250.f });
	boxRect.setPosition(boxClickableArea.left, boxClickableArea.top);
	boxRect.setFillColor(sf::Color(255, 0, 0, 100));  // 300 is invalid; changed to 255 max
	boxRect.setOutlineThickness(3.f);
	boxRect.setOutlineColor(sf::Color::Green);

	albumRect.setSize({ 90.f, 200.f });
	albumRect.setPosition(albumClickableArea.left, albumClickableArea.top);
	albumRect.setFillColor(sf::Color(0, 0, 255, 100));  // Blue translucent
	albumRect.setOutlineThickness(3.f);
	albumRect.setOutlineColor(sf::Color::Blue);

	// ArrowButton callbacks
	leftArrow->SetCallBack([this]() {
		if (albumUi.IsVisible())
			albumUi.Hide();
		else if (shelfUi.IsVisible())
			shelfUi.Hide();
		else if (boxUi.IsVisible())
			boxUi.Hide();
		else
			SCENE_MGR.ChangeScene(SceneIds::Dev2);
		});

	rightArrow->SetCallBack([this]() {
		if (shelfUi.IsVisible())
			shelfUi.Hide();
		if (boxUi.IsVisible())
			boxUi.Hide();
		else
		{
			// TODO: next scene logic
		}
		});

	numPad.SetOnOkPressed([this]() {
		if (numPad.IsPasswordCorrect())
		{
			std::cout << "[Scene1] Correct password!\n";
			sf::Texture& openedBoxTex = TEXTURE_MGR.Get("graphics/box_open_ui.png");
			boxUi.ChangeTexture(openedBoxTex);
			boxUi.SetOpened(true);
			numPad.SetActive(false);
		}
		});

	Scene::Init();
}

void Scene1::Enter()
{
	Scene::Enter();
	SetUpViews();
}

void Scene1::Exit()
{
	Scene::Exit();

	delete leftArrow;
	leftArrow = nullptr;

	delete rightArrow;
	rightArrow = nullptr;
}

void Scene1::Update(float dt)
{
	Scene::Update(dt);
	InputMgr::Update(dt);
	numPad.Update(dt);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		sf::Vector2f mousePosF = FRAMEWORK.GetWindow().mapPixelToCoords(InputMgr::GetMousePosition());

		if (albumUi.IsVisible())
		{
			// Handle clicks when album UI is visible (currently empty)
		}
		else if (shelfUi.IsVisible())
		{
			if (albumUi.CheckClick(mousePosF))
			{
				albumUi.Show();
				std::cout << "albumUi clicked\n";
			}
			else if (shelfUi.CheckClick(mousePosF))
			{
				std::cout << "이미 shelfUi 열려있음\n";
			}
		}
		else
		{
			if (shelfUi.CheckClick(mousePosF))
			{
				shelfUi.Show();
				boxUi.Hide();
				albumUi.Hide();
				numPad.SetActive(false);
				std::cout << "shelfUi clicked\n";
			}
			if (boxUi.CheckClick(mousePosF))
			{
				boxUi.Show();
				shelfUi.Hide();
				albumUi.Hide();
				numPad.SetActive(true);
				std::cout << "boxUi clicked\n";
			}
		}
	}

	// Update arrows if exist
	if (leftArrow) leftArrow->Update(dt);
	if (rightArrow) rightArrow->Update(dt);

	// Lighting effect (blink)
	blinkTimer += dt;
	if (blinkTimer >= blinkInterval)
	{
		blinkTimer = 0.f;
		int alpha = rand() % 176 + 80; // alpha range: 80~255
		light.setColor(sf::Color(255, 255, 255, alpha));
	}
}

void Scene1::ResourceLoad()
{
	texIds.push_back(texId);
	texIds.push_back(texId1);
	texIds.push_back("graphics/shelf_ui.png");
	texIds.push_back("graphics/box_ui.png");
	texIds.push_back("graphics/album_ui.png");
	texIds.push_back("graphics/box_open_ui.png");
}

void Scene1::SetUpViews()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	ResourceLoad();
	TEXTURE_MGR.Load(texIds);

	background1.setTexture(TEXTURE_MGR.Get(texId), true);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);
}

void Scene1::HandleEvent(const sf::Event& event)
{
	std::cout << "[Scene1] HandleEvent called, event type: " << event.type << std::endl;

	InputMgr::UpdateEvent(event);
	FRAMEWORK.GetWindow().setView(uiView);

	if (leftArrow)
		leftArrow->HandleEvent(event, FRAMEWORK.GetWindow());

	if (rightArrow)
		rightArrow->HandleEvent(event, FRAMEWORK.GetWindow());
}

void Scene1::Draw(sf::RenderWindow& window)
{
	window.setView(uiView);

	window.draw(background1);
	window.draw(light);

	window.draw(shelfRect);
	window.draw(boxRect);

	shelfUi.Draw(window, &albumRect);

	if (albumUi.IsVisible())
		window.draw(shadowBg);

	albumUi.Draw(window);
	boxUi.Draw(window);

	if (boxUi.IsVisible() && !boxUi.IsOpened() && numPad.GetActive())
		numPad.Draw(window);

	if (leftArrow) leftArrow->Draw(window);
	if (rightArrow) rightArrow->Draw(window);
}
