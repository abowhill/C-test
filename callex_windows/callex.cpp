// call_examples.cpp: Allan Bowhill
// 
// (version for VS 2013 community edition = 3 changes had to be made
// to code from LLVM, and a special build file had to be made)
//
// Some basic sample code to illustrate object calls with different 
// types of basic data used in different ways as parameters.

// compile with:  c++ call_examples.cpp 2>&1 | most

#include <iostream>

// disallow threads - a C++0x feature not supported in VS 2013
// #include <thread>
//
// MUST include <string> because VS 2013 community edition <iostream>
// doesn't understand what a string is with the redirection << operator
// of std::cout
#include <string>

using namespace std;

// define some classes that can visibly respond after initialization
class RedObject 
    { 
     public: 
        const string name = "RedObject";
        RedObject() { } 
        ~RedObject() { }
    };

class GreenObject 
   { 
   public: 
      string name; 
      GreenObject(string & s) : name(s) { }
      ~GreenObject() { }
   };

class BlueObject { public: string name(void) { return "BlueObject"; } };
class YellowObject 
   {
   public: 
      string name; 
      YellowObject(string & s) : name(s) { }
      ~YellowObject() { cout << "Destroying Yellow" << endl; }
   };


// here is the int(void) function we are pointing-to with FunctionPointer in this example
int test_function(string s)
    {
    int size = s.length();
    return size;
    }

// This defines a data type of function pointer called
// "FunctionPointer" that takes a string and returns an int
typedef int (*FunctionPointer)(string);

struct little_hash_schema
{
   string key1;
   char my_name[5];
   int my_array[3];
};


class TestClass
   {
   int an_int;
   string a_string;
   float * some_floats;
   double * some_doubles;
   RedObject red;
   GreenObject green;
   BlueObject * blue;
   YellowObject * yellow;
   FunctionPointer fptr;
   little_hash_schema test_struct;

   public:
      TestClass(int, string &, float[], double *, 
         RedObject, GreenObject &, BlueObject *, YellowObject *, 
         FunctionPointer, little_hash_schema &);

      ~TestClass();
      void print(void);
      // for threads, we must use static as instances have a 
      // signature that contains hidden param "this"
      static void functionA(int, string);
      static void functionB(int, string);
   };

// take note on how each type is received. 
// param1 = stack primitive rcd by value
// param2 = built-in stack object rcd by reference
// param3 = stack array (pointer) recd by reference, but with brackets
// param4 = pointer to stack array received explicitly as pointer 
// param5 = Custom stack object received by value (a copy is made)
// param6 = Custom stack oject sent by value, received by reference (no copy)
// param7 = Pointer to stack object received explicitly by pointer
// param8 = Pointer to heap object reveived as pointer
// param9 = Function pointer on stack recieved as data type of function pointer
TestClass::TestClass(int a, string & s, float f[], double * d, 
      RedObject r, GreenObject & g, BlueObject * b, YellowObject * y,
      FunctionPointer fp, little_hash_schema & ts)
  :an_int(a), a_string(s), some_floats(f), some_doubles(d), 
      red(r), green(g), blue(b), yellow(y), fptr(fp), test_struct(ts)
   {
   // Nothing to do here
   }

void TestClass::print(void)
   {
   cout << an_int << endl;
   cout << a_string << endl;

   for (int i = 0; i < 3; ++i)
      {
      cout << some_floats[i] << " ";
      }
   cout << endl;
   
   for (int i = 0; i < 3; ++i)
      {
      cout << some_doubles[i] << " ";
      }
   cout << endl;

   cout << red.name << endl;
   cout << green.name << endl;
   cout << blue->name() << endl;
   cout << yellow->name << endl;

   string string_input = "Vault 21";
   cout << string_input << " Size = " << fptr(string_input) << endl;

   cout << "Struct contents:" << endl;
   cout << test_struct.key1 << endl;
   cout << test_struct.my_name << endl;
   cout << test_struct.my_array[1] << endl;
   }

TestClass::~TestClass(void)
   {
   }

void TestClass::functionA(int i, string s)
   {
   for (int k = 0; k < i; ++k)
      {
      cout << ".";
      }
   cout << endl;
   cout << "functionA: " << s << endl;
   }

void TestClass::functionB(int i, string s)
   {
   string sv = s;
   for (int k = 0; k < i; ++k)
      {
      cout << "+";
      }
   cout << endl;
   cout << "functionB: " << sv << endl;
   }


int main(void)
   {
   int a = 5;
   string s = "Hi There";
   float f[] = { 1.0, 2.0, 3.0 };
   double d[3] = { 4.0, 5.0, 6.0 };
   RedObject r;  // stack based object

   string g_string = "GreenObject"; // this must be assigned or we get a temporary
   GreenObject g(g_string); //stack object with parameter
   
   BlueObject b; 
   BlueObject * bp = &b;  // pointer to a stack object

   string y_string = "YellowObject";
   YellowObject * y = new YellowObject(y_string); // heap object
 
   FunctionPointer fp = &test_function;  // function pointer

   // direct aggregate initialization (probably dangerous)
   little_hash_schema fx {"hi", {'f','o','o','x','\0'}, {100,200,300}};

   little_hash_schema ts;
   ts.key1 = "foo";
   // strncpy must be changed to strncpy_s
   (void) strncpy_s (ts.my_name, "bar\0", sizeof(ts.my_name));
   for (int i = 0; i < 3; ++i)
   {
      ts.my_array[i] = i*10;
   }

   TestClass example(a,s,f,d,r,g,bp,y,fp,ts); // drop all into object and print
   example.print();
/*
   // spawn thread on functionA and functionB
   // both are static. Either call works.
   thread T1 (TestClass::functionA, 500, "This was string A");
   string p2("This was string B");
   thread T2 (example.functionB, 500, p2);
  
   // both threads running
   
   T1.join(); // wait for other
   T2.join();
*/
   delete y;

   return (0);
   }
