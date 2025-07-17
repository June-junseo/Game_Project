#include "stdafx.h"
#include "Scene1.h"
#include "Scene2.h"
#include "ArrowButton.h"
#include "ZoomUI.h"
#include "Inventory.h"
#include "SceneUiMgr.h"
#include "Scene3.h"
#include "Scene4.h"

Scene4::Scene4()
	:Scene(SceneIds::Scene4)
{
}

void Scene4::Init()
{
	Inventory::Instance().Init();
	ResourceLoad();
	TEXTURE_MGR.Load(texIds);
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	background4.setPosition(0.f, 0.f);
	background4.setTexture(TEXTURE_MGR.Get(texId4), true);

	openDoorSprite.setTexture(TEXTURE_MGR.Get("graphics/scene4_door_open.png"));
	openDoorSprite.setPosition(0.f, 0.f);

	sceneUiMgr.Init(FRAMEWORK.GetWindow(), windowSize);
	sceneUiMgr.CreateArrowButtons(windowSize);

	ArrowButton* leftArrow = sceneUiMgr.GetLeftArrow();
	ArrowButton* rightArrow = sceneUiMgr.GetRightArrow();
	sceneUiMgr.AddArrowButtons(leftArrow, rightArrow);

	leftArrow->SetCallBack([this]() 
	{
	});
	rightArrow->SetCallBack([this]() 
	{
		SCENE_MGR.ChangeScene(SceneIds::Scene3);
	});
	Scene::Init();
}

void Scene4::Enter()
{
	Scene::Enter();
	ResourceLoad();
	TEXTURE_MGR.Load(texIds);
	background4.setTexture(TEXTURE_MGR.Get(texId4), true);
}

void Scene4::Exit()
{
	Scene::Exit();
}

void Scene4::Update(float dt)
{
	Scene::Update(dt);
	sceneUiMgr.Update(dt);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = FRAMEWORK.GetWindow().mapPixelToCoords(InputMgr::GetMousePosition());

		if (!isDoorOpened)
		{
			sf::FloatRect doorArea(uiView.getCenter().x - 350.f, uiView.getCenter().y - 300.f, 400.f, 700.f);

			if (doorArea.contains(mousePos))
			{
				Item* selectedItem = Inventory::Instance().GetSelectedItem();
				if (selectedItem && selectedItem->GetName() == "key")
				{
					isDoorOpened = true;
					isKeyUsed = true;
					Inventory::Instance().RemoveSelectedItem();
					std::cout << "door open." << std::endl;
				}
			}
		}
		Inventory::Instance().HandleClick(mousePos);
	}
}

void Scene4::HandleEvent(const sf::Event& event)
{
	sceneUiMgr.HandleEvent(event, FRAMEWORK.GetWindow());
}


void Scene4::Draw(sf::RenderWindow& window)
{
	window.setView(uiView);

	if (isDoorOpened && isKeyUsed)
	{
		window.draw(openDoorSprite);
	}
	else
	{
		window.draw(background4);
	}

	sceneUiMgr.Draw(window);
}

void Scene4::ResourceLoad()
{
	texIds.push_back("graphics/scene4_bg.png");
	texIds.push_back("graphics/scene4_door_open.png");
}
void Scene4::SetUpViews()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	background4.setTexture(TEXTURE_MGR.Get(texId4), true);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);
}

