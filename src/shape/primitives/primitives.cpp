#include "primitives.hpp"
#include <cmath>
#include <GL/gl.h>
#include <SOIL.h>
#include <memory>

// Sphere
//Sphere::Sphere(Material material, v3d position, double radius): Shape(material), position(position), radius(radius) {};
//Sphere::Sphere(v3d position, double radius): Sphere(Material(), position, radius) {};

double Sphere::distance(const Sphere &other) const {
  return other.position.distance(this->position) - this->radius - other.radius;
}

bool Sphere::collidesWith(const Sphere &other) const{
  return distance(other) <= 0;
}

bool Sphere::collidesWith(const Cube &other) const{
  bool insideX = this->position.x + this->radius > other.position.x - (other.size.x / 2) && this->position.x - this->radius < other.position.x + (other.size.x / 2);
  bool insideY = this->position.y + this->radius > other.position.y - (other.size.y / 2) && this->position.y - this->radius < other.position.y + (other.size.y / 2);
  bool insideZ = this->position.z + this->radius > other.position.z - (other.size.z / 2) && this->position.z - this->radius < other.position.z + (other.size.z / 2);
  return insideX && insideY && insideZ;
}

bool Sphere::collidesWith(const Grid &other) const{
  bool insideX = this->position.x + this->radius > other.position.x - (other.size.x / 2) && this->position.x - this->radius < other.position.x + (other.size.x / 2);
  bool insideY = this->position.y + this->radius > other.position.y && this->position.y - this->radius < other.position.y;
  bool insideZ = this->position.z + this->radius > other.position.z - (other.size.z / 2) && this->position.z - this->radius < other.position.z + (other.size.z / 2);
  return insideX && insideY && insideZ;
}

bool Sphere::collidesWith(const Cylinder &other) const{
  double diffz = position.z - other.position.z;
  double diffy = position.y - other.position.y;
  bool insideLength = sqrt(diffy * diffy + diffz * diffz) < radius + other.radius;
  bool insideX = position.x + radius > other.position.x - (other.length / 2) && position.x - radius < other.position.x + (other.length / 2);

  return insideX && insideLength;
}

std::unique_ptr<Shape> Sphere::clone() const {
  return std::make_unique<Sphere>(*this);
}

bool Sphere::collidesWith(const Function &other) const{
  return this->position.y < other.position.y;
}

