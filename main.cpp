#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>

/* TODO

enable docking
show fps

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
    bool showCircle = true;
    float infectionRadius = 200.0f;
    int infectionTime = 100;
    float ScircleColor[3] = { (float)49/255, (float)96/255, (float)110/255};
    float IcircleColor[3] = { (float)247/255, (float)102/255, (float)84/255};
    float RcircleColor[3] = { (float)160/255, (float)159/255, (float)161/255};
    int state = 0;

    // creating shapes

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
        ImGui::SliderFloat("Radius", &infectionRadius, 100.0f, 300.0f);
        ImGui::SliderInt("Time", &infectionTime, 3, 150);
        ImGui::ColorEdit3("S Color", ScircleColor);
        ImGui::ColorEdit3("I Color", IcircleColor);
        ImGui::ColorEdit3("R Color", RcircleColor);
        if (ImGui::Button("Reset")){
            state = 0;
        }
        switch(state) {
            case 0:
                if (ImGui::Button("Simulate")){
                    state = 1;
                }
                break;
            case 1:
                if (ImGui::Button("Pause")){
                    state = 2;
                }
                break;
            case 2:
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

        // render imgui
        ImGui::SFML::Render(window);
        // display window
        window.display();
    }

    // shut down imgui
    ImGui::SFML::Shutdown();
    return 0;
}