#include <iostream>
#include <cmath>
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include "node.h"

/* TODO

create infected node generation based on area
make area dragable
create node movement
_______________________
enable docking
show fps
show graphs
enable custom drawing

*/

int main()
{
    // initialize random seed
    srand (time(NULL));

    // creating window
    sf::RenderWindow window(sf::VideoMode(1280, 720), "epidemicSpread", sf::Style::Titlebar | sf::Style::Close);

    // modifying window
    //get window handle:    sf::WindowHandle handle = window.getSystemHandle();
    //set vsync:            window.setVerticalSyncEnabled(true);
    //set framerate:        window.setFramerateLimit(60);

    // setting up imgui
    if (ImGui::SFML::Init(window));
    // disabling imgui.ini
    ImGui::GetIO().IniFilename = NULL;

    // logic variables
    int numOfS = 0;
    int numOfI = 0;
    int numOfR = 0;
    int numOfStartingNodes = 2;
    float percentageOfInfected = 0.f;
    float infectionRadius = 2.f;
    int infectionTime = 3;
    int area1X = 427;
    int area1Y = 240;
    int area2X = 853;
    int area2Y = 480;
    float probabilityOfInfection = 50.f;
    int timeToRecover = 5;
    float ScircleColor[3] = { (float)49/255, (float)96/255, (float)110/255};
    float IcircleColor[3] = { (float)247/255, (float)102/255, (float)84/255};
    float RcircleColor[3] = { (float)160/255, (float)159/255, (float)161/255};
    int state = 0;

    // creating shapes
    std::vector<Node> nodes;
    sf::RectangleShape rectangle(sf::Vector2f(128.0f,128.0f));
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setPosition(320,240);

    // creating clock for imgui
    sf::Clock deltaClock;

    // creating clock for nodes
    sf::Clock clock;
    float elapsed;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // process imgui event
            ImGui::SFML::ProcessEvent(event);

            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // update imgui
        ImGui::SFML::Update(window, deltaClock.restart());
        // imgui stuff here
        ImGui::Begin("Control Panel");
        // clear window
        window.clear();
        switch(state) {
            case 0:
                // creating state 0 GUI
                ImGui::SliderInt("#Nodes", &numOfStartingNodes, 2, 5000);
                ImGui::SliderFloat("%OfI", &percentageOfInfected, 0.f, 100.0f);

                ImGui::SliderInt("area1X", &area1X, 0, area2X-10);
                ImGui::SliderInt("area1Y", &area1Y, 0, area2Y-10);
                ImGui::SliderInt("area2X", &area2X, area1X+10, 1280);
                ImGui::SliderInt("area2Y", &area2Y, area1Y+10, 720);

                ImGui::SliderFloat("Radius", &infectionRadius, 1.f, 10.0f);
                ImGui::SliderInt("Time(I)", &infectionTime, 0, 10);
                ImGui::SliderFloat("POI", &probabilityOfInfection, 0.f, 100.0f);
                ImGui::SliderInt("Time(R)", &timeToRecover, 0, 20);
                ImGui::ColorEdit3("SColor", ScircleColor);
                ImGui::ColorEdit3("IColor", IcircleColor);
                ImGui::ColorEdit3("RColor", RcircleColor);
                // initial infected area rectangle
                rectangle.setSize(sf::Vector2f((float)area2X-area1X,(float)area2Y-area1Y));
                rectangle.setPosition(area1X,area1Y);
                window.draw(rectangle);
                // initial logic here
                if (ImGui::Button("Simulate")){
                    srand((unsigned) time(NULL));
                    // generate shapes here
                    // figure out how many are infected
                    int numOfInfected = (percentageOfInfected/100)*numOfStartingNodes;
                    for (int i = 0; i < numOfStartingNodes-numOfInfected; i++){
                        int chancex = rand() % 1279 + 1;
                        int chancey = rand() % 719 + 1;
                        nodes.push_back(Node(0,chancex,chancey, ScircleColor, IcircleColor, RcircleColor, infectionRadius, timeToRecover));
                        numOfS++;
                    }
                    for (int i = 0; i < numOfInfected; i++){
                        int chancex = rand() % (area2X-area1X) + area1X;
                        int chancey = rand() % (area2Y-area1Y) + area1Y;
                        nodes.push_back(Node(1,chancex,chancey, ScircleColor, IcircleColor, RcircleColor, infectionRadius, timeToRecover));
                        numOfI++;
                    }
                    state = 1;
                    // start timer here
                    clock.restart();
                }
                break;
            case 1:
                // creating state 1 GUI
                ImGui::Text("Stats");
                ImGui::Text("S = %i", numOfS);
                ImGui::Text("I = %i", numOfI);
                ImGui::Text("R = %i", numOfR);
                if (ImGui::Button("Reset")){
                    // delete shapes here
                    while (!nodes.empty())
                    {
                        nodes.pop_back();
                    }
                    state = 0;
                    numOfS = 0;
                    numOfI = 0;
                    numOfR = 0;
                }
                // simulation logic here
                // check if infection timer ended
                elapsed = clock.getElapsedTime().asSeconds();
                if (elapsed >= infectionTime){
                    // check for each infected node if there are any nodes near
                    for(int i = 0; i < nodes.size(); i++){
                        if (nodes[i].getType() == 1){
                            for (int j = 0; j < nodes.size(); j++){
                                if (nodes[j].getType() == 0){
                                    // check if node[j] is in node[i] infection radius
                                    bool inRadius = false;
                                    sf::Vector2f ipos = nodes[i].getShape().getPosition();
                                    sf::Vector2f jpos = nodes[j].getShape().getPosition();
                                    sf::Vector2f distanceVec = jpos - ipos;
                                    float distance = std::sqrt((distanceVec.x*distanceVec.x)+(distanceVec.y*distanceVec.y));
                                    if (distance <= infectionRadius*nodes[i].getShape().getSize().x){
                                        inRadius = true;
                                    }
                                    if (inRadius){
                                        // EXPOSED take chance and either infect or no
                                        int chance = rand() % 100 + 1;
                                        if ((float)chance <= probabilityOfInfection){
                                            numOfS--;
                                            numOfI++;
                                            nodes[j].infect();
                                        }
                                    }
                                }
                            }
                        }
                    }
                    clock.restart();
                }

                // check if recover timer ended
                for (int i = 0; i < nodes.size(); i++){
                    if (nodes[i].getType() == 1){
                        if(nodes[i].recover()){
                            numOfI--;
                            numOfR++;
                        }
                    }
                    // move nodes here
                    int randomX = 1 + (rand() % 12);
                    int randomY = 1 + (rand() % 12);
                    if (randomX <= 10){
                        randomX *= -1;
                    }else if (randomX >= 1280-nodes[i].getShape().getPosition().x){
                        randomX *= -1;
                    }
                    if (randomY <= 10){
                        randomY *= -1;
                    }else if (randomY >= 720-nodes[i].getShape().getPosition().y){
                        randomY *= -1;
                    }
                    nodes[i].setVelocityX(randomX);
                    nodes[i].setVelocityY(randomY);
                }
                // logic ends here
                break;
        }

        ImGui::Text("www.yahyaabdulmohsin.com");
        ImGui::End();

        // render shapes
        for (int i = 0; i < nodes.size(); i++){
            window.draw(nodes[i].getShape());
            window.draw(nodes[i].getCircle());
        }
        // render imgui
        ImGui::SFML::Render(window);
        // display window
        window.display();
    }

    // shut down imgui
    ImGui::SFML::Shutdown();
    return 0;
}