void Sphere::really_draw(const DrawOptions &options) const {
  // push position
  glPushMatrix();
  glTranslated(position.x, position.y, position.z);
  glScaled(radius, radius, radius);

  // TODO set n from global tessalation value
  const int n = options.tesselations;
  const int slices=n, stacks=n;
  double step_phi = M_PI / stacks;


  // start of sphere...
  // simplified case, since the pole stays the same
  {
    glBegin(GL_TRIANGLE_FAN);
    double sin_phi_step = sinf(step_phi);
    double cos_phi_step = cosf(step_phi);

    v3d start(0, 0, 1);
    start.glNormal();
    start.glVertex();

    // end point is the same as the start point...
    // needs to be drawn twice
    for(int i = 0; i <= slices; i++) {
      double theta = i / (double)slices * 2.0 * M_PI;
      double cos_theta = cosf(theta);
      double sin_theta = sinf(theta);
      v3d curr(sin_phi_step * cos_theta,
          sin_phi_step * sin_theta,
          cos_phi_step);
      curr.glNormal();
      curr.glVertex();
    }
    glEnd();
  }


#if 1
  // middle of sphere
  for (int j = 1; j < stacks-1; j++) {
    double phi = j / (double)stacks * M_PI;
    glBegin(GL_QUAD_STRIP);
    double sin_phi = sinf(phi);
    double sin_phi_step = sinf(phi+step_phi);
    double cos_phi = cosf(phi);
    double cos_phi_step = cosf(phi+step_phi);

    for (int i = 0; i <= slices; i++) {
      double theta = i / (double)slices * 2.0 * M_PI;
      double cos_theta = cosf(theta);
      double sin_theta = sinf(theta);

      v3d curr(sin_phi * cos_theta,
          sin_phi * sin_theta,
          cos_phi);
      curr.glNormal();
      curr.glVertex();

      v3d step(sin_phi_step * cos_theta,
          sin_phi_step * sin_theta,
          cos_phi_step);
      step.glNormal();
      step.glVertex();
    }
    glEnd();
  }
#endif


  // end of sphere...
  // simplified case, since the pole stays the same
  {
    double phi = (stacks-1) / (double)stacks * M_PI;
    glBegin(GL_TRIANGLE_FAN);
    double sin_phi = sinf(phi);
    double cos_phi = cosf(phi);
    v3d start(0, 0, -1);
    start.glNormal();
    start.glVertex();

    // end point is the same as the start point...
    // needs to be drawn twice
    for (int i = slices; i >= 0; i--) {
      double theta = i / (double)slices * 2.0 * M_PI;
      double cos_theta = cosf(theta);
      double sin_theta = sinf(theta);
      v3d curr(sin_phi * cos_theta,
          sin_phi * sin_theta,
          cos_phi);
      curr.glNormal();
      curr.glVertex();
    }
    glEnd();
  }

  // normals
  if(options.normals) {
    glPushAttrib(GL_LIGHTING);
    glDisable(GL_LIGHTING);
    glColor3f(0,1,0);
    for (int j = 0; j <= stacks; j++) {
      double phi = j / (double)stacks * M_PI;
      double sin_phi = sinf(phi);
      double cos_phi = cosf(phi);

      for (int i = 0; i <= slices; i++) {
        double theta = i / (double)slices * 2.0 * M_PI;
        double cos_theta = cosf(theta);
        double sin_theta = sinf(theta);

        v3d curr(sin_phi * cos_theta,
            sin_phi * sin_theta,
            cos_phi);

        curr.draw(curr);
      }
    }
    glPopAttrib();
  }


  glPopMatrix();
}

// Function
//Function::Function(v3d position, v3d size): position(position), size(size) {};
bool Function::collidesWith(const Cube &other) const{
  return false;
}

bool Function::collidesWith(const Grid &other) const{
  return false;
}

bool Function::collidesWith(const Cylinder &other) const{
  return false;
}

bool Function::collidesWith(const Sphere &other) const{
  return other.collidesWith(*this);
}

bool Function::collidesWith(const Function &other) const{
  return false;
}


