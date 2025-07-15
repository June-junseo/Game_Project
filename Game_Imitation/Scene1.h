#pragma once
#include "stdafx.h"
#include "NumPad.h"
#include "ZoomUI.h"
#include "SceneUiMgr.h"
#include "Inventory.h"

class Scene1 : public Scene
{
public:
    Scene1();
    virtual ~Scene1() = default;

    void Init() override;
    void Enter() override;
    void Exit() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;
    void HandleEvent(const sf::Event& event) override;

private:
    void ResourceLoad();
    void SetUpViews();

    std::string texId = "graphics/scene1_bg.png";
    std::string texId1 = "graphics/light.png";
    std::vector<std::string> texIds;

    sf::Sprite background1;
    sf::Sprite light;
    sf::RectangleShape shadowBg;

    NumPad numPad;

    ZoomUI shelfUi;
    ZoomUI boxUi;
    ZoomUI albumUi;

    ArrowButton* leftArrow = nullptr;
    ArrowButton* rightArrow = nullptr;

    sf::RectangleShape shelfRect;
    sf::RectangleShape boxRect;
    sf::RectangleShape albumRect;

    sf::Sprite batterySprite;
    bool isBatteryVisible = false;

    float blinkTimer = 0.f;
    float blinkInterval = 0.15f;

    SceneUiMgr sceneUiMgr;
};

