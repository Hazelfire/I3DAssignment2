#include "../vector/vector.h"


class camera {
	public:
		v3d rotation;
		v3d position;

		camera(void);

		void move_to() const;

		v3d get_forward() const;
		v3d get_forward_xz() const;
};
