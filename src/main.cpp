#include "main.hpp"
#include "terrain.hpp"

void update(void) {
  _time::update(glutGet(GLUT_ELAPSED_TIME));
  const _time& t = _time::get_instance();

#if UNIT_TESTS
  test::rotate();
#endif

  handle_keys();

  scene.update(t.delta);
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
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glPushMatrix();

#define ENABLE_LIGHTING 1

#if ENABLE_LIGHTING
  glEnable(GL_LIGHTING);
#endif

  // camera
  // anything before here is relative to the camera
  player_camera->pushTransform();
  // anything after here is relative to the world

  const _time& time = _time::get_instance();

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glColor3f(1,1,1);

  float shininess = 128;
  //float shininess = 50;
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess);
  float ambient[] = {0,0.15,0.3,1};
  float diffuse[] = {0,0.5,1,1};
  float specular[] = {1,1,1,1};
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

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
  sun.draw();
#if ENABLE_LIGHTING
  glEnable(GL_LIGHTING);
#endif



#if 0
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 1/*index of texture, returned by loading function*/);
  // give this for every vertex
  // normal and tex coord should be before the glvert call
  glTexCoord2d(/*u[0,1]*/0, /*v[0,1]*/0);
#endif

#define DRAW_FILL 1
#if DRAW_FILL
  //glPolygonMode(GL_FRONT, GL_FILL);
  //glPolygonMode(GL_BACK, GL_LINE);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#else
#define WIREFRAME 1
#if WIREFRAME
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#else
  glPolygonMode(GL_BACK, GL_LINE);
  glPolygonMode(GL_FRONT, GL_POINT);
  glPointSize(10);
#endif
#endif

  scene.draw();

  glDisable(GL_LIGHTING);
  glColor3f(1,1,1);
#if ENABLE_LIGHTING
  glEnable(GL_LIGHTING);
#endif
  /*
  Tute_Water test_func(v3d(2,2,0), v3d(2,1,1));
  test_func.x_mul = 10;
  test_func.z_mul = 5;
  test_func.t = time.current;
  test_func.draw();
*/

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
  //X axis
  glColor3f(1,0,0);
  v3d::X.draw();
  //Y axis
  glColor3f(0,1,0);
  v3d::Y.draw();
  //Z axis
  glColor3f(0,0,1);
  v3d::Z.draw();
#if ENABLE_LIGHTING
  glEnable(GL_LIGHTING);
#endif

  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  //glPolygonMode(GL_BACK, GL_LINE);
  int numverts = 20;
  double x_max = 2*PI;
  double tangent_diff = 0.001;

  glColor3f(1, 1, 0);

#define DRAW_SIN 0
#if DRAW_SIN
#define DRAW_SIN_NORMALS 0
#if DRAW_SIN_NORMALS
  glBegin(GL_LINES);
  for(int row = 0; row < numverts; row++) {
    for(int col = 0; col < numverts; col++) {
      v3d current = v3d(row, sinf(col * x_max/numverts), col);
      v3d next = v3d(row+1, sinf(col * x_max/numverts), col);
      v3d current_beside = v3d(row, sinf((col+tangent_diff) * x_max/numverts), col+tangent_diff);
      v3d tangent = current - current_beside;
      v3d normal = v3d::cross(tangent, current - next).normalise()*0.3;
      if(normal.dot(v3d::Y) < 0)
        normal *= -1;
      normal += current;
      glVertex3f(current.x, current.y, current.z);
      glVertex3f(normal.x, normal.y, normal.z);
    }
  }
  glEnd();
#endif
  
  for(int row = 0; row < numverts; row++) {
    glColor3f((row+1) / (double)numverts, 1, 1);
    glBegin(GL_QUAD_STRIP);
    for(int col = 0; col < numverts; col++) {
      v3d current = v3d(row, sinf(col * x_max/numverts), col);
      v3d next = v3d(row+1, sinf(col * x_max/numverts), col);

      //normals
      v3d current_beside = v3d(row, sinf((col+tangent_diff) * x_max/numverts), col+tangent_diff);
      v3d tangent = current - current_beside;
      v3d normal = v3d::cross(tangent, current - next).normalise()*0.3;
      if(normal.dot(v3d::Y) < 0)
        normal *= -1;

      // normals 2
      v3d current_beside2 = v3d(row+1, sinf((col+tangent_diff) * x_max/numverts), col+tangent_diff);
      v3d tangent2 = next - current_beside2;
      v3d normal2 = v3d::cross(tangent, current - next).normalise()*0.3;
      if(normal2.dot(v3d::Y) < 0)
        normal2 *= -1;

      glNormal3f(normal.x, normal.y, normal.z);
      current.glVertex();
      glNormal3f(normal2.x, normal2.y, normal2.z);
      next.glVertex();
    }
    glEnd();
  }
#endif


  player_camera->popTransform();
  glPopMatrix();
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

void mouse(int x, int y) {
  //std::cout << "x: " << x << "\ny: " << y << std::endl;
  static int last_x = 0;
  static int last_y = 0;

  int dx = x - last_x;
  int dy = y - last_y;

  focus->rotation.y += 0.5 * dx;
  focus->rotation.x += 0.5 * dy;

  if(focus->rotation.x > 0) {
    focus->rotation.x = 0;
  } else if(focus->rotation.x < -90) {
    focus->rotation.x = -90;
  }

  last_x = x;
  last_y = y;
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
}

void handle_keys() {
  double movement = 5;
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
  if(*keys & kb_space) {
    player->jump();
  }
  if(*keys & kb_d) {
    player->jumpV.rotate(-movement * time.delta, v3d::Y);
  }
  if(*keys & kb_a) {
    player->jumpV.rotate(movement * time.delta, v3d::Y);
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


void init() {

#define DRAW_OBJECTS 0
#if DRAW_OBJECTS
  scene.add(new GameObject(new Cube(v3d(-0.5,3,-0.5), v3d(1,2,1))), "object");
  scene.add(new GameObject(new Sphere(v3d(0,2,1), 1)), "object");
  scene.add(new GameObject(new Cylinder(v3d(0.5,0.5,1), 0.5, 2)), "object");
  scene.add(new GameObject(new Sin_and_Cos(v3d(2,2,0), v3d(1,1,1))), "object");
#endif
  scene.add(player, "player");

  create_terrain(scene);

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
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutKeyboardUpFunc(keyboardUp);
  glutSpecialFunc(special);
  glutSpecialUpFunc(specialUp);
  glutIdleFunc(update);
  glutMainLoop();

}
