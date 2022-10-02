#include "node.h"
Node::Node(int type, int x, int y, float ScircleColor[], float IcircleColor[], float RcircleColor[], float infectionRadius, int timeToRecover){
    this->timeToRecover = timeToRecover;
    this->ScircleColor = ScircleColor;
    this->IcircleColor = IcircleColor;
    this->RcircleColor = RcircleColor;
    this->infectionRadius = infectionRadius;
    this->type = type;
    this->x = x;
    this->y = y;
    this->rectangle.setOrigin(this->rectangle.getSize().x/2,this->rectangle.getSize().x/2);
    this->rectangle.setPosition(x,y);
    // setting initial color
    switch(this->type){
        case 0:
            this->rectangle.setFillColor(sf::Color(ScircleColor[0]*255, ScircleColor[1]*255, ScircleColor[2]*255));
            break;
        case 1:
            this->rectangle.setFillColor(sf::Color(IcircleColor[0]*255, IcircleColor[1]*255, IcircleColor[2]*255));
            this->circle.setRadius(infectionRadius*this->rectangle.getSize().x);
            this->circle.setOrigin(infectionRadius*this->rectangle.getSize().x,infectionRadius*this->rectangle.getSize().x);
            this->circle.setPosition(x,y);
            this->circle.setFillColor(sf::Color(IcircleColor[0]*255, IcircleColor[1]*255, IcircleColor[2]*255, 50));
            
            break;
        case 2:
            this->rectangle.setFillColor(sf::Color(RcircleColor[0]*255, RcircleColor[1]*255, RcircleColor[2]*255));
            break;
    }
}
sf::RectangleShape Node::getShape(){
    return this->rectangle;
}

sf::CircleShape Node::getCircle(){
    return this->circle;
}

int Node::getType(){
    return this->type;
}

void Node::infect(){
    this->type = 1;
    this->rectangle.setFillColor(sf::Color(IcircleColor[0]*255, IcircleColor[1]*255, IcircleColor[2]*255));
    this->circle.setRadius(infectionRadius*this->rectangle.getSize().x);
    this->circle.setOrigin(infectionRadius*this->rectangle.getSize().x,infectionRadius*this->rectangle.getSize().x);
    this->circle.setPosition(x,y);
    this->circle.setFillColor(sf::Color(IcircleColor[0]*255, IcircleColor[1]*255, IcircleColor[2]*255, 50));
    this->clock.restart();
}

bool Node::recover(){
    this->elapsed = clock.getElapsedTime().asSeconds();
    if(elapsed >= this->timeToRecover){
        this->type = 2;
        this->rectangle.setFillColor(sf::Color(RcircleColor[0]*255, RcircleColor[1]*255, RcircleColor[2]*255));
        this->circle.setRadius(0);
        return true;
    }
    return false;
}