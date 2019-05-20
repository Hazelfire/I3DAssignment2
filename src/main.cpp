#include "main.h"

void update(void) {


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

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  // camera
  glPushMatrix();
  player_camera.move_to();

  glBegin(GL_QUADS);
  glVertex3f(0,0,0);
  glVertex3f(0,0.5,0);
  glVertex3f(0.5,0.5,0);
  glVertex3f(0.5,0,0);
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

void mouseMotion(int x, int y) {
  std::cout << "x: " << x << "\ny: " << y << std::endl;
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

void keyboard(unsigned char key, int x, int y) {
  switch(key) {
    default:
    break;
  }
}


void init() {
  player_camera = camera();

  glMatrixMode(GL_PROJECTION);
  glOrtho(-1.0, (GLUT_SCREEN_HEIGHT * 2 / GLUT_SCREEN_WIDTH) - 1, -1.0, 1.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
#if VSYNC
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
#else
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
#endif
  glutCreateWindow("frogger cross section");

  init();

  glutPassiveMotionFunc(mouseMotion);
  glutMotionFunc(mouseMotion);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutKeyboardUpFunc(keyboardUp);
  glutSpecialFunc(special);
  glutSpecialUpFunc(specialUp);
  glutIdleFunc(update);
  glutMainLoop();

}
