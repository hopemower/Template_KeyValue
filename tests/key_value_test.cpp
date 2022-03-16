// this tells catch to provide a main()
// only do this in one cpp file
#define CATCH_CONFIG_MAIN
#include "../externals/catch2/catch.hpp"

#include <array>
#include <fstream>
#include <string>
#include "carton.h"
#include "key_value.h"

using namespace std;

const int kSize = 5;

//******************************constructors******************************
TEST_CASE(
    "Default constructor creates a KeyValue container of size zero for keys of "
    "type int and values of type int",
    "[start]") {
  KeyValue<int, int, kSize> key_value;
  REQUIRE(key_value.GetSize() == 0);
}

TEST_CASE(
    "Default constructor creates a KeyValue container of size zero for keys of "
    "type int and values of type double",
    "[start]") {
  KeyValue<int, double, kSize> key_value;
  REQUIRE(key_value.GetSize() == 0);
}

TEST_CASE(
    "Default constructor creates a KeyValue container of size zero for keys of "
    "type int and values of type string",
    "[start]") {
  KeyValue<int, string, kSize> key_value;
  REQUIRE(key_value.GetSize() == 0);
}

TEST_CASE(
    "Default constructor creates a KeyValue container of size zero for keys of "
    "type int and values of type Carton",
    "[start]") {
  KeyValue<int, Carton, kSize> key_value;
  REQUIRE(key_value.GetSize() == 0);
}

TEST_CASE(
    "Default constructor creates a KeyValue container of size zero for keys of "
    "type string and values of type int",
    "[start]") {
  KeyValue<string, int, kSize> key_value;
  REQUIRE(key_value.GetSize() == 0);
}

TEST_CASE(
    "Default constructor creates a KeyValue container of size zero for keys of "
    "type string and values of type double",
    "[start]") {
  KeyValue<string, double, kSize> key_value;
  REQUIRE(key_value.GetSize() == 0);
}

TEST_CASE(
    "Default constructor creates a KeyValue container of size zero for keys of "
    "type string and values of type string",
    "[start]") {
  KeyValue<string, string, kSize> key_value;
  REQUIRE(key_value.GetSize() == 0);
}

TEST_CASE(
    "Default constructor creates a KeyValue container of size zero for keys of "
    "type string and values of type Carton",
    "[start]") {
  KeyValue<string, Carton, kSize> key_value;
  REQUIRE(key_value.GetSize() == 0);
}

//******************************int, int, 5******************************
TEST_CASE(
    "Add method adds keys and values expected in loop"
    "for keys of type int and values of type int "
    "throws out_of_range exception when Add called after full",
    "[add][value]") {
  KeyValue<int, int, kSize> key_value;
  // add key value pairs to container
  for (int i = 0; i < kSize; i++) {
    key_value.Add(i, i * 10);
  }
  // test size
  REQUIRE(key_value.GetSize() == kSize);

  // test key and value are in the KeyValue container
  for (int i = 0; i < kSize; i++) {
    REQUIRE(key_value.ValueAt(i) == i * 10);
  }

  // add one after full, expect exception
  REQUIRE_THROWS_AS(key_value.Add(101, 1010), out_of_range);
}

TEST_CASE(
    "Add method adds keys and values expected and ValueAt finds them"
    "for keys of type int and values of type int "
    "throws out_of_range exception when Add called after full",
    "[add][value]") {
  KeyValue<int, int, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, 22);
  key_value.Add(3, 12);
  key_value.Add(9, 18);
  key_value.Add(5, 91);
  key_value.Add(17, 35);

  // test size
  REQUIRE(key_value.GetSize() == 5);

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt(7) == 22);
  REQUIRE(key_value.ValueAt(3) == 12);
  REQUIRE(key_value.ValueAt(9) == 18);
  REQUIRE(key_value.ValueAt(5) == 91);
  REQUIRE(key_value.ValueAt(17) == 35);

  // add one after full, expect exception
  REQUIRE_THROWS_AS(key_value.Add(101, 99), out_of_range);
}

TEST_CASE(
    "Add method adds keys and values expected and ValueAt finds them"
    "for keys of type int and values of type int "
    "ValueAt method throws out_of_range when key not found",
    "[add][value]") {
  KeyValue<int, int, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, 22);
  key_value.Add(3, 12);
  key_value.Add(9, 18);
  key_value.Add(5, 91);
  key_value.Add(17, 35);

  // test size
  REQUIRE(key_value.GetSize() == 5);

  // call ValueAt with key not used, expect exception
  REQUIRE_THROWS_AS(key_value.ValueAt(107), out_of_range);
}

TEST_CASE(
    "RemoveOne method removes key and value expected and returns true "
    "for keys of type int and values of type int",
    "[remove_one]") {
  KeyValue<int, int, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, 22);
  key_value.Add(3, 12);
  key_value.Add(7, 18);
  key_value.Add(5, 91);
  key_value.Add(7, 35);

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(key_value.RemoveOne(7));

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt(7) > 17);
  REQUIRE(key_value.ValueAt(3) == 12);
  REQUIRE(key_value.ValueAt(5) == 91);

  // test size
  REQUIRE(key_value.GetSize() == 4);

  REQUIRE(key_value.RemoveOne(3));

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt(7) > 17);
  REQUIRE(key_value.ValueAt(5) == 91);

  // test size
  REQUIRE(key_value.GetSize() == 3);

  REQUIRE(key_value.RemoveOne(7));

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt(7) > 17);
  REQUIRE(key_value.ValueAt(5) == 91);

  // test size
  REQUIRE(key_value.GetSize() == 2);

  REQUIRE(key_value.RemoveOne(7));

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt(5) == 91);

  // test size
  REQUIRE(key_value.GetSize() == 1);

  REQUIRE(key_value.RemoveOne(5));

  // test size
  REQUIRE(key_value.GetSize() == 0);

  REQUIRE(!key_value.RemoveOne(5));

  // test size
  REQUIRE(key_value.GetSize() == 0);
}

TEST_CASE(
    "RemoveOne method removes nothing and returns false when key not found "
    "for keys of type int and values of type int",
    "[remove_one]") {
  KeyValue<int, int, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, 22);
  key_value.Add(3, 12);
  key_value.Add(7, 18);
  key_value.Add(5, 91);
  key_value.Add(7, 35);

  // test size before remove
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(!key_value.RemoveOne(17));

  // test size after remove
  REQUIRE(key_value.GetSize() == 5);

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt(7) > 17);
  REQUIRE(key_value.ValueAt(3) == 12);
  REQUIRE(key_value.ValueAt(5) == 91);
}

TEST_CASE(
    "RemoveOne method removes nothing and returns false container is empty "
    "for keys of type int and values of type int",
    "[remove_one]") {
  KeyValue<int, int, kSize> key_value;

  REQUIRE(!key_value.RemoveOne(7));

  // test size after remove
  REQUIRE(key_value.GetSize() == 0);
}

TEST_CASE(
    "RemoveAll method removes keys and values expected and returns number when "
    "key is found multiple times "
    "for keys of type int and values of type int ",
    "[remove_all]") {
  KeyValue<int, int, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, 22);
  key_value.Add(3, 12);
  key_value.Add(7, 18);
  key_value.Add(5, 91);
  key_value.Add(7, 35);

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(key_value.RemoveAll(7) == 3);

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt(3) == 12);
  REQUIRE(key_value.ValueAt(5) == 91);

  // test size
  REQUIRE(key_value.GetSize() == 2);
  REQUIRE_THROWS_AS(key_value.ValueAt(7), out_of_range);
}

TEST_CASE(
    "RemoveAll method removes keys and values expected and returns 1 when "
    "key is found one time "
    "for keys of type int and values of type int ",
    "[remove_all]") {
  KeyValue<int, int, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, 22);
  key_value.Add(3, 12);
  key_value.Add(7, 18);
  key_value.Add(5, 91);
  key_value.Add(7, 35);

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(key_value.RemoveAll(5) == 1);

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt(3) == 12);
  REQUIRE(key_value.ValueAt(7) > 17);
  REQUIRE_THROWS_AS(key_value.ValueAt(5), out_of_range);
  // test size
  REQUIRE(key_value.GetSize() == 4);
}

TEST_CASE(
    "RemoveAll method removes nothing and returns zero when key not found "
    "for keys of type int and values of type int ",
    "[remove_all]") {
  KeyValue<int, int, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, 22);
  key_value.Add(3, 12);
  key_value.Add(9, 18);
  key_value.Add(5, 91);
  key_value.Add(17, 35);

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(key_value.RemoveAll(22) == 0);

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt(7) == 22);
  REQUIRE(key_value.ValueAt(3) == 12);
  REQUIRE(key_value.ValueAt(9) == 18);
  REQUIRE(key_value.ValueAt(5) == 91);
  REQUIRE(key_value.ValueAt(17) == 35);

  // test size
  REQUIRE(key_value.GetSize() == 5);
}

