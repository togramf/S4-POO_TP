# S4 - Object oriented Programming course

Repo forked forked from JulesFouchy/Simple-Cpp-Setup

## Lessons

### Level 1

#### Use an IDEs
VSCode 4ever <3
- rename : F2
- go to definition : F12
- go to symbol : CTRL + SHIFT + 0 
- go to file : CTRL + P 
- switch .h and .cpp : ALT + 0 
- find all references 
- search for a word : CTRL + F (current file), CTRL + SHIFT + F (whole project)
- build : F7
- run : CTRL + F5 

#### Use Git 
gitKraken <3

#### Debugger

- [x] try 'Run and Debug'
- [x] try to place breakpoints
- [x] inspect state and call stack

#### Formatting tool & Static Analysers 
Clang format - Clang tidy 

#### Naming
Take the time to rename whenever you notice a name that is not quite accurate!

**Good name = consise + descriptive**

Boolean as question to make clear what true and false mean

no abbreviations

append "out" to non-const reference parameters

- [ ] watch from 41:30 [Kevlin Henney, Clean Coders Hate What Happens to Your Code When You Use These Enterprise Programming Tricks](https://youtu.be/FyCYva9DhsI?t=2490)

#### Stack vs Heap
- always use the stack (`int i = 3`, `std::variant`)
- if need to use the heap (for big object, polymorphism):
    - never use `new`
    - but a `std::unique_ptr` or a `std::shared_ptr`

#### Consistency in style
separate words for example `snake_case` 

### Level 2

#### Make it work, then make it good
once it works, go back to the code and try to improve it 

#### Free Functions
methods :
- depends on the whole class, 
- useful to encapsulate data and access it in defined ways

free fonctions :
- are clearer on dependencies
- easier to reuse 
- for a class, if the function only require the public interface

To-do 
- [ ] watch 1min from 36:00 [David Sankel, “Building Software Capital: How to write the highest quality code and why"](https://youtu.be/ta3S8CRN2TM)
- [ ] read [Make a function a member only if it needs direct access to the representation of a class](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c4-make-a-function-a-member-only-if-it-needs-direct-access-to-the-representation-of-a-class)

#### Design cohesive classes
class : enforcing invariants
- private members
- methods (must not be private, not use only public members of the class )
- inheritance
- must respect the single responsability principle

struct : members can vary independently
- members can be used by free functions

#### Use structs to group data
When ? when we pass the same group of parameters to several functions (remove duplications, useful abstraction + default values)

+ initialization example to see again 

#### Write small functions 
"too large" if doesn't fit on a screen 
one to five lines should be normal 

#### D.R.Y.
avoid duplications by using :
- loop or algorithm
- function
- template
- struct or class
- (macro)

#### Enums (enum class)
to express different possible situations

Example :
``` c++
enum class Direction { North, South,};
can be used by 
switch (direction) {
    case Direction::North:
        /*...*/
}
```
or 
``` c++
using enum Direction;
switch (direction) {
    case North:
        /*...*/
}
```

#### Split problems in small pieces 
it's all in the title 

#### Composition over Inheritance  
inheritance = too complex and can often be replace by : 
- functions : reuse logic
- function overloads
- composition : reuse member variables
- function objects
- templates 

composition : 
- put the reused member variables int a class or a struct 
- then add it as an attribute in the classes where you need them 

polymorphism : 
- prefer static to dynamic (templates and functions overloads)
- prefer using std::variant and std::function to dynamic polymorphism 
- ok for purely abstract class (interfaces), recurring template patter

- [ ] see [Mateusz Pusz “Effective replacement of dynamic polymorphism with std::variant”](https://youtu.be/gKbORJtnVu8)

### Level 3

#### std::vector
container like `std::list` but often more performant because of cache cohenrency. 

- [ ] see [Dynamic Arrays in C++ (std::vector) by The Cherno](https://youtu.be/PocJ5jXv8No)

#### Minimize dependencies
definition : dependencies are all the things a class / function can access to and that make it complex.

Reasons to minimize them : 
- less potential for bugs
- clearer code
- easier to change some parts of the code without adapting everything

How : 
- free functions 
- minimum and precise parameters

#### Strong Types
Wrap to give an `int` a name, invariants, etc.
-> expresses intent, helps concrete representation of concepts and prevents misuse and logic errors

**Example :** 

`Rectangle r (10, 12);` -> we don't know which one is height or width

`using Width = NamedType<double, struct WidthParameter>;` -> WidthParameter is a struct used to differentiate Width from Height

And now we can do : `Rectangle r (Width(10), Height(12));`

**Resources :** 
- [Type safe library Git](https://github.com/foonathan/type_safe)
- [ ] Read [Tutorial: Emulating strong/opaque typedefs in C++](https://www.foonathan.net/2016/10/strong-typedefs/) 
- [x] Read [Strong types for strong interfaces](https://www.fluentcpp.com/2016/12/08/strong-types-for-strong-interfaces/)
- [ ] See [CppCon 2016: Ben Deane “Using Types Effectively"](https://youtu.be/ojZbFIQSdl8)
- [ ] Watch [CppCon 2020: Mateusz Pusz "A Physical Units Library For the Next C++"](https://youtu.be/7dExYGSOJzo) 
- [ ] Watch [CppCon 2016: Robert Ramey “C++, Abstract Algebra and Practical Applications"](https://youtu.be/632a-DMM5J0)

#### Use libraries
Use Git submodule & Read documentation !! 

Cmake :
``` cmake
add_subdirectory(libname)
target_link_libraries(${PROJECT_NAME} PRIVATE libname)
```

#### Range-based for loop 
Why : 
- guaranties the index in the body of the loop won't be modified
- expresses the intent 

Examples : 
- to modify elements : `for (auto& element : container)`
- no modification and element is costly : `for (const auto& element : container)`
- no modification and element is cheap : `for (auto element : container)`

#### std::optional 

don't need to allocate memory on the free store

How to: 
- `#include <optional>` since C++17
- `std::optional<type> optionalPtr`
- `std::nullopt`
- `std::make_optional<type_or_nothing>(optionalValue)`
- `std::in_place`
- check if there is a value: `has_value()` or `if (optional)`
- accessing the store value: `operator*` or `operator->` (if empty = undefined); `value()`; `value_or(defaultValue)`
- changing the value: `emplace(value)`; `reset()`; 
- comparisons is possible with "<", ">", etc. 


When: when the lack of value is as natural as having any regular value
- to represent a nullable type 
- return a result that can be empty and it's not an error
- to pass optional parameters into functions 

**Resources:**
- [x] Read [Using C++17 std::optional](https://www.cppstories.com/2018/05/using-optional/)
- [ ] Watch [CppCon 2016: Ben Deane “Using Types Effectively"](https://youtu.be/ojZbFIQSdl8)

#### Markdown

- [x] See [Markdown Cheatsheet](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet)

## TP

#### General Notes: 

STOP: copy of string in argument

Naming system : 
- function_and_parameters_names ; 
- StructNames ; 
- _struct_properties_names ;

### Guess the number 

- [x] make it work
- [x] make it prettier 

- [x] add a score counter
- [x] correct display of score (not really clean) 

Ideas : 
- [ ] see the score for a random player ? 

Corrections:
- [x] D.R.Y. problem: `int int_user = get_input_from_user<int>(min, max);`
- [x] rename `score` => `number_of_tries`


### Hangman 

Aside : 
- [x] isolate rand function
- [x] turn rand in template
- [x] isolate get_input_from_a_user 
- [x] turn it into a template 

Game :
- [x] first functionning version 
- [x] make prettier 
- [x] bonus class (wordWithMissingLetters)
- [x] add congrats and reproaches words and a random display of them

### Adding a menu 

- [x] basic menu
- [x] separate file 
- [x] struct game and map 

Resources 
- [To loop through a map](https://www.codegrepper.com/code-examples/cpp/how+to+loop+through+map+c%2B%2B)
- [Find element in a map](https://www.cplusplus.com/reference/map/map/find/)

### Noughts and Crosses 
 
- [x] install p6 as submodule 
    - [x] fork repo
    - [x] correct problems 
    - [ ] pull request ? (stand by)
- [x] display an empty window
- [x] display a grid in the window 
- [x] separate the code and the main and update the menu
- [x] detect cells and hoover : `T map(T x, T from_min, T from_max, T to_min, T to_max);`
    - [x] position -> cell index
    - [x] cell_index -> position
    - [x] use std::optional 
- [X] draw noughts and crosses
    - [x] nought
    - [X] cross
- [x] fix noughts and crosses on click 
    - [x] class Board to store the state of the game 
    - [x] function to draw shapes according to the state of the board
- [x] check for the end of the game 
    - [x] check that the board is full 
    - [x] check that a player has won 
- [ ] clean the code
    - [ ] congratulation messages in separate functions


Resources 
- [Making things with p6](https://julesfouchy.github.io/p6-docs/)
- [std::optional](https://en.cppreference.com/w/cpp/utility/optional) 

### Connect 4  

Make it Work: 
- [x] move some code from Noughts and Crosses to draw the board
- [x] correct the board to have more colums than rows
- [x] separate the board functions in another file
- [x] draw coins
- [x] play in column : basic version
- [x] check for the end of the game 
    - [x] check that the board is full 
    - [x] check that a player has won : check in the 4 directions if 4 coins are aligned 
- [x] display a message when the game is over

Make it better: 
- [x] correct problem with the mouse (slight offset on the edges of the board between the mouse and the cells)
    - [ ] now when we click outside of the board, the coin is placed in the first column :/ 
- [x] add a delay of two seconds at the end (I borrowed your code Jules <3)