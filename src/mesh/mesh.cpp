#include "mesh.h"

mesh::mesh(void): vertices() {}

#if USE_VEC_SMRT_PTR
using DI = DereferenceIterator<std::vector<std::unique_ptr<struct vertex>>::iterator>;

mesh::DI mesh::begin() {
	return DI::dereference_iterator(vertices.begin());
}
mesh::DI mesh::end() {
	return DI::dereference_iterator(vertices.end());
}
#endif