TEST_CASE(
    "KeyExists method returns true when key found and false when key not found "
    "for keys of type int and values of type int ",
    "[found]") {
  KeyValue<int, int, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, 22);
  key_value.Add(3, 12);
  key_value.Add(9, 18);
  key_value.Add(5, 91);
  key_value.Add(17, 35);

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(!key_value.KeyExists(22));

  // test key and value are in the KeyValue container
  REQUIRE(key_value.KeyExists(7));
  REQUIRE(key_value.KeyExists(3));
  REQUIRE(key_value.KeyExists(9));
  REQUIRE(key_value.KeyExists(5));
  REQUIRE(key_value.KeyExists(17));

  // test size
  REQUIRE(key_value.GetSize() == 5);
}

TEST_CASE(
    "Empty method returns true when empty and false when not empty "
    "for keys of type int and values of type int ",
    "[empty]") {
  KeyValue<int, int, kSize> key_value;
  // add key value pairs to container

  REQUIRE(key_value.Empty());
  // test size
  REQUIRE(key_value.GetSize() == 0);
  key_value.Add(7, 22);
  REQUIRE(!key_value.Empty());
  // test size
  REQUIRE(key_value.GetSize() == 1);
  key_value.RemoveOne(7);
  REQUIRE(key_value.Empty());
  // test size
  REQUIRE(key_value.GetSize() == 0);
}

TEST_CASE(
    "Full method returns true when full and false when not full "
    "for keys of type int and values of type int "
    "Also, tests size method",
    "[full]") {
  KeyValue<int, int, kSize> key_value;
  // add key value pairs to container

  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 0);
  key_value.Add(7, 22);
  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 1);
  key_value.Add(3, 12);
  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 2);
  key_value.Add(9, 18);
  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 3);
  key_value.Add(5, 91);
  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 4);
  key_value.Add(17, 35);
  REQUIRE(key_value.Full());
  REQUIRE(key_value.GetSize() == 5);
  key_value.RemoveOne(7);
  REQUIRE(!key_value.Full());
  // test size
  REQUIRE(key_value.GetSize() == 4);
}

TEST_CASE(
    "The << operator works and outputs key, space, value, carriage return for "
    "all elements in the KeyValue container "
    "for keys of type int and values of type int ",
    "[remove_all]") {
  KeyValue<int, int, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, 22);
  key_value.Add(3, 12);
  key_value.Add(9, 18);
  key_value.Add(5, 91);
  key_value.Add(17, 35);
  REQUIRE(key_value.GetSize() == 5);
  // test <<size>>
  ofstream out("test_output.txt");
  out << key_value;
  out.close();

  ifstream in("test_output.txt");
  string line;
  getline(in, line);
  REQUIRE("7: 22" == line);
  getline(in, line);
  REQUIRE("3: 12" == line);
  getline(in, line);
  REQUIRE("9: 18");
  getline(in, line);
  REQUIRE("5: 91" == line);
  getline(in, line);
  REQUIRE("17: 35" == line);
  getline(in, line);
  REQUIRE("" == line);

  in.close();
}

TEST_CASE(
    "The << operator only prints out the valid keys and values,"
    "does not print out the entire arrays when not full. "
    "for keys of type int and values of type int ") {
  KeyValue<int, int, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, 22);
  key_value.Add(3, 12);
  key_value.Add(9, 18);
  REQUIRE(key_value.GetSize() == 3);
  // test <<size>>
  ofstream out("test_output.txt");
  out << key_value;
  out.close();

  ifstream in("test_output.txt");
  string line;
  getline(in, line);
  REQUIRE("7: 22" == line);
  getline(in, line);
  REQUIRE("3: 12" == line);
  getline(in, line);
  REQUIRE("9: 18");
  getline(in, line);
  REQUIRE("" == line);

  in.close();
}

//******************************int, string, 5******************************
TEST_CASE(
    "Add method adds keys and values expected in loop"
    "for keys of type int and values of type string "
    "throws out_of_range exception when Add called after full",
    "[add][value]") {
  KeyValue<int, string, kSize> key_value;
  // add key value pairs to container
  for (int i = 0; i < kSize; i++) {
    key_value.Add(i, "blue" + i);
  }
  // test size
  REQUIRE(key_value.GetSize() == kSize);

  // test key and value are in the KeyValue container
  for (int i = 0; i < kSize; i++) {
    REQUIRE(key_value.ValueAt(i) == "blue" + i);
  }

  // add one after full, expect exception
  REQUIRE_THROWS_AS(key_value.Add(101, "orange"), out_of_range);
}

TEST_CASE(
    "Add method adds keys and values expected and ValueAt finds them"
    "for keys of type int and values of type string "
    "throws out_of_range exception when Add called after full",
    "[add][value]") {
  KeyValue<int, string, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, "blue");
  key_value.Add(3, "gray");
  key_value.Add(9, "purple");
  key_value.Add(5, "yellow");
  key_value.Add(17, "green");

  // test size
  REQUIRE(key_value.GetSize() == 5);

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt(7) == "blue");
  REQUIRE(key_value.ValueAt(3) == "gray");
  REQUIRE(key_value.ValueAt(9) == "purple");
  REQUIRE(key_value.ValueAt(5) == "yellow");
  REQUIRE(key_value.ValueAt(17) == "green");

  // add one after full, expect exception
  REQUIRE_THROWS_AS(key_value.Add(101, "orange"), out_of_range);
}

TEST_CASE(
    "Add method adds keys and values expected and ValueAt finds them"
    "for keys of type int and values of type string "
    "ValueAt method throws out_of_range when key not found",
    "[add][value]") {
  KeyValue<int, string, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, "blue");
  key_value.Add(3, "gray");
  key_value.Add(9, "purple");
  key_value.Add(5, "yellow");
  key_value.Add(17, "green");

  // test size
  REQUIRE(key_value.GetSize() == 5);

  // call ValueAt with key not used, expect exception
  REQUIRE_THROWS_AS(key_value.ValueAt(107), out_of_range);
}

TEST_CASE(
    "RemoveOne method removes key and value expected and returns true "
    "for keys of type int and values of type string",
    "[remove_one]") {
  KeyValue<int, string, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, "blue");
  key_value.Add(3, "gray");
  key_value.Add(7, "purple");
  key_value.Add(5, "yellow");
  key_value.Add(7, "green");

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(key_value.RemoveOne(7));

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt(3) == "gray");
  REQUIRE(key_value.ValueAt(5) == "yellow");

  // test size
  REQUIRE(key_value.GetSize() == 4);

  REQUIRE(key_value.RemoveOne(3));

  // test key and value are in the KeyValue container
  REQUIRE(key_value.GetSize() == 3);

  REQUIRE(key_value.RemoveOne(7));

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt(5) == "yellow");

  // test size
  REQUIRE(key_value.GetSize() == 2);

  REQUIRE(key_value.RemoveOne(7));

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt(5) == "yellow");

  // test size
  REQUIRE(key_value.GetSize() == 1);

  REQUIRE(key_value.RemoveOne(5));

  // test size
  REQUIRE(key_value.GetSize() == 0);

  REQUIRE(!key_value.RemoveOne(5));

  // test size
  REQUIRE(key_value.GetSize() == 0);
}

TEST_CASE(
    "RemoveOne method removes nothing and returns false when key not found "
    "for keys of type int and values of type string",
    "[remove_one]") {
  KeyValue<int, string, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, "blue");
  key_value.Add(3, "gray");
  key_value.Add(7, "purple");
  key_value.Add(5, "yellow");
  key_value.Add(7, "green");

  // test size before remove
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(!key_value.RemoveOne(17));

  // test size after remove
  REQUIRE(key_value.GetSize() == 5);

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt(3) == "gray");
  REQUIRE(key_value.ValueAt(5) == "yellow");
}

TEST_CASE(
    "RemoveOne method removes nothing and returns false container is empty "
    "for keys of type int and values of type string",
    "[remove_one]") {
  KeyValue<int, string, kSize> key_value;

  REQUIRE(!key_value.RemoveOne(7));

  // test size after remove
  REQUIRE(key_value.GetSize() == 0);
}

TEST_CASE(
    "RemoveAll method removes keys and values expected and returns number when "
    "key is found multiple times "
    "for keys of type int and values of type string ",
    "[remove_all]") {
  KeyValue<int, string, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, "blue");
  key_value.Add(3, "gray");
  key_value.Add(7, "purple");
  key_value.Add(5, "yellow");
  key_value.Add(7, "green");

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(key_value.RemoveAll(7) == 3);

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt(3) == "gray");
  REQUIRE(key_value.ValueAt(5) == "yellow");

  // test size
  REQUIRE(key_value.GetSize() == 2);
  REQUIRE_THROWS_AS(key_value.ValueAt(7), out_of_range);
}

