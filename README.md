# S4 - Object oriented Programming course

Repo forked forked from JulesFouchy/Simple-Cpp-Setup

## Lessons

### Level 1

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
Good name = consise + descriptive

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
separate words ? `snake_case` 

#### Make it work, then make it good
once it works, go back to the code and try to improve it 

### Level 2

#### Free Functions


## TP

### Guess the number 

- [x] make it work
- [ ] make it prettier 

- [x] add a score counter
- [ ] correct display of score (not really clean) 

### Hangman 

Aside : 
- [x] isolate rand function
- [ ] turn rand in template
- [x] isolate get_input_from_a_user 
- [x] turn it into a template 

Game :
- [x] first functionning version 
- [x] make prettier 
- [ ] bonus class

### Adding a menu 

- [x] basic menu
- [ ] struct game and separate file 