#pragma once

#include <raylib.h>
#include "pong.hpp"
#include "paddle.hpp"
#include <random>
#include <string>

const Color blk = {43,43,43,255};
const Color wht = {235,235,235,255};
const Color grn = {169, 207, 84,255};

#include <iostream>


class Game {
    

    const Vector2 WIN_SIZE = {1080,720};

    Rectangle nogoArea , Line;
    Paddle p1, p2;
    Pong pong;
    bool paused = false;
    bool gameOver ;
    

    void Update(float dt){
        if (IsKeyPressed(KEY_SPACE)) paused = !paused;

        if (!paused) {
            p1.processMovement(dt, WIN_SIZE.y);
            // p1.computeMovement(pong.getPosition(),pong.getVelocity().y, dt, WIN_SIZE);

            p2.computeMovement(pong.getPosition(),pong.getVelocity(), dt, WIN_SIZE ,dt);
                
            // if(pong.getPosition().x < WIN_SIZE.x/2){
            // }else{
            // }
            pong.detectCollision(p2.getRect());
            pong.detectCollision(p1.getRect());
                
            pong.move(dt, WIN_SIZE.y);
            
            short outStatus = pong.checkBounds(WIN_SIZE.x);
            if (outStatus != 0) {
                gameOver = true;
                //wiining logic
                
            }
        }
    }
    Vector2 randomStart(){
        std::random_device rd;                         // Random hardware entropy (non-deterministic)
        std::mt19937 gen(rd());                        // Mersenne Twister engine seeded by rd
        std::uniform_real_distribution<float> dist(-1, 1);  // Range: 1 to 100
    
        return {dist(gen), dist(gen)};
    }
    void restartGame(){
        pong.reset(WIN_SIZE,randomStart() , wht);
                    p1.reset(WIN_SIZE,LEFT,wht);
                    p2.reset(WIN_SIZE,RIGHT,wht); 
                    gameOver =false;
    }
public:
    Game(){

            InitWindow(WIN_SIZE.x, WIN_SIZE.y, "Ultimate Pong");
            nogoArea = {WIN_SIZE.x/2 - WIN_SIZE.x/4,0,WIN_SIZE.x/2,WIN_SIZE.y};
            Line = {WIN_SIZE.x/2-7,0,14,WIN_SIZE.y};
            gameOver = true;

        }

    ~Game() {
        CloseWindow();
    }

    void run() {
        while (!WindowShouldClose()) {
            float dt = GetFrameTime();
            
            if(!gameOver)
            {
                Update(dt);
            }else{              
                if (IsKeyPressed(KEY_ENTER)){
                    restartGame();
                }   
            }

            
            BeginDrawing();
            ClearBackground(blk);
            DrawRectangleRec(nogoArea,grn);
            DrawRectangleRec(Line,blk);
           

            p1.render();
            p2.render();
            pong.render();

            if (paused){
                DrawRectangleGradientV(0,0,WIN_SIZE.x,WIN_SIZE.y ,Color{20,20,20,255}, Color{100,100,100,200});
                DrawText("PAUSED", WIN_SIZE.x / 2 - 50, 20, 20, RED);
                DrawText("Enter to Restart!",WIN_SIZE.x/2 -200 ,WIN_SIZE.y/2,50,GREEN);
                if (IsKeyPressed(KEY_ENTER)){
                    restartGame();
                    paused = ! paused;
                } 

            }
            if(gameOver){
                DrawRectangleGradientV(0,0,WIN_SIZE.x,WIN_SIZE.y , Color{100,100,100,200},Color{20,20,20,255});
                DrawText("Enter to Play!",WIN_SIZE.x/2 -200 ,WIN_SIZE.y/2,50,WHITE);

            }
            DrawText(std::to_string(int(1/dt)).c_str(), 20, 20, 50, GREEN);
            EndDrawing();
        }
    }

};
