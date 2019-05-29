#include "shape/primitives/primitives.hpp"
#include "gameobject/gameobject.hpp"
#include "material/material.hpp"

#include <iostream>

void create_frog(std::shared_ptr<GameObject> player){

  Colour white(1, 1, 1, 1);
  Colour black(0, 0, 0, 1);
  float ambient_scale = 0.4;

  Colour red(1, 0, 0, 1);
  Colour green(0, 1, 0.1, 1);
  Material frogMaterial(128, green * ambient_scale, green, 0.3 * white);

  Material eyeMaterial(128, white * ambient_scale, white, black);
  Material pupilMaterial(128, black * ambient_scale, black, white);
  Material tongueMaterial(128, red * ambient_scale, red, white * 0.8);

  double body_zsize = 0.8;
  auto body = std::make_shared<GameObject>(std::make_shared<Cube>(frogMaterial, 
        v3d(0,0,0),//position
        v3d(0.5, 0.5, body_zsize)//size
        ));
  body->setParent(player);

  auto headrotator = std::make_shared<GameObject>(nullptr);
  headrotator->position = v3d(0, 0, body_zsize/2);
  headrotator->setParent(body);

  double head_zsize = 0.2;
  double head_diameter = 0.4;
  auto head = std::make_shared<GameObject>(std::make_shared<Cube>(
        frogMaterial,
        v3d(0,0,0),// position
        v3d(head_diameter, head_diameter, head_zsize)// size
        ));
  head->position = v3d(0, 0, head_zsize/2);
  head->setParent(headrotator);

  double snout_zsize = 0.2;
  double snout_ypos = -0.1;
  double snout_ysize = 0.2;
  auto snout = std::make_shared<GameObject>(std::make_shared<Cube>(
        frogMaterial,
        v3d(0,0,0),// position
        v3d(0.3, snout_ysize, snout_zsize)// size
        ));
  snout->position = v3d(0, snout_ypos, head_zsize/2 + snout_zsize/2);
  snout->setParent(head);

  double eye_distance = 0.015;
  double eyesnout_distance = 0;
  double lefteye_zsize = 0.05;
  double lefteye_diameter = 0.18;
  double lefteye_xpos = -1 * lefteye_diameter/2 - eye_distance;
  double lefteye_ypos = snout_ypos + snout_zsize/2 + lefteye_diameter/2 + eyesnout_distance/2;
  auto lefteye = std::make_shared<GameObject>(std::make_shared<Cube>(
        eyeMaterial,
        v3d(0,0,0),// position
        v3d(lefteye_diameter, lefteye_diameter, lefteye_zsize)// size
        ));
  lefteye->position = v3d(lefteye_xpos, lefteye_ypos, head_zsize/2 + lefteye_zsize/2);
  lefteye->setParent(head);

  double pupil_percent = 0.30;
  double pupil_zsize = 0.001;
  double pupil_diameter = lefteye_diameter * pupil_percent;
  auto leftpupil = std::make_shared<GameObject>(std::make_shared<Cube>(
        pupilMaterial,
        v3d(0,0,0),// position
        v3d(pupil_diameter, pupil_diameter, pupil_zsize)// size
        ));
  leftpupil->position = v3d(0, 0, lefteye_zsize/2 + pupil_zsize/2);
  leftpupil->setParent(lefteye);


#define MIRROR 1
#if MIRROR
  auto righteye = lefteye->clone();
  righteye->position.x *= -1;
#endif

  auto mouthrotator = std::make_shared<GameObject>(nullptr);
  mouthrotator->position = v3d(0, -1*head_diameter/2, -1*head_zsize/2);
  mouthrotator->setParent(head);
  mouthrotator->rotation.x = -30;

  double mouth_zsize = 0.4;
  double mouth_ysize = 0.07;
  double mouth_xsize = 4 * mouth_ysize;
  auto mouth = std::make_shared<GameObject>(std::make_shared<Cube>(
        frogMaterial,
        v3d(0,0,0),// position
        v3d(mouth_xsize, mouth_ysize, mouth_zsize)// size
        ));
  mouth->position = v3d(0, 0, mouth_zsize/2);
  mouth->setParent(mouthrotator);

  auto tonguerotator = std::make_shared<GameObject>(nullptr);
  tonguerotator->setParent(mouthrotator);
  tonguerotator->rotation.x = 10;

  double tongue_xsize = mouth_xsize * 0.5;
  double tongue_ysize = mouth_ysize * 0.8;
  double tongue_zsize = mouth_zsize * 0.8;//TODO extend tongue on jump
  auto tongue = std::make_shared<GameObject>(std::make_shared<Cube>(
        tongueMaterial,
        v3d(0,0,0),// position
        v3d(tongue_xsize, tongue_ysize, tongue_zsize)// size
        ));
  tongue->position = v3d(0, 0, tongue_zsize/2);
  tongue->setParent(tonguerotator);



  auto left_leg = std::make_shared<GameObject>(std::make_shared<Cube>(
        frogMaterial,
        v3d(0,0,0),// position
        v3d(0.1, 0.1, 0.1)// size
        ));
  left_leg->position = v3d(1,1,1);
  left_leg->setParent(body);

  auto left_toe = std::make_shared<GameObject>(std::make_shared<Cube>(
        frogMaterial,
        v3d(0,0,0),// position
        v3d(0.1, 0.1, 0.1)// size
        ));
  left_toe->position = v3d(1,1,1);
  left_toe->setParent(left_leg);

  auto right_leg = left_leg->clone();
  right_leg->position.x *= -1;
  Cube *right_leg_cube = dynamic_cast<Cube *>(&*right_leg->shape);

}
