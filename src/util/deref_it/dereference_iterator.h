#include <cstddef>
// source:
// https://jonasdevlieghere.com/containers-of-unique-pointers/

using namespace std;

template <class BaseIterator> class DereferenceIterator : public BaseIterator {
	public:
		using value_type = typename BaseIterator::value_type::element_type;
		using pointer = value_type *;
		using reference = value_type &;

		DereferenceIterator(const BaseIterator &other) : BaseIterator(other) {};

		reference operator*() const {
			return *(this->BaseIterator::operator*());
		}
		pointer operator->() const {
			return this->BaseIterator::operator*().get();
		}

		reference operator[](size_t n) const {
			return *(this->BaseIterator::operator[](n));
		}

		static DereferenceIterator<BaseIterator> dereference_iterator(BaseIterator t) {
			return DereferenceIterator<BaseIterator>(t);
		}
};