void Function::really_draw(const DrawOptions &options) const {
  // push position
  glPushMatrix();
  glTranslated(position.x, position.y, position.z);
  glScaled(size.x, size.y, size.z);

  //glBegin(GL_POINTS);

  // TODO set n from global tessalation value
  const int n = options.tesselations;

  //double y_vals[n][n];
  double (*y_vals)[(n+1)] = nullptr;
  std::unique_ptr<double[]> y_val_cont;
  {
    double *temp = new double[(n+1)*(n+1)];
    y_val_cont = std::unique_ptr<double[]>(temp);
    y_vals = (double(*)[(n+1)])temp;
  }

  //v3d normals[n][n];
  v3d (*normals)[(n+1)] = nullptr;
  std::unique_ptr<v3d[]> normal_cont;
  {
    v3d *temp = new v3d[(n+1)*(n+1)];
    normal_cont = std::unique_ptr<v3d[]>(temp);
    normals = (v3d(*)[(n+1)])temp;
  }

  //v3d x_tan[n][n];
  v3d (*x_tan)[(n+1)] = nullptr;
  std::unique_ptr<v3d[]> x_tan_cont;
  {
    v3d *temp = new v3d[(n+1)*(n+1)];
    x_tan_cont = std::unique_ptr<v3d[]>(temp);
    x_tan = (v3d(*)[(n+1)])temp;
  }

  //v3d z_tan[n][n];
  v3d (*z_tan)[(n+1)] = nullptr;
  std::unique_ptr<v3d[]> z_tan_cont;
  {
    v3d *temp = new v3d[(n+1)*(n+1)];
    z_tan_cont = std::unique_ptr<v3d[]>(temp);
    z_tan = (v3d(*)[(n+1)])temp;
  }

  for(int i = 0; i <= n; i++) {
    double x = (double)i / n - 0.5;
    for(int j = 0; j <= n; j++) {
      double z = (double)j / n - 0.5;
      y_vals[i][j] = f(x, z);
      double dy_x = df_x(x, z);
      double dy_z = df_z(x, z);


      v3d current(x, y_vals[i][j], z);

      /*
       * tangent of f(x) at x=a
       * f(x)
       * g(x) = d/dx f(x)
       * b = f(a)
       *
       * tangent equation:
       *   y = g(a)x + (b - g(a) * a)
       */

      double new_x = x + 1.0/n;
      v3d x_next = v3d(new_x, dy_x * new_x + (y_vals[i][j] - dy_x * x), z) - current;
      x_tan[i][j] = x_next + current;

      double new_z = z + 1.0/n;
      v3d z_next = v3d(x, dy_z * new_z + (y_vals[i][j] - dy_z * z), new_z) - current;
      z_tan[i][j] = z_next + current;

      // TODO: check if the 2 vectors are already the same length, and if they can be easily normalised
      v3d normal = v3d::cross(v3d::normalise(z_next), v3d::normalise(x_next));
      // 2nd normalise doesn't need to be done, because we have opengl normalising for us
      normals[i][j] = normal;
    }
  }


  for(int i = 0; i <= n-1; i++) {
    glBegin(GL_TRIANGLE_STRIP);
    double x = (double)i / n - 0.5;
    for(int j = 0; j <= n; j++) {
      double z = (double)j / n - 0.5;

      normals[i+1][j].glNormal();
      v3d(x + 1.0/n, y_vals[i+1][j], z).glVertex();

      normals[i][j].glNormal();
      v3d(x, y_vals[i][j], z).glVertex();
    }
    glEnd();
  }

  if(options.normals){
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    for(int i = 0; i <= n; i++) {
      double x = (double)i / n - 0.5;
      for(int j = 0; j <= n; j++) {
        double z = (double)j / n - 0.5;

        // draw normals
        glColor3f(0,1,0);
        v3d current(x, y_vals[i][j], z);
        current.glVertex();
        (current + normals[i][j] * 1.0/n).glVertex();

        // draw x tangents
        glColor3f(1,0,0);
        current.glVertex();
        x_tan[i][j].glVertex();

        // draw z tangents
        glColor3f(0,0,1);
        current.glVertex();
        z_tan[i][j].glVertex();
      }
    }
    glEnd();
  }
  glPopMatrix();
}


// Cube
//Cube::Cube(v3d position, v3d size): position(position), size(size){};
bool Cube::collidesWith(const Sphere &other) const{
  return other.collidesWith(*this);
}

bool Cube::collidesWith(const Cube &other) const{
  bool insideX = this->position.x + (this->size.x / 2) > other.position.x - (other.size.x / 2) && this->position.x - ( this->size.x / 2 ) < other.position.x + (other.size.x / 2);
  bool insideY = this->position.y + (this->size.y / 2) > other.position.y - (other.size.y / 2) && this->position.y - ( this->size.y / 2 ) < other.position.y + (other.size.y / 2);
  bool insideZ = this->position.z + (this->size.z / 2) > other.position.z - (other.size.z / 2) && this->position.z - ( this->size.z / 2 ) < other.position.z + (other.size.z / 2);
  return insideX && insideY && insideZ;
}

bool Cube::collidesWith(const Grid &other) const{
  bool insideX = this->position.x + (this->size.x / 2) > other.position.x - (other.size.x / 2) && this->position.x - ( this->size.x / 2 ) < other.position.x + (other.size.x / 2);
  bool insideY = this->position.y + (this->size.y / 2) > other.position.y && this->position.y - ( this->size.y / 2 ) < other.position.y ;
  bool insideZ = this->position.z + (this->size.z / 2) > other.position.z - (other.size.z / 2) && this->position.z - ( this->size.z / 2 ) < other.position.z + (other.size.z / 2);
  return insideX && insideY && insideZ;
}

