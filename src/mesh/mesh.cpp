#include "mesh.h"


mesh::mesh(void): vertices() {}

void mesh::test(void) {
	std::set<struct vertex>::iterator asdf = vertices.begin();
}



// get vertex iterator
mesh::vert_cit mesh::cbegin_vertex() const noexcept {
	return vertices.cbegin();
}
mesh::vert_cit mesh::cend_vertex() const noexcept {
	return vertices.cend();
}

// erase vertex
mesh::vert_cit mesh::erase_vertex(vert_cit pos) {
	return vertices.erase(pos);
}

mesh::vert_size_type mesh::erase_vertex(const struct vertex& pos) {
	return vertices.erase(pos);
}

void mesh::erase_vertex(vert_cit first, vert_cit last) {
	vertices.erase(first, last);
}

// mark erase vertex
void mesh::mark_erase_vertex(vert_cit pos) {
	pos->to_delete = true;
}

void mesh::mark_erase_vertex(const struct vertex& pos) {
	pos.to_delete = true;
}

void mesh::mark_erase_vertex(vert_cit first, vert_cit last) {
	for(vert_cit it = first; it != last; it++) {
		it->to_delete = true;
	}
}

void mesh::erase_tris_with_deleted_vertices() {
	for(auto it = tris.begin(); it != tris.end();) {
		if( it->vertices[0]->to_delete ||
				it->vertices[1]->to_delete ||
				it->vertices[2]->to_delete )
			it = tris.erase(it);
		else
			it++;
	}
}
