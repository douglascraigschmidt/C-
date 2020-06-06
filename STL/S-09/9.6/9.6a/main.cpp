#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

/**
 * Whether for use with custom algorithms and containers or with
 * STL's, sometimes one want to create custom functors. Here are some
 * tips for making them work:
 * 
 * . Functors need to provide an appropriate function call
 *   operator. This is what makes them usable just like regular
 *   functions.
 * 
 * . Functors must implement correct copy semantics. Passing by value
 *   always introduces additional copies of the functors. Thus,
 *   functors with a state need to ensure that their state information
 *   gets mirrored correctly to additional copies of them. This
 *   requires a specialized copy constructor as well as a specialized
 *   assignment operator, so that the values pointed to get copied
 *   rather than just copying their references; this is what is known
 *   as making a "deep copy."
 *
 * . Functors should be small to avoid expensive copies. Passing by
 *   value always comes at a performance penalty because instead of
 *   simply copying or assigning a small pointer, the complete object
 *   needs to be copied or assigned. This performance penalty will
 *   increase the bigger the object itself is. 
 * 
 * . Functors should not contain any polymorphic elements (in other
 *   words, no virtual functions). Using polymorphic functors opens
 *   the door to some problems. If a derived class functor is being
 *   passed by value into parameters of the corresponding base class
 *   type, a problem occurs: While copying the object, the additional
 *   parts of the derived class are removed.
 * 
 * However, there is still a way to use polymorphic functors, but only
 * by putting the polymorphic parts into a separate class. The
 * remaining non-polymorphic functor then contains a pointer to this
 * separate class. This is a well-known design pattern, usually
 * referred to as the Bridge pattern.
 * 
 * When one create a new class one can define what "+" does for
 * objects of that class. Other operators can be defined too. Objects
 * with "()" defined are called function objects or functors. Here's a
 * simple example:
 */
class is_more_than_two {
public:
   bool operator() (int val) {return val > 2;}
};

int main () {
  vector<int> v{1, 3, 4, 2, 6, 5, 0};

  // Use custom functor.
  auto n = count_if(v.begin(),
                    v.end(),
                    is_more_than_two());

  cout << n << endl;

  // Use predefined functor + a binder adapter.
  n = count_if(v.begin(),
             v.end(),
             bind2nd(greater<int>(), 2));

  cout << n << endl;

  // Use a lambda function.
  n = count_if(v.begin(),
             v.end(),
             [] (int val) { return val > 2; });

  cout << n << endl;

  return 0 ;
}
