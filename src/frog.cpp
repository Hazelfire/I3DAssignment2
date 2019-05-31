#include "shape/primitives/primitives.hpp"
#include "gameobject/gameobject.hpp"
#include "gameobject/animated_gameobject/animated_gameobject.hpp"
#include "material/material.hpp"

#include <initializer_list>
#include <iostream>


using animation = animated_gameobject::animation;
using anim_map = std::map<anim::anim, animation>;

void create_frog(std::shared_ptr<GameObject> player){


  Colour white(1, 1, 1, 1);
  Colour black(0, 0, 0, 1);
  float ambient_scale = 0.4;

  Colour debug_pink(1, 0.2, 0.5, 0.6);
  Material debug_material(128, debug_pink * ambient_scale, debug_pink, 0.3 * white);

  Colour red(1, 0, 0, 1);
  Colour green(0, 1, 0.1, 1);
  Material frog_material(128, green * ambient_scale, green, 0.3 * white);

  Material eye_material(128, white * ambient_scale, white, black);
  Material pupil_material(128, black * ambient_scale, black, white);
  Material tongue_material(128, red * ambient_scale, red, white * 0.8);

  double body_xsize = 0.5;
  double body_ysize = 0.5;
  double body_zsize = 1;
  auto body = std::make_shared<animated_gameobject>(std::make_shared<Cube>(frog_material, 
        v3d(0,0,0),//position
        v3d(body_xsize, body_ysize, body_zsize)//size
        ));
  body->setParent(player);
#if GO_DEBUG_LABELS
  body->name = "body";
#endif




  //HEAD


  auto headrotator = std::make_shared<GameObject>(nullptr);
  headrotator->position = v3d(0, 0, body_zsize/2);
  headrotator->setParent(body);
#if GO_DEBUG_LABELS
  headrotator->name = "headrotator";
#endif

  double head_zsize = 0.2;
  double head_diameter = 0.4;
  auto head = std::make_shared<GameObject>(std::make_shared<Cube>(
        frog_material,
        v3d(0,0,0),// position
        v3d(head_diameter, head_diameter, head_zsize)// size
        ));
  head->position = v3d(0, 0, head_zsize/2);
  head->setParent(headrotator);
#if GO_DEBUG_LABELS
  head->name = "head";
#endif

  double snout_zsize = 0.2;
  double snout_xsize = 0.3;
  double snout_ypos = -0.1;
  double snout_ysize = 0.2;
  auto snout = std::make_shared<GameObject>(std::make_shared<Cube>(
        frog_material,
        v3d(0,0,0),// position
        v3d(snout_xsize, snout_ysize, snout_zsize)// size
        ));
  snout->position = v3d(0, snout_ypos, head_zsize/2 + snout_zsize/2);
  snout->setParent(head);
#if GO_DEBUG_LABELS
  snout->name = "snout";
#endif




// EYE

  double eye_distance = 0.015;
  double eyesnout_distance = 0;
  double lefteye_zsize = 0.05;
  double lefteye_diameter = 0.18;
  double lefteye_xpos = -1 * lefteye_diameter/2 - eye_distance;
  double lefteye_ypos = snout_ypos + snout_zsize/2 + lefteye_diameter/2 + eyesnout_distance/2;
  auto lefteye = std::make_shared<GameObject>(std::make_shared<Cube>(
        eye_material,
        v3d(0,0,0),// position
        v3d(lefteye_diameter, lefteye_diameter, lefteye_zsize)// size
        ));
  lefteye->position = v3d(lefteye_xpos, lefteye_ypos, head_zsize/2 + lefteye_zsize/2);
  lefteye->setParent(head);
#if GO_DEBUG_LABELS
  lefteye->name = "lefteye";
#endif

  double pupil_percent = 0.30;
  double pupil_zsize = 0.001;
  double pupil_diameter = lefteye_diameter * pupil_percent;
  auto leftpupil = std::make_shared<GameObject>(std::make_shared<Cube>(
        pupil_material,
        v3d(0,0,0),// position
        v3d(pupil_diameter, pupil_diameter, pupil_zsize)// size
        ));
  leftpupil->position = v3d(0, 0, lefteye_zsize/2 + pupil_zsize/2);
  leftpupil->setParent(lefteye);
#if GO_DEBUG_LABELS
  leftpupil->name = "leftpupil";
#endif


#define MIRROR 1
#if MIRROR
  auto righteye = lefteye->clone();
  righteye->position.x *= -1;
#endif


  //MOUTH


  auto mouth_root = std::make_shared<GameObject>(nullptr);
  mouth_root->position = v3d(0, -0.4 * head_diameter, -1*head_zsize/2);
  mouth_root->setParent(head);
#if GO_DEBUG_LABELS
  mouth_root->name = "mouth_root";
#endif


  double mouth_jumpanim_angle = -60;
  std::unique_ptr<anim_map> mouth_animation = std::make_unique<anim_map>(); 
  {
    auto mouth_ribbet_anim = std::make_unique<animation>(std::move(
          std::make_unique<std::vector<animation::keyframe>, std::initializer_list<animation::keyframe>>({
            animation::keyframe(v3d(0,0,0), v3d(-30,0,0), 0.25),
            animation::keyframe(v3d(0,0,0), v3d(0,0,0), 0.3)
            })));

    (*mouth_animation)[anim::ribbet] = *mouth_ribbet_anim.release();

    auto mouth_jump_anim = std::make_unique<animation>(std::move(
          std::make_unique<std::vector<animation::keyframe>, std::initializer_list<animation::keyframe>>({
            animation::keyframe(v3d(0,0,0), v3d(mouth_jumpanim_angle,0,0), 0.2),
            animation::keyframe(v3d(0,0,0), v3d(mouth_jumpanim_angle,0,0), 0.8),
            animation::keyframe(v3d(0,0,0), v3d(0,0,0), 1)
            })));

    (*mouth_animation)[anim::jump] = *mouth_jump_anim.release();
  }


  double underbite = 0.9;
  double mouth_zsize = (head_zsize + snout_zsize) * underbite;
  double mouth_xsize = snout_xsize * 0.9;
  double mouth_ysize = mouth_xsize / 4;
  auto mouth = std::make_shared<animated_gameobject>(
      std::make_shared<Cube>(
        frog_material,
        v3d(0,0,0),// position
        v3d(mouth_xsize, mouth_ysize, mouth_zsize)// size
        ),
      std::move(mouth_animation));
  mouth->position = v3d(0, 0, mouth_zsize/2);
  // open mouth angle:
  //mouth->rotation.x = -32;
  mouth->rotation.x = -25;
  mouth->setParent(mouth_root);
#if GO_DEBUG_LABELS
  mouth->name = "mouth";
#endif

  auto tongue_root = std::make_shared<GameObject>(nullptr);
  tongue_root->position = v3d(0,0,-0.18);
  tongue_root->setParent(mouth);
#if GO_DEBUG_LABELS
  tongue_root->name = "tongue_root";
#endif


  double tongue_stickout = mouth_zsize * 2.5;
  std::unique_ptr<anim_map> tongue_animation = std::make_unique<anim_map>(); 
  {
    auto tongue_ribbet_anim = std::make_unique<animation>(std::move(
          std::make_unique<std::vector<animation::keyframe>, std::initializer_list<animation::keyframe>>({
            animation::keyframe(v3d(0,0,0), v3d(-30,0,0), 0.25),
            animation::keyframe(v3d(0,0,0), v3d(0,0,0), 0.3)
            })));

    (*tongue_animation)[anim::ribbet] = *tongue_ribbet_anim.release();

    auto tongue_jump_anim = std::make_unique<animation>(std::move(
          std::make_unique<std::vector<animation::keyframe>, std::initializer_list<animation::keyframe>>({
            animation::keyframe(v3d(0,0,tongue_stickout), v3d(mouth_jumpanim_angle / -2,0,0), 0.2),
            animation::keyframe(v3d(0,0,tongue_stickout), v3d(mouth_jumpanim_angle / -2,0,0), 0.8),
            animation::keyframe(v3d(0,0,0), v3d(0,0,0), 1)
            })));

    (*tongue_animation)[anim::jump] = *tongue_jump_anim.release();
  }

  double tongue_restlen = mouth_zsize * 0.8;

  double tongue_xsize = mouth_xsize * 0.5;
  double tongue_ysize = mouth_ysize * 0.8;
  double tongue_zsize = tongue_stickout + tongue_restlen;
  auto tongue = std::make_shared<animated_gameobject>(std::make_shared<Cube>(
        tongue_material,
        v3d(0,0,0),// position
        v3d(tongue_xsize, tongue_ysize, tongue_zsize)// size
        ),
      std::move(tongue_animation));
  tongue->position = v3d(0, 0, tongue_restlen - tongue_zsize/2);
  tongue->rotation.x = 10;
  tongue->setParent(tongue_root);
#if GO_DEBUG_LABELS
  tongue->name = "tongue";
#endif




  // LEG



  double left_thigh_diameter = 0.2;
  auto left_thigh_root = std::make_shared<GameObject>(
#if 1
      nullptr
#else
      //std::make_shared<Sphere>(frog_material, v3d::zero, 0.2)
      std::make_shared<Cube>(debug_material, v3d::zero, 0.2 * v3d::unit)
#endif
      );
  left_thigh_root->position = v3d(body_xsize/2, -1 * body_ysize/2 + left_thigh_diameter/2, -1 * body_zsize/2);
  left_thigh_root->setParent(body);
#if GO_DEBUG_LABELS
  left_thigh_root->name = "left_thigh_root";
#endif


  // clone now, so we can separately clone the thigh
  //   so that we can change the thighs angle
  auto right_thigh_root = left_thigh_root->clone();

  double thigh_jumpanim_angle = -60;
  std::unique_ptr<anim_map> thigh_animation = std::make_unique<anim_map>(); 
  {

    auto thigh_jump_anim = std::make_unique<animation>(std::move(
          std::make_unique<std::vector<animation::keyframe>, std::initializer_list<animation::keyframe>>({
            animation::keyframe(v3d(0,0,0), v3d(thigh_jumpanim_angle,0,0), 0.2),
            animation::keyframe(v3d(0,0,0), v3d(thigh_jumpanim_angle*1.2,0,0), 0.6),
            animation::keyframe(v3d(0,0,0), v3d(0,0,0), 1)
            })));

    (*thigh_animation)[anim::jump] = *thigh_jump_anim.release();
  }



  double left_thigh_zsize = 0.7;
  auto left_thigh = std::make_shared<animated_gameobject>(std::make_shared<Cube>(
        frog_material,
        v3d(0,0,0),// position
        v3d(left_thigh_diameter, left_thigh_diameter, left_thigh_zsize)// size
        ),
      std::move(thigh_animation));
  left_thigh->position = v3d(0,0, left_thigh_zsize/2);
  left_thigh->rotation = v3d(0,30,15);
  left_thigh->setParent(left_thigh_root);
#if GO_DEBUG_LABELS
  left_thigh->name = "left_thigh";
#endif

  auto left_shin_root = std::make_shared<GameObject>(
#if 0
      std::make_shared<Cube>(debug_material, v3d::zero, 0.2 * v3d::unit)
#endif
      );
  left_shin_root->position = v3d(0, 0, left_thigh_zsize/2);
  left_shin_root->setParent(left_thigh);
#if GO_DEBUG_LABELS
  left_shin_root->name = "left_shin_root";
#endif


  double shin_jumpanim_angle = 130;
  std::unique_ptr<anim_map> shin_animation = std::make_unique<anim_map>(); 
  {

    auto shin_jump_anim = std::make_unique<animation>(std::move(
          std::make_unique<std::vector<animation::keyframe>, std::initializer_list<animation::keyframe>>({
            animation::keyframe(v3d(0,0,0), v3d(shin_jumpanim_angle,0,0), 0.2),
            animation::keyframe(v3d(0,0,0), v3d(shin_jumpanim_angle,0,0), 0.6),
            animation::keyframe(v3d(0,0,0), v3d(0,0,0), 0.8)
            })));

    (*shin_animation)[anim::jump] = *shin_jump_anim.release();
  }



  double left_shin_diameter = left_thigh_diameter * 0.8;
  double left_shin_zsize = 0.5;
  auto left_shin = std::make_shared<animated_gameobject>(std::make_shared<Cube>(
        frog_material,
        v3d(0,0,0),// position
        v3d(left_shin_diameter, left_shin_diameter, left_shin_zsize)// size
        ),
      std::move(shin_animation));
  left_shin->position = v3d(0, 0, left_thigh_zsize/2);
  left_shin->rotation.x = -150;
  left_shin->setParent(left_shin_root);
#if GO_DEBUG_LABELS
  left_shin->name = "left_shin";
#endif


  auto left_foot_root = std::make_shared<GameObject>(
#if 0
      std::make_shared<Cube>(debug_material, v3d::zero, 0.2 * v3d::unit)
#endif
      );
  left_foot_root->position = v3d(0, 0, left_shin_zsize/2);
  left_foot_root->setParent(left_shin);
#if GO_DEBUG_LABELS
  left_foot_root->name = "left_foot_root";
#endif

  double foot_jumpanim_angle = -90;
  std::unique_ptr<anim_map> foot_animation = std::make_unique<anim_map>(); 
  {

    auto foot_jump_anim = std::make_unique<animation>(std::move(
          std::make_unique<std::vector<animation::keyframe>, std::initializer_list<animation::keyframe>>({
            animation::keyframe(v3d(0,0,0), v3d(foot_jumpanim_angle,0,0), 0.2),
            animation::keyframe(v3d(0,0,0), v3d(foot_jumpanim_angle,0,0), 0.6),
            animation::keyframe(v3d(0,0,0), v3d(0,0,0), 1.2)
            })));

    (*foot_animation)[anim::jump] = *foot_jump_anim.release();
  }

  double left_foot_diameter = left_shin_diameter * 0.8f;
  double left_foot_zsize = 0.5;
  auto left_foot = std::make_shared<animated_gameobject>(std::make_shared<Cube>(
        frog_material,
        v3d(0,0,0),// position
        v3d(left_foot_diameter, left_foot_diameter, left_foot_zsize)// size
        ),
      std::move(foot_animation));
  left_foot->position = v3d(0, 0, left_shin_zsize/2);
  left_foot->rotation.x = 140;
  left_foot->setParent(left_foot_root);
#if GO_DEBUG_LABELS
  left_foot->name = "left_foot";
#endif


  auto left_ball_root = std::make_shared<GameObject>(
#if 0
      std::make_shared<Cube>(debug_material, v3d::zero, 0.2 * v3d::unit)
#endif
      );
  left_ball_root->position = v3d(0, 0, left_foot_zsize/2);
  left_ball_root->setParent(left_foot);
#if GO_DEBUG_LABELS
  left_ball_root->name = "left_ball_root";
#endif

  double left_ball_xsize = left_foot_diameter * 1.3;
  double left_ball_ysize = left_ball_xsize * 0.8;
  double left_ball_zsize = left_ball_xsize;
  auto left_ball = std::make_shared<GameObject>(std::make_shared<Cube>(
        frog_material,
        v3d(0,0,0),// position
        v3d(left_ball_xsize, left_ball_ysize, left_ball_zsize)// size
        ));
  left_ball->position = v3d(0, 0, left_ball_zsize/2);
  left_ball->setParent(left_ball_root);
#if GO_DEBUG_LABELS
  left_ball->name = "left_ball";
#endif

  double left_toe_diameter = left_ball_xsize * 0.3;
  double left_toe_zsize = left_toe_diameter * 2.7;
  auto left_toe = std::make_shared<GameObject>(std::make_shared<Cube>(
        frog_material,
        v3d(0,0,0),// position
        v3d(left_toe_diameter, left_toe_diameter, left_toe_zsize)// size
        ));
  left_toe->position = v3d(0, 0, left_toe_zsize/2 + left_ball_zsize/2);
  left_toe->setParent(left_ball);
#if GO_DEBUG_LABELS
  left_toe->name = "left_toe";
#endif

  auto left_toe_2 = left_toe->clone();
  left_toe_2->rotation.y = 20;
  left_toe_2->position.x += left_toe_diameter/2;
  auto left_toe_3 = left_toe->clone();
  left_toe_3->rotation.y = -20;
  left_toe_3->position.x -= left_toe_diameter/2;


  right_thigh_root->position.x *= -1;
  auto right_thigh = left_thigh->clone();
  right_thigh->setParent(right_thigh_root);
#if GO_DEBUG_LABELS
  right_thigh->name = "right_thigh";
#endif
  right_thigh->rotation.y *= -1;
  right_thigh->rotation.z *= -1;



  // ARMS

  double left_arm_diameter = 0.13;
  auto left_arm_root = std::make_shared<GameObject>(
#if 1
      nullptr
#else
      std::make_shared<Cube>(debug_material, v3d::zero, 0.2 * v3d::unit)
#endif
      );
  left_arm_root->position = v3d(body_xsize/2, -1 * body_ysize/2 + left_arm_diameter/2, body_zsize/2 - left_arm_diameter/2);
  left_arm_root->setParent(body);
#if GO_DEBUG_LABELS
  left_arm_root->name = "left_arm_root";
#endif

  // clone now, so we can separately clone the arm
  //   so that we can change the arms angle
  auto right_arm_root = left_arm_root->clone();

  double left_arm_zsize = 0.2;
  auto left_arm = std::make_shared<GameObject>(std::make_shared<Cube>(
        frog_material,
        v3d(0,0,0),// position
        v3d(left_arm_diameter, left_arm_diameter, left_arm_zsize)// size
        ));
  left_arm->position = v3d(0,0, left_arm_zsize/2);
  left_arm->rotation = v3d(-50,30,15);
  left_arm->setParent(left_arm_root);
#if GO_DEBUG_LABELS
  left_arm->name = "left_arm";
#endif


  auto left_forearm_root = std::make_shared<GameObject>(
#if 1
      nullptr
#else
      std::make_shared<Cube>(debug_material, v3d::zero, 0.2 * v3d::unit)
#endif
      );
  left_forearm_root->position = v3d(0, 0, left_arm_zsize/2);
  left_forearm_root->setParent(left_arm);
#if GO_DEBUG_LABELS
  left_forearm_root->name = "left_forearm_root";
#endif


  double left_forearm_diameter = left_arm_diameter * 0.8;
  double left_forearm_zsize = left_arm_zsize * 1.1;
  auto left_forearm = std::make_shared<GameObject>(std::make_shared<Cube>(
        frog_material,
        v3d(0,0,0),// position
        v3d(left_forearm_diameter, left_forearm_diameter, left_forearm_zsize)// size
        ));
  left_forearm->position = v3d(0,0, left_forearm_zsize/2);
  left_forearm->rotation = v3d(20, 0, 0);
  left_forearm->setParent(left_forearm_root);
#if GO_DEBUG_LABELS
  left_forearm->name = "left_forearm";
#endif






  auto left_hand_root = std::make_shared<GameObject>(
#if 0
      std::make_shared<Cube>(debug_material, v3d::zero, 0.2 * v3d::unit)
#endif
      );
  left_hand_root->position = v3d(0, 0, left_forearm_zsize/2);
  left_hand_root->setParent(left_forearm);
#if GO_DEBUG_LABELS
  left_hand_root->name = "left_hand_root";
#endif

  double left_hand_xsize = left_forearm_diameter * 1.3;
  double left_hand_ysize = left_hand_xsize * 0.8;
  double left_hand_zsize = left_hand_xsize;
  auto left_hand = std::make_shared<GameObject>(std::make_shared<Cube>(
        frog_material,
        v3d(0,0,0),// position
        v3d(left_hand_xsize, left_hand_ysize, left_hand_zsize)// size
        ));
  left_hand->position = v3d(0, 0, left_hand_zsize/2);
  left_hand->setParent(left_hand_root);
#if GO_DEBUG_LABELS
  left_hand->name = "left_hand";
#endif

  double left_finger_diameter = left_hand_xsize * 0.3;
  double left_finger_zsize = left_finger_diameter * 2.7;
  auto left_finger = std::make_shared<GameObject>(std::make_shared<Cube>(
        frog_material,
        v3d(0,0,0),// position
        v3d(left_finger_diameter, left_finger_diameter, left_finger_zsize)// size
        ));
  left_finger->position = v3d(0, 0, left_finger_zsize/2 + left_hand_zsize/2);
  left_finger->setParent(left_hand);
#if GO_DEBUG_LABELS
  left_finger->name = "left_finger";
#endif

  auto left_finger_2 = left_finger->clone();
  left_finger_2->rotation.y = 30;
  left_finger_2->position.x += left_finger_diameter/2;
  auto left_finger_3 = left_finger->clone();
  left_finger_3->rotation.y = -30;
  left_finger_3->position.x -= left_finger_diameter/2;





  right_arm_root->position.x *= -1;
  auto right_arm = left_arm->clone();
  right_arm->setParent(right_arm_root);
#if GO_DEBUG_LABELS
  right_arm->name = "right_arm";
#endif
  right_arm->rotation.y *= -1;
  right_arm->rotation.z *= -1;

}
