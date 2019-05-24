#include "player.hpp"
#include <iostream>


Player::Player(): GameObject(new Sphere(v3d::zero, 0.2)){};

void Player::draw(DrawOptions options){
  GameObject::draw(options); 

  drawJump();
}

void Player::drawJump(){

  v3d currentPos(position);
  v3d currentVel(jumpV);
  
  const double dt = 0.1;
  const double gravity = 0.2;
  while(currentPos.y >= 0){
    v3d newPos = currentPos + currentVel * dt;
    currentVel.y -= dt * gravity;
    v3d movement = newPos - currentPos;
    movement.draw(currentPos.x, currentPos.y, currentPos.z);
    currentPos = newPos;
  }
}

void Player::jump(){
  if(grounded){
    velocity = v3d(jumpV);
    grounded = false;
  }
}

void Player::update(double dt){
  if(!grounded){
    const double gravity = 0.2;
    position += velocity * dt;
    velocity.y -= dt * gravity;
    if(position.y <= 0){
      grounded = true;
    }
  }   
}
