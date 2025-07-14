#pragma once
#include "stdafx.h"

class NumPad : public GameObject
{
public:
    NumPad(const std::string& name = "NumPad");

    void Init(const sf::Vector2f& position, const sf::Vector2f& buttonSize);

    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;

    void SetPassword(const std::string& pw);
    bool IsPasswordCorrect() const;
    void ClearInput();
    const std::string& GetInput() const;

    void SetOnOkPressed(std::function<void()> callback);

    void Init() override {}                     
    void Release() override {}                   
    void Reset() override { input.clear(); }     

    void HandleEvent(const sf::Event& event, const sf::RenderWindow& window) override {} 
    sf::FloatRect GetLocalBounds() const override { return sf::FloatRect(); }

    sf::FloatRect GetGlobalBounds() const override {
        if (!buttons.empty())
            return buttons.front().getGlobalBounds(); 
        return sf::FloatRect();
    }

private:
    sf::Vector2f buttonSize;
    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> texts;
    std::vector<std::string> labels;

    std::string password;
    std::string input;

    sf::Font font;
    int pressedIndex = -1;
    sf::Clock pressClock;

    std::function<void()> onOkPressed;
};
