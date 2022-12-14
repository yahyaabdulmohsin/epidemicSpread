#include <SFML/Graphics.hpp>
class Node{
public:
    Node(int type, int x, int y, float ScircleColor[], float IcircleColor[], float RcircleColor[], float infectionRadius, int timeToRecover);
    sf::RectangleShape getShape();
    sf::CircleShape getCircle();
    int getType();
    void infect();
    bool recover();
    void setVelocityX(int newV);
    int getVelocityX();
    void setVelocityY(int newV);
    int getVelocityY();
    void move();
private:
    int vel_x;
    int vel_y;
    int timeToRecover;
    int type,x,y;
    sf::RectangleShape rectangle{sf::Vector2f(10, 10)};
    sf::CircleShape circle;
    float* ScircleColor;
    float* IcircleColor;
    float* RcircleColor;
    float infectionRadius;
    sf::Clock clock;
    float elapsed;
};