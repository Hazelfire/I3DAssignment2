#include <cstddef>
// source:
// https://jonasdevlieghere.com/containers-of-unique-pointers/

using namespace std;

template <class BaseIterator> class DereferenceIterator : public BaseIterator {
	public:
		using value_type = typename BaseIterator::value_type::element_type;
		using pointer = value_type *;
		using reference = value_type &;

		DereferenceIterator(const BaseIterator &other);

		reference operator*() const;
		pointer operator->() const;
		reference operator[](size_t n) const;

};
template <typename Iterator> DereferenceIterator<Iterator> dereference_iterator(Iterator t);

