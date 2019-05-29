#include "main.hpp"
#include "terrain.hpp"

void reset(void) {
  player->position = v3d::zero;
  player->ground();
}

void drawOsd(){
  const _time& t = _time::get_instance();
  glColor3f(1.0, 1.0, 1.0);

  char cstring[100];
  sprintf(cstring, "Tesselations %d\nFPS: %.2f\nFT: %.2f", drawOpts.tesselations, 1 / t.delta, t.delta * 1000);

  glRasterPos3f(0.5, 0.5, -1);
  glutBitmapString(GLUT_BITMAP_HELVETICA_18, cstring);
  
}

void drawGameOver(){
  glColor3f(1.0, 1.0, 1.0);

  char* string = (char*)"Game Over";
  glRasterPos3f(0, 0, -1);
  glutBitmapString(GLUT_BITMAP_HELVETICA_18, string);
}

int lives = 5;
int score = 0;
bool playerDead = false;

void update(void) {
  _time::update(glutGet(GLUT_ELAPSED_TIME));
  const _time& t = _time::get_instance();

#if UNIT_TESTS
  test::rotate();
#endif

  handle_keys();

  if(drawOpts.animation){
    Scene::update(t.delta);
  }

  if(Scene::get_instance().getCollidingObjectsByTag(*player, tag::death).size() > 0){
    lives--;
    reset();
    if(lives == 0){
      playerDead = true;    
    }
  }

  if(player->position.z > 24){
    score++;
    reset();
  }

  auto logsCollided = Scene::get_instance().getCollidingObjectsByTag(*player, tag::log);
  if(logsCollided.size() > 0){
    (*player).bind(*logsCollided[0]);
  }

  focus->position = v3d::zero -player->position;


  // redraw the screen
  glutPostRedisplay();
}

#if !USE_FREEGLUT
void glutBitmapString(void *font, char *str) {
  for(int i = 0; str[i] != '\0'; i++) {
    glutBitmapCharacter(font, str[i]);
  }
}
#endif

// draw
void display() {
  glColor3f(1.0, 1.0, 1.0);
  glRasterPos2f(0.5, 0.5);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();
  glPushMatrix();


  if(drawOpts.lighting){
    glEnable(GL_LIGHTING);
  }


  // camera
  // anything before here is relative to the camera
  player_camera->pushTransform();
  // anything after here is relative to the world

  const _time& time = _time::get_instance();

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glColor3f(1,1,1);

  Colour blue(0,0.5,1,1);
  Colour green(0,1,0,1);
  Colour pink(1,0.1,0.5,1);
  Colour white(1,1,1,1);
  Material debug_material(128, pink * 0.3, pink, white);
  glMaterialfv(GL_FRONT_AND_BACK, debug_material);

  glEnable(GL_LIGHT0);
  float light_pos[] = {3,10,1,0};
  float light_colour_a[] = {0.1,0.1,0.1,0.1};
  float light_colour_d[] = {1,1,1,1};
  float light_colour_s[] = {1,1,1,1};
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_colour_a);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_colour_d);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_colour_s);
  //glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.5);
  //glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.4);
  //glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1);
  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
  Sphere sun(v3d(light_pos[0],light_pos[1],light_pos[2]), 0.2);

  glDisable(GL_LIGHTING);
  sun.draw(drawOpts);
  if(drawOpts.lighting){
    glEnable(GL_LIGHTING);
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



#if 0
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 1/*index of texture, returned by loading function*/);
  // give this for every vertex
  // normal and tex coord should be before the glvert call
  glTexCoord2d(/*u[0,1]*/0, /*v[0,1]*/0);
