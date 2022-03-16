# CHALLENGE: THE TEMPLATE KEYVALUE CLASS

---

## Purpose:
It can be efficient to create a single class that can work with a 
variety of types. To accomplish this a template class (a pattern) can be 
created. 
When this template class is called, the compiler will automatically create 
a complete class that matches the type in the object declaration. 

This is one form of code reuse.


## Skills:
This activity will help you practice the following skills that are essential to 
know for basic programming in `C++`:
- Define template class
- Use a template class with a C++ primitive data type
- Use a template class with a user defined data type
- Catch2

## Knowledge:
This lab will also help you to become familiar with the following important 
content knowledge in CS:  
  - generic programming
  - code reuse
  - Use unit testing to validate code


## Challenge Activity
For this activity we will create a class for a key-value container. This
container works with two different variable types. One type is for the key
and the other type is for the value. The class stores key-value pairs.

For example, there may be a KeyValue object that stores the month and the
number of days in the month. The KeyValue object could have keys of type int
and values of type int.

KeyValue<int, int, 12> days_in_month_number;

This object would have key-value pairs of 

    1 31
    2 28
    3 31
    4 30
    5 31
    6 30
    7 31
    8 31
    9 30
    10 31
    11 30
    12 31

Another KeyValue object that stores the month and the
number of days in the month could have keys of type string
and values of type int.

KeyValue<string, int, 12> days_in_month_string;

This object would have key-value pairs of 

    January 31
    February 28
    March 31
    April 30
    May 31
    June 30
    July 31
    August 31
    September 30
    October 31
    November 30
    December 31

Another KeyValue object could use a name for the key and their favorite color  
as the value. The
key (name) would be of type string
and value (color) would be of type string.

KeyValue<string, string, 20> days_in_month_string;

This object would have key-value pairs of 

    John green
    Mary blue
    Kim lavender
    Kelly yellow
    Walter orange


---
### Files to work on
We will be working in the following files.

- There is a header file `src/key_value.h` where we will write the 
   KeyValue template class.
- There is a library `carton` that contains the carton class. The library 
  consists of these two files:
  - `src/carton.cpp`
  - `src/carton.h`
- Our "driver" will be `src/main.cpp`.

Please **DO NOT MODIFY** any other files. Modifying any other file may result 
in the unit tests not passing.

___

## Part 1: Begin the Template KeyValue Class


The `KeyValue` class is a template class so that it can be used with a 
variety of types. The KeyValue class is a container for key-value pairs. 



1. In the `key_value.h` file begin the `KeyValue` class.
   - add include guards to protect the header file from being included more
     than once
   - add the template header that includes three parts
     - the variable type for the `keys`
     - the variable type for the `values`
     - an int that specifies the maximum size of the KeyValue container
   - add the class named `KeyValue`
    - add two private data members that are arrays, one to store the keys and one to 
    store the values and 
    - add a private data member to keep track of the current size

   - add a public section with the following method declarations
   ```
       KeyValue();
       ~KeyValue();
       int GetSize() const;
       bool KeyExists(K key) const;
       void Add(K key, V item);
       V ValueAt(K key) const;
       bool Full() const;
       bool Empty() const;
       bool RemoveOne(K key);
       int RemoveAll(K key);
   ```  
    Notice that I have used `K` for the variable type for keys and `V` for the 
    variable type for values. You can follow this pattern or use a different
    name for the types. This will not matter when doing the unit tests.

   - add the following method declaration in the private section, this
   method will be internally by the KeyValue class but will not be 
   publicly available to users of the class 
   

```
    int FindIndex(K key) const;
```

2. Write the implementation for the `default constructor`. This constructor 
   initializes the size to 0. 
   
   Remember to put the template header above this method definition and to add 
   the name of the class followed by the template variables before the name of 
   the method. Remember this each time you add a method implementation outside 
   the class declaration.
   
   Also, remember to keep the function implementations in the .h file.

3. Write the `destructor`. It does not need to do anything. Just add the { }s
   
4. Write the implementation of `GetSize` method. This is a getter for the 
   private data member `size_` and simply returns the current size of the 
   KeyValue container. This data member keeps track of how many key-value
   pairs are currently being stored in the KeyValue container. 


---

## Part 2: The Adding and Finding Methods

The `Add` method provides the functionality to add key-value pairs to the 
container. Then the `FindIndex`, `KeyExists`, and `ValueAt` methods provide the means
to identify if a key exists in the KeyValue container and what the matching 
value is for that key.

1. Write the implementation for the `Add` method. 
   
   This method receives two values.
    - a new `key`
    - a new `value`

   It adds these to the key and value containers and increases the size. If 
   the KeyValue container is full, it is to throw an out_of_range exception that
   reports the KeyValue container is full.

   It returns nothing. 

2. Write the implementation for the private method `FindIndex`. This method can 
   be used be other methods in the the KeyValue class. 
   
   This method receives one value.
    - a `key`

   It looks in the key container for this key.

   It returns either
      - the index for the first matching key. 
      - a -1 if the key is not found
   
   This index can be used 
   to access the key or the matching value in the containers.

3. Write the implementation for the `KeyExists` method.
   This method receives one value.
    - a `key`

   It looks in the key container for this key. (Notice that the
   FindIndex method can tell you this. This is an opportunity to reuse 
   code by calling the 
   FindIndex method instead of re-writing code.)

   This method can be used to make sure a key exists before trying to 
   access the matching value. Using this check, can avoid an exception.

   It returns either
      - `true` if the key is found
      - `false` if the key is not found
   
