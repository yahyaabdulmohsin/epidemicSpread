#include <SFML/Graphics.hpp>
class Node{
public:
    Node(int type, int x, int y, float ScircleColor[], float IcircleColor[], float RcircleColor[], float infectionRadius);
    sf::RectangleShape getShape();
    sf::CircleShape getCircle();
    int getType();
private:
    int type,x,y;
    sf::RectangleShape rectangle{sf::Vector2f(50, 50)};
    sf::CircleShape circle;
};