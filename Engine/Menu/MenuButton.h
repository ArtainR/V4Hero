#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
class ButtonList;
class MenuButton
{
public:
    std::string buttonText;
    std::string endString;
    sf::Text t_buttonText;
    bool selected = false;
    float originX;
    float originY;
    sf::RectangleShape debug_text_bounding_box;
    ButtonList* parentList;
    int buttonListIndex;
    void Update(sf::RenderWindow& window, float fps, sf::Vector2f* mousePos);
    void SetSelected(bool isSelected);
    void MouseUp(int xPos, int yPos);
    void UpdateText();
    void AddEndString(std::string text);
    std::string GetEndString(std::string text);

    MenuButton(std::string text, sf::Font* font, int fontSize, float y, ButtonList* p_list, int index, float x = -1);
    ~MenuButton();
};


#endif // CAMERA_H
