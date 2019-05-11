#include <set>
#include "../generated_directories.h"
#include VECTOR_H
#include DEREFERENCE_IT_H


class mesh {
	struct vertex {
		v3d point;
		v3d normal;

		// for sorting...
		// should by ordered by position,
		//	by increasing x, then y, then z
		friend bool operator<(const vertex& left, const vertex& right) {
			if(left.point.x == right.point.x) {
				if(left.point.y == right.point.y) {
					return left.point.z < left.point.z;
				} else {
					return left.point.y < left.point.y;
				}
			} else {
				return left.point.x < left.point.x;
			}
		}
		friend bool operator==(const vertex& left, const vertex& right) {
			return !(left < right) && !(right < left);
		}
	};

	struct triangle {
		// no arrays of references
		const vertex* vertices[3];

		// still not sure on this.. its not useful for finding the triangle if the
		//   vertices are out of order
		friend bool operator<(const triangle& left, const triangle& right) {
			// test the 1st and 2nd
			for(int i = 0; i < 2; i++) {
				if(left.vertices[i] < right.vertices[i]) {
					return true;
				} else if(right.vertices[i] < left.vertices[i]) {
					return false;
				}
			}
			// else just give the result of the last
			return left.vertices[2] < right.vertices[2];
		}
	};
// i don't think mesh should be an array of smart-pointers any more
// arrays are good for caching, pointers nullify that effect
#define USE_VEC_SMRT_PTR 0
#if USE_VEC_SMRT_PTR
	std::vector<std::unique_ptr<struct vertex>> vertices;
#endif
	// http://eel.is/c++draft/associative.reqmts#9
	// "The insert and emplace members shall not affect the validity of iterators 
	//   and references to the container, and the erase members shall invalidate 
	//   only iterators and references to the erased elements."
	// this means, the tris can hold a const reference to the vertices, without
	//   the references being invalidated
	std::set<struct vertex> vertices;
	std::set<struct triangle> tris;

	public:
		mesh(void);

#if USE_VEC_SMRT_PTR
		using DI = DereferenceIterator<std::vector<std::unique_ptr<struct vertex>>::iterator>;
		DI begin();
		DI end();
#endif
};