TEST_CASE(
    "RemoveAll method removes keys and values expected and returns 1 when "
    "key is found one time "
    "for keys of type int and values of type string ",
    "[remove_all]") {
  KeyValue<int, string, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, "blue");
  key_value.Add(3, "gray");
  key_value.Add(7, "purple");
  key_value.Add(5, "yellow");
  key_value.Add(7, "green");

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(key_value.RemoveAll(5) == 1);

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt(3) == "gray");
  REQUIRE_THROWS_AS(key_value.ValueAt(5), out_of_range);
  // test size
  REQUIRE(key_value.GetSize() == 4);
}

TEST_CASE(
    "RemoveAll method removes nothing and returns zero when key not found "
    "for keys of type int and values of type string ",
    "[remove_all]") {
  KeyValue<int, string, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, "blue");
  key_value.Add(3, "gray");
  key_value.Add(9, "purple");
  key_value.Add(5, "yellow");
  key_value.Add(17, "green");

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(key_value.RemoveAll(22) == 0);

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt(7) == "blue");
  REQUIRE(key_value.ValueAt(3) == "gray");
  REQUIRE(key_value.ValueAt(9) == "purple");
  REQUIRE(key_value.ValueAt(5) == "yellow");
  REQUIRE(key_value.ValueAt(17) == "green");

  // test size
  REQUIRE(key_value.GetSize() == 5);
}

TEST_CASE(
    "KeyExists method returns true when key found and false when key not found "
    "for keys of type int and values of type string ",
    "[found]") {
  KeyValue<int, string, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, "blue");
  key_value.Add(3, "gray");
  key_value.Add(9, "purple");
  key_value.Add(5, "yellow");
  key_value.Add(17, "green");

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(!key_value.KeyExists(22));

  // test key and value are in the KeyValue container
  REQUIRE(key_value.KeyExists(7));
  REQUIRE(key_value.KeyExists(3));
  REQUIRE(key_value.KeyExists(9));
  REQUIRE(key_value.KeyExists(5));
  REQUIRE(key_value.KeyExists(17));

  // test size
  REQUIRE(key_value.GetSize() == 5);
}

TEST_CASE(
    "Empty method returns true when empty and false when not empty "
    "for keys of type int and values of type string ",
    "[empty]") {
  KeyValue<int, string, kSize> key_value;
  // add key value pairs to container

  REQUIRE(key_value.Empty());
  // test size
  REQUIRE(key_value.GetSize() == 0);
  key_value.Add(7, "green");
  REQUIRE(!key_value.Empty());
  // test size
  REQUIRE(key_value.GetSize() == 1);
  key_value.RemoveOne(7);
  REQUIRE(key_value.Empty());
  // test size
  REQUIRE(key_value.GetSize() == 0);
}

TEST_CASE(
    "Full method returns true when full and false when not full "
    "for keys of type int and values of type string "
    "Also, tests size method",
    "[full]") {
  KeyValue<int, string, kSize> key_value;
  // add key value pairs to container

  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 0);
  key_value.Add(7, "blue");
  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 1);
  key_value.Add(3, "gray");
  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 2);
  key_value.Add(9, "purple");
  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 3);
  key_value.Add(5, "yellow");
  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 4);
  key_value.Add(17, "green");
  REQUIRE(key_value.Full());
  REQUIRE(key_value.GetSize() == 5);
  key_value.RemoveOne(7);
  REQUIRE(!key_value.Full());
  // test size
  REQUIRE(key_value.GetSize() == 4);
}

TEST_CASE(
    "The << operator works and outputs key, space, value, carriage return for "
    "all elements in the KeyValue container "
    "for keys of type int and values of type string ") {
  KeyValue<int, string, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, "blue");
  key_value.Add(3, "gray");
  key_value.Add(9, "purple");
  key_value.Add(5, "yellow");
  key_value.Add(17, "green");
  REQUIRE(key_value.GetSize() == 5);
  // test <<size>>
  ofstream out("test_output.txt");
  out << key_value;
  out.close();

  ifstream in("test_output.txt");
  string line;
  getline(in, line);
  REQUIRE("7: blue" == line);
  getline(in, line);
  REQUIRE("3: gray" == line);
  getline(in, line);
  REQUIRE("9: purple");
  getline(in, line);
  REQUIRE("5: yellow" == line);
  getline(in, line);
  REQUIRE("17: green" == line);
  getline(in, line);
  REQUIRE("" == line);

  in.close();
}
TEST_CASE(
    "The << operator only prints out the valid keys and values,"
    "does not print out the entire arrays when not full. "
    "for keys of type int and values of type string") {
  KeyValue<int, string, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, "blue");
  key_value.Add(3, "gray");
  REQUIRE(key_value.GetSize() == 2);
  // test <<size>>
  ofstream out("test_output.txt");
  out << key_value;
  out.close();

  ifstream in("test_output.txt");
  string line;
  getline(in, line);
  REQUIRE("7: blue" == line);
  getline(in, line);
  REQUIRE("3: gray" == line);
  getline(in, line);
  REQUIRE("" == line);

  in.close();
}
//******************************int, Carton, 5******************************

TEST_CASE(
    "The << operator prints Cartons as Carton length x width x height with a "
    "precision of one digit after the decimal",
    "[insertion]") {
  // test size
  Carton one(22, 7, 19.38);
  Carton two(8, 20, 9.54);

  std::ofstream out("test.out");
  out << one << std::endl;
  out << two << std::endl;
  out.close();

  std::ifstream in("test.out");
  std::string line;
  getline(in, line);
  REQUIRE("Carton 22.0 x 7.0 x 19.4" == line);


  getline(in, line);
  REQUIRE("Carton 8.0 x 20.0 x 9.5" == line);

  getline(in, line);
  REQUIRE("" == line);
}

TEST_CASE(
    "Add method adds keys and values expected and ValueAt finds them"
    "for keys of type int and values of type Carton "
    "throws out_of_range exception when Add called after full",
    "[add][value]") {
  KeyValue<int, Carton, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, Carton(22, 7, 19.3));
  key_value.Add(3, Carton(16, 8, 20));
  key_value.Add(9, Carton(6, 8.5, 16));
  key_value.Add(5, Carton(14, 9.6, 12));
  key_value.Add(17, Carton(20.8, 12, 14.2));

  // test size
  REQUIRE(key_value.GetSize() == 5);

  // test key and value are in the KeyValue container
  REQUIRE(fabs(key_value.ValueAt(7).Volume() - 2972.2) < .1);
  REQUIRE(fabs(key_value.ValueAt(3).Volume() - 2560) < .1);
  REQUIRE(fabs(key_value.ValueAt(9).Volume() - 816) < .1);
  REQUIRE(fabs(key_value.ValueAt(5).Volume() - 1612.8) < .1);
  REQUIRE(fabs(key_value.ValueAt(17).Volume() - 3544.32) < .1);

  // add one after full, expect exception
  REQUIRE_THROWS_AS(key_value.Add(101, Carton(22, 7, 19.3)), out_of_range);
}

TEST_CASE(
    "Add method adds keys and values expected and ValueAt finds them"
    "for keys of type int and values of type Carton "
    "ValueAt method throws out_of_range when key not found",
    "[add][value]") {
  KeyValue<int, Carton, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, Carton(22, 7, 19.3));
  key_value.Add(3, Carton(16, 8, 20));
  key_value.Add(9, Carton(6, 8.5, 16));
  key_value.Add(5, Carton(14, 9.6, 12));
  key_value.Add(17, Carton(20.8, 12, 14.2));

  // test size
  REQUIRE(key_value.GetSize() == 5);

  // call ValueAt with key not used, expect exception
  REQUIRE_THROWS_AS(key_value.ValueAt(107), out_of_range);
}

TEST_CASE(
    "RemoveOne method removes key and value expected and returns true "
    "for keys of type int and values of type Carton",
    "[remove_one]") {
  KeyValue<int, Carton, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, Carton(22, 7, 19.3));
  key_value.Add(3, Carton(16, 8, 20));
  key_value.Add(7, Carton(6, 8.5, 16));
  key_value.Add(5, Carton(14, 9.6, 12));
  key_value.Add(7, Carton(20.8, 12, 14.2));

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(key_value.RemoveOne(7));

  // test key and value are in the KeyValue container
  REQUIRE(fabs(key_value.ValueAt(3).Volume() - 2560) < .1);
  REQUIRE(fabs(key_value.ValueAt(5).Volume() - 1612.8) < .1);

  // test size
  REQUIRE(key_value.GetSize() == 4);

  REQUIRE(key_value.RemoveOne(3));

  // test key and value are in the KeyValue container
  REQUIRE(key_value.GetSize() == 3);

  REQUIRE(key_value.RemoveOne(7));

  // test key and value are in the KeyValue container
  REQUIRE(fabs(key_value.ValueAt(5).Volume() - 1612.8) < .1);

  // test size
  REQUIRE(key_value.GetSize() == 2);

  REQUIRE(key_value.RemoveOne(7));

  // test key and value are in the KeyValue container
  REQUIRE(fabs(key_value.ValueAt(5).Volume() - 1612.8) < .1);

  // test size
  REQUIRE(key_value.GetSize() == 1);

  REQUIRE(key_value.RemoveOne(5));

  // test size
  REQUIRE(key_value.GetSize() == 0);

  REQUIRE(!key_value.RemoveOne(5));

  // test size
  REQUIRE(key_value.GetSize() == 0);
}
//*******************************
TEST_CASE(
    "RemoveOne method removes nothing and returns false when key not found "
    "for keys of type int and values of type Carton",
    "[remove_one]") {
  KeyValue<int, Carton, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, Carton(22, 7, 19.3));
  key_value.Add(3, Carton(16, 8, 20));
  key_value.Add(9, Carton(6, 8.5, 16));
  key_value.Add(5, Carton(14, 9.6, 12));
  key_value.Add(17, Carton(20.8, 12, 14.2));

  // test size before remove
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(!key_value.RemoveOne(28));

  // test size after remove
  REQUIRE(key_value.GetSize() == 5);

  // test key and value are in the KeyValue container
  REQUIRE(fabs(key_value.ValueAt(3).Volume() - 2560) < .1);
  REQUIRE(fabs(key_value.ValueAt(5).Volume() - 1612.8) < .1);
}

