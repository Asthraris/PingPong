#pragma once

#include <raylib.h>
#include <cmath>

enum SideofPaddle{
    LEFT,RIGHT
};


class Paddle {
private:
    Vector2 _pos;
    Color _color;
    const Vector2 _size = {30, 100};
    const float _speed = 400.0f; // Units per second, not per frame
    SideofPaddle side;
    Rectangle getPureRect() const {
        return Rectangle{_pos.x - _size.x / 2, _pos.y - _size.y / 2, _size.x, _size.y};
    }

public:
    Paddle(){

    }//default

    void move(short direction, float deltaTime, float windowHeight) {
        _pos.y += direction * _speed * deltaTime ;

        // Clamp paddle to window bounds
        float halfHeight = _size.y / 2;
        if (_pos.y - halfHeight < 0) _pos.y = halfHeight;
        if (_pos.y + halfHeight > windowHeight) _pos.y = windowHeight - halfHeight;
    }

    void render() const {
        DrawRectangleRounded(getPureRect(), 1.0, 2, _color);
    }

    void processMovement(float deltaTime, float windowHeight) {
        if (IsKeyDown(KEY_W)) {
            move(-1, deltaTime, windowHeight);
        } else if (IsKeyDown(KEY_S)) {
            move(1, deltaTime, windowHeight);
        }
    }

    void computeMovement(Vector2 ball_pos , Vector2 ball_velo, float deltaTime,Vector2 Win_size,float dt , float BOT_LEVEL = 0.2f) {
        
            float reactionDistance = Win_size.x / 1.5f;  // How far before paddle starts reacting
            float center = _pos.y + _size.y / 2.0f;
        
            // only react if ball is coming toward the paddle AND within reaction range
            bool isBallApproaching = (side == LEFT && ball_velo.x < 0) || (side == RIGHT && ball_velo.x > 0);
            bool isBallCloseEnough = fabs(ball_pos.x - _pos.x) < reactionDistance;
        
            if (isBallApproaching && isBallCloseEnough) {
                float predictionTarget = ball_pos.y;
        
                // Predict Y offset with ball speed factor
                  // increase for smarter bot
                predictionTarget += ball_velo.y * BOT_LEVEL * dt * 60.0f;
        
                if (center < predictionTarget - 10.0f)
                    move(1, dt, Win_size.y);  // down
                else if (center > predictionTarget + 10.0f)
                    move(-1, dt, Win_size.y);  // up
            }
        
    }

    Vector2 getPosition() const {
        return _pos;
    }

    Rectangle getRect() const {
        return getPureRect();
    }
    void reset(Vector2 Winsize , SideofPaddle sideofpaddle ,const Color& col){
        side = sideofpaddle;
        if(sideofpaddle == LEFT){
            _pos = Vector2{40, Winsize.y / 2};
        }
        else{
            _pos = Vector2{Winsize.x - 40, Winsize.y / 2};
        }
        _color = col;
    }
};