// Bad implementation, pretends the cylinder is a cube
bool Cube::collidesWith(const Cylinder &other) const{
  bool insideX = position.x + (size.x / 2) > other.position.x - other.radius && position.x - ( size.x / 2 ) < other.position.x + other.radius;
  bool insideY = position.y + (size.y / 2) > other.position.y - other.radius && position.y - ( size.y / 2 ) < other.position.y + other.radius;
  bool insideZ = position.z + (size.z / 2) > other.position.z - other.radius && position.z - ( size.z / 2 ) < other.position.z + other.radius;
  return insideX && insideY && insideZ;
}

std::unique_ptr<Shape> Cube::clone() const {
  return std::make_unique<Cube>(*this);
}

bool Cube::collidesWith(const Function &other) const{
  return false;
}

void Cube::really_draw(const DrawOptions &options) const {
  // push position
  glPushMatrix();
  glTranslated(position.x, position.y, position.z);
  glScaled(size.x, size.y, size.z);

  //                                 |
  //       2---------6               |
  //      /|        /|               |
  //     / |       / |    Y          |
  //    /  |      /  |    |          |
  //   3---------7   |    |          |
  //   |   |     |   |    |          |
  //   |   0-----|---4    *---X      |
  //   |  /      |  /    /           |
  //   | /       | /    /            |
  //   |/        |/    Z             |
  //   1---------5                   |
  //                                 |
  //                                 |
  //     0---4---6---2               |
  //     |   |   |   |               |
  //     |   |   |   |               |
  //     1---5---7---3---2---6       |
  //             |   |   |   |       |
  //             |   |   |   |       |
  //             5---1---0---4       |
  //                                 |

  v3d points[8] = {
    v3d(0,0,0),
    v3d(0,0,1),
    v3d(0,1,0),
    v3d(0,1,1),
    v3d(1,0,0),
    v3d(1,0,1),
    v3d(1,1,0),
    v3d(1,1,1),
  };
  for(int i = 0; i < 8; i++) {
    points[i] -= v3d::unit / 2;
  }



#define CUBE_USE_STRIPS 0
  // can't use strips for cube lighting, since the 
#if CUBE_USE_STRIPS
  glBegin(GL_QUAD_STRIP);
  points[1].draw();
  points[0].draw();
  points[5].draw();
  points[4].draw();
  points[7].draw();
  points[6].draw();
  points[3].draw();
  points[2].draw();
  glEnd();
  glBegin(GL_QUAD_STRIP);
  points[5].draw();
  points[7].draw();
  points[1].draw();
  points[3].draw();
  points[0].draw();
  points[2].draw();
  points[4].draw();
  points[6].draw();
  glEnd();
#else
  glBegin(GL_QUADS);
  {
    //+x
    v3d::X.glNormal();
    glTexCoord2f(0, 0);
    points[5].glVertex();
    v3d::X.glNormal();
    glTexCoord2f(1, 0);
    points[4].glVertex();
    v3d::X.glNormal();
    glTexCoord2f(1, 1);
    points[6].glVertex();
    v3d::X.glNormal();
    glTexCoord2f(0, 1);
    points[7].glVertex();

    //-x
    (-1*v3d::X).glNormal();
    glTexCoord2f(0, 0);
    points[0].glVertex();
    (-1*v3d::X).glNormal();
    glTexCoord2f(1, 0);
    points[1].glVertex();
    (-1*v3d::X).glNormal();
    glTexCoord2f(1, 1);
    points[3].glVertex();
    (-1*v3d::X).glNormal();
    glTexCoord2f(0, 1);
    points[2].glVertex();
  }
  {
    //+y
    v3d::Y.glNormal();
    glTexCoord2f(0, 0);
    points[2].glVertex();
    v3d::Y.glNormal();
    glTexCoord2f(1, 0);
    points[3].glVertex();
    v3d::Y.glNormal();
    glTexCoord2f(1, 1);
    points[7].glVertex();
    v3d::Y.glNormal();
    glTexCoord2f(0, 1);
    points[6].glVertex();
    //-y
    (-1*v3d::Y).glNormal();
    glTexCoord2f(0, 0);
    points[1].glVertex();
    (-1*v3d::Y).glNormal();
    glTexCoord2f(1, 0);
    points[0].glVertex();
    (-1*v3d::Y).glNormal();
    glTexCoord2f(1, 1);
    points[4].glVertex();
    (-1*v3d::Y).glNormal();
    glTexCoord2f(0, 1);
    points[5].glVertex();
  }
  {
    //+z
    v3d::Z.glNormal();
    glTexCoord2f(0, 0);
    points[3].glVertex();
    v3d::Z.glNormal();
    glTexCoord2f(1, 0);
    points[1].glVertex();
    v3d::Z.glNormal();
    glTexCoord2f(1, 1);
    points[5].glVertex();
    v3d::Z.glNormal();
    glTexCoord2f(0, 1);
    points[7].glVertex();
    //-z
    (-1*v3d::Z).glNormal();
    glTexCoord2f(0, 0);
    points[0].glVertex();
    (-1*v3d::Z).glNormal();
    glTexCoord2f(1, 0);
    points[2].glVertex();
    (-1*v3d::Z).glNormal();
    glTexCoord2f(1, 1);
    points[6].glVertex();
    (-1*v3d::Z).glNormal();
    glTexCoord2f(0, 1);
    points[4].glVertex();
  }
  glEnd();
#endif

  // normals
  if(options.normals) {
    glPushAttrib(GL_LIGHTING);
    glDisable(GL_LIGHTING);
    glColor3f(0,1,0);

    {
      //+x
      v3d::X.draw(points[5]);
      v3d::X.draw(points[4]);
      v3d::X.draw(points[6]);
      v3d::X.draw(points[7]);

      //-x
      (-1*v3d::X).draw(points[0]);
      (-1*v3d::X).draw(points[1]);
      (-1*v3d::X).draw(points[3]);
      (-1*v3d::X).draw(points[2]);
    }
    {
      //+y
      v3d::Y.draw(points[2]);
      v3d::Y.draw(points[3]);
      v3d::Y.draw(points[7]);
      v3d::Y.draw(points[6]);
      //-y
      (-1*v3d::Y).draw(points[1]);
      (-1*v3d::Y).draw(points[0]);
      (-1*v3d::Y).draw(points[4]);
      (-1*v3d::Y).draw(points[5]);
    }
    {
      //+z
      v3d::Z.draw(points[3]);
      v3d::Z.draw(points[1]);
      v3d::Z.draw(points[5]);
      v3d::Z.draw(points[7]);
      //-z
      (-1*v3d::Z).draw(points[0]);
      (-1*v3d::Z).draw(points[2]);
      (-1*v3d::Z).draw(points[6]);
      (-1*v3d::Z).draw(points[4]);
    }
    glPopAttrib();
  }



  glPopMatrix();
}