TEST_CASE(
    "RemoveOne method removes nothing and returns false container is empty "
    "for keys of type int and values of type Carton",
    "[remove_one]") {
  KeyValue<int, string, kSize> key_value;

  REQUIRE(!key_value.RemoveOne(7));

  // test size after remove
  REQUIRE(key_value.GetSize() == 0);
}

TEST_CASE(
    "RemoveAll method removes keys and values expected and returns number when "
    "key is found multiple times "
    "for keys of type int and values of type Carton ",
    "[remove_all]") {
  KeyValue<int, Carton, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, Carton(22, 7, 19.3));
  key_value.Add(3, Carton(16, 8, 20));
  key_value.Add(7, Carton(6, 8.5, 16));
  key_value.Add(5, Carton(14, 9.6, 12));
  key_value.Add(7, Carton(20.8, 12, 14.2));

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(key_value.RemoveAll(7) == 3);

  // test key and value are in the KeyValue container
  REQUIRE(fabs(key_value.ValueAt(3).Volume() - 2560) < .1);
  REQUIRE(fabs(key_value.ValueAt(5).Volume() - 1612.8) < .1);

  // test size
  REQUIRE(key_value.GetSize() == 2);
  REQUIRE_THROWS_AS(key_value.ValueAt(7), out_of_range);
}

TEST_CASE(
    "RemoveAll method removes keys and values expected and returns 1 when "
    "key is found one time "
    "for keys of type int and values of type Carton ",
    "[remove_all]") {
  KeyValue<int, Carton, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, Carton(22, 7, 19.3));
  key_value.Add(3, Carton(16, 8, 20));
  key_value.Add(7, Carton(6, 8.5, 16));
  key_value.Add(5, Carton(14, 9.6, 12));
  key_value.Add(7, Carton(20.8, 12, 14.2));

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(key_value.RemoveAll(5) == 1);

  // test key and value are in the KeyValue container
  REQUIRE(fabs(key_value.ValueAt(3).Volume() - 2560) < .1);
  REQUIRE_THROWS_AS(key_value.ValueAt(5), out_of_range);
  // test size
  REQUIRE(key_value.GetSize() == 4);
}

TEST_CASE(
    "RemoveAll method removes nothing and returns zero when key not found "
    "for keys of type int and values of type Carton ",
    "[remove_all]") {
  KeyValue<int, Carton, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, Carton(22, 7, 19.3));
  key_value.Add(3, Carton(16, 8, 20));
  key_value.Add(9, Carton(6, 8.5, 16));
  key_value.Add(5, Carton(14, 9.6, 12));
  key_value.Add(17, Carton(20.8, 12, 14.2));

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(key_value.RemoveAll(22) == 0);

  // test key and value are in the KeyValue container
  REQUIRE(fabs(key_value.ValueAt(7).Volume() - 2972.2) < .1);
  REQUIRE(fabs(key_value.ValueAt(3).Volume() - 2560) < .1);
  REQUIRE(fabs(key_value.ValueAt(9).Volume() - 816) < .1);
  REQUIRE(fabs(key_value.ValueAt(5).Volume() - 1612.8) < .1);
  REQUIRE(fabs(key_value.ValueAt(17).Volume() - 3544.32) < .1);

  // test size
  REQUIRE(key_value.GetSize() == 5);
}

TEST_CASE(
    "KeyExists method returns true when key found and false when key not found "
    "for keys of type int and values of type Carton ",
    "[found]") {
  KeyValue<int, Carton, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, Carton(22, 7, 19.3));
  key_value.Add(3, Carton(16, 8, 20));
  key_value.Add(9, Carton(6, 8.5, 16));
  key_value.Add(5, Carton(14, 9.6, 12));
  key_value.Add(17, Carton(20.8, 12, 14.2));

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(!key_value.KeyExists(22));

  // test key and value are in the KeyValue container
  REQUIRE(key_value.KeyExists(7));
  REQUIRE(key_value.KeyExists(3));
  REQUIRE(key_value.KeyExists(9));
  REQUIRE(key_value.KeyExists(5));
  REQUIRE(key_value.KeyExists(17));

  // test size
  REQUIRE(key_value.GetSize() == 5);
}

TEST_CASE(
    "Empty method returns true when empty and false when not empty "
    "for keys of type int and values of type Carton ",
    "[empty]") {
  KeyValue<int, Carton, kSize> key_value;
  // add key value pairs to container

  REQUIRE(key_value.Empty());
  // test size
  REQUIRE(key_value.GetSize() == 0);
  key_value.Add(7, Carton(6, 8.5, 16));
  REQUIRE(!key_value.Empty());
  // test size
  REQUIRE(key_value.GetSize() == 1);
  key_value.RemoveOne(7);
  REQUIRE(key_value.Empty());
  // test size
  REQUIRE(key_value.GetSize() == 0);
}

TEST_CASE(
    "Full method returns true when full and false when not full "
    "for keys of type int and values of type Carton "
    "Also, tests size method",
    "[full]") {
  KeyValue<int, Carton, kSize> key_value;

  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 0);
  key_value.Add(7, Carton(22, 7, 19.3));
  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 1);
  key_value.Add(3, Carton(16, 8, 20));
  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 2);
  key_value.Add(9, Carton(6, 8.5, 16));
  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 3);
  key_value.Add(5, Carton(14, 9.6, 12));
  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 4);
  key_value.Add(17, Carton(20.8, 12, 14.2));
  REQUIRE(key_value.Full());
  REQUIRE(key_value.GetSize() == 5);
  key_value.RemoveOne(7);
  REQUIRE(!key_value.Full());
  // test size
  REQUIRE(key_value.GetSize() == 4);
}

TEST_CASE(
    "The << operator works and outputs key, space, value, carriage return for "
    "all elements in the KeyValue container "
    "for keys of type int and values of type Carton ") {
  KeyValue<int, Carton, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, Carton(22, 7, 19.3));
  key_value.Add(3, Carton(16, 8, 20));
  key_value.Add(9, Carton(6, 8.5, 16));
  key_value.Add(5, Carton(14, 9.6, 12));
  key_value.Add(17, Carton(20.8, 12, 14.2));
  // test size
  REQUIRE(key_value.GetSize() == 5);

  // test <<
  ofstream out("test_output.txt");
  out << key_value;
  out.close();

  ifstream in("test_output.txt");
  string line;
  getline(in, line);
    REQUIRE("7: Carton 22.0 x 7.0 x 19.3" == line);

  getline(in, line);
    REQUIRE("3: Carton 16.0 x 8.0 x 20.0" == line);

  getline(in, line);
    REQUIRE("9: Carton 6.0 x 8.5 x 16.0" == line);

  getline(in, line);
    REQUIRE("5: Carton 14.0 x 9.6 x 12.0" == line);

  getline(in, line);
  REQUIRE("17: Carton 20.8 x 12.0 x 14.2" == line);

  getline(in, line);
  REQUIRE("" == line);

  in.close();
}
TEST_CASE(
    "The << operator only prints out the valid keys and values,"
    "does not print out the entire arrays when not full. "
    "for keys of type int and values of type Carton ") {
  KeyValue<int, Carton, kSize> key_value;
  // add key value pairs to container
  key_value.Add(7, Carton(22, 7, 19.3));
  key_value.Add(3, Carton(16, 8, 20));
  key_value.Add(9, Carton(6, 8.5, 16));
  key_value.Add(5, Carton(14, 9.6, 12));
  // test size
  REQUIRE(key_value.GetSize() == 4);

  // test <<
  ofstream out("test_output.txt");
  out << key_value;
  out.close();

  ifstream in("test_output.txt");
  string line;
  getline(in, line);
  REQUIRE("7: Carton 22.0 x 7.0 x 19.3" == line);

  getline(in, line);
  REQUIRE("3: Carton 16.0 x 8.0 x 20.0" == line);

  getline(in, line);
  REQUIRE("9: Carton 6.0 x 8.5 x 16.0" == line);

  getline(in, line);
  REQUIRE("5: Carton 14.0 x 9.6 x 12.0" == line);

  getline(in, line);
  REQUIRE("" == line);

  in.close();
}
//******************************string, int, 5******************************

