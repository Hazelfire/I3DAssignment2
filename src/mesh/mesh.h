#include <vector>
#include <memory>
#include "../generated_directories.h"
#include VECTOR_H
#include DEREFERENCE_IT_H


class mesh {
	struct vertex {
		v3d point;
		v3d normal;
	};
	std::vector<std::unique_ptr<struct vertex>> vertices;

	public:
		mesh(void);

		using DI = DereferenceIterator<std::vector<std::unique_ptr<struct vertex>>::iterator>;
		DI begin();
		DI end();
};