4. Write the implementation for the `ValueAt` method.
   This method receives one value.
    - a `key`

   It looks in the key container for this key. When the key is found, it 
   returns the value that matches the key. When the key is not found it
   throws an out_of_range exception that reports the key was not found.

   It returns 
      - the first `value` that matches the key
   

---

## Part 3: The Empty and Full Methods

These methods report if a KeyValue container is full or empty. This information
can be used to avoid trying to add an item to a full container or
trying to remove an item from an empty container. When users of this class
use these methods effectively, they can avoid exceptions being thrown.

1. Write the implementation for the `Empty` method. 
   
   This method receives nothing.

   It returns true if the KeyValue container is empty and false otherwise. 

2. Write the implementation for the `Full` method. 
   
   This method receives nothing.

   It returns true if the KeyValue container is full and false otherwise. 


---

## Part 4: The RemoveOne and RemoveAll Methods

The `RemoveOne` and `RemoveAll` methods provide the functionality to 
remove items from the KeyValue container. 

1. Write the implementation for the `RemoveOne` method. 
   
   This method receives one value.
    - a `key`

   It removes the first occurrence of the key and its matching value. To do
   this all key-value pairs that come after the removed item will need to be
   shifted to fill the gap.

   It returns  
      - `true` if the item was found and removed
      - `false` if the item was not found in the KeyValue container

2. Write the implementation for the `RemoveAll` method. 
   
   This method receives one value.
    - a `key`

   It removes the all occurrences of the key and its matching value(s).
   To do
      this all key-value pairs that come after each of the removed 
      items will need to be
      shifted to fill the gap.

   It returns the number of items removed.
   

---

## Part 5: Overload the << Operator

It is handy to be able to write a KeyValue object using the << operator. To 
write a KeyValue object, we will write each 
key-value pair with a : and a space between them followed by a carriage return. 
  ```
  key: value

  ```

For example, the KeyValue that has months and number of days in the month 
would be output like this.
  ```
    January: 31
    February: 28
    March: 31
    April: 30
    May: 31
    June: 30
    July: 31
    August: 31
    September: 30
    October: 31
    November: 30
    December: 31

  ```

The KeyValue that has names and colors would be output like this.

  ```
    John: green
    Mary: blue
    Kim: lavender
    Kelly: yellow
    Walter: orange

  ```

1. Overload the << operator for the KeyValue class.

    - This method is a friend method
    - It returns an ostream object by reference
    - It is named operator<<
    - The first parameter is an ostream object passed by reference
    - The second parameter is a value of the variable type KeyValue passed by
      reference. No change is made to this parameter so set it to const.
    - Put the complete function implementation inside the class declaration
    - The method is to output the text and values described above. Be careful to
      add the :, spaces, and carriage returns as shown so it will pass the 
      unit tests.

    Now the KeyValue class uses the << operator to write out the key-value
    pairs. This means whatever type the key is and whatever type the value is 
    will need to work with the
    << operator. Ints, doubles, and strings all work with the << operator. 
    However, the Carton class does not. To be able to create a KeyValue that 
    contains Cartons we will need to overload the << operator in the Carton
    class.
    
    To do this we need to specify what it means to output a Carton object. The
    output will look like this:
      ```
      Carton length x width x height
      ```
    The words length, width, and height will be replaced by the actual values.
    
    Example
      ```
      Carton 16 x 12 x 14
      ```
    Another example.
      ```
      Carton 19.8 x 13.0 x 16.2
      ```

2. Overload the << operator for the Carton class.

- In the carton.h file write the method declaration
    - This method is a friend method
    - It returns an ostream object by reference
    - It is named operator<<
    - The first parameter is an ostream object passed by reference
    - The second parameter is a value of the variable type Carton passed by
      reference. No change is made to this parameter so set it to const.

  
- In the carton.cpp file write the method implementation 
  - The method is to output the text and values described above
  - There is a space between Carton and length
  - There is a space on both sides of each x
  - There is NO carriage return or space after height
  - To limit the output to display only a single digit after the decimal
    place, set the output to fixed and precision to 1 

Note: The keys are compared using the == operator in several of the methods.
This means whatever type the key is will need to work with the == operator.
We will be testing the KeyValue class with ints and strings as the key type.
We will not use any type for keys that need to overload the == operator.

---


## Part 6: Demonstrate Using the KeyValue Class With a Variety of Types

The unit tests will test KeyValue objects using the following
six types so you will want to make sure your code supports all these
combinations.

  | Key    | Value  |
  | ------ | ------ |
  | int    | int    |
  | int    | string |
  | int    | Carton |
  | string | int    |
  | string | string |
  | string | Carton |

Demonstrate how to create and use KeyValue objects.

1. In the `main.cpp` file create two KeyValue objects with different types from
  the table above. 
  - Have one use a key of type int and the other use a key
  of type string. 
  - Have one use
  values of type Carton and the other have values of type int or string.
  
  
   For each of the two types do the following.

     - Define a KeyValue object
     - Add 3-12 key-value pairs
     - Call the ValueAt method to get a value
       - This can potentially throw an exception. Handle this by choosing one
         (not both) of the following 
           - use a try/catch block to handle the exception
           - use the KeyExists method to make sure the key exists before calling the 
             ValueAt method
     - Remove one or more key-value pairs
     - Output the KeyValue object to the screen using the << operator


---
     
## Validate your code

Once you are satisfied with your work, run the unit test file:

From the dropdown select main_test and run.

Sample output:

Tests passed: 83 of 83 tests

---

## Submit your code

Zip your src folder and submit in Canvas.

---
