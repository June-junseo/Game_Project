#pragma once
#include "stdafx.h"
#include "ZoomUI.h"
#include "SceneUiMgr.h"
#include "Inventory.h"

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

    ArrowButton* leftArrow = nullptr;
    ArrowButton* rightArrow = nullptr;

    sf::Sprite background2;
    ZoomUI tvUi;
    sf::RectangleShape tvRect;

    SceneUiMgr sceneUiMgr;
};
