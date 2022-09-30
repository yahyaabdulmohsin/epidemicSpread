# epidemicSpread

honors project for physics :)

Build with g++:

> g++ -c main.cpp pathToProject\imgui\imgui.cpp pathToProject\imgui\imgui_widgets.cpp pathToProject\imgui\imgui_draw.cpp pathToProject\imgui\imgui_tables.cpp pathToProject\imgui\imgui-SFML.cpp -IpathToProject\imgui -IpathToSFML\include -DSFML_STATIC
>
> g++ main.o imgui.o imgui_widgets.o imgui_draw.o imgui_tables.o imgui-SFML.o -o main -LpathToSFML\lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32