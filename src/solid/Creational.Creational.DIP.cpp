// DEPENDENCY INVERSE PRINCIPEL

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

// A. High-level modules should not depend on low-level modules.
//    Both should depend on abstractions.
// B. Abstractions should not depend on details. 
//    Details should depend on abstractions.


// Relationship's types
enum class Relationship {
  parent,
  child,
  sibling
};

// An object type have relations
struct Person {
  string name;
};

// this is a interface for Person relationships
struct RelationshipBrowser {
  virtual vector<Person> find_all_children_of(const string& name) = 0;
};

// low-level, implementation
struct Relationships : RelationshipBrowser  {

  // A vector to save all relationships between persons
  vector<tuple<Person, Relationship, Person>> relations;

// this method add 2 relationships between two personswith each type
  void add_parent_and_child(const Person& parent, const Person& child) {
    relations.push_back({parent, Relationship::parent, child});
    relations.push_back({child, Relationship::child, parent});
  }

// Method to find a relationships by Person's name
  vector<Person> find_all_children_of(const string &name) override {
    vector<Person> result;
    for (auto&& [first, rel, second] : relations) {
      if (first.name == name && rel == Relationship::parent) {
        result.push_back(second);
      }
    }
    return result;
  }
};

 // high-level: A component client that use the relationship component
 // this depend on the interface, not on the implemntation directly
struct Research {
  Research(RelationshipBrowser& browser) {
    for (auto& child : browser.find_all_children_of("John")) {
      cout << "John has a child called " << child.name << endl;
    }
  }

//  Research(const Relationships& relationships)
//  {
//    auto& relations = relationships.relations;
//    for (auto&& [first, rel, second] : relations)
//    {
//      if (first.name == "John" && rel == Relationship::parent)
//      {
//        cout << "John has a child called " << second.name << endl;
//      }
//    }
//  }
};

int main()
{
  // we create 3 Person objects
  Person parent{"John"};
  Person child1{"Chris"};
  Person child2{"Matt"};

  // add th relationships
  Relationships relationships;
  relationships.add_parent_and_child(parent, child1);
  relationships.add_parent_and_child(parent, child2);

  // use the component
  Research _(relationships);

  return 0;
}