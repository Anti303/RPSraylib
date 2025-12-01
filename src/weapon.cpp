#include "weapon.hpp"
#include <raylib.h>

Weapon::Weapon(const char *imagePath, Vector2 imagePosition, string type, float scale){
    Image image = LoadImage(imagePath);
    
    int width = image.width;
    int height = image.height;

    int modWidth = static_cast<int>(width * scale);
    int modHeight = static_cast<int>(height * scale);
    ImageResize(&image, modWidth, modHeight);

    texture = LoadTextureFromImage(image);
    UnloadImage(image);
    position = imagePosition;
    identity = type;
}

Weapon::~Weapon(){
    UnloadTexture(texture);
}

void Weapon::Draw(){
    DrawTextureV(texture, position, WHITE);
}

bool Weapon::IsPressed(Vector2 mousePos, bool mousePress){
    Rectangle rect = {position.x, position.y, static_cast<float>(texture.width), static_cast<float>(texture.height)};
    if(CheckCollisionPointRec(mousePos, rect) && mousePress) {
        return true;
    }
    
    return false;
}
