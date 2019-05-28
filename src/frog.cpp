#include "shape/primitives/primitives.hpp"
#include "gameobject/gameobject.hpp"
#include "material/material.hpp"


void create_frog(std::shared_ptr<GameObject> player){

  Colour white_specular(1, 1, 1, 1);
  Colour no_specular(0, 0, 0, 0);
  float ambient_scale = 0.4;

  Colour green(0, 1, 0.1, 1);
  Material frogMaterial(128, green * ambient_scale, green, white_specular);
  /*
  auto body = std::make_shared<Cube>(frogMaterial, 
      v3d(0,0,0),//position
      v3d(0.5, 0.5, 1)//size
      );
      */
  auto body_shape = std::make_shared<Cube>(frogMaterial, 
      v3d(0,0,0),//position
      v3d(1, 1, 1)//size
      );

  auto body = std::make_shared<GameObject>(body_shape);
  body->setParent(player);

  auto left_leg = std::make_shared<GameObject>(std::make_shared<Cube>(
        frogMaterial,
        v3d(1,1,1),// position
        v3d(0.1, 0.1, 0.1)// size
        ));
  left_leg->setParent(body);

}
