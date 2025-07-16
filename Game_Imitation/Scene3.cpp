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
	sf::FloatRect scaleArea(center.x - scaleSize.x * 0.5f - 200, center.y - scaleSize.y * 0.5f + 150, scaleSize.x, scaleSize.y);
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

	scaleStick.setPosition(center.x - 60 - scaleStick.getGlobalBounds().width * 0.5f, center.y - 100.f);
	scaleLeft.setPosition(scaleStick.getPosition().x - 150.f, scaleStick.getPosition().y - 60.f);
	scaleRight.setPosition(scaleStick.getPosition().x - 200.f + scaleStick.getGlobalBounds().width, scaleStick.getPosition().y - 60.f);

	isScaleActive = false;

	leftArrow->SetCallBack([this]() {
		if (scaleUi.IsVisible())
			scaleUi.Hide();
		else
			SCENE_MGR.ChangeScene(SceneIds::Scene4);
		});
	rightArrow->SetCallBack([this]() {
		if (scaleUi.IsVisible())
			scaleUi.Hide();
		else
			SCENE_MGR.ChangeScene(SceneIds::Scene2);
		});

	keySprite.setTexture(TEXTURE_MGR.Get("graphics/item_key.png"));
	keySprite.setScale(2.f, 2.f);
	keySprite.setOrigin(keySprite.getGlobalBounds().width / 2.f, keySprite.getGlobalBounds().height / 2.f);
	keySprite.setPosition(windowSize.x * 0.5f - 10.f, windowSize.y * 0.5f + 110.f);

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

	sf::Vector2f mousePos = FRAMEWORK.GetWindow().mapPixelToCoords(InputMgr::GetMousePosition(), uiView);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		if (scaleUi.CheckClick(mousePos))
		{
			isScaleActive = true;
			scaleUi.Show();
			return;
		}

		if (isScaleActive)
		{
			Item* selectedItem = Inventory::Instance().GetSelectedItem();
			if (selectedItem)
			{
				sf::Sprite scaleLeftClickable = scaleLeft;
				sf::Sprite scaleRightClickable = scaleRight;

				scaleLeftClickable.setOrigin(scaleLeftClickable.getLocalBounds().width * 0.5f,
					scaleLeftClickable.getLocalBounds().height * 0.5f);
				scaleLeftClickable.setPosition(scaleLeft.getPosition().x + scaleLeft.getGlobalBounds().width * 0.5f,
					scaleLeft.getPosition().y + scaleLeft.getGlobalBounds().height * 0.5f);
				scaleLeftClickable.setScale(2.f, 2.f);

				scaleRightClickable.setOrigin(scaleRightClickable.getLocalBounds().width * 0.5f,
					scaleRightClickable.getLocalBounds().height * 0.5f);
				scaleRightClickable.setPosition(scaleRight.getPosition().x + scaleRight.getGlobalBounds().width * 0.5f,
					scaleRight.getPosition().y + scaleRight.getGlobalBounds().height * 0.5f);
				scaleRightClickable.setScale(2.f, 2.f);

				if (scaleLeftClickable.getGlobalBounds().contains(mousePos))
				{
					AddItemToScale(selectedItem, true);
					Inventory::Instance().RemoveSelectedItem();
				}
				else if (scaleRightClickable.getGlobalBounds().contains(mousePos))
				{
					AddItemToScale(selectedItem, false);
					Inventory::Instance().RemoveSelectedItem();
				}
			}
		}

		if (!isKeyCollected && puzzleSolved)
		{
			SetUpViews();
			if (keySprite.getGlobalBounds().contains(mousePos))
			{
				std::cout << "Key clicked!" << std::endl;
				if (!Inventory::Instance().HasItem("key"))
				{
					Item* keyItem = new Item("key", "graphics/item_key.png");
					keyItem->Init();
					Inventory::Instance().AddItem(keyItem);
				}
				isKeyCollected = true;
			}
		}

		Inventory::Instance().HandleClick(mousePos);
	}

	float interpSpeed = 6.f;
	stickCurrentRotation += (stickTargetRotation - stickCurrentRotation) * dt * interpSpeed;
	leftCurrentOffsetY += (leftTargetOffsetY - leftCurrentOffsetY) * dt * interpSpeed;
	rightCurrentOffsetY += (rightTargetOffsetY - rightCurrentOffsetY) * dt * interpSpeed;

	scaleStick.setRotation(stickCurrentRotation);
	scaleLeft.setPosition(scaleStick.getPosition().x - 150.f, scaleStick.getPosition().y - 60.f + leftCurrentOffsetY);
	scaleRight.setPosition(scaleStick.getPosition().x - 200.f + scaleStick.getGlobalBounds().width, scaleStick.getPosition().y - 60.f + rightCurrentOffsetY);
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
		leftTargetOffsetY = Utils::Clamp(-15.f * leftItems.size(), -30.f, 30.f);
	}
	else
	{
		rightItems.push_back(item);
		rightWeight += weight;
		rightTargetOffsetY = Utils::Clamp(15.f * rightItems.size(), -30.f, 30.f);
	}

	CheckPuzzleSolved();
}

void Scene3::CheckPuzzleSolved()
{
	if (abs(leftWeight - rightWeight) < 0.01f && !puzzleSolved)
	{
		puzzleSolved = true;
		std::cout << "clear!" << std::endl;
	}

	float diff = rightWeight - leftWeight;
	stickTargetRotation = Utils::Clamp(diff * 3.f, -10.f, 10.f);
	leftTargetOffsetY = Utils::Clamp(diff * -70.f, -30.f, 70.f);
	rightTargetOffsetY = Utils::Clamp(diff * 70.f, -30.f, 70.f);
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

	window.draw(scaleRect);

	if (!isScaleActive || scaleUi.IsVisible())
		scaleUi.Draw(window);

	if (isScaleActive && scaleUi.IsVisible())
	{
		window.draw(scaleStick);
		window.draw(scaleLeft);
		window.draw(scaleRight);

		window.draw(leftDebugRect);
		window.draw(rightDebugRect);

		for (size_t i = 0; i < leftItems.size(); ++i)
		{
			if (leftItems[i])
			{
				float baseX = scaleLeft.getPosition().x + 50.f;
				float baseY = scaleLeft.getPosition().y - 100.f;
				leftItems[i]->SetPosition({ baseX, baseY - static_cast<float>(i) * 30.f });
				leftItems[i]->Draw(window);
			}
		}

		for (size_t i = 0; i < rightItems.size(); ++i)
		{
			if (rightItems[i])
			{
				float baseX = scaleRight.getPosition().x + 50.f;
				float baseY = scaleRight.getPosition().y - 100.f;
				rightItems[i]->SetPosition({ baseX, baseY - static_cast<float>(i) * 30.f });
				rightItems[i]->Draw(window);
			}
		}

		if (!isKeyCollected && puzzleSolved)
			window.draw(keySprite);
	}

	sceneUiMgr.Draw(window);
}

void Scene3::SetUpViews()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	background3.setTexture(TEXTURE_MGR.Get(texId3), true);
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);
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
		"graphics/item_key.png"
	};
}
