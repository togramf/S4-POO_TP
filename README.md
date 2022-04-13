# S4 - Object oriented Programming course

Repo forked forked from JulesFouchy/Simple-Cpp-Setup

## Lessons

### Level 1

#### Use an IDE
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
- [ ] try to place breakpoints
- [ ] inspect state and call stack

#### Formatting tool
Clang format -> doesn't work 

#### Static Analysers 
Clang tidy 

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
`enum class Direction { North, South,};`
can be used by 
`switch (direction) {
    case Direction::North:
        /*...*/
}`
or 
`using enum Direction;
switch (direction) {
    case North:
        /*...*/
}`

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

## TP

General Notes: 
- [ ] STOP: copy of string in argument

### Guess the number 

- [x] make it work
- [x] make it prettier 

- [x] add a score counter
- [x] correct display of score (not really clean) 

Ideas : 
- [ ] see the score for a random player ? 

Corrections:
- [ ] D.R.Y. problem: `int int_user = get_input_from_user<int>(min, max);`
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

Ideas : 
refer to cells with index ? a tab ? 
first : only take mouse click to place nought/cross ? in order to code the game 
then : to hoover, convert mouse position to corresponding cell 
problem : fix noughts and crosses when mouse_pressed


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


Resources 
- [Making things with p6](https://julesfouchy.github.io/p6-docs/)
- [std::optional](https://en.cppreference.com/w/cpp/utility/optional) 