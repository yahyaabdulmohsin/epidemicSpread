# epidemicSpread

honors project for physics :)

You need:
- SFML
- Dear ImGui (included in source code)

![alt text](https://yahyaabdulmohsin.com/epidemicSpread/initial.png)

![alt text](https://yahyaabdulmohsin.com/epidemicSpread/final.png)

Build with g++:

>g++ -c main.cpp node.cpp C:\Users\yahya\Desktop\playground\c++\imgui\imgui.cpp C:\Users\yahya\Desktop\playground\c++\imgui\imgui_widgets.cpp C:\Users\yahya\Desktop\playground\c++\imgui\imgui_draw.cpp C:\Users\yahya\Desktop\playground\c++\imgui\imgui_tables.cpp C:\Users\yahya\Desktop\playground\c++\imgui\imgui-SFML.cpp -IC:\Users\yahya\Desktop\playground\c++\imgui -IC:\SFML-2.5.1\include -DSFML_STATIC
>
>g++ main.o node.o imgui.o imgui_widgets.o imgui_draw.o imgui_tables.o imgui-SFML.o -o main -LC:\SFML-2.5.1\lib -static -static-libgcc -static-libstdc++ -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -mwindows
