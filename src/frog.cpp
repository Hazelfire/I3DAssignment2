#include "shape/primitives/primitives.hpp"
#include "gameobject/gameobject.hpp"
#include "material/material.hpp"

#include <iostream>

void create_frog(std::shared_ptr<GameObject> player){

  Colour white(1, 1, 1, 1);
  Colour black(0, 0, 0, 1);
  float ambient_scale = 0.4;

  Colour pink(1, 0.2, 0.5, 1);
  Material debugMaterial(128, pink * ambient_scale, pink, 0.3 * white);

  Colour red(1, 0, 0, 1);
  Colour green(0, 1, 0.1, 1);
  Material frogMaterial(128, green * ambient_scale, green, 0.3 * white);

  Material eyeMaterial(128, white * ambient_scale, white, black);
  Material pupilMaterial(128, black * ambient_scale, black, white);
  Material tongueMaterial(128, red * ambient_scale, red, white * 0.8);

  double body_xsize = 0.5;
  double body_ysize = 0.5;
  double body_zsize = 0.8;
  auto body = std::make_shared<GameObject>(std::make_shared<Cube>(frogMaterial, 
        v3d(0,0,0),//position
        v3d(body_xsize, body_ysize, body_zsize)//size
        ));
  body->setParent(player);




  //HEAD


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
  double snout_xsize = 0.3;
  double snout_ypos = -0.1;
  double snout_ysize = 0.2;
  auto snout = std::make_shared<GameObject>(std::make_shared<Cube>(
        frogMaterial,
        v3d(0,0,0),// position
        v3d(snout_xsize, snout_ysize, snout_zsize)// size
        ));
  snout->position = v3d(0, snout_ypos, head_zsize/2 + snout_zsize/2);
  snout->setParent(head);




// EYE

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


  //MOUTH


  auto mouth_root = std::make_shared<GameObject>(nullptr);
  mouth_root->position = v3d(0, -0.4 * head_diameter, -1*head_zsize/2);
  mouth_root->setParent(head);

  double underbite = 0.9;
  double mouth_zsize = (head_zsize + snout_zsize) * underbite;
  double mouth_xsize = snout_xsize * 0.9;
  double mouth_ysize = mouth_xsize / 4;
  auto mouth = std::make_shared<GameObject>(std::make_shared<Cube>(
        frogMaterial,
        v3d(0,0,0),// position
        v3d(mouth_xsize, mouth_ysize, mouth_zsize)// size
        ));
  mouth->position = v3d(0, 0, mouth_zsize/2);
  // open mouth angle:
  //mouth->rotation.x = -32;
  mouth->rotation.x = -25;
  mouth->setParent(mouth_root);

  auto tongue_root = std::make_shared<GameObject>(nullptr);
  tongue_root->position = v3d(0,0,-0.18);
  tongue_root->setParent(mouth);

  double tongue_xsize = mouth_xsize * 0.5;
  double tongue_ysize = mouth_ysize * 0.8;
  double tongue_zsize = mouth_zsize * 0.8;//TODO extend tongue on jump
  auto tongue = std::make_shared<GameObject>(std::make_shared<Cube>(
        tongueMaterial,
        v3d(0,0,0),// position
        v3d(tongue_xsize, tongue_ysize, tongue_zsize)// size
        ));
  tongue->position = v3d(0, 0, tongue_zsize/2);
  tongue->rotation.x = 10;
  tongue->setParent(tongue_root);




  // LEG



  double left_thigh_diameter = 0.15;
  auto left_thigh_root = std::make_shared<GameObject>(
#if 1
      nullptr
#else
      //std::make_shared<Sphere>(frogMaterial, v3d::zero, 0.2)
      std::make_shared<Cube>(debugMaterial, v3d::zero, 0.2 * v3d::unit)
#endif
      );
  left_thigh_root->position = v3d(body_xsize/2, -1 * body_ysize/2 + left_thigh_diameter/2, -1 * body_zsize/2);
  left_thigh_root->setParent(body);


  double left_thigh_zsize = 0.7;
  auto left_thigh = std::make_shared<GameObject>(std::make_shared<Cube>(
        frogMaterial,
        v3d(0,0,0),// position
        v3d(left_thigh_diameter, left_thigh_diameter, left_thigh_zsize)// size
        ));
  left_thigh->position = v3d(0,0, left_thigh_zsize/2);
  left_thigh->rotation = v3d(0,30,15);
  left_thigh->setParent(left_thigh_root);

  auto left_shin_root = std::make_shared<GameObject>(
#if 0
      std::make_shared<Cube>(debugMaterial, v3d::zero, 0.2 * v3d::unit)
#endif
      );
  left_shin_root->position = v3d(0, 0, left_thigh_zsize/2);
  left_shin_root->setParent(left_thigh);

  double left_shin_diameter = 0.1;
  double left_shin_zsize = 0.5;
  auto left_shin = std::make_shared<GameObject>(std::make_shared<Cube>(
        frogMaterial,
        v3d(0,0,0),// position
        v3d(left_shin_diameter, left_shin_diameter, left_shin_zsize)// size
        ));
  left_shin->position = v3d(0, 0, left_thigh_zsize/2);
  left_shin->rotation.x = -150;
  left_shin->setParent(left_shin_root);


  auto left_foot_root = std::make_shared<GameObject>(
#if 0
      std::make_shared<Cube>(debugMaterial, v3d::zero, 0.2 * v3d::unit)
#endif
      );
  left_foot_root->position = v3d(0, 0, left_shin_zsize/2);
  left_foot_root->setParent(left_shin);

  double left_foot_diameter = 0.1;
  double left_foot_zsize = 0.5;
  auto left_foot = std::make_shared<GameObject>(std::make_shared<Cube>(
        frogMaterial,
        v3d(0,0,0),// position
        v3d(left_foot_diameter, left_foot_diameter, left_foot_zsize)// size
        ));
  left_foot->position = v3d(0, 0, left_shin_zsize/2);
  left_foot->rotation.x = 140;
  left_foot->setParent(left_foot_root);


  auto left_ball_root = std::make_shared<GameObject>(
#if 0
      std::make_shared<Cube>(debugMaterial, v3d::zero, 0.2 * v3d::unit)
#endif
      );
  left_ball_root->position = v3d(0, 0, left_foot_zsize/2);
  left_ball_root->setParent(left_foot);

  double left_ball_xsize = left_foot_diameter * 1.3;
  double left_ball_ysize = left_ball_xsize * 0.8;
  double left_ball_zsize = left_ball_xsize;
  auto left_ball = std::make_shared<GameObject>(std::make_shared<Cube>(
        frogMaterial,
        v3d(0,0,0),// position
        v3d(left_ball_xsize, left_ball_ysize, left_ball_zsize)// size
        ));
  left_ball->position = v3d(0, 0, left_ball_zsize/2);
  left_ball->setParent(left_ball_root);

  double left_toe_diameter = left_ball_xsize * 0.3;
  double left_toe_zsize = left_toe_diameter * 2.7;
  auto left_toe = std::make_shared<GameObject>(std::make_shared<Cube>(
        frogMaterial,
        v3d(0,0,0),// position
        v3d(left_toe_diameter, left_toe_diameter, left_toe_zsize)// size
        ));
  left_toe->position = v3d(0, -1*left_ball_ysize/2 + left_toe_diameter/2, left_toe_zsize/2 + left_ball_zsize/2);
  left_toe->setParent(left_ball);

  auto left_toe_2 = left_toe->clone();
  left_toe_2->rotation.y = 30;
  auto left_toe_3 = left_toe->clone();
  left_toe_3->rotation.y = -30;


#if 0
  auto right_leg = left_thigh_rotator->clone();
  right_leg_rotator->position.x *= -1;
  Cube *right_leg_cube = dynamic_cast<Cube *>(&*right_leg->shape);
#endif

}
