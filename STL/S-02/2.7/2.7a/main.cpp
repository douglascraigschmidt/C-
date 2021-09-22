#include <vector>
#include <string>
#include <iostream>
#include <list>
#include <deque>
using namespace std;

/**
 * A template can take a parameter that is itself the name of a
 * template. These parameters have the name of template template
 * parameters. Let's use a simple example. Start with a template for a
 * stack that would accept a type of data to be stored and a container
 * type to adapt into a stack.
 *
 * The first parameter, T, is just the name of a datatype as
 * usual. The second parameter, container, is a "template template"
 * parameter. It's the name of a class template that has a single type
 * name parameter, and we didn't specify a type of data contained in
 * the original container.
 *
 * The stack template uses its "typename" parameter to instantiate
 * its "template template" parameter. The resulting container type is
 * used to implement the stack object:
*/
template <typename T,
          template <typename ...> class container = deque>
class stack {
public:
  void push(const T &t) { s.push_back(t); }
  void pop() { s.pop_back(); }
  T top() { return s.back(); }
  // ...

private:
  container<T> s;
};

/**
 * The template template parameter approach above allows coordination
 * between the element and its container to be handled by the
 * implementation of the stack itself, rather than in all the various
 * code that specializes the stack class.
 *
 * This single point of specialization reduces the possibility of
 * mismatches between the element type and the container used to hold
 * the elements.
 * 
 * Below, we show how to create a stack object from a list or from a
 * deque.  The stack created from the list will hold integers while
 * the stack created from the deque will hold strings. All of this
 * resulted from allowing the stack template to have a parameter that
 * is itself a template.
*/
int main() {
    stack<string> a_deque_stack_of_strings; // defaults to deque
    stack<int, list> a_list_stack_of_ints;

    a_deque_stack_of_strings.push("hello");
    string s = a_deque_stack_of_strings.top();
    cout << s << endl;
    a_deque_stack_of_strings.pop();

    a_list_stack_of_ints.push(42);
    int i = a_list_stack_of_ints.top();
    cout << i << endl;
    a_list_stack_of_ints.pop();

    return 0;
}

