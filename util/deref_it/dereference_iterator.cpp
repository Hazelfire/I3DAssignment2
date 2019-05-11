#include "dereference_iterator.h"


DereferenceIterator(const BaseIterator &other) : BaseIterator(other) {}

template <typename Iterator> DereferenceIterator<Iterator> DereferenceIterator<Iterator>::dereference_iterator(Iterator t) {
	return DereferenceIterator<Iterator>(t);
}

reference DereferenceIterator<Iterator>::operator*() const {
	return *(this->BaseIterator::operator*());
}

pointer DereferenceIterator<Iterator>::operator->() const {
	return this->BaseIterator::operator*().get();
}

reference DereferenceIterator<Iterator>::operator[](size_t n) const {
	return *(this->BaseIterator::operator[](n));
}
