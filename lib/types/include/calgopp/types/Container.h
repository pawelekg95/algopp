#pragma once

namespace calgopp::types {

template <typename Type>
class Container
{
public:
    Container()
        : m_capacity(10)
        , m_data(new Type[m_capacity])
        , m_begin(Iterator(m_data))
        , m_end(m_begin + 1)
    {}

    explicit Container(int size)
        : m_size(size)
        , m_capacity(m_size > 0 ? m_size * 2 : 10)
        , m_empty(m_size == 0)
        , m_data(new Type[m_capacity])
        , m_begin(Iterator(m_data))
        , m_end(Iterator(&m_data[m_size]))
    {}

    template <typename InputType>
    Container(const InputType* values, unsigned int length)
        : m_size(length)
        , m_capacity(m_size > 0 ? m_size * 2 : 10)
    {
        if (!values)
        {
            throw "Invalid array";
        }
        m_data = new InputType[m_capacity]; // NOLINT cppcoreguidelines-owning-memory
        for (unsigned int i = 0; i < m_size; i++)
        {
            m_data[i] = values[i];
        }
        m_empty = m_size == 0;
        updateIterators();
    }

    template <typename ContainerType>
    explicit Container(const ContainerType& values)
        : Container(values.data(), values.size())
    {}

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

    ~Container() { delete[] m_data; }

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
        return *this;
    }

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
        return *this;
    }

    void append(const Type& data)
    {
        if (m_size >= m_capacity)
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
        m_data[m_size] = data;
        m_size++;
        m_empty = m_size == 0;
        updateIterators();
    }

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

    Type& operator[](unsigned int index)
    {
        if (index >= m_size)
        {
            throw "Index out of scope"; // NOLINT
        }
        return m_data[index];
    }

    Type at(unsigned int index) const
    {
        if (index >= m_size)
        {
            throw "Index out of scope"; // NOLINT
        }
        return m_data[index];
    }

    unsigned int size() const { return m_size; }

    unsigned int capacity() const { return m_capacity; }

    bool empty() const { return m_empty; }

    class Iterator
    {
    public:
        Iterator() = default;

        Iterator(Type* data)
            : m_data(data)
        {}

        Iterator& operator++()
        {
            m_data++;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator tmp = *this;
            m_data++;
            return tmp;
        }

        Iterator& operator--()
        {
            m_data--;
            return *this;
        }

        Iterator operator--(int)
        {
            Iterator tmp = *this;
            m_data--;
            return tmp;
        }

        Iterator operator+(int value) { return m_data + value; }

        Iterator operator-(int value) { return m_data - value; }

        bool operator==(const Iterator& rhs) { return m_data == rhs.m_data; }

        bool operator!=(const Iterator& rhs) { return !(*this == rhs); }

        bool operator>(const Iterator& rhs) { return m_data > rhs.m_data; }

        bool operator<(const Iterator& rhs) { return m_data < rhs.m_data; }

        bool operator>=(const Iterator& rhs) { return !(*this < rhs); }

        bool operator<=(const Iterator& rhs) { return !(*this > rhs); }

        Type& operator*() { return *m_data; }

    private:
        Type* m_data{nullptr};
    };

    Iterator begin() const { return m_begin; }

    Iterator end() const { return m_end; }

protected:
    void updateIterators()
    {
        m_begin = m_data;
        m_end = &m_data[m_size];
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
