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

		private:
		  // want to mark vertices for deletion before they are deleted.
			//   this is because any tri could use this vertex, so to avoid
			//   O(n^2) behavior, we mark the vertices to be deleted, then
			//   we check each tri, then we delete the vertex
			// this can not be part of the key (compare func), otherwise 
			//   we would not be able to change the value while the set is
			//   holding it, since the key affects the position of the item,
			//   and the set does not change position of the item while it
			//   is in the set.
			//   (which is a feature of set we are making deliberate use of)
			mutable bool to_delete;
			friend class mesh;
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
	// http://eel.is/c++draft/associative.reqmts#9
	// "The insert and emplace members shall not affect the validity of 
	//   iterators and references to the container, and the erase members 
	//   shall invalidate only iterators and references to the erased 
	//   elements."
	// this means, the tris can hold a const reference to the vertices, 
	//   without the references being invalidated
	std::set<struct vertex> vertices;
	std::set<struct triangle> tris;

	public:
		mesh(void);

		void test(void);

		using vert_cit = std::set<struct vertex>::const_iterator;
		using vert_size_type = std::set<struct vertex>::size_type;

		// NYI
		std::pair<vert_cit,bool> insert_vertex( const struct vertex& value );
		void insert_vertex(std::initializer_list<struct vertex> ilist);

		vert_cit cbegin_vertex() const noexcept;
		vert_cit cend_vertex() const noexcept;

		// these are dangerous
		//   when you erase a vertex, any triangles with references
		//   to that vertex will be invalidated. you need to mark the
		//   vertex to be erased, then call:
		//     erase_tris_with_deleted_vertices()
		//   then erase the vertex
		// the safe way to do this is order O(n^2) as opposed to O(n)
		vert_cit erase_vertex(vert_cit pos);
		vert_size_type erase_vertex(const struct vertex& key);
		void erase_vertex(vert_cit first, vert_cit last);

		void mark_erase_vertex(vert_cit pos);
		void mark_erase_vertex(const struct vertex& key);
		void mark_erase_vertex(vert_cit first, vert_cit last);

		void erase_tris_with_deleted_vertices();
};
