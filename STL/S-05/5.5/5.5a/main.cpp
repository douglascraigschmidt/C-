#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

/**
 * A map is a sorted associative container that associates key objects
 * with value objects.  It is called a pair associative container
 * because its value_type is actually implemented as pair<const Key,
 * Value>.  For a map, keys must be unique. The keys don’t have to be
 * integers, so a map is more general than a sequential container such
 * as vector, deque, or list.
 *
 * template <typename Key,
 *           typename Value,
 *           typename Compare = less<Key>,
 *           typename Allocator = allocator <pair<const Key, Value>> >
 * class map { ... };
 * 
 * Characteristics of map
 * . Inserting a new element into a map does not invalidate iterators
 *   that point to existing elements.
 *
 * . Erasing an element from a map also does not invalidate any
 *   iterators, except those iterators that actually point to the
 *   element that is being erased.
 * 
 * To use a map you must supply a key type and data type.  You can
 * also choose to provide a comparing function that does the job of
 * the less-than operator so that data can be placed in order by key:
 * 
 * map <key_type, data_type [, comparison_function]>
 */
int main () {
  std::vector<std::string> word_list {"now", "is", "the", "time", 
                                      "for", "all", "good", "people",
                                      "to", "come", "to", "the", 
                                      "aid", "of", "their", "party"};

  typedef std::map<std::string, int> WORD_MAP;
  WORD_MAP word_map; // Map of words and their frequencies.

  // Use range-based for loop to count the number of times each word
  // appears in the word_list.
  for (auto const &word : word_list)
    ++word_map[word];

#if 0  
  // Use an explicit iterator to count the number of times each word
  // appears in the word_list.
  for (/*WORD_MAP::iterator*/std::vector<std::string>::const_iterator word_iter = word_list.cbegin ();
       word_iter != word_list.cend ();
       ++word_iter)
    ++word_map[*word_iter];

  // Use an auto iterator to count the number of times each word
  // appears in the word_list.
  for (/*auto const &*/ std::vector<std::string>::iterator word_iter = word_list.begin ();
       word_iter != word_list.end ();
       ++word_iter)
    ++word_map[*word_iter];
#endif

  // Print out the word_map.
  for (auto const &i : word_map)
    std::cout << i.second << " " << i.first << std::endl; 

  // Create a functor.
  class total_it {
  public:
    explicit total_it (int i): i_ (i) {}

    void operator()(const WORD_MAP::value_type &p) {
      i_ += p.second;
    }

    int count() const { return i_; }
  private:
    int i_; 
  };

  auto total = 0;

  // Count the total number of words in the map.
  total_it it = for_each (word_map.begin(),
                          word_map.end(),
                          // Use a functor.
                          total_it (total));
  total = it.count();

  std::cout << "total number of words = " << total << std::endl;

  total = 0;

  // Count the total number of words in the map. 
  for_each (word_map.begin(),
            word_map.end(),
            // Use a lambda function.
            [&total] (const WORD_MAP::value_type &p) {
              total += p.second;
            });

  std::cout << "total number of words = " << total << std::endl;

  return 0;
}
