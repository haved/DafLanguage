This is all deprecated. The language is changing too quickly. Just know that this text is old, but kept for history's sake. (Even though it's in git)
# Daf Language
Ideas for a programming language I want.
Syntax highlighting files and specifications may be located here.
The actual compiler project can be found [here](https://github.com/haved/DafCompiler "DafCompiler on Github")
#### Why?
I like programming in java, but I still want the joy of allocating classes on the stack. C++ is nice, but writing header files is annoying. Therefore I want a language where imports are handled like in java, however you don't need to put procedures in classes. Putting stuff on the stack instead of the heap is nice because you know the de-allocation of the memory is nearly instantaneous.  

Object orientation is easy to do, but not mandatory. I therefore allow for actual function pointers (only a lot more nice looking than what you find in C++). I also require memory uncertain variables and constructors to be marked as such. If a class is to be inherited from, its destructor must be virtual. This is to make sure the delete keyword allways de-allocates everything. If this is a problem, and you only want to allocate the class on the stack without any pesky virtual method overhead, simply don't inherit. Declare the superclass as a field marked as *base*. You'll be able to access all it's fields as if they were inherited.

Classes may contain fields, methods and functions. Fields may be initialized at any point, but unless they are given a value in either their declaration or in the constructor, the constructor must be marked as uncertain. It doesn't force anything on you, but is there to make memory safety more difficult to forget. Classes can also have methods and functions implemented outside of the actual class. Virtual methods must be declared inside the class, because they sort of work like fields. Constructors however, may be implemented outside. Classes may also have real generics.

Daf lets you pass variables by reference, or pass pointers to variables. Mutability is explicit, both when declaring variables and pointers. References don't exist outside of functions, however. If you want to automaticly dereference a pointer, you may just define some identifier to mean "dereference this pointer" and let the compiler handle the rest.

Sadly the *def* system is not capable of doing all compile-time wonders. That's why you also have a nice preprocessor with useful directives. Macros with parameters allowing for recursion. Expressions allowing for arithmetic to happen while compiling. If, then & else allowing for flow control in the middle of anything. These directives allow you to easily implement FizzBuzz, if that's what you want.

I'll make some other document detailing every feature I want to have.
