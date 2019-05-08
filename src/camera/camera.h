#include "../generated_directories.h"
#include VECTOR_H


class camera {
	private:
		v3d right;
	public:
		v3d rotation;
		v3d position;

		camera(void);

		void move_to() const;

		v3d get_forward() const;
};
