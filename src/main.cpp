#include <raylib.h>
#include "weapon.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Defining Functions
string getComputerMove(int move){
    if (move == 0) {
        return "r";
    }
    else if (move == 1) {
        return "p";
    }
    return "s";
}

const char* roundResult(string playerMove, string compMove) {
    if (playerMove == compMove) {
        return "\t\t The battlefield is BARREN. (Tie)";
    }
    if (playerMove == "r" && compMove == "p") {
        return "You were SURROUNDED by PAPER. (Lose)";
    }
    if (playerMove == "r" && compMove == "s") {
        return "\t\t\t\tYou crushed SCISSORS! (Win)";
    }
    if (playerMove == "p" && compMove == "r") {
        return "\t\t\t\t\tYou captured ROCKS! (Win)";
    }
    if (playerMove == "p" && compMove == "s") {
        return "\t\tYou were CUT by SCISSORS. (Lose)";
    }
    if (playerMove == "s" && compMove == "r") {
        return "\tYou were PUMMELED by ROCKS. (Lose)";
    }
    if (playerMove == "s" && compMove == "p") {
        return "\t\t\t\t\tYou tore some PAPER! (Win)";
    }
    else {
        return 0;
    }
}

Color colorResult(string playerMove, string compMove, Sound war, Sound rock, Sound paper, Sound scissors) {
    if (playerMove == compMove) {
        PlaySound(war);
        return BLACK;
    }
    if (playerMove == "r" && compMove == "p") {
        PlaySound(paper);
        return {216, 55, 63, 255};
    }
    if (playerMove == "r" && compMove == "s") {
        PlaySound(rock);
        return {23, 171, 210, 255};
    }
    if (playerMove == "p" && compMove == "r") {
        PlaySound(paper);
        return {23, 171, 210, 255};
    }
    if (playerMove == "p" && compMove == "s") {
        PlaySound(scissors);
        return {216, 55, 63, 255};
    }
    if (playerMove == "s" && compMove == "r") {
        PlaySound(rock);
        return {216, 55, 63, 255};
    }
    if (playerMove == "s" && compMove == "p") {
        PlaySound(scissors);
        return {23, 171, 210, 255};
    }
    else {
        return BLACK;
    }
}

int main() 
{   
    // Defining Varibales
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "A Game of Rock Paper Scissors");
    InitAudioDevice();
    SetTargetFPS(60);
    Texture2D background = LoadTexture("graphics/wrinkledPaper.png");
    Weapon rock("graphics/DeRock.png", {50, 350}, "rock", 0.6);
    Weapon paper("graphics/MonPapel.png", {320, 350}, "paper", 0.2);
    Weapon scissors("graphics/ElScissors.png", {450, 270}, "scissors", 1);
    Sound impact = LoadSound("sfx/impact.mp3");
    Sound wind = LoadSound("sfx/wind.mp3");
    Sound crumple = LoadSound("sfx/crumple.mp3");
    Sound blade = LoadSound("sfx/blade.mp3");

    srand(time(0));
    Color winLose = BLACK;
    string playerMove;
    string compMove;
    const char* flavorText = "";

    // Game Loop
    while(!WindowShouldClose()){
        // Player Input
        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        // Game Update
        if (rock.IsPressed(mousePosition, mousePressed)){
            playerMove = "r";
            compMove = getComputerMove(rand() % 3);
            flavorText = roundResult(playerMove, compMove);
            winLose = colorResult(playerMove, compMove, wind, impact, crumple, blade);
        }
        if (paper.IsPressed(mousePosition, mousePressed)){
            playerMove = "p";
            compMove = getComputerMove(rand() % 3);
            flavorText = roundResult(playerMove, compMove);
            winLose = colorResult(playerMove, compMove, wind, impact, crumple, blade);
        }
        if (scissors.IsPressed(mousePosition, mousePressed)){
            playerMove = "s";
            compMove = getComputerMove(rand() % 3);
            flavorText = roundResult(playerMove, compMove);
            winLose = colorResult(playerMove, compMove, wind, impact, crumple, blade);
        }
        
        // Drawing
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexture(background, 0, 0, WHITE);
            DrawText(flavorText, 100, 180, 30, winLose);
            rock.Draw();
            paper.Draw();
            scissors.Draw();
        EndDrawing();
    }
    CloseAudioDevice();
    CloseWindow();
}