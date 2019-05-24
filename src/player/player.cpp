#include "player.hpp"
#include <iostream>


Player::Player(): GameObject(new Sphere(v3d::zero, 1)){};

void Player::draw(){
  GameObject::draw(); 

  drawJump();
}

void Player::drawJump(){

  v3d currentPos(position);
  v3d currentVel(jump);
  
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
