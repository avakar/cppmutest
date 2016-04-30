#ifndef MUTEST_DETAIL_LIST_H
#define MUTEST_DETAIL_LIST_H

namespace utest {

template <typename T>
struct list_node
{
	list_node * next;
	list_node * prev;
};

template <typename T>
struct list_iterator
{
	list_iterator()
		: m_node(nullptr)
	{
	}

	explicit list_iterator(list_node<T> * node)
		: m_node(node)
	{
	}

	list_iterator & operator++()
	{
		m_node = m_node->next;
		return *this;
	}

	list_iterator operator++(int)
	{
		list_iterator prev(*this);
		++(*this);
		return prev;
	}

	T * operator->() const
	{
		return static_cast<T *>(m_node);
	}

	T & operator*() const
	{
		return *static_cast<T *>(m_node);
	}

	friend bool operator==(list_iterator const & lhs, list_iterator const & rhs)
	{
		return lhs.m_node == rhs.m_node;
	}

	friend bool operator!=(list_iterator const & lhs, list_iterator const & rhs)
	{
		return !(lhs == rhs);
	}

	list_node<T> * m_node;
};

template <typename T>
list_iterator<T> begin(list_node<T> * list)
{
	return list_iterator<T>(list->next);
}

template <typename T>
list_iterator<T> end(list_node<T> * list)
{
	return list_iterator<T>(list);
}

} // namespace utest

#endif // MUTEST_DETAIL_LIST_H
