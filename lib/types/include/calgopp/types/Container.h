#pragma once

namespace calgopp::types {

/**
 * Calgopp generic container, for continuous memory storage on the heap.
 * @tparam Type                     Type of elements to be stored
 */
template <typename Type>
class Container
{
public:
    /**
     * Default constructor. Initializes empty container. Pre allocates memory for 10 elements.
     */
    Container()
        : m_capacity(10)
        , m_data(new Type[m_capacity])
        , m_begin(Iterator(m_data))
        , m_end(m_begin + 1)
    {}

    /**
     * Initializes empty container with memory allocated for elements number equal to size argument.
     * @param size                  Size of allocated memory
     */
    explicit Container(int size)
        : m_size(size)
        , m_capacity(m_size > 0 ? m_size * 2 : 10)
        , m_empty(m_size == 0)
        , m_data(new Type[m_capacity])
        , m_begin(m_data)
        , m_end(&m_data[m_size])
    {}

    /**
     * Initializes Container from C-style array.
     * @param values                Elements to be stored
     * @param length                Array size
     */
    Container(const Type* values, unsigned int length)
        : m_size(length)
        , m_capacity(m_size > 0 ? m_size * 2 : 10)
    {
        if (!values)
        {
            throw "Invalid array";
        }
        m_data = new Type[m_capacity]; // NOLINT cppcoreguidelines-owning-memory
        for (unsigned int i = 0; i < m_size; i++)
        {
            m_data[i] = values[i];
        }
        m_empty = m_size == 0;
        updateIterators();
    }

    /**
     * Constructs container from STL containers
     * @tparam ContainerType        STL alike container type
     * @param values                Elements to be stored
     */
    template <typename ContainerType>
    explicit Container(const ContainerType& values)
        : Container(values.data(), values.size())
    {}

    /**
     * Copy constructor.
     * @param other                 Other container
     */
    Container(const Container& other)
        : m_size(other.m_size)
        , m_capacity(other.m_capacity)
        , m_empty(other.m_empty)
    {
        if (&other == this)
        {
            return;
        }
        delete[] m_data;
        m_data = new Type[m_capacity]; // NOLINT cppcoreguidelines-owning-memory
        for (unsigned int i = 0; i < m_size; i++)
        {
            m_data[i] = other.m_data[i];
        }
        updateIterators();
    }

    /**
     * Moving constructor
     * @param other                 Other container
     */
    Container(Container&& other) noexcept
        : m_size(other.m_size)
        , m_capacity(other.m_capacity)
        , m_empty(other.m_empty)
    {
        if (&other == this)
        {
            return;
        }
        delete[] m_data;
        m_data = other.m_data;
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
        other.m_empty = true;
        updateIterators();
    }

    /**
     * Destructor. Deallocates memory
     */
    ~Container() { delete[] m_data; }

    /**
     * Copy assignment operator.
     * @param other                 Other container
     * @return New container
     */
    Container& operator=(const Container& other)
    {
        if (&other == this)
        {
            return *this;
        }
        delete[] m_data;
        m_size = other.m_size;
        m_empty = other.m_empty;
        m_capacity = other.m_capacity;
        m_data = new Type[m_capacity]; // NOLINT cppcoreguidelines-owning-memory
        for (unsigned int i = 0; i < m_size; i++)
        {
            m_data[i] = other.m_data[i];
        }
        updateIterators();
        return *this;
    }

    /**
     * Move assignment operator.
     * @param other                 Other container.
     * @return New container
     */
    Container& operator=(Container&& other) noexcept
    {
        if (&other == this)
        {
            return *this;
        }
        delete[] m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_empty = other.m_empty;
        m_data = other.m_data;
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
        other.m_empty = true;
        updateIterators();
        return *this;
    }

    /**
     * Appends new element to end of container. If allocated memory is not enough, expands it twice.
     * @param data                  Element to be added.
     */
    void append(const Type& data)
    {
        if (m_size >= m_capacity)
        {
            extend();
        }
        m_data[m_size] = data;
        m_size++;
        m_empty = m_size == 0;
        updateIterators();
    }

    /**
     * Inserts element on at defined index.
     * @param data                  Element to be inserted
     * @param index                 Index where to store element
     */
    void insert(const Type& data, unsigned int index)
    {
        if (m_size >= m_capacity)
        {
            extend();
        }
        for (unsigned int i = m_size; i > index; i--)
        {
            m_data[i] = m_data[i - 1];
        }
        m_data[index] = data;
        m_size++;
        m_empty = m_size == 0;
        updateIterators();
    }

    /**
     * Removes element placed at index
     * @param index                 Index of element to be removed
     */
    void remove(unsigned int index)
    {
        if (index >= m_size)
        {
            throw "Index out of scope"; // NOLINT
        }
        for (unsigned int i = index; i < m_size - 1; i++)
        {
            m_data[i] = m_data[i + 1];
        }
        m_size--;
        m_empty = m_size == 0;
        updateIterators();
    }

    /**
     * Index operator. Accesses element at index.
     * @param index                 Index of element to access.
     * @return Reference to element at index.
     */
    Type& operator[](unsigned int index)
    {
        if (index >= m_size)
        {
            throw "Index out of scope"; // NOLINT
        }
        return m_data[index];
    }

    /**
     * Returns copy of element stored at index.
     * @param index                 Index of element to copy.
     * @return Copy of element at index.
     */
    Type at(unsigned int index) const
    {
        if (index >= m_size)
        {
            throw "Index out of scope"; // NOLINT
        }
        return m_data[index];
    }