#endif

  if(drawOpts.wireframe){
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  else{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }


#define RENDER_TEST_WATER 0
#if RENDER_TEST_WATER
  Tute_Water test_func(Material(128,//shine
        Colour(0.1, 0.1, 0.1, 0.1), //ambient
        Colour(1, 0, 0, 1),         //diffuse
        Colour(1, 1, 1, 1)          //specular
        ), v3d(2,2,0), v3d(2,1,1)); //position, scale
  test_func.x_mul = 10;
  test_func.z_mul = 5;
  test_func.t = time.current;
  test_func.draw(drawOpts);
#endif



  const Scene& scene = Scene::get_instance();
  scene.draw(drawOpts);

  glDisable(GL_LIGHTING);
  glColor3f(1,1,1);
  if(drawOpts.lighting){
    glEnable(GL_LIGHTING);
  }




#define DRAW_3_SQUARES 0
#if DRAW_3_SQUARES
  glBegin(GL_QUADS);
  glVertex3f(0,0,5);
  glVertex3f(0,0.5,5);
  glVertex3f(0.5,0.5,5);
  glVertex3f(0.5,0,5);
  glEnd();
  glBegin(GL_QUADS);
  glVertex3f(1,0,5);
  glVertex3f(1,0.5,5);
  glVertex3f(1.5,0.5,5);
  glVertex3f(1.5,0,5);
  glEnd();
  glBegin(GL_QUADS);
  glVertex3f(0,1,5);
  glVertex3f(0,1.5,5);
  glVertex3f(0.5,1.5,5);
  glVertex3f(0.5,1,5);
  glEnd();
#endif

  glDisable(GL_LIGHTING);
  if(drawOpts.drawAxes){
    //X axis
    glColor3f(1,0,0);
    v3d::X.draw();
    //Y axis
    glColor3f(0,1,0);
    v3d::Y.draw();
    //Z axis
    glColor3f(0,0,1);
    v3d::Z.draw();
  }
  if(drawOpts.lighting){
    glEnable(GL_LIGHTING);
  }

  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  //glPolygonMode(GL_BACK, GL_LINE);
  int numverts = 20;
  double x_max = 2*PI;
  double tangent_diff = 0.001;

  glColor3f(1, 1, 0);


  player_camera->popTransform();
  glPopMatrix();

  glDisable(GL_LIGHTING);
  if(drawOpts.osd){
    drawOsd();
  }

  if(playerDead){
    drawGameOver();
  }


#ifndef VSYNC
#define VSYNC 1
#endif
#if VSYNC
  //vsync
  glutSwapBuffers();
#else
  glFlush();
#endif


  // print out errors
  int err;
  while ((err = glGetError()) != GL_NO_ERROR) {
    printf("display: %s\n", gluErrorString(err));
  }

}

void reshape(int x, int y) {
  //std::cout << "new window size: x(" << x << ")\t y(" << y << ")" << std::endl;

  /*
  glMatrixMode(GL_PROJECTION);
  glOrtho(-1.0, (GLUT_SCREEN_HEIGHT * 2 / GLUT_SCREEN_WIDTH) - 1, -1.0, 1.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  */

  glMatrixMode(GL_PROJECTION);                  // Set the matrix we want to manipulate
  glLoadIdentity();                             // Overwrite the contents with the identity
  gluPerspective(75, (double)x / y, 0.01, 100); // Multiply the current matrix with a generated perspective matrix
  glMatrixMode(GL_MODELVIEW);                   // Change back to the modelview matrix
  
  // update the viewport with the new width and height
  glViewport(0,0, x, y);
}

bool rightDown = false;
bool leftDown = false;

void mouse(int x, int y) {
  //std::cout << "x: " << x << "\ny: " << y << std::endl;
  static int last_x = 0;
  static int last_y = 0;

  int dx = x - last_x;
  int dy = y - last_y;

  if(leftDown){
    focus->rotation.y += 0.5 * dx;
    focus->rotation.x += 0.5 * dy;

    if(focus->rotation.x > 0) {
      focus->rotation.x = 0;
    } else if(focus->rotation.x < -90) {
      focus->rotation.x = -90;
    }
  }

  if(rightDown){
    player_camera->position.z += 0.1 * dy;
  }

  last_x = x;
  last_y = y;
}

void mouseClick(int button, int state, int x, int y){
  leftDown = button == GLUT_LEFT_BUTTON && state == GLUT_DOWN;
  rightDown = button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN;
}

void specialUp(int key, int x, int y) {
  keyboard::release_special(key);
}

void special(int key, int x, int y) {
  keyboard::hold_special(key);
}

void keyboardUp(unsigned char key, int x, int y) {
  if(glutGetModifiers() & GLUT_ACTIVE_CTRL) {
    keyboard::hold_ctrl();
  } else {
    keyboard::release_ctrl();
  }
  keyboard::release(key);
}

void keyboard(unsigned char key, int x, int y) {
  if(glutGetModifiers() & GLUT_ACTIVE_CTRL) {
    keyboard::hold_ctrl();
  } else {
    keyboard::release_ctrl();
  }
  keyboard::hold(key);
  
  switch(key){
    case 'x':
      drawOpts.drawAxes = !drawOpts.drawAxes;
      break;
    case 'n':
      drawOpts.normals = !drawOpts.normals;
      break;
    case 'f':
      drawOpts.wireframe = !drawOpts.wireframe;
      break;
    case 't':
      drawOpts.textures = !drawOpts.textures;
      break;
    case 'g':
      drawOpts.animation = !drawOpts.animation;
      break;
    case 'l':
      drawOpts.lighting = !drawOpts.lighting;
      break;
    case 'o':
      drawOpts.osd = !drawOpts.osd;
      break;
    case '+':
      drawOpts.tesselations *= 2;
      break;
    case '-':
      if(drawOpts.tesselations > 4){
        drawOpts.tesselations /= 2;
      }
      break;
    case 'r':
      reset();
      break;
  }
}

