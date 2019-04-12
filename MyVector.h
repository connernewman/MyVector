#ifndef MyVector_h
#define MyVector_h

#include <stdexcept>
#include <initializer_list>

template <typename T>
class MyVector
{
	public:
		using value_type		= T;
		using size_type			= size_t;
		using difference_type	= ptrdiff_t;
		using pointer			= value_type*;
		using const_pointer		= const value_type*;
		using reference			= value_type&;
		using const_reference	= const value_type&;
		using iterator			= pointer;
		using const_iterator	= const_pointer;

	private:
		pointer data;
		size_type max_allocated_size;
		size_type current_ptr;

	public:
		MyVector(): max_allocated_size(0), current_ptr(0), data(nullptr) {}

		MyVector(size_type startSize): max_allocated_size(startSize), current_ptr(startSize), data((pointer)malloc(startSize * sizeof(T)))
		{
			for(size_type i = 0; i < startSize; ++i)
			{
				data[i] = T();
			}
		}

		MyVector(size_type startSize, const_reference startVal): max_allocated_size(startSize), current_ptr(startSize), data((pointer)malloc(startSize * sizeof(value_type)))
		{
			for(size_type i = 0; i < startSize; ++i)
			{
				data[i] = startVal;
			}
		}

		MyVector(std::initializer_list<value_type> init): max_allocated_size(init.size()), current_ptr(init.size()), data((pointer)malloc(init.size() * sizeof(value_type)))
		{
			size_t ptr = 0;
			for(const_reference e : init)
			{
				data[ptr++] = e;
			}
		}

		~MyVector()
		{
			if(data != nullptr)
			{
				for(size_type i = 0; i < current_ptr; ++i)
				{
					~data[i];
				}
				free(data);
			}
		}

		void operator =(const MyVector& rhs)
		{
			if(max_allocated_size >= rhs.current_ptr)
			{
				for(size_type i = 0; i < current_ptr; ++i)
				{
					~data[i];
				}
				for(size_type i = 0; i < rhs.current_ptr; ++i)
				{
					data[i] = rhs.data[i];
				}
			}
			else
			{
				reserve(rhs.current_ptr);
				for(size_type i = 0; i < rhs.current_ptr; ++i)
					data[i] = rhs.data[i];
				max_allocated_size = rhs.current_ptr;
			}
			current_ptr = rhs.current_ptr;
		}

		bool operator ==(const MyVector& rhs) const
		{
			if(size() != rhs.size())
				return false;
			for(size_type i = 0; i < current_ptr; ++i)
			{
				if((*this)[i] != rhs[i])
					return false;
			}
			return true;
		}

		size_type size() const
		{
			return this->current_ptr;
		}

		size_type capacity() const
		{
			return this->max_allocated_size;
		}

		bool empty() const
		{
			return this->current_ptr == 0;
		}

		void reserve(size_type newSize)
		{
			if(newSize > max_allocated_size)
			{
				pointer newData = (pointer)malloc(newSize * sizeof(T));
				for(size_type i = 0; i < max_allocated_size; ++i)
				{
					newData[i] = data[i];
				}
				if(data != nullptr)
				{
					for(size_type i = 0; i < current_ptr; ++i)
						~data[i];
					free(data);
				}
				data = newData;
				max_allocated_size = newSize;
			}
		}

		void shrink_to_fit()
		{
			if(current_ptr < max_allocated_size)
			{
				max_allocated_size = 0;
				reserve(current_ptr);
			}
		}

		reference at(int64_t index)
		{
			if(index >= 0 && (size_type)index >= current_ptr || index < 0 && (int64_t)(index + current_ptr) < 0)
				throw std::out_of_range("Index out of range.");
			if(index < 0)
				return data[current_ptr + index];
			return data[index];
		}

		const_reference at(int64_t index) const
		{
			if(index >= 0 && (size_type)index >= current_ptr || index < 0 && (int64_t)(index + current_ptr) < 0)
				throw std::out_of_range("Index out of range.");
			if(index < 0)
				return data[current_ptr + index];
			return data[index];
		}

		reference operator [](size_type index)
		{
			return data[index];
		}

		const_reference operator [](size_type index) const
		{
			return data[index];
		}

		void push_back(const_reference t)
		{
			if(current_ptr == max_allocated_size)
			{
				// Copy to new, larger buffer
				size_type newSize = 2 * max_allocated_size + 1;
				reserve(newSize);
			}

			data[current_ptr++] = t;
		}

		value_type pop()
		{
			if(current_ptr < 1)
				throw std::out_of_range("Pop on zero-length MyVector.");
			return data[--current_ptr];
		}

		iterator begin()
		{
			return data;
		}

		const_iterator begin() const
		{
			return data;
		}

		iterator end()
		{
			return data + current_ptr;
		}

		const_iterator end() const
		{
			return data + current_ptr;
		}
};

#endif
