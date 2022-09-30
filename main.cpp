#include <imgui.h>
#include <imgui-SFML.h>
#include <iostream>
#include <SFML/Graphics.hpp>

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
    // disaplying imgui.ini
    ImGui::GetIO().IniFilename = NULL;

    // logic variables
    bool showCircle = true;
    float circleRadius = 200.0f;
    int circleSegments = 100;
    float circleColor[3] = { (float)204/255, (float)77/255, (float)5/255};

    // creating shapes
    sf::CircleShape shape(circleRadius,100);
    shape.setFillColor(sf::Color(
        (int)(circleColor[0] * 255),
        (int)(circleColor[1] * 255),
        (int)(circleColor[2] * 255)
    ));
    shape.setOrigin(circleRadius, circleRadius);
    shape.setPosition(400,300);

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
        ImGui::Checkbox("Circle", &showCircle);
        ImGui::SliderFloat("Radius", &circleRadius, 100.0f, 300.0f);
        ImGui::SliderInt("Segments", &circleSegments, 3, 150);
        ImGui::ColorEdit3("Color", circleColor);
        if (ImGui::Button("Simulate"))
            std::cout << "Hello world!";
        ImGui::Text("www.yahyaabdulmohsin.com");
        ImGui::End();
        // clear window
        window.clear(
        );
        // render shapes
        if (showCircle){

            shape.setPointCount(circleSegments);
            shape.setRadius(circleRadius);
            shape.setOrigin(circleRadius, circleRadius);
            shape.setFillColor(sf::Color(
                (int)(circleColor[0] * 255),
                (int)(circleColor[1] * 255),
                (int)(circleColor[2] * 255)
            ));
            window.draw(shape);
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