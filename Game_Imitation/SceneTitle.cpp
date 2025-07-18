#include "stdafx.h"
#include "SceneTitle.h"

SceneTitle::SceneTitle()
	:Scene(SceneIds::Title)
{
}

void SceneTitle::Init()
{
	Scene::Init();

	SetUpViews();  

	titleBg.setTexture(TEXTURE_MGR.Get(texIdTitle), true);

	font = FONT_MGR.Get("fonts/fFlyingBird.ttf");
	titleText.setFont(font);
	titleText.setString("Start");
	titleText.setCharacterSize(80);
	titleText.setFillColor(sf::Color::White);

	sf::FloatRect bounds = titleText.getLocalBounds();
	titleText.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);

	float yOffset = 300.f;
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	titleText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f + yOffset);
	
}

void SceneTitle::Enter()
{
	SetUpViews();
	Scene::Enter();
}

void SceneTitle::Exit()
{
	Scene::Exit();
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);
	sf::Vector2i mousePos = sf::Mouse::getPosition(FRAMEWORK.GetWindow());
	sf::Vector2f worldPos = FRAMEWORK.GetWindow().mapPixelToCoords(mousePos, uiView);

	if (titleText.getGlobalBounds().contains(worldPos))
	{
		titleText.setFillColor(sf::Color::Black);
		titleText.setScale(1.1f, 1.1f);
	}
	else
	{
		titleText.setFillColor(sf::Color::Yellow);
		titleText.setScale(1.0f, 1.0f);
	}

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		if (titleText.getGlobalBounds().contains(worldPos))
		{
			SCENE_MGR.ChangeScene(SceneIds::Scene1);
		}
	}

}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	window.setView(uiView);
	window.draw(titleBg);
	window.draw(titleText);
}

void SceneTitle::ResourceLoad()
{
	fontIds.push_back("fonts/fFlyingBird.ttf");
	texIds.push_back(texIdTitle);
}

void SceneTitle::SetUpViews()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	ResourceLoad();
	TEXTURE_MGR.Load(texIds);
	FONT_MGR.Load(fontIds);

	titleBg.setTexture(TEXTURE_MGR.Get(texIdTitle), true);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);
}
