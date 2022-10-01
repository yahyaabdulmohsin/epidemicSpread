#include <iostream>
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include "node.h"

/* TODO

create node class
test two nodes and make sure it works
create node generation
create node movement
_______________________
enable docking
show fps
show graphs
enable custom drawomg

*/

int main()
{
    // creating window
    sf::RenderWindow window(sf::VideoMode(800, 600), "epidemicSpread", sf::Style::Titlebar | sf::Style::Close);

    // modifying window
    //get window handle:    sf::WindowHandle handle = window.getSystemHandle();
    //set vsync:            window.setVerticalSyncEnabled(true);
    //set framerate:        window.setFramerateLimit(60);

    // setting up imgui
    ImGui::SFML::Init(window);
    // disabling imgui.ini
    ImGui::GetIO().IniFilename = NULL;

    // logic variables
    int numOfStartingNodes = 2;
    float percentageOfInfected = 0.f;
    float infectionRadius = 2.f;
    int infectionTime = 3;
    float probabilityOfInfection = 50.f;
    int timeToRecover = 0;
    float ScircleColor[3] = { (float)49/255, (float)96/255, (float)110/255};
    float IcircleColor[3] = { (float)247/255, (float)102/255, (float)84/255};
    float RcircleColor[3] = { (float)160/255, (float)159/255, (float)161/255};
    int state = 0;

    // creating shapes
    std::vector<Node> nodes;
    
    // creating clock
    sf::Clock deltaClock;

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
        if (state == 0){
            ImGui::SliderInt("#Nodes", &numOfStartingNodes, 2, 100000);
            ImGui::SliderFloat("%OfI", &percentageOfInfected, 0.f, 100.0f);
            ImGui::SliderFloat("Radius", &infectionRadius, 1.f, 10.0f);
            ImGui::SliderInt("Time(I)", &infectionTime, 0, 10);
            ImGui::SliderFloat("POI", &probabilityOfInfection, 0.f, 100.0f);
            ImGui::SliderInt("Time(R)", &timeToRecover, 0, 20);
            ImGui::ColorEdit3("SColor", ScircleColor);
            ImGui::ColorEdit3("IColor", IcircleColor);
            ImGui::ColorEdit3("RColor", RcircleColor);
        }else if (ImGui::Button("Reset")){
            // delete shapes here
            while (!nodes.empty())
            {
                nodes.pop_back();
            }
            state = 0;
        }
        switch(state) {
            case 0:
                // initial logic here
                if (ImGui::Button("Simulate")){
                    // generate shapes here
                    nodes.push_back(Node(0,650,200, ScircleColor, IcircleColor, RcircleColor, infectionRadius));
                    nodes.push_back(Node(1,550,200, ScircleColor, IcircleColor, RcircleColor, infectionRadius));
                    state = 1;
                }
                break;
            case 1:
                // simulation logic here
                
                    // start timer for infected nodes

                    // when timer ends
                        // check for each infected node if there are any nodes near
                            // if there are nodes take a chance and either infect them or no

                    // reset timer

                // logic ends here
                if (ImGui::Button("Pause")){
                    state = 2;
                }
                break;
            case 2:
                // simulation is paused here
                if (ImGui::Button("Continue")){
                    state = 1;
                }
                break;
        }
      
        if (state != 0){
            ImGui::Text("Stats");
            ImGui::Text("S =");
            ImGui::Text("I =");
            ImGui::Text("R =");
        }

        ImGui::Text("www.yahyaabdulmohsin.com");
        ImGui::End();
        // clear window
        window.clear(
        );
        // render shapes
        for (int i = 0; i < nodes.size(); i++){
            window.draw(nodes[i].getShape());
            window.draw(nodes[i].getCircle());
        }
        //window.draw(rectangle);
        // render imgui
        ImGui::SFML::Render(window);
        // display window
        window.display();
    }

    // shut down imgui
    ImGui::SFML::Shutdown();
    return 0;
}