TEST_CASE(
    "Add method adds keys and values expected and ValueAt finds them"
    "for keys of type string and values of type int "
    "throws out_of_range exception when Add called after full",
    "[add][value]") {
  KeyValue<string, int, kSize> key_value;
  // add key value pairs to container
  key_value.Add("John", 22);
  key_value.Add("Carol", 12);
  key_value.Add("Walter", 18);
  key_value.Add("Samantha", 91);
  key_value.Add("Kelly", 35);

  // test size
  REQUIRE(key_value.GetSize() == 5);

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt("John") == 22);
  REQUIRE(key_value.ValueAt("Carol") == 12);
  REQUIRE(key_value.ValueAt("Walter") == 18);
  REQUIRE(key_value.ValueAt("Samantha") == 91);
  REQUIRE(key_value.ValueAt("Kelly") == 35);

  // add one after full, expect exception
  REQUIRE_THROWS_AS(key_value.Add("Pat", 99), out_of_range);
}

TEST_CASE(
    "Add method adds keys and values expected and ValueAt finds them"
    "for keys of type string and values of type int "
    "ValueAt method throws out_of_range when key not found",
    "[add][value]") {
  KeyValue<string, int, kSize> key_value;
  // add key value pairs to container
  key_value.Add("John", 22);
  key_value.Add("Carol", 12);
  key_value.Add("Walter", 18);
  key_value.Add("Samantha", 91);
  key_value.Add("Kelly", 35);

  // test size
  REQUIRE(key_value.GetSize() == 5);

  // call ValueAt with key not used, expect exception
  REQUIRE_THROWS_AS(key_value.ValueAt("Pat"), out_of_range);
}

TEST_CASE(
    "RemoveOne method removes key and value expected and returns true "
    "for keys of type string and values of type int",
    "[remove_one]") {
  KeyValue<string, int, kSize> key_value;
  // add key value pairs to container
  key_value.Add("John", 22);
  key_value.Add("Carol", 12);
  key_value.Add("John", 18);
  key_value.Add("Samantha", 91);
  key_value.Add("John", 35);

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(key_value.RemoveOne("John"));

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt("Carol") == 12);
  REQUIRE(key_value.ValueAt("Samantha") == 91);

  // test size
  REQUIRE(key_value.GetSize() == 4);

  REQUIRE(key_value.RemoveOne("Carol"));

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt("Samantha") == 91);

  // test size
  REQUIRE(key_value.GetSize() == 3);

  REQUIRE(key_value.RemoveOne("John"));

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt("Samantha") == 91);

  // test size
  REQUIRE(key_value.GetSize() == 2);

  REQUIRE(key_value.RemoveOne("John"));

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt("Samantha") == 91);

  // test size
  REQUIRE(key_value.GetSize() == 1);

  REQUIRE(key_value.RemoveOne("Samantha"));

  // test size
  REQUIRE(key_value.GetSize() == 0);

  REQUIRE(!key_value.RemoveOne("Samantha"));

  // test size
  REQUIRE(key_value.GetSize() == 0);
}

TEST_CASE(
    "RemoveOne method removes nothing and returns false when key not found "
    "for keys of type string and values of type int",
    "[remove_one]") {
  KeyValue<string, int, kSize> key_value;
  // add key value pairs to container
  key_value.Add("John", 22);
  key_value.Add("Carol", 12);
  key_value.Add("John", 18);
  key_value.Add("Samantha", 91);
  key_value.Add("John", 35);

  // test size before remove
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(!key_value.RemoveOne("Pat"));

  // test size after remove
  REQUIRE(key_value.GetSize() == 5);

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt("Carol") == 12);
  REQUIRE(key_value.ValueAt("Samantha") == 91);
}

TEST_CASE(
    "RemoveOne method removes nothing and returns false container is empty "
    "for keys of type string and values of type int",
    "[remove_one]") {
  KeyValue<string, int, kSize> key_value;

  REQUIRE(!key_value.RemoveOne("John"));

  // test size after remove
  REQUIRE(key_value.GetSize() == 0);
}

TEST_CASE(
    "RemoveAll method removes keys and values expected and returns number when "
    "key is found multiple times "
    "for keys of type string and values of type int ",
    "[remove_all]") {
  KeyValue<string, int, kSize> key_value;
  // add key value pairs to container
  key_value.Add("John", 22);
  key_value.Add("Carol", 12);
  key_value.Add("John", 18);
  key_value.Add("Samantha", 91);
  key_value.Add("John", 35);

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(key_value.RemoveAll("John") == 3);

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt("Carol") == 12);
  REQUIRE(key_value.ValueAt("Samantha") == 91);

  // test size
  REQUIRE(key_value.GetSize() == 2);
  REQUIRE_THROWS_AS(key_value.ValueAt("John"), out_of_range);
}

TEST_CASE(
    "RemoveAll method removes keys and values expected and returns 1 when "
    "key is found one time "
    "for keys of type string and values of type int ",
    "[remove_all]") {
  KeyValue<string, int, kSize> key_value;
  // add key value pairs to container
  key_value.Add("John", 22);
  key_value.Add("Carol", 12);
  key_value.Add("John", 18);
  key_value.Add("Samantha", 91);
  key_value.Add("John", 35);

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(key_value.RemoveAll("Samantha") == 1);

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt("Carol") == 12);
  REQUIRE_THROWS_AS(key_value.ValueAt("Samantha"), out_of_range);
  // test size
  REQUIRE(key_value.GetSize() == 4);
}

TEST_CASE(
    "RemoveAll method removes nothing and returns zero when key not found "
    "for keys of type string and values of type int ",
    "[remove_all]") {
  KeyValue<string, int, kSize> key_value;
  // add key value pairs to container
  key_value.Add("John", 22);
  key_value.Add("Carol", 12);
  key_value.Add("Walter", 18);
  key_value.Add("Samantha", 91);
  key_value.Add("Kelly", 35);

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(key_value.RemoveAll("Kim") == 0);

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt("John") == 22);
  REQUIRE(key_value.ValueAt("Carol") == 12);
  REQUIRE(key_value.ValueAt("Walter") == 18);
  REQUIRE(key_value.ValueAt("Samantha") == 91);
  REQUIRE(key_value.ValueAt("Kelly") == 35);

  // test size
  REQUIRE(key_value.GetSize() == 5);
}

TEST_CASE(
    "KeyExists method returns true when key found and false when key not found "
    "for keys of type string and values of type int ",
    "[found]") {
  KeyValue<string, int, kSize> key_value;
  // add key value pairs to container
  key_value.Add("John", 22);
  key_value.Add("Carol", 12);
  key_value.Add("Walter", 18);
  key_value.Add("Samantha", 91);
  key_value.Add("Kelly", 35);

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(!key_value.KeyExists("Kim"));

  // test key and value are in the KeyValue container
  REQUIRE(key_value.KeyExists("John"));
  REQUIRE(key_value.KeyExists("Carol"));
  REQUIRE(key_value.KeyExists("Walter"));
  REQUIRE(key_value.KeyExists("Samantha"));
  REQUIRE(key_value.KeyExists("Kelly"));

  // test size
  REQUIRE(key_value.GetSize() == 5);
}

TEST_CASE(
    "Empty method returns true when empty and false when not empty "
    "for keys of type string and values of type int ",
    "[empty]") {
  KeyValue<string, int, kSize> key_value;
  // add key value pairs to container

  REQUIRE(key_value.Empty());
  // test size
  REQUIRE(key_value.GetSize() == 0);
  key_value.Add("John", 22);
  REQUIRE(!key_value.Empty());
  // test size
  REQUIRE(key_value.GetSize() == 1);
  key_value.RemoveOne("John");
  REQUIRE(key_value.Empty());
  // test size
  REQUIRE(key_value.GetSize() == 0);
}

TEST_CASE(
    "Full method returns true when full and false when not full "
    "for keys of type string and values of type int "
    "Also, tests size method",
    "[full]") {
  KeyValue<string, int, kSize> key_value;
  // add key value pairs to container

  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 0);
  key_value.Add("John", 22);
  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 1);
  key_value.Add("Carol", 12);
  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 2);
  key_value.Add("Walter", 18);
  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 3);
  key_value.Add("Samantha", 91);
  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 4);
  key_value.Add("Kelly", 35);
  REQUIRE(key_value.Full());
  REQUIRE(key_value.GetSize() == 5);
  key_value.RemoveOne("John");
  REQUIRE(!key_value.Full());
  // test size
  REQUIRE(key_value.GetSize() == 4);
}

