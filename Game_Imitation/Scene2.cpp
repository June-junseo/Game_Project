#include "stdafx.h"
#include "Scene1.h"
#include "Scene2.h"
#include "ArrowButton.h"
#include "ZoomUI.h"
#include "Inventory.h"
#include "SceneUiMgr.h"
#include "SceneData.h"

Scene2::Scene2() 
	: Scene(SceneIds::Scene2)
{
}

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
	sf::Vector2f tvSize(420.f, 350.f);
	sf::FloatRect tvArea(center.x - tvSize.x * 0.5 -100, center.y - tvSize.y * 0.5f + 170, tvSize.x, tvSize.y);
	tvUi.Init(TEXTURE_MGR.Get("graphics/tv_ui.png"), center);
	tvUi.SetClickableArea(tvArea);

	leftArrow->SetCallBack([this]() {
		if (tvUi.IsVisible()) 
		{ 
			tvUi.Hide();
		}
		else
		SCENE_MGR.ChangeScene(SceneIds::Scene3);
		});
	rightArrow->SetCallBack([this]() { //func
		if (tvUi.IsVisible())
		{
			tvUi.Hide();
		}
		else
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
	if (SceneData::batteryUsed)
	{
		tvUi.ChangeTexture(TEXTURE_MGR.Get("graphics/tv_ui_battery.png"));
	}
	else
	{
		tvUi.ChangeTexture(TEXTURE_MGR.Get("graphics/tv_ui.png"));
	}
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

		if (tvUi.CheckClick(mousePos)) {

			tvUi.Show();

			Item* selectedItem = Inventory::Instance().GetSelectedItem();

			if (selectedItem && selectedItem->GetName() == "battery") {

				SceneData::batteryUsed = true;

				Inventory::Instance().RemoveSelectedItem();

				tvUi.ChangeTexture(TEXTURE_MGR.Get("graphics/tv_ui_battery.png"));
				tvUi.Show();

				itemsInTv.clear();
				nextItemIndex = 0;
				isItemInTvVisible = true;

				sf::Vector2f basePos = uiView.getCenter() + sf::Vector2f(-210.f,-120.f) ;
				sf::Vector2f itemSize(50.f, 50.f);

				for (int i = 0; i < 4; ++i) {
					switch (i) {
					case 0:
						itemName = "beer";
						textureName = "graphics/item_beer.png";
						break;
					case 1:
						itemName = "clock";
						textureName = "graphics/item_clock.png";
						break;
					case 2:
						itemName = "drug";
						textureName = "graphics/item_drug.png";
						break;
					case 3:
						itemName = "phone";
						textureName = "graphics/item_phone.png";
						break;
					}

					Item* item = new Item(itemName, textureName);
					item->Init();
					item->SetPosition(basePos);
					itemsInTv.push_back(item);
				}
			}
		}

		if (isItemInTvVisible && nextItemIndex < itemsInTv.size()) {
			Item* currentItem = itemsInTv[nextItemIndex];
			if (currentItem && currentItem->GetGlobalBounds().contains(mousePos)) {

				Inventory::Instance().AddItem(currentItem);

				itemsInTv[nextItemIndex] = nullptr;
				nextItemIndex++;

				if (nextItemIndex >= itemsInTv.size()) {
					isItemInTvVisible = false;
					itemsInTv.clear();
				}
			}
		}
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
	window.draw(tvRect);
	if (tvUi.IsVisible()) tvUi.Draw(window);
	sceneUiMgr.Draw(window);
	if (isItemInTvVisible) {
		for (auto& item : itemsInTv) {
			if (item)
				item->Draw(window);
		}
	}
}

void Scene2::ResourceLoad()
{
	texIds = { texId2,
		"graphics/tv_ui.png",
		"graphics/tv_ui_battery.png", 
		"graphics/item_beer.png",
		"graphics/item_clock.png",
		"graphics/item_phone.png",
		"graphics/item_drug.png"
	};
}

void Scene2::SetUpViews()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	background2.setTexture(TEXTURE_MGR.Get(texId2), true);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);
}