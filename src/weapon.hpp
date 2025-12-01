#pragma once
#include <raylib.h>
#include <iostream>
using namespace std;

class Weapon {
    public:
        Weapon(const char *imagePath, Vector2 imagePosition, string type, float scale);
        ~Weapon();
        void Draw();
        bool IsPressed(Vector2 mousePos, bool mousePress);
    private:
        Texture2D texture;
        Vector2 position;
        string identity;
};