TEST_CASE(
    "The << operator works and outputs key, space, value, carriage return for "
    "all elements in the KeyValue container "
    "for keys of type string and values of type int ") {
  KeyValue<string, int, kSize> key_value;
  // add key value pairs to container
  key_value.Add("John", 22);
  key_value.Add("Carol", 12);
  key_value.Add("Walter", 18);
  key_value.Add("Samantha", 91);
  key_value.Add("Kelly", 35);
  REQUIRE(key_value.GetSize() == 5);
  // test <<size>>
  ofstream out("test_output.txt");
  out << key_value;
  out.close();

  ifstream in("test_output.txt");
  string line;
  getline(in, line);
  REQUIRE("John: 22" == line);
  getline(in, line);
  REQUIRE("Carol: 12" == line);
  getline(in, line);
  REQUIRE("Walter: 18");
  getline(in, line);
  REQUIRE("Samantha: 91" == line);
  getline(in, line);
  REQUIRE("Kelly: 35" == line);
  getline(in, line);
  REQUIRE("" == line);

  in.close();
}
TEST_CASE(
    "The << operator only prints out the valid keys and values,"
    "does not print out the entire arrays when not full. "
    "for keys of type string and values of type int ") {
  KeyValue<string, int, kSize> key_value;
  // add key value pairs to container
  key_value.Add("John", 22);
  key_value.Add("Carol", 12);
  key_value.Add("Walter", 18);
  key_value.Add("Samantha", 91);
  REQUIRE(key_value.GetSize() == 4);
  // test <<size>>
  ofstream out("test_output.txt");
  out << key_value;
  out.close();

  ifstream in("test_output.txt");
  string line;
  getline(in, line);
  REQUIRE("John: 22" == line);
  getline(in, line);
  REQUIRE("Carol: 12" == line);
  getline(in, line);
  REQUIRE("Walter: 18");
  getline(in, line);
  REQUIRE("Samantha: 91" == line);
  getline(in, line);
  REQUIRE("" == line);

  in.close();
}
//******************************string, string, 5******************************

TEST_CASE(
    "Add method adds keys and values expected and ValueAt finds them"
    "for keys of type string and values of type string "
    "throws out_of_range exception when Add called after full",
    "[add][value]") {
  KeyValue<string, string, kSize> key_value;
  // add key value pairs to container
  key_value.Add("John", "blue");
  key_value.Add("Carol", "gray");
  key_value.Add("Walter", "purple");
  key_value.Add("Samantha", "yellow");
  key_value.Add("Kelly", "green");

  // test size
  REQUIRE(key_value.GetSize() == 5);

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt("John") == "blue");
  REQUIRE(key_value.ValueAt("Carol") == "gray");
  REQUIRE(key_value.ValueAt("Walter") == "purple");
  REQUIRE(key_value.ValueAt("Samantha") == "yellow");
  REQUIRE(key_value.ValueAt("Kelly") == "green");

  // add one after full, expect exception
  REQUIRE_THROWS_AS(key_value.Add("Pat", "orange"), out_of_range);
}

TEST_CASE(
    "Add method adds keys and values expected and ValueAt finds them"
    "for keys of type string and values of type string "
    "ValueAt method throws out_of_range when key not found",
    "[add][value]") {
  KeyValue<string, string, kSize> key_value;
  // add key value pairs to container
  key_value.Add("John", "blue");
  key_value.Add("Carol", "gray");
  key_value.Add("Walter", "purple");
  key_value.Add("Samantha", "yellow");
  key_value.Add("Kelly", "green");

  // test size
  REQUIRE(key_value.GetSize() == 5);

  // call ValueAt with key not used, expect exception
  REQUIRE_THROWS_AS(key_value.ValueAt("Pat"), out_of_range);
}

TEST_CASE(
    "RemoveOne method removes key and value expected and returns true "
    "for keys of type string and values of type string",
    "[remove_one]") {
  KeyValue<string, string, kSize> key_value;
  // add key value pairs to container
  key_value.Add("John", "blue");
  key_value.Add("Carol", "gray");
  key_value.Add("John", "purple");
  key_value.Add("Samantha", "yellow");
  key_value.Add("John", "green");

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(key_value.RemoveOne("John"));

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt("Carol") == "gray");
  REQUIRE(key_value.ValueAt("Samantha") == "yellow");

  // test size
  REQUIRE(key_value.GetSize() == 4);

  REQUIRE(key_value.RemoveOne("Carol"));

  // test key and value are in the KeyValue container
  REQUIRE(key_value.GetSize() == 3);

  REQUIRE(key_value.RemoveOne("John"));

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt("Samantha") == "yellow");

  // test size
  REQUIRE(key_value.GetSize() == 2);

  REQUIRE(key_value.RemoveOne("John"));

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt("Samantha") == "yellow");

  // test size
  REQUIRE(key_value.GetSize() == 1);

  REQUIRE(key_value.RemoveOne("Samantha"));

  // test size
  REQUIRE(key_value.GetSize() == 0);

  REQUIRE(!key_value.RemoveOne("Samantha"));

  // test size
  REQUIRE(key_value.GetSize() == 0);
}

TEST_CASE(
    "RemoveOne method removes nothing and returns false when key not found "
    "for keys of type string and values of type string",
    "[remove_one]") {
  KeyValue<string, string, kSize> key_value;
  // add key value pairs to container
  key_value.Add("John", "blue");
  key_value.Add("Carol", "gray");
  key_value.Add("Walter", "purple");
  key_value.Add("Samantha", "yellow");
  key_value.Add("Kelly", "green");

  // test size before remove
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(!key_value.RemoveOne("Pat"));

  // test size after remove
  REQUIRE(key_value.GetSize() == 5);

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt("John") == "blue");
  REQUIRE(key_value.ValueAt("Carol") == "gray");
  REQUIRE(key_value.ValueAt("Walter") == "purple");
  REQUIRE(key_value.ValueAt("Samantha") == "yellow");
  REQUIRE(key_value.ValueAt("Kelly") == "green");
}

TEST_CASE(
    "RemoveOne method removes nothing and returns false container is empty "
    "for keys of type string and values of type string",
    "[remove_one]") {
  KeyValue<string, string, kSize> key_value;

  REQUIRE(!key_value.RemoveOne("John"));

  // test size after remove
  REQUIRE(key_value.GetSize() == 0);
}

TEST_CASE(
    "RemoveAll method removes keys and values expected and returns number when "
    "key is found multiple times "
    "for keys of type string and values of type string ",
    "[remove_all]") {
  KeyValue<string, string, kSize> key_value;
  // add key value pairs to container
  key_value.Add("John", "blue");
  key_value.Add("Carol", "gray");
  key_value.Add("John", "purple");
  key_value.Add("Samantha", "yellow");
  key_value.Add("John", "green");

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(key_value.RemoveAll("John") == 3);

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt("Carol") == "gray");
  REQUIRE(key_value.ValueAt("Samantha") == "yellow");

  // test size
  REQUIRE(key_value.GetSize() == 2);
  REQUIRE_THROWS_AS(key_value.ValueAt("John"), out_of_range);
}

TEST_CASE(
    "RemoveAll method removes keys and values expected and returns 1 when "
    "key is found one time "
    "for keys of type string and values of type string ",
    "[remove_all]") {
  KeyValue<string, string, kSize> key_value;
  // add key value pairs to container
  key_value.Add("John", "blue");
  key_value.Add("Carol", "gray");
  key_value.Add("John", "purple");
  key_value.Add("Samantha", "yellow");
  key_value.Add("John", "green");

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(key_value.RemoveAll("Samantha") == 1);

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt("Carol") == "gray");
  REQUIRE_THROWS_AS(key_value.ValueAt("Samantha"), out_of_range);
  // test size
  REQUIRE(key_value.GetSize() == 4);
}

TEST_CASE(
    "RemoveAll method removes nothing and returns zero when key not found "
    "for keys of type string and values of type string ",
    "[remove_all]") {
  KeyValue<string, string, kSize> key_value;
  // add key value pairs to container
  key_value.Add("John", "blue");
  key_value.Add("Carol", "gray");
  key_value.Add("Walter", "purple");
  key_value.Add("Samantha", "yellow");
  key_value.Add("Kelly", "green");

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(key_value.RemoveAll("Pat") == 0);

  // test key and value are in the KeyValue container
  REQUIRE(key_value.ValueAt("John") == "blue");
  REQUIRE(key_value.ValueAt("Carol") == "gray");
  REQUIRE(key_value.ValueAt("Walter") == "purple");
  REQUIRE(key_value.ValueAt("Samantha") == "yellow");
  REQUIRE(key_value.ValueAt("Kelly") == "green");

  // test size
  REQUIRE(key_value.GetSize() == 5);
}

TEST_CASE(
    "KeyExists method returns true when key found and false when key not found "
    "for keys of type string and values of type string ",
    "[found]") {
  KeyValue<string, string, kSize> key_value;
  // add key value pairs to container
  key_value.Add("John", "blue");
  key_value.Add("Carol", "gray");
  key_value.Add("Walter", "purple");
  key_value.Add("Samantha", "yellow");
  key_value.Add("Kelly", "green");

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(!key_value.KeyExists("Pat"));

  // test key and value are in the KeyValue container
  REQUIRE(key_value.KeyExists("John"));
  REQUIRE(key_value.KeyExists("Carol"));
  REQUIRE(key_value.KeyExists("Walter"));
  REQUIRE(key_value.KeyExists("Samantha"));
  REQUIRE(key_value.KeyExists("Kelly"));

  // test size
  REQUIRE(key_value.GetSize() == 5);
}

