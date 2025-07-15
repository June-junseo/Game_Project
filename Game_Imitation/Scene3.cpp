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

	sf::Vector2f center = windowSize * 0.5f;
	sf::Vector2f scaleSize(600.f, 600.f);
	sf::FloatRect scaleArea(center.x - scaleSize.x * 0.5 - 200, center.y - scaleSize.y * 0.5f + 150, scaleSize.x, scaleSize.y);
	scaleUi.Init(TEXTURE_MGR.Get("graphics/scale_ui.png"), center);
	scaleUi.SetClickableArea(scaleArea);

	sceneUiMgr.Init(FRAMEWORK.GetWindow(), windowSize);
	sceneUiMgr.CreateArrowButtons(windowSize);

	ArrowButton* leftArrow = sceneUiMgr.GetLeftArrow();
	ArrowButton* rightArrow = sceneUiMgr.GetRightArrow();
	sceneUiMgr.AddArrowButtons(leftArrow, rightArrow);

	scaleStick.setTexture(TEXTURE_MGR.Get("graphics/scale_stick.png"));
    scaleLeft.setTexture(TEXTURE_MGR.Get("graphics/scale_left.png"));
    scaleRight.setTexture(TEXTURE_MGR.Get("graphics/scale_right.png"));

    scaleStick.setPosition(center.x - 20.f, center.y - 100.f);
    scaleLeft.setPosition(center.x - 200.f, center.y);
    scaleRight.setPosition(center.x + 150.f, center.y);

	leftArrow->SetCallBack([this]() 
	{
		if (scaleUi.IsVisible())
		{
			scaleUi.Hide();
		}
		else
		SCENE_MGR.ChangeScene(SceneIds::Scene4);
	});
	rightArrow->SetCallBack([this]() 
	{ 
		if (scaleUi.IsVisible())
		{
			scaleUi.Hide();
		}
		else
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

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left)) 
	{
		sf::Vector2f mousePos = FRAMEWORK.GetWindow().mapPixelToCoords(InputMgr::GetMousePosition());

		Item* selectedItem = Inventory::Instance().GetSelectedItem();
		if (selectedItem) 
		{
			if (scaleLeft.getGlobalBounds().contains(mousePos)) 
			{
				AddItemToScale(selectedItem, true);
				Inventory::Instance().RemoveSelectedItem();
			}
			else if (scaleRight.getGlobalBounds().contains(mousePos)) 
			{
				AddItemToScale(selectedItem, false);
				Inventory::Instance().RemoveSelectedItem();
			}
		}

		Inventory::Instance().HandleClick(mousePos);
	}
}

void Scene3::AddItemToScale(Item* item, bool toLeft)
{
	float weight = 0.f;

	if (item->GetName() == "beer") weight = 2.0f;
	else if (item->GetName() == "clock") weight = 3.5f;
	else if (item->GetName() == "drug") weight = 1.5f;
	else if (item->GetName() == "phone") weight = 3.0f;

	if (toLeft) 
	{
		leftItems.push_back(item);
		leftWeight += weight;
	}
	else 
	{
		rightItems.push_back(item);
		rightWeight += weight;
	}

	CheckPuzzleSolved();
}

void Scene3::CheckPuzzleSolved()
{
	if (abs(leftWeight - rightWeight) < 0.01f && !puzzleSolved) 
	{
		puzzleSolved = true;
		std::cout << "ÆÛÁñ Å¬¸®¾î!" << std::endl;
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
	scaleUi.Draw(window);

	window.draw(scaleStick);
	window.draw(scaleLeft);
	window.draw(scaleRight);

	//items
	for (auto& item : leftItems)
		if (item) item->Draw(window);

	for (auto& item : rightItems)
		if (item) item->Draw(window);

	sceneUiMgr.Draw(window);
}

void Scene3::ResourceLoad()
{
	texIds = 
	{ 
		"graphics/scene3_bg.png", 
		"graphics/scale_ui.png",
		"graphics/scale_stick.png",
		"graphics/scale_left.png",
		"graphics/scale_right.png",
	};
}
void Scene3::SetUpViews()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	background3.setTexture(TEXTURE_MGR.Get(texId3), true);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);
}

