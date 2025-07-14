#pragma once

class NumPad {
public:
    void Init(const sf::Vector2f& position, const sf::Vector2f& buttonSize);
    void Draw(sf::RenderWindow& window);
    void HandleEvent(const sf::Event& event, sf::RenderWindow& window);
    void Update(float dt);

    void SetVisible(bool visible);
    bool IsVisible() const;

    void SetPassword(const std::string& pw);
    bool IsPasswordCorrect() const;
    void ClearInput();
    void SetOnOkPressed(std::function<void()> callback);
    const std::string& GetInput() const;

private:
    std::vector<sf::RectangleShape> buttons;
    std::vector<std::string> labels;
    std::vector<sf::Text> texts;
    std::function<void()> onOkPressed;

    std::string input;
    std::string password;

    sf::Font font;
    bool visible = false;

    sf::Vector2f position;
    sf::Vector2f buttonSize;

    int pressedIndex = -1;
    sf::Clock pressClock;
};
