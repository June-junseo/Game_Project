#include "stdafx.h"
#include "NumPad.h"

NumPad::NumPad(const std::string& name)
    : GameObject(name)
{
    active = false;
}

void NumPad::Init(const sf::Vector2f& position, const sf::Vector2f& buttonSize)
{
    this->position = position;
    this->buttonSize = buttonSize;

    buttons.clear();
    texts.clear();

    font.loadFromFile("fonts/fFlyingBird.ttf");

    labels = {
        "1", "2", "3",
        "4", "5", "6",
        "7", "8", "9",
        "C", "0", "OK"
    };

    for (int i = 0; i < 12; ++i)
    {
        sf::RectangleShape button(buttonSize);
        int row = i / 3;
        int col = i % 3;
        button.setPosition(position.x + col * (buttonSize.x + 10.f), position.y + row * (buttonSize.y + 10.f));
        button.setFillColor(sf::Color(255, 195, 30));
        button.setOutlineColor(sf::Color::Black);
        button.setOutlineThickness(4.f);

        buttons.push_back(button);

        sf::Text text;
        text.setFont(font);
        text.setString(labels[i]);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Black);

        sf::FloatRect textRect = text.getGlobalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
        sf::Vector2f buttonCenter = button.getPosition() + buttonSize / 2.f;
        text.setPosition(buttonCenter);
        texts.push_back(text);
    }
}

void NumPad::Draw(sf::RenderWindow& window)
{
    if (!active) return;

    for (size_t i = 0; i < buttons.size(); ++i)
    {
        window.draw(buttons[i]);
        window.draw(texts[i]);
    }
}

void NumPad::Update(float dt)
{
    if (!active) return;

    if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
    {
        sf::Vector2i rawMousePos = InputMgr::GetMousePosition();
        sf::Vector2f mappedMousePos = FRAMEWORK.GetWindow().mapPixelToCoords(rawMousePos);
     
        for (size_t i = 0; i < buttons.size(); ++i)
        {
            if (buttons[i].getGlobalBounds().contains(mappedMousePos))
            {

                buttons[i].setFillColor(sf::Color(255, 100, 0));
                pressedIndex = static_cast<int>(i);
                pressClock.restart();

                const std::string& label = labels[i];
                if (label == "C")
                {
                    input.clear();
                }
                else if (label == "OK")
                {
                    if (onOkPressed)
                        onOkPressed();
                }
                else
                {
                    input += label;
                }

                break;
            }
        }
    }

    if (pressedIndex != -1 && pressClock.getElapsedTime().asSeconds() > 0.2f)
    {
        buttons[pressedIndex].setFillColor(sf::Color(255, 195, 30));
        pressedIndex = -1;
    }
}

void NumPad::SetPassword(const std::string& pw) { password = pw; }
bool NumPad::IsPasswordCorrect() const { return input == password; }
void NumPad::ClearInput() { input.clear(); }
const std::string& NumPad::GetInput() const { return input; }
void NumPad::SetOnOkPressed(std::function<void()> callback) { onOkPressed = callback; }