TEST_CASE(
    "Empty method returns true when empty and false when not empty "
    "for keys of type string and values of type string ",
    "[empty]") {
  KeyValue<string, string, kSize> key_value;
  // add key value pairs to container

  REQUIRE(key_value.Empty());
  // test size
  REQUIRE(key_value.GetSize() == 0);
  key_value.Add("John", "green");
  REQUIRE(!key_value.Empty());
  // test size
  REQUIRE(key_value.GetSize() == 1);
  key_value.RemoveOne("John");
  REQUIRE(key_value.Empty());
  // test size
  REQUIRE(key_value.GetSize() == 0);
}

TEST_CASE(
    "Full method returns true when full and false when not full "
    "for keys of type string and values of type string "
    "Also, tests size method",
    "[full]") {
  KeyValue<string, string, kSize> key_value;
  // add key value pairs to container

  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 0);
  key_value.Add("John", "blue");
  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 1);
  key_value.Add("Carol", "gray");
  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 2);
  key_value.Add("Walter", "purple");
  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 3);
  key_value.Add("Samantha", "yellow");
  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 4);
  key_value.Add("Kelly", "green");
  REQUIRE(key_value.Full());
  REQUIRE(key_value.GetSize() == 5);
  key_value.RemoveOne("John");
  REQUIRE(!key_value.Full());
  // test size
  REQUIRE(key_value.GetSize() == 4);
}

TEST_CASE(
    "The << operator works and outputs key, space, value, carriage return for "
    "all elements in the KeyValue container "
    "for keys of type string and values of type string ",
    "[remove_all]") {
  KeyValue<string, string, kSize> key_value;
  // add key value pairs to container
  key_value.Add("John", "blue");
  key_value.Add("Carol", "gray");
  key_value.Add("Walter", "purple");
  key_value.Add("Samantha", "yellow");
  key_value.Add("Kelly", "green");
  REQUIRE(key_value.GetSize() == 5);
  // test <<size>>
  ofstream out("test_output.txt");
  out << key_value;
  out.close();

  ifstream in("test_output.txt");
  string line;
  getline(in, line);
  REQUIRE("John: blue" == line);
  getline(in, line);
  REQUIRE("Carol: gray" == line);
  getline(in, line);
  REQUIRE("Walter: purple");
  getline(in, line);
  REQUIRE("Samantha: yellow" == line);
  getline(in, line);
  REQUIRE("Kelly: green" == line);
  getline(in, line);
  REQUIRE("" == line);

  in.close();
}
TEST_CASE(
    "The << operator only prints out the valid keys and values,"
    "does not print out the entire arrays when not full. "
    "for keys of type string and values of type string ") {
  KeyValue<string, string, kSize> key_value;
  // add key value pairs to container
  key_value.Add("John", "blue");
  key_value.Add("Carol", "gray");
  key_value.Add("Walter", "purple");
  key_value.Add("Samantha", "yellow");
  REQUIRE(key_value.GetSize() == 4);
  // test <<size>>
  ofstream out("test_output.txt");
  out << key_value;
  out.close();

  ifstream in("test_output.txt");
  string line;
  getline(in, line);
  REQUIRE("John: blue" == line);
  getline(in, line);
  REQUIRE("Carol: gray" == line);
  getline(in, line);
  REQUIRE("Walter: purple");
  getline(in, line);
  REQUIRE("Samantha: yellow" == line);
  getline(in, line);
  REQUIRE("" == line);

  in.close();
}

//******************************string, Carton, 5******************************

TEST_CASE(
    "Add method adds keys and values expected and ValueAt finds them"
    "for keys of type string and values of type Carton "
    "throws out_of_range exception when Add called after full",
    "[add][value]") {
  KeyValue<string, Carton, kSize> key_value;
  // add key value pairs to container
  key_value.Add("SLC", Carton(22, 7, 19.3));
  key_value.Add("Ogden", Carton(16, 8, 20));
  key_value.Add("Layton", Carton(6, 8.5, 16));
  key_value.Add("Roy", Carton(14, 9.6, 12));
  key_value.Add("Taylor", Carton(20.8, 12, 14.2));

  // test size
  REQUIRE(key_value.GetSize() == 5);

  // test key and value are in the KeyValue container
  REQUIRE(fabs(key_value.ValueAt("SLC").Volume() - 2972.2) < .1);
  REQUIRE(fabs(key_value.ValueAt("Ogden").Volume() - 2560) < .1);
  REQUIRE(fabs(key_value.ValueAt("Layton").Volume() - 816) < .1);
  REQUIRE(fabs(key_value.ValueAt("Roy").Volume() - 1612.8) < .1);
  REQUIRE(fabs(key_value.ValueAt("Taylor").Volume() - 3544.32) < .1);

  // add one after full, expect exception
  REQUIRE_THROWS_AS(key_value.Add("Willard", Carton(22, 7, 19.3)),
                    out_of_range);
}

TEST_CASE(
    "Add method adds keys and values expected and ValueAt finds them"
    "for keys of type string and values of type Carton "
    "ValueAt method throws out_of_range when key not found",
    "[add][value]") {
  KeyValue<string, Carton, kSize> key_value;
  // add key value pairs to container
  key_value.Add("SLC", Carton(22, 7, 19.3));
  key_value.Add("Ogden", Carton(16, 8, 20));
  key_value.Add("Layton", Carton(6, 8.5, 16));
  key_value.Add("Roy", Carton(14, 9.6, 12));
  key_value.Add("Taylor", Carton(20.8, 12, 14.2));

  // test size
  REQUIRE(key_value.GetSize() == 5);

  // call ValueAt with key not used, expect exception
  REQUIRE_THROWS_AS(key_value.ValueAt("Willard"), out_of_range);
}

TEST_CASE(
    "RemoveOne method removes key and value expected and returns true "
    "for keys of type string and values of type Carton",
    "[remove_one]") {
  KeyValue<string, Carton, kSize> key_value;
  // add key value pairs to container
  key_value.Add("SLC", Carton(22, 7, 19.3));
  key_value.Add("Ogden", Carton(16, 8, 20));
  key_value.Add("SLC", Carton(6, 8.5, 16));
  key_value.Add("Roy", Carton(14, 9.6, 12));
  key_value.Add("SLC", Carton(20.8, 12, 14.2));

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(key_value.RemoveOne("SLC"));

  // test key and value are in the KeyValue container
  REQUIRE(fabs(key_value.ValueAt("Ogden").Volume() - 2560) < .1);
  REQUIRE(fabs(key_value.ValueAt("Roy").Volume() - 1612.8) < .1);

  // test size
  REQUIRE(key_value.GetSize() == 4);

  REQUIRE(key_value.RemoveOne("Ogden"));

  // test key and value are in the KeyValue container
  REQUIRE(key_value.GetSize() == 3);

  REQUIRE(key_value.RemoveOne("SLC"));

  // test key and value are in the KeyValue container
  REQUIRE(fabs(key_value.ValueAt("Roy").Volume() - 1612.8) < .1);

  // test size
  REQUIRE(key_value.GetSize() == 2);

  REQUIRE(key_value.RemoveOne("SLC"));

  // test key and value are in the KeyValue container
  REQUIRE(fabs(key_value.ValueAt("Roy").Volume() - 1612.8) < .1);

  // test size
  REQUIRE(key_value.GetSize() == 1);

  REQUIRE(key_value.RemoveOne("Roy"));

  // test size
  REQUIRE(key_value.GetSize() == 0);

  REQUIRE(!key_value.RemoveOne("Roy"));

  // test size
  REQUIRE(key_value.GetSize() == 0);
}
//*******************************
TEST_CASE(
    "RemoveOne method removes nothing and returns false when key not found "
    "for keys of type string and values of type Carton",
    "[remove_one]") {
  KeyValue<string, Carton, kSize> key_value;
  // add key value pairs to container
  key_value.Add("SLC", Carton(22, 7, 19.3));
  key_value.Add("Ogden", Carton(16, 8, 20));
  key_value.Add("Layton", Carton(6, 8.5, 16));
  key_value.Add("Roy", Carton(14, 9.6, 12));
  key_value.Add("Taylor", Carton(20.8, 12, 14.2));

  // test size before remove
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(!key_value.RemoveOne("Willard"));

  // test size after remove
  REQUIRE(key_value.GetSize() == 5);

  // test key and value are in the KeyValue container
  REQUIRE(fabs(key_value.ValueAt("Ogden").Volume() - 2560) < .1);
  REQUIRE(fabs(key_value.ValueAt("Roy").Volume() - 1612.8) < .1);
}

