#ifndef XORLINKEDLIST_HPP_
#define XORLINKEDLIST_H_

#include <stddef.h>	// Needed for NULL define

template <class T>
class xorlinkedlist
{

public:
	xorlinkedlist()
	{
		// Initialize our head and tail pointers to NULL
		_head = _previousIterator = _iterator = _tail = NULL;

		// Initialize our size to be 0
		_size = 0;
	}

	~xorlinkedlist()
	{
		// Call 'clear' to delete all of our items
		clear();
	}

	// List modifier functions, below runctions return true if successful

	// Insert our item to the end of the list
	void insert(const T& data, bool insertAtEnd = true)
	{
		// If we currently have an empty head and tail, we need to insert our initial values
		if (!_head && !_tail)
			_head = _tail = __insert(NULL, NULL, data);
		else
		if (_head == _tail)
			_tail = __insert(NULL, _tail, data);
		else
		if (insertAtEnd)
			_tail = __insert(_tail->link, _tail, data);
		else
			_head = __insert(_head->link, _head, data);

		_size++;
	}

	// Move our current node to the next node in the list
	bool iterateFromHead()
	{
		if (!_head)
			return false;

		_previousIterator = _iterator = _head;

		return true;
	}

	// Move our current node to the previous node in the list
	bool iterateFromTail()
	{
		if (!_tail)
			return false;
		
		_previousIterator = _iterator = _tail;

		return true;
	}

	void move()
	{
		if (_iterator->link == _iterator)
			return;
		else
		if (_iterator == _previousIterator)
			_iterator = _iterator->link;
		else
		{
			xornode* temp = _iterator;
			_iterator = __xor(_previousIterator, _iterator->link);
			_previousIterator = temp;
		}
	}

	// Clear all of our items
	void clear()
	{
		xornode* previous = NULL, *current = _head;
		while (current)
		{
			current->link = __xor(current->link, previous);

			if (previous)
				delete previous;

			if (!current->link)
			{
				delete current;
				current = NULL;
			}
			else
			{
				previous = current;
				current = current->link;
			}

			_size--;
		}

		_head = _previousIterator = _iterator = _tail = NULL;
	}

	// Data functions
	unsigned int getSize() const
	{
		return _size;
	}

	bool getData(T* data) const
	{
		if (data && _iterator)
		{
			*data = _iterator->data;
			return true;
		}

		return false;
	}

private:
	struct xornode
	{
		T data;
		xornode* link;
	};

	xornode* _head, *_previousIterator, *_iterator, *_tail;
	unsigned int _size;

	xornode* __xor(xornode* lhs, xornode* rhs)
	{
		return (xornode*)((unsigned int)lhs ^ (unsigned int)rhs);
	}

	xornode* __insert(xornode* previous, xornode* current, const T& data)
	{
		// Add a node to the list
		xornode* next = NULL;

		next = new xornode();
		next->data = data;
		next->link = current;

		if (!current)
			return next;
		else
		if (!previous)
			current->link = next;
		else
			current->link = __xor(previous, next);

		return next;
	}

};

#endif // !XORLINKEDLIST_H_
