#include <string>

template<typename T>
struct Hash;

template<>
struct Hash<std::string>
{
  std::size_t operator() (const std::string &value) const
  {
    std::size_t ret = 0;

    std::size_t i = 0;
    for (; i < value.size(); i += sizeof (std::size_t))
    {
      std::size_t chunk = 0;
      for (std::size_t c = 0; c < sizeof (std::size_t); ++c)
      {
        chunk <<= 8;
        chunk |= value[i + c];
      }
      ret ^= chunk;
    }

    // Handle remaining bytes
    std::size_t last_chunk = 0;
    for (; i < value.size(); ++i)
    {
      last_chunk <<= 8;
      last_chunk |= value[i];
    }
    ret ^= last_chunk;
    return ret;
  }
};

std::size_t next_prime(const std::size_t i)
{
  // NYI
  return i;
}


template<typename K, typename V>
class HashMap
{
public:
  HashMap(const std::size_t size = 7)
    : entries_size_(size)
    , entries_(initialize_entries_(entries_size))
  {
  }

  ~HashMap()
  {
    delete[] entries_;
  }

  void insert(const K &key, const V &value)
  {
    const std::size_t hash = Hash<K>()(key);
    entries_[hash % entries_size_]
  }

  void emplace(K &&key, V &&value)
  {

  }

  void remove(const K &key)
  {
    
  }

private:
  static Entry **initialize_entries_(const std::size_t size)
  {
    Entry **ret = new Entry *[size];
    for (std::size_t i = 0; i < entries_size_; ++i)
    {
      ret[i] = nullptr;
    }
    return ret;
  }

  struct Entry
  {
    Entry(const K &key, const V &value)
      : key(key)
      , value(value)
      , next(nullptr)
    {
    }

    Entry(K &&key, V &&value)
      : key(std::move(key))
      , value(std::move(value))
      , next(nullptr)
    {
    }
    
    K key;
    V value;
    Entry *next;
  };

  std::size_t entries_size_;
  Entry **entries_;
};