void handle_keys() {
  double movement = 20;
  double extensionSpeed = 1;

#define USE_XZ 0
#if USE_XZ
  v3d forward = player_camera.get_forward_xz();
  // cross is already normalised, since forward is in the x-z plane
  v3d right = v3d::cross(v3d::Y, forward)/*.normalise()*/;
#else
  v3d forward = player_camera->get_forward();
  v3d right = v3d::cross(v3d::Y, forward).normalise();
#endif

  const _time& time = _time::get_instance();
  const enum keys *keys = &keyboard::get_instance().held;


#define PRINT_KEYS_INFO 0
#if PRINT_KEYS_INFO
  std::cout << "forward: " << forward << std::endl;
  std::cout << "movement: " << movement << std::endl;
  std::cout << "dt: " << time.delta << std::endl;
  std::cout << "player_camera.position: " << player_camera.position << std::endl;
  std::cout << "right.length: " << right.length() << std::endl;
#endif

#define FLY_MOVEMENT 0
#if FLY_MOVEMENT
  if(*keys & kb_w) {
    player_camera.position += forward * movement * time.delta;
  }
  if(*keys & kb_s) {
    player_camera.position -= forward * movement * time.delta;
  }
  if(*keys & kb_c) {
    player_camera.position += v3d::Y * movement * time.delta;
  }
#endif

  if(!playerDead){
    if(*keys & kb_space) {
      player->jump();
    }
    if(*keys & kb_d) {
      player->jumpV.rotate(movement * time.delta, v3d::Y);
    }
    if(*keys & kb_a) {
      player->jumpV.rotate(-movement * time.delta, v3d::Y);
    }
    v3d jumpD(player->jumpV);
    jumpD.normalise();
    if(*keys & kb_up) {
      player->jumpV += jumpD * extensionSpeed * time.delta;
    }
    if(*keys & kb_down) {
      player->jumpV -= jumpD * extensionSpeed * time.delta;
    }
    if(*keys & kb_left) {
      v3d right = jumpD.cross(v3d::Y);
      player->jumpV.rotate(movement * time.delta, right);
    }
    if(*keys & kb_right) {
      v3d right = jumpD.cross(v3d::Y);
      player->jumpV.rotate(-movement * time.delta, right);
    }
  }
}


void init() {
  const Scene& scene = Scene::get_instance();

#define DRAW_OBJECTS 0
#if DRAW_OBJECTS
  scene.add(std::shared_ptr<GameObject>(std::shared_ptr<Cube>( v3d(-0.5,3,-0.5), v3d(1,2,1))), tag::object);
  scene.add(std::shared_ptr<GameObject>(std::shared_ptr<Sphere>( v3d(0,2,1), 1)), tag::object);
  scene.add(std::shared_ptr<GameObject>(std::shared_ptr<Cylinder>( v3d(0.5,0.5,1), 0.5, 2)), tag::object);
  scene.add(std::shared_ptr<GameObject>(std::shared_ptr<Sin_and_Cos>( v3d(2,2,0), v3d(1,1,1))), tag::object);
#endif
  Scene::add(player, tag::player);

  create_frog(player);
  create_terrain();

  /*
   * The camera has a "focus", which is an empty game object that tracks
   * the position of the player. Rotating and moving this focus makes sure
   * that the camera is always pointing towards the player
   */

  player_camera->position.z = -4;
  player_camera->setParent(focus);



  // init singletons
  keyboard::get_instance();
  _time::get_instance();

  reshape(0,0);
  mouse(0,0);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  // load textures here
#if VSYNC
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
#else
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
#endif
  glutCreateWindow("Frogger 3D");

  init();

  glutReshapeFunc(reshape);
  glutPassiveMotionFunc(mouse);
  glutMotionFunc(mouse);
  glutMouseFunc(mouseClick);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutKeyboardUpFunc(keyboardUp);
  glutSpecialFunc(special);
  glutSpecialUpFunc(specialUp);
  glutIdleFunc(update);
  glutMainLoop();

}
