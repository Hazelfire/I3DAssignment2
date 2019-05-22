#include "main.hpp"

void update(void) {
  _time::update(glutGet(GLUT_ELAPSED_TIME));

#if UNIT_TESTS
  test::rotate();
#endif

  handle_keys();

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

  float shininess = 0;
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess);

  // camera
  // anything before here is relative to the camera
  player_camera.move_to();
  // anything after here is relative to the world

  glColor3f(1,1,1);

  glEnable(GL_LIGHT0);
  float light_pos[] = {3,2,1,0};
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

  scene.add(GameObject(new Cube(v3d(-0.5,3,-0.5), v3d(1,2,1))), "object");
  scene.add(GameObject(new Sphere(v3d(0,2,1), 1)), "object");
  scene.add(GameObject(new Cylinder(v3d(0.5,0.5,1), 0.5, 2)), "object");
  scene.add(GameObject(new Sin_and_Cos(v3d(2,2,0), v3d(1,1,1))), "object");
  scene.draw();

  glDisable(GL_LIGHTING);
  glColor3f(1,1,1);
#if ENABLE_LIGHTING
  glEnable(GL_LIGHTING);
#endif

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

  player_camera.rotation.x += 0.5 * dx;
  player_camera.rotation.y += 0.5 * dy;

  if(player_camera.rotation.y > 90) {
    player_camera.rotation.y = 90;
  } else if(player_camera.rotation.y < -90) {
    player_camera.rotation.y = -90;
  }

  last_x = x;
  last_y = y;
}

void specialUp(int key, int x, int y) {
  switch(key) {
    default:
    break;
  }
}

void special(int key, int x, int y) {
  switch(key) {
    default:
    break;
  }
}

void keyboardUp(unsigned char key, int x, int y) {
  keyboard::release(key);
}

void keyboard(unsigned char key, int x, int y) {
  keyboard::hold(key);
}

void handle_keys() {
  double movement = 5;

#define USE_XZ 0
#if USE_XZ
  v3d forward = player_camera.get_forward_xz();
  // cross is already normalised, since forward is in the x-z plane
  v3d right = v3d::cross(v3d::Y, forward)/*.normalise()*/;
#else
  v3d forward = player_camera.get_forward();
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

  if(*keys & kb_w) {
    player_camera.position += forward * movement * time.delta;
  }
  if(*keys & kb_s) {
    player_camera.position -= forward * movement * time.delta;
  }
  if(*keys & kb_d) {
    player_camera.position -= right * movement * time.delta;
  }
  if(*keys & kb_a) {
    player_camera.position += right * movement * time.delta;
  }
  if(*keys & kb_space) {
    player_camera.position -= v3d::Y * movement * time.delta;
  }
  if(*keys & kb_c) {
    player_camera.position += v3d::Y * movement * time.delta;
  }
}


void init() {
  player_camera = camera();

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
