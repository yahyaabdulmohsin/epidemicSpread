# epidemicSpread

honors project for physics :)

You need:
- SFML
- Dear ImGui (included in source code)

![alt text](/epidemicSpread/initial.png)

![alt text](/epidemicSpread/final.png)

Build with g++:

>g++ -c main.cpp node.cpp .\imgui\imgui.cpp .\imgui\imgui_widgets.cpp .\imgui\imgui_draw.cpp .\imgui\imgui_tables.cpp .\imgui\imgui-SFML.cpp -I.\imgui -IC:\SFML-2.5.1\include -DSFML_STATIC
>
>g++ main.o node.o imgui.o imgui_widgets.o imgui_draw.o imgui_tables.o imgui-SFML.o -o main -LC:\SFML-2.5.1\lib -static -static-libgcc -static-libstdc++ -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -mwindows