// Grid
bool Grid::collidesWith(const Sphere &other) const{
  return other.collidesWith(*this);
}

bool Grid::collidesWith(const Cube &other) const{
  return other.collidesWith(*this);
}

bool Grid::collidesWith(const Grid &other) const{
  return false;
}

bool Grid::collidesWith(const Cylinder &other) const{
  return false;
}

bool Grid::collidesWith(const Function &other) const{
  return false;
}

std::unique_ptr<Shape> Grid::clone() const {
  return std::make_unique<Grid>(*this);
}

void Grid::really_draw(const DrawOptions &options) const {
  glPushMatrix();
  glTranslated(position.x, position.y, position.z);
  glScaled(size.x, size.y, size.z);

  double cellSize = 1.0 / tesselation;
  
  for(int i = 0; i < tesselation; i++){
    for(int j = 0; j < tesselation + 1; j++){
      glBegin(GL_QUADS);
      v3d pos4 = v3d(-0.5 + i * cellSize, 0, -0.5 + j * cellSize);
      v3d pos3 = v3d(-0.5 + (i + 1) * cellSize, 0, -0.5 + j * cellSize);
      v3d pos2 = v3d(-0.5 + (i + 1) * cellSize, 0, -0.5 + (j + 1) * cellSize);
      v3d pos1 = v3d(-0.5 + i * cellSize, 0, -0.5 + (j + 1) * cellSize);

      v3d::Y.glNormal();
      glTexCoord2f(pos1.x + 0.5, pos1.z + 0.5);
      pos1.glVertex();

      v3d::Y.glNormal();
      glTexCoord2f(pos2.x + 0.5, pos2.z + 0.5);
      pos2.glVertex();

      v3d::Y.glNormal();
      glTexCoord2f(pos3.x + 0.5, pos3.z + 0.5);
      pos3.glVertex();

      v3d::Y.glNormal();
      glTexCoord2f(pos4.x + 0.5, pos4.z + 0.5);
      pos4.glVertex();

      glEnd();
    }

  }
  for(int i = 0; i < tesselation + 1; i++){
    for(int j = 0; j < tesselation + 1; j++){
      v3d pos1 = v3d(-0.5 + i * cellSize, 0, -0.5 + j * cellSize);
      if(options.normals) {
        v3d::Y.draw(pos1);
      }
    }
  }

  glPopMatrix();
}

