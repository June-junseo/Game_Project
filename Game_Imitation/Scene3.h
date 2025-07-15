#pragma once
#include "stdafx.h"
#include "ZoomUI.h"
#include "SceneUiMgr.h"
#include "Inventory.h"

class Scene3 : public Scene
{
public:
    Scene3();
    virtual ~Scene3() = default;

    void Init() override;
    void Enter() override;
    void Exit() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;
    void HandleEvent(const sf::Event& event) override;

private:
    void ResourceLoad();
    void SetUpViews();

    std::string texId3 = "graphics/scene3_bg.png";
    sf::Sprite background3;

    std::vector<std::string> texIds;

    SceneUiMgr sceneUiMgr;

    ZoomUI scaleUi;
};