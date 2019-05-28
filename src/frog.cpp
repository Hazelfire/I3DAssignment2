#include "shape/primitives/primitives.hpp"
#include "gameobject/gameobject.hpp"
#include "material/material.hpp"

#include <iostream>

void create_frog(std::shared_ptr<GameObject> player){

  Colour white_specular(1, 1, 1, 1);
  Colour no_specular(0, 0, 0, 0);
  float ambient_scale = 0.4;

  Colour green(0, 1, 0.1, 1);
  Material frogMaterial(128, green * ambient_scale, green, white_specular);

  auto body = std::make_shared<GameObject>(std::make_shared<Cube>(frogMaterial, 
        v3d(0,0,0),//position
        v3d(1, 1, 1)//size
        ));
  body->setParent(player);

  auto left_leg = std::make_shared<GameObject>(std::make_shared<Cube>(
        frogMaterial,
        v3d(1,1,1),// position
        v3d(0.1, 0.1, 0.1)// size
        ));
  left_leg->setParent(body);

  auto right_leg = left_leg->clone();
  Cube *temp = dynamic_cast<Cube *>(&*right_leg->shape);

  temp->position.x *= -1;

  std::cout << "test" << std::endl;
}