// Cylinder
//Cylinder::Cylinder(Material material, v3d position, double radius, double length): Shape(material), position(position), radius(radius), length(length) {};
//Cylinder::Cylinder(v3d position, double radius, double length): Cylinder(Material(), position, radius, length) {};

bool Cylinder::collidesWith(const Sphere &other) const{
  return other.collidesWith(*this);
}

bool Cylinder::collidesWith(const Cube &other) const{
  return other.collidesWith(*this);
}

bool Cylinder::collidesWith(const Grid &other) const{
  return other.collidesWith(*this);
}

bool Cylinder::collidesWith(const Cylinder &other) const{
  double diffz = position.z - other.position.z;
  double diffy = position.y - other.position.y;
  bool insideLength = sqrt(diffy * diffy + diffz * diffz) < radius + other.radius;
  bool insideX = position.x + length / 2 > other.position.x - (other.length / 2) && position.x - length / 2 < other.position.x + (other.length / 2);
  return insideX && insideLength;
}


std::unique_ptr<Shape> Cylinder::clone() const {
  return std::make_unique<Cylinder>(*this);
}

bool Cylinder::collidesWith(const Function &other) const{
  return false;
}

void Cylinder::really_draw(const DrawOptions &options) const {
  // push position
  glPushMatrix();
  glTranslated(position.x, position.y, position.z);
  glRotatef(90, 0, 1, 0);
  glScaled(radius, radius, length);

  // TODO set n from global tessalation value
  const int n = options.tesselations;
  const int slices=n, stacks=n;

  // for some reason, there is an artifact on the inside of the cylinder
  // in the non-stack mode.
  // not quite sure why. since turning on CYLINDER_COLOR makes the
  // artifact go away


  // start of cylinder...
  // simplified case, since the pole stays the same
  {
    glBegin(GL_POLYGON);

    for(int i = 0; i < slices; i++) {
      double theta = i / (double)slices * 2.0 * M_PI;
      double cos_theta = cosf(theta);
      double sin_theta = sinf(theta);

      glNormal3f(0,0,1);
      v3d(cos_theta, sin_theta, 0.5).glVertex();
    }
    glEnd();
  }



#define CYLINDER_USE_STACKS 0
#if CYLINDER_USE_STACKS
  // middle of cylinder
  for(int i = 0; i <= slices; i++) {
    double theta = i / (double)slices * 2.0 * M_PI;
    double cos_theta = cosf(theta);
    double sin_theta = sinf(theta);

    glBegin(GL_QUAD_STRIP);
    for(int j = 0; j < stacks; j++) {
      double zpos = (double)j / stacks - 0.5;
      double step = 1.0 / stacks;

      glNormal3f(cos_theta, sin_theta, 0);
      glVertex3f(cos_theta, sin_theta, zpos+step);

      glNormal3f(cos_theta, sin_theta, 0);
      glVertex3f(cos_theta, sin_theta, zpos);
    }
    glEnd();
  }
#else
  glBegin(GL_QUAD_STRIP);
  for(int i = 0; i <= slices; i++) {
    double theta = i / (double)slices * 2.0 * M_PI;
    double cos_theta = cosf(theta);
    double sin_theta = sinf(theta);

    glNormal3f(cos_theta, sin_theta, 0);
    glTexCoord2f(theta / (2.0 * M_PI), 0);
    v3d(cos_theta, sin_theta, 0.5).glVertex();
    glTexCoord2f(theta / (2.0 * M_PI), 1);
    glNormal3f(cos_theta, sin_theta, 0);
    v3d(cos_theta, sin_theta, -0.5).glVertex();
  }
  glEnd();
#endif



  // end of cylinder...
  // simplified case, since the pole stays the same
  if(1) {
    glBegin(GL_POLYGON);

    // reverse order, so that the end is facing outwards
    for (int i = slices; i > 0; i--) {
      double theta = i / (double)slices * 2.0 * M_PI;
      double cos_theta = cosf(theta);
      double sin_theta = sinf(theta);

      glNormal3f(0,0,-1);
      v3d(cos_theta, sin_theta, -0.5).glVertex();
    }
    glEnd();
  }


  // normals
  if(options.normals) {
    glPushAttrib(GL_LIGHTING);
    glPushAttrib(GL_TEXTURE_1D);
    glPushAttrib(GL_TEXTURE_2D);
    glPushAttrib(GL_TEXTURE_3D);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_1D);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_3D);
    glColor3f(0,1,0);


    // start of cylinder...
    // simplified case, since the pole stays the same
    {

      for(int i = 0; i < slices; i++) {
        double theta = i / (double)slices * 2.0 * M_PI;
        double cos_theta = cosf(theta);
        double sin_theta = sinf(theta);

        v3d(0,0,1).draw(v3d(cos_theta, sin_theta, 0.5));
      }
    }

