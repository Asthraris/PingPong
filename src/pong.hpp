#pragma once

#include <raylib.h>
#include <cmath>
// Normalize a vector
Vector2 Vector2Normalize(Vector2 v) {
    float length = sqrtf(v.x * v.x + v.y * v.y);
    if (length == 0.0f) return (Vector2){ 0.0f, 0.0f };  // Avoid division by zero
    return (Vector2){ v.x / length, v.y / length };
}

// Scale a vector by a scalar
Vector2 Vector2Scale(Vector2 v, float scale) {
    return (Vector2){ v.x * scale, v.y * scale };
}

// Combined function: normalize and scale
Vector2 NormalizeAndScale(Vector2 dir, float speed) {
    Vector2 norm = Vector2Normalize(dir);
    return Vector2Scale(norm, speed);
}

class Pong {
private:
    Vector2 _pos;
    Vector2 _velocity;
    float _speed = 500.0f; // pixels per second
    Color _color;
    float _radius = 20.0f;
    
public:
    Pong(){}//default

    Vector2 getPosition() const {
        return _pos;
    }

    Vector2 getVelocity() const {
        return _velocity;
    }

    void move(float deltaTime, float windowHeight) {
        _pos.x += _velocity.x * deltaTime;
        _pos.y += _velocity.y * deltaTime;

        // Bounce off top and bottom
        if (_pos.y - _radius < 0 || _pos.y + _radius > windowHeight) {
            _velocity.y *= -1;
        }
    }

    void render() const {
        DrawCircleV(_pos, _radius, _color);
    }

    // Returns: -1 if ball is out on left, 1 if out on right, 0 otherwise
    short checkBounds(float windowWidth) const {
        if (_pos.x + _radius < 0) return -1;
        if (_pos.x - _radius > windowWidth) return 1;
        return 0;
    }

    void detectCollision(const Rectangle& paddleRect) {
        
        if (CheckCollisionCircleRec(_pos, _radius, paddleRect)) {
            if(_pos.y < paddleRect.y || (_pos.y > (paddleRect.y+paddleRect.height))){
                _velocity.y *= -1;
            }
            _velocity.x *= -1;
        }
    }
    void reset(Vector2 Winsize,Vector2 dir ,const Color& col ){
        _pos = Vector2{Winsize.x / 2, Winsize.y / 2};
        _velocity = NormalizeAndScale(dir, _speed);
        _color = col;
    }
};
