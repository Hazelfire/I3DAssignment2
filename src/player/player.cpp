#include "player.hpp"
#include "gameobject/animated_gameobject/animated_gameobject.hpp"
#include <iostream>
#include "vector/vector.h"


Colour player_green(0,1,0.2,1);
Colour specular_white(1,1,1,1);
Material player_mat(128, player_green * 0.3, player_green, specular_white);
Player::Player(): GameObject(std::shared_ptr<Shape>(nullptr), std::make_shared<Sphere>(player_mat, v3d::zero, 0.5)){};

void Player::draw(DrawOptions options) const {
  GameObject::draw(options);

  drawJump();
}

void Player::bind(GameObject& other){
  if(!bound){
    boundTo = &other;
    boundDistance = v3d(0, (((Cylinder*)other.shape.get())->radius) + 0.55, 0);
    bound = true;
  }
}

void Player::reset(void) {
  position = v3d::zero;
  grounded = false;
  velocity = v3d(0,-5,0);


  Sphere* sphere = static_cast<Sphere*>(this->collider.get());
  sphere->position = position;
}



void Player::drawJump() const {
  glColor3f(1, 1, 1);

  v3d currentPos(position);
  v3d currentVel(jumpV);
  
  glPushAttrib(GL_ENABLE_BIT);
  glPushAttrib(GL_NORMALIZE);
  glPushAttrib(GL_COLOR_MATERIAL);

  glDisable(GL_LIGHTING);


  const double dt = 0.1;
  const double gravity = 1;
  while(currentPos.y >= -1){
    v3d newPos = currentPos + currentVel * dt;
    currentVel.y -= dt * gravity;
    v3d movement = newPos - currentPos;
    movement.draw(currentPos.x, currentPos.y, currentPos.z);
    currentPos = newPos;
  }
  glPopAttrib();
  glPopAttrib();
  glPopAttrib();

}

void Player::ribbet(double dt) {

  time_till_ribbet -= dt;
  if(time_till_ribbet < 0) {
    time_till_ribbet = rand() % time_between_ribbet;


    if(grounded) {
      for(auto child : children) {
        auto animation_child = dynamic_cast<animated_gameobject*>(child.get());
        if(animation_child) {
          animation_child->recursive_play(anim::ribbet);
        }
      }
    }
  }
}

void Player::jump(){
  if(grounded){
    velocity = v3d(jumpV);
    grounded = false;
    bound = false;

    for(auto child : children) {
      auto animation_child = dynamic_cast<animated_gameobject*>(child.get());
      if(animation_child) {
        animation_child->recursive_play(anim::jump);
      }
    }
  }
}

void Player::rotate_to_jump() {
  v3d forward = v3d::reject(jumpV, v3d::Y).normalise();

  double y_angle = v3d::angle(forward, v3d::Z);
  if(v3d::dot(forward, v3d::X) < 0) {
    y_angle *= -1;
  }

  double x_angle = v3d::angle(jumpV, forward);
  if(v3d::dot(jumpV, v3d::Y) < 0) {
    x_angle *= -1;
  }

  for(auto child : children) {
    child->rotation.y = y_angle;
    for(auto meta_child : child->children) {
      meta_child->rotation.x = x_angle;
    }
  }
}

void Player::ground(){
  grounded = true;
}
#include "scene/scene.hpp"

void Player::update(double dt){
  ribbet(dt);
  rotate_to_jump();

  Sphere* sphere = static_cast<Sphere*>(this->collider.get());
  if(!grounded){
    const Scene& scene = Scene::get_instance();
    const double gravity = 1;
    v3d old_pos = position;
    position += velocity * dt;
    sphere->position = this->position;

    // collide with -y
    if(position.y <= -10){
      grounded = true;
    }

    // collide with floor
    std::vector<std::shared_ptr<GameObject>> colliding_floors = 
      scene.getCollidingObjectsByTag(*this, tag::floor);
    if(!colliding_floors.empty()) {
      grounded = true;
      //return;
    }

    if(grounded) {
      // reverse the position to before we collided
      position = old_pos;
      sphere->position = old_pos;
    }
    velocity.y -= dt * gravity;
  }
  
  if(bound){
    position = boundDistance + boundTo->position;
    grounded = true;
  }

  GameObject::update(dt);
 }