TEST_CASE(
    "RemoveOne method removes nothing and returns false container is empty "
    "for keys of type string and values of type Carton",
    "[remove_one]") {
  KeyValue<string, string, kSize> key_value;

  REQUIRE(!key_value.RemoveOne("SLC"));

  // test size after remove
  REQUIRE(key_value.GetSize() == 0);
}

TEST_CASE(
    "RemoveAll method removes keys and values expected and returns number when "
    "key is found multiple times "
    "for keys of type string and values of type Carton ",
    "[remove_all]") {
  KeyValue<string, Carton, kSize> key_value;
  // add key value pairs to container
  key_value.Add("SLC", Carton(22, 7, 19.3));
  key_value.Add("Ogden", Carton(16, 8, 20));
  key_value.Add("SLC", Carton(6, 8.5, 16));
  key_value.Add("Roy", Carton(14, 9.6, 12));
  key_value.Add("SLC", Carton(20.8, 12, 14.2));

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(key_value.RemoveAll("SLC") == 3);

  // test key and value are in the KeyValue container
  REQUIRE(fabs(key_value.ValueAt("Ogden").Volume() - 2560) < .1);
  REQUIRE(fabs(key_value.ValueAt("Roy").Volume() - 1612.8) < .1);

  // test size
  REQUIRE(key_value.GetSize() == 2);
  REQUIRE_THROWS_AS(key_value.ValueAt("SLC"), out_of_range);
}

TEST_CASE(
    "RemoveAll method removes keys and values expected and returns 1 when "
    "key is found one time "
    "for keys of type string and values of type Carton ",
    "[remove_all]") {
  KeyValue<string, Carton, kSize> key_value;
  // add key value pairs to container
  key_value.Add("SLC", Carton(22, 7, 19.3));
  key_value.Add("Ogden", Carton(16, 8, 20));
  key_value.Add("SLC", Carton(6, 8.5, 16));
  key_value.Add("Roy", Carton(14, 9.6, 12));
  key_value.Add("SLC", Carton(20.8, 12, 14.2));

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(key_value.RemoveAll("Roy") == 1);

  // test key and value are in the KeyValue container
  REQUIRE(fabs(key_value.ValueAt("Ogden").Volume() - 2560) < .1);
  REQUIRE_THROWS_AS(key_value.ValueAt("Roy"), out_of_range);
  // test size
  REQUIRE(key_value.GetSize() == 4);
}

TEST_CASE(
    "RemoveAll method removes nothing and returns zero when key not found "
    "for keys of type string and values of type Carton ",
    "[remove_all]") {
  KeyValue<string, Carton, kSize> key_value;
  // add key value pairs to container
  key_value.Add("SLC", Carton(22, 7, 19.3));
  key_value.Add("Ogden", Carton(16, 8, 20));
  key_value.Add("Layton", Carton(6, 8.5, 16));
  key_value.Add("Roy", Carton(14, 9.6, 12));
  key_value.Add("Taylor", Carton(20.8, 12, 14.2));

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(key_value.RemoveAll("Willard") == 0);

  // test key and value are in the KeyValue container
  REQUIRE(fabs(key_value.ValueAt("SLC").Volume() - 2972.2) < .1);
  // Carton(22, 7, 19.3));  2972.2
  REQUIRE(fabs(key_value.ValueAt("Ogden").Volume() - 2560) < .1);
  // Carton(16, 8, 20));  2560
  REQUIRE(fabs(key_value.ValueAt("Layton").Volume() - 816) < .1);
  // Carton(6, 8.5, 16)); 816
  REQUIRE(fabs(key_value.ValueAt("Roy").Volume() - 1612.8) < .1);
  // Carton(14, 9.6, 12));  1612.8
  REQUIRE(fabs(key_value.ValueAt("Taylor").Volume() - 3544.32) < .1);
  // Carton(20.8, 12, 14.2));  3544.32

  // test size
  REQUIRE(key_value.GetSize() == 5);
}

TEST_CASE(
    "KeyExists method returns true when key found and false when key not found "
    "for keys of type string and values of type Carton ",
    "[found]") {
  KeyValue<string, Carton, kSize> key_value;
  // add key value pairs to container
  key_value.Add("SLC", Carton(22, 7, 19.3));
  key_value.Add("Ogden", Carton(16, 8, 20));
  key_value.Add("Layton", Carton(6, 8.5, 16));
  key_value.Add("Roy", Carton(14, 9.6, 12));
  key_value.Add("Taylor", Carton(20.8, 12, 14.2));

  // test size
  REQUIRE(key_value.GetSize() == 5);

  REQUIRE(!key_value.KeyExists("Willard"));

  // test key and value are in the KeyValue container
  REQUIRE(key_value.KeyExists("SLC"));
  REQUIRE(key_value.KeyExists("Ogden"));
  REQUIRE(key_value.KeyExists("Layton"));
  REQUIRE(key_value.KeyExists("Roy"));
  REQUIRE(key_value.KeyExists("Taylor"));

  // test size
  REQUIRE(key_value.GetSize() == 5);
}

TEST_CASE(
    "Empty method returns true when empty and false when not empty "
    "for keys of type string and values of type Carton ",
    "[empty]") {
  KeyValue<string, Carton, kSize> key_value;
  // add key value pairs to container

  REQUIRE(key_value.Empty());
  // test size
  REQUIRE(key_value.GetSize() == 0);
  key_value.Add("SLC", Carton(6, 8.5, 16));
  REQUIRE(!key_value.Empty());
  // test size
  REQUIRE(key_value.GetSize() == 1);
  key_value.RemoveOne("SLC");
  REQUIRE(key_value.Empty());
  // test size
  REQUIRE(key_value.GetSize() == 0);
}

TEST_CASE(
    "Full method returns true when full and false when not full "
    "for keys of type string and values of type Carton "
    "Also, tests size method",
    "[full]") {
  KeyValue<string, Carton, kSize> key_value;

  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 0);
  key_value.Add("SLC", Carton(22, 7, 19.3));
  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 1);
  key_value.Add("Ogden", Carton(16, 8, 20));
  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 2);
  key_value.Add("Layton", Carton(6, 8.5, 16));
  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 3);
  key_value.Add("Roy", Carton(14, 9.6, 12));
  REQUIRE(!key_value.Full());
  REQUIRE(key_value.GetSize() == 4);
  key_value.Add("Taylor", Carton(20.8, 12, 14.2));
  REQUIRE(key_value.Full());
  REQUIRE(key_value.GetSize() == 5);
  key_value.RemoveOne("SLC");
  REQUIRE(!key_value.Full());
  // test size
  REQUIRE(key_value.GetSize() == 4);
}

TEST_CASE(
    "The << operator works and outputs key, space, value, carriage return for "
    "all elements in the KeyValue container "
    "for keys of type string and values of type Carton ") {
  KeyValue<string, Carton, kSize> key_value;
  // add key value pairs to container
  key_value.Add("SLC", Carton(22, 7, 19.3));
  key_value.Add("Ogden", Carton(16, 8, 20));
  key_value.Add("Layton", Carton(6, 8.5, 16));
  key_value.Add("Roy", Carton(14, 9.6, 12));
  key_value.Add("Taylor", Carton(20.8, 12, 14.2));
  // test size
  REQUIRE(key_value.GetSize() == 5);

  // test <<
  ofstream out("test_output.txt");
  out << key_value;
  out.close();

  ifstream in("test_output.txt");
  string line;
  getline(in, line);
  REQUIRE("SLC: Carton 22.0 x 7.0 x 19.3" == line);

  getline(in, line);
  REQUIRE("Ogden: Carton 16.0 x 8.0 x 20.0" == line);

  getline(in, line);
  REQUIRE("Layton: Carton 6.0 x 8.5 x 16.0" == line);

  getline(in, line);
  REQUIRE("Roy: Carton 14.0 x 9.6 x 12.0" == line);

  getline(in, line);
  REQUIRE("Taylor: Carton 20.8 x 12.0 x 14.2" == line);

  getline(in, line);
  REQUIRE("" == line);

  in.close();
}

TEST_CASE(
    "The << operator only prints out the valid keys and values,"
    "does not print out the entire arrays when not full. "
    "for keys of type string and values of type Carton ") {
  KeyValue<string, Carton, kSize> key_value;
  // add key value pairs to container
  key_value.Add("SLC", Carton(22, 7, 19.3));
  key_value.Add("Ogden", Carton(16, 8, 20));
  key_value.Add("Layton", Carton(6, 8.5, 16));
  // test size
  REQUIRE(key_value.GetSize() == 3);

  // test <<
  ofstream out("test_output.txt");
  out << key_value;
  out.close();

  ifstream in("test_output.txt");
  string line;
  getline(in, line);
  REQUIRE("SLC: Carton 22.0 x 7.0 x 19.3" == line);

  getline(in, line);
  REQUIRE("Ogden: Carton 16.0 x 8.0 x 20.0" == line);

  getline(in, line);
  REQUIRE("Layton: Carton 6.0 x 8.5 x 16.0" == line);

  getline(in, line);
  REQUIRE("" == line);

  in.close();
}