#if CYLINDER_USE_STACKS
    // middle of cylinder
    for(int i = 0; i < slices; i++) {
      double theta = i / (double)slices * 2.0 * M_PI;
      double cos_theta = cosf(theta);
      double sin_theta = sinf(theta);

      v3d normal(cos_theta, sin_theta, 0);
      glBegin(GL_QUAD_STRIP);

      for(int j = 0; j < stacks; j++) {
        double zpos = (double)j / stacks - 0.5;

        v3d(cos_theta, sin_theta, 0).draw(cos_theta, sin_theta, zpos);
      }
    }
#else
    for(int i = 0; i <= slices; i++) {
      double theta = i / (double)slices * 2.0 * M_PI;
      double cos_theta = cosf(theta);
      double sin_theta = sinf(theta);

      v3d(cos_theta, sin_theta, 0).draw(cos_theta, sin_theta, 0.5);
      v3d(cos_theta, sin_theta, 0).draw(cos_theta, sin_theta, -0.5);
    }
#endif
    // end of cylinder...
    // simplified case, since the pole stays the same
    {
      for (int i = 0; i < slices; i++) {
        double theta = i / (double)slices * 2.0 * M_PI;
        double cos_theta = cosf(theta);
        double sin_theta = sinf(theta);

        v3d(0,0,-1).draw(cos_theta, sin_theta, -0.5);
      }
    }

    glPopAttrib();
    glPopAttrib();
    glPopAttrib();
    glPopAttrib();
  }
  // end of normal


  glPopMatrix();
}
