#ifndef MyVector_h
#define MyVector_h

#include <stdexcept>
#include <initializer_list>

template <typename T>
class MyVector
{
	private:
		T* data;
		size_t max_allocated_size;
		size_t current_ptr;

	public:
		MyVector(): max_allocated_size(0), current_ptr(0), data(nullptr) {}

		MyVector(size_t startSize): max_allocated_size(startSize), current_ptr(startSize), data((T*)malloc(startSize * sizeof(T)))
		{
			for(size_t i = 0; i < startSize; ++i)
			{
				data[i] = T();
			}
		}

		MyVector(size_t startSize, const T& startVal): max_allocated_size(startSize), current_ptr(startSize), data((T*)malloc(startSize * sizeof(T)))
		{
			for(size_t i = 0; i < startSize; ++i)
			{
				data[i] = startVal;
			}
		}

		MyVector(std::initializer_list<T> init): max_allocated_size(init.size()), current_ptr(init.size()), data((T*)malloc(init.size() * sizeof(T)))
		{
			size_t ptr = 0;
			for(const T& e : init)
			{
				data[ptr++] = e;
			}
		}

		~MyVector()
		{
			if(data != nullptr)
			{
				for(size_t i = 0; i < current_ptr; ++i)
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
				for(size_t i = 0; i < current_ptr; ++i)
				{
					~data[i];
				}
				for(size_t i = 0; i < rhs.current_ptr; ++i)
				{
					data[i] = rhs.data[i];
				}
			}
			else
			{
				for(size_t i = 0; i < current_ptr; ++i)
					~data[i];
				if(data != nullptr)
					free(data);
				data = (T*)malloc(rhs.current_ptr * sizeof(T));
				for(size_t i = 0; i < rhs.current_ptr; ++i)
					data[i] = rhs.data[i];
				max_allocated_size = rhs.current_ptr;
			}
			current_ptr = rhs.current_ptr;
		}

		size_t size() const
		{
			return this->current_ptr;
		}

		size_t max_size() const
		{
			return this->max_allocated_size;
		}

		bool empty() const
		{
			return this->current_ptr == 0;
		}

		void reserve(size_t newSize)
		{

		}

		T& at(int64_t index)
		{
			if(index >= 0 && (size_t)index >= current_ptr || index < 0 && (int64_t)(index + current_ptr) < 0)
				throw std::out_of_range("Index out of range.");
			if(index < 0)
				return data[current_ptr + index];
			return data[index];
		}

		const T& at(int64_t index) const
		{
			if(index >= 0 && (size_t)index >= current_ptr || index < 0 && (int64_t)(index + current_ptr) < 0)
				throw std::out_of_range("Index out of range.");
			if(index < 0)
				return data[current_ptr + index];
			return data[index];
		}

		T& operator [](size_t index)
		{
			return data[index];
		}

		const T& operator [](size_t index) const
		{
			return data[index];
		}

		void push_back(const T& t)
		{
			if(current_ptr == max_allocated_size)
			{
				// Copy to new, larger buffer
				size_t newSize = 2 * max_allocated_size + 1;
				T* newData = (T*)malloc(newSize * sizeof(T));
				for(size_t i = 0; i < max_allocated_size; ++i)
				{
					newData[i] = data[i];
				}
				if(data != nullptr)
				{
					for(size_t i = 0; i < current_ptr; ++i)
					{
						~data[i];
					}
					free(data);
				}
				data = newData;
				max_allocated_size = newSize;
			}

			data[current_ptr++] = t;
		}

		T pop()
		{
			if(current_ptr < 1)
				throw std::out_of_range("Pop on zero-length MyVector.");
			return data[--current_ptr];
		}

		T* begin()
		{
			return data;
		}

		const T* begin() const
		{
			return data;
		}

		T* end()
		{
			return data + current_ptr;
		}

		const T* end() const
		{
			return data + current_ptr;
		}
};

#endif
