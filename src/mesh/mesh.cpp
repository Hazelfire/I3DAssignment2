#include "mesh.h"

mesh::mesh(void): vertices() {}

//using DI = DereferenceIterator<std::vector<std::unique_ptr<struct vertex>>::iterator>;

mesh::DI mesh::begin() {
	return dereference_iterator(vertices.begin());
}
mesh::DI mesh::end() {
	return dereference_iterator(vertices.end());
}
