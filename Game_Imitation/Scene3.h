#pragma once
#include "stdafx.h"
#include "ZoomUI.h"
#include "SceneUiMgr.h"
#include "Inventory.h"
#include "AniPlayer.h"

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
    void ScaleReset();

    std::string texId3 = "graphics/scene3_bg.png";
    sf::Sprite background3;

    std::vector<std::string> texIds;

    sf::Sprite scaleStick;
    sf::Sprite scaleLeft;
    sf::Sprite scaleRight;
    std::vector<Item*> leftItems;
    std::vector<Item*> rightItems;

    sf::RectangleShape leftDebugRect;
    sf::RectangleShape rightDebugRect;

    sf::RectangleShape shadowBg;

    float leftWeight = 0.f;
    float rightWeight = 0.f;

    bool puzzleSolved = false;

    void AddItemToScale(Item* item, bool toLeft);
    void CheckPuzzleSolved();

    bool isScaleActive = false;

    bool isResetPending = false; 
    float resetTimer = 0.f;      
    const float resetDelay = 1.5f; 

    int scaleItems = 4;

    sf::Sprite keySprite;

    SceneUiMgr sceneUiMgr;

    ZoomUI scaleUi;
    ZoomUI goddnessUi;

    sf::RectangleShape scaleRect;
    sf::RectangleShape goddnessRect;

    sf::FloatRect leftScaleRect;
    sf::FloatRect rightScaleRect;

    //scale animaton
    float stickTargetRotation = 0.f;
    float stickCurrentRotation = 0.f;

    float leftTargetOffsetY = 0.f;
    float leftCurrentOffsetY = 0.f;

    float rightTargetOffsetY = 0.f;
    float rightCurrentOffsetY = 0.f;

    bool isKeyCollected = false;
    bool isKeyVisible = false;

    bool isGoddnessClicked = false;

};