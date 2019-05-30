#include "player.hpp"
#include "gameobject/animated_gameobject/animated_gameobject.hpp"
#include <iostream>


Colour player_green(0,1,0.2,1);
Colour specular_white(1,1,1,1);
Material player_mat(128, player_green * 0.3, player_green, specular_white);
Player::Player(): GameObject(std::shared_ptr<Shape>(nullptr), std::make_shared<Sphere>(player_mat, v3d::zero, 0.2)){};

void Player::draw(DrawOptions options) const {
  GameObject::draw(options);

  drawJump();
}

void Player::bind(GameObject& other){
  if(!bound){
    boundTo = &other;
    boundDistance = v3d(0, (((Cylinder*)other.shape.get())->radius) + 0.25, 0);
    bound = true;
  }
}
void Player::drawJump() const {
  glColor3f(1, 1, 1);

  v3d currentPos(position);
  v3d currentVel(jumpV);
  
  const double dt = 0.1;
  const double gravity = 1;
  while(currentPos.y >= -1){
    v3d newPos = currentPos + currentVel * dt;
    currentVel.y -= dt * gravity;
    v3d movement = newPos - currentPos;
    movement.draw(currentPos.x, currentPos.y, currentPos.z);
    currentPos = newPos;
  }
}

void Player::jump(){
  for(auto child : children) {
    auto animation_child = dynamic_cast<animated_gameobject*>(child.get());
    if(animation_child) {
      std::cout << "ribbet..?" << std::endl;
      animation_child->recursive_play(anim::ribbet);
    } else {
      std::cout << "child does not animate" << std::endl;
    }
  }

  if(grounded){
    velocity = v3d(jumpV);
    grounded = false;
    bound = false;
  }
}

void Player::ground(){
  grounded = true;
}
#include "scene/scene.hpp"

void Player::update(double dt){
  Sphere* sphere =  (Sphere*) this->collider.get();
  sphere->position = this->position;
  if(!grounded){
    const Scene& scene = Scene::get_instance();
    const double gravity = 1;
    position += velocity * dt;

    // collide with -y
    if(position.y <= -10){
      grounded = true;
    }

    // collide with floor
    std::vector<std::shared_ptr<GameObject>> colliding_floors = 
      scene.getCollidingObjectsByTag(*this, tag::floor);
    if(!colliding_floors.empty()) {
      grounded = true;
      return;
    }

    if(grounded) {
      // reverse the position to before we collided
      position -= velocity * dt;
    }
    velocity.y -= dt * gravity;
  }
  
  if(bound){
    position = boundDistance + boundTo->position;
    grounded = true;
  }
 }
