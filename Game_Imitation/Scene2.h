#pragma once
#include "stdafx.h"
#include "ZoomUI.h"
#include "SceneUiMgr.h"
#include "Inventory.h"
#include "TextGo.h"

class Scene2 : public Scene
{
public:
    Scene2();
    virtual ~Scene2() = default;

    void Init() override;
    void Enter() override;
    void Exit() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;
    void HandleEvent(const sf::Event& event) override;

private:
    void ResourceLoad();
    void SetUpViews();

    std::string texId2 = "graphics/scene2_bg.png";
    std::vector<std::string> texIds;

    sf::Sprite background2;
    ZoomUI tvUi;
    sf::RectangleShape tvRect;

    SceneUiMgr sceneUiMgr;
    sf::RectangleShape itemBg;

    bool isBatteryInserted = false;

    std::vector<Item*> itemsInTv;
    size_t nextItemIndex = 0;

    bool isItemInTvVisible = false;
    std::vector<sf::RectangleShape> itemBgsInTv;
    std::vector<TextGo*> itemLabels;

    std::string itemName;
    std::string textureName;
};
