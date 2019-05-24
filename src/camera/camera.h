#include "vector/vector.h"
#include "gameobject/gameobject.hpp"


class Camera : public GameObject{
  public:

    Camera(void);

    v3d get_forward() const;
    v3d get_forward_xz() const;
};