    /**
     * Gets index of element. Throws const char* in case of no such element.
     * @param element               Element to be found
     * @return Index of element.
     */
    unsigned int index(const Type& element) const
    {
        for (unsigned int i = 0; i < m_size; i++)
        {
            if (m_data[i] == element)
            {
                return i;
            }
        }
        throw "No element";
    }

    /**
     * Returns size of container.
     * @return Size of container.
     */
    unsigned int size() const { return m_size; }

    /**
     * Returns for how many objects memory has been allocated.
     * @return Capacity of container.
     */
    unsigned int capacity() const { return m_capacity; }

    /**
     * Checks if container is empty.
     * @return True if container is empty, false otherwise.
     */
    bool empty() const { return m_empty; }

    /**
     * Iterator class of container.
     */
    class Iterator
    {
    public:
        /**
         * Default constructor. Points to no element.
         */
        Iterator() = default;

        /**
         * Initializes iterator with data.
         * @param data                  Pointer to data.
         */
        Iterator(Type* data)
            : m_data(data)
        {}

        /**
         * Pre increment.
         * @return Iterator on next element.
         */
        Iterator& operator++()
        {
            m_data++;
            return *this;
        }

        /**
         * Post increment.
         * @return This.
         */
        Iterator operator++(int)
        {
            Iterator tmp = *this;
            m_data++;
            return tmp;
        }

        /**
         * Pre decrement.
         * @return Iterator to previous element.
         */
        Iterator& operator--()
        {
            m_data--;
            return *this;
        }

        /**
         * Post decrement
         * @return This
         */
        Iterator operator--(int)
        {
            Iterator tmp = *this;
            m_data--;
            return tmp;
        }

        /**
         * Pointer access operator. Allows to access element like pointer.
         * @return Reference to held object
         */
        Type& operator->() { return *m_data; }

        /**
         * Addition operator.
         * @param value                 Value to increment iterator.
         * @return New iterator incremented by value.
         */
        Iterator operator+(int value) const { return m_data + value; }

        /**
         * Subtraction operator.
         * @param value                 Value to decrement iterator.
         * @return New iterator decremented by value.
         */
        Iterator operator-(int value) const { return m_data - value; }

        /**
         * Equlity operator.
         * @param rhs                   Right hand iterator.
         * @return True if iterators point to the same data, false otherwise.
         */
        bool operator==(const Iterator& rhs) const { return m_data == rhs.m_data; }

        /**
         * Inequality operator.
         * @param rhs                   Right hand iterator.
         * @return True if iterators point to different data, false otherwise.
         */
        bool operator!=(const Iterator& rhs) const { return !(*this == rhs); }

        /**
         * Greater operator.
         * @param rhs                   Right hand iterator.
         * @return True if this iterator points to data consecutive to rhs, false otherwise.
         */
        bool operator>(const Iterator& rhs) const { return m_data > rhs.m_data; }

        /**
         * Less operator.
         * @param rhs                   Right hand iterator.
         * @return True if this iterator points to preceding data to rhs, false otherwise.
         */
        bool operator<(const Iterator& rhs) const { return m_data < rhs.m_data; }

        /**
         * Greater or equal operator.
         * @param rhs                   Right hand iterator.
         * @return True if this iterator points to the same or consecutive data to rhs, false otherwise.
         */
        bool operator>=(const Iterator& rhs) const { return !(*this < rhs); }

        /**
         * Less or equal operator.
         * @param rhs                   Right hand iterator.
         * @return True if this iterator points to the same or preceding data to rhs, false otherwise.
         */
        bool operator<=(const Iterator& rhs) const { return !(*this > rhs); }

        friend unsigned int operator-(const Iterator& lhs, const Iterator& rhs)
        {
            return (lhs.m_data - rhs.m_data) / sizeof(Type);
        }

        friend unsigned int operator+(const Iterator& lhs, const Iterator& rhs)
        {
            return (lhs.m_data + rhs.m_data) / sizeof(Type);
        }

        /**
         * Dereference operator.
         * @return Reference to data.
         */
        Type& operator*() const { return *m_data; }

    private:
        Type* m_data{nullptr};
    };

    /**
     * Returns iterator to first point of the signal.
     * @return Iterator to first point.
     */
    Iterator begin() const { return m_begin; }

    /**
     * Returns iterator to data past last point in the signal.
     * @return Iterator to last point + 1
     */
    Iterator end() const { return m_end; }

    /**
     * Searches for element in signal and returns it's iterator. If no element found, return end iterator.
     * @param element                   Element to find.
     * @return Iterator to element if present in signal, end() iterator otherwise.
     */
    Iterator find(const Type& element)
    {
        for (unsigned int i = 0; i < m_size; i++)
        {
            if (m_data[i] == element)
            {
                return &m_data[i];
            }
        }
        return end();
    }

    const Type* data() const { return m_data; }

protected:
    /**
     * Updates iterators.
     */
    void updateIterators()
    {
        m_begin = m_data;
        m_end = &m_data[m_size];
    }

    /**
     * Extends memory by twice the current size and moves data there. Deallocates old block.
     */
    void extend()
    {
        m_capacity = m_capacity * 2;
        auto* tmp = new Type[m_capacity]; // NOLINT cppcoreguidelines-owning-memory
        for (unsigned int i = 0; i < m_size; i++)
        {
            tmp[i] = m_data[i];
        }
        delete[] m_data;
        m_data = tmp;
    }

protected:
    unsigned int m_size{};
    unsigned int m_capacity{};
    bool m_empty{true};
    Type* m_data{nullptr};
    Iterator m_begin;
    Iterator m_end;
};

} // namespace calgopp::types
