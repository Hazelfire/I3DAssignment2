#include "main.h"

void update(void) {
  _time::update(glutGet(GLUT_ELAPSED_TIME));

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

  // camera
  glPushMatrix();
  player_camera.move_to();

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

  //X axis
  glBegin(GL_LINES);
  glColor3f(1,0,0);
  glVertex3f(0,0,0);
  glVertex3f(1,0,0);
  glEnd();
  //Y axis
  glBegin(GL_LINES);
  glColor3f(0,1,0);
  glVertex3f(0,0,0);
  glVertex3f(0,1,0);
  glEnd();
  //Z axis
  glBegin(GL_LINES);
  glColor3f(0,0,1);
  glVertex3f(0,0,0);
  glVertex3f(0,0,1);
  glEnd();



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

  glMatrixMode(GL_PROJECTION);	// Set the matrix we want to manipulate
  glLoadIdentity();			// Overwrite the contents with the identity
  gluPerspective(75, (double)x / y, 0.01, 100);		// Multiply the current matrix with a generated perspective matrix
  glMatrixMode(GL_MODELVIEW);	// Change back to the modelview matrix
}

void mouse(int x, int y) {
  //std::cout << "x: " << x << "\ny: " << y << std::endl;
  static int last_x = 0;
  static int last_y = 0;

  int dx = x - last_x;
  int dy = y - last_y;

  player_camera.rotation.x += 0.5 * dx;
  player_camera.rotation.y += 0.5 * dy;

  last_x = x;
  last_y = y;
}

void specialUp(int key, int x, int y) {
  switch(key) {
	  default:
	  break;
  }
}
void keyboardUp(unsigned char key, int x, int y) {
  keyboard::release(key);
}

void special(int key, int x, int y) {
  switch(key) {
	  default:
	  break;
  }
}

void handle_keys() {
  double movement = 5;

#define USE_XZ 1
#if USE_XZ
  v3d forward = player_camera.get_forward_xz();
  // cross is already normalised, since forward is in the x-z plane
  v3d right = -1*v3d::cross(v3d::Y, forward)/*.normalise()*/;
#else
  v3d forward = player_camera.get_forward();
  v3d right = -1*v3d::cross(v3d::Y, forward).normalise();
#endif

  const _time& time = _time::get_instance();
  const enum keys *keys = &keyboard::get_instance().held;


#define PRINT_KEYS_INFO 1
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
	  player_camera.position += right * movement * time.delta;
  }
  if(*keys & kb_a) {
	  player_camera.position -= right * movement * time.delta;
  }
  if(*keys & kb_space) {
	  player_camera.position += v3d::Y * movement * time.delta;
  }
  if(*keys & kb_c) {
	  player_camera.position -= v3d::Y * movement * time.delta;
  }
}

void keyboard(unsigned char key, int x, int y) {
  keyboard::hold(key);
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
