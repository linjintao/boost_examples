#include <iostream>
using namespace std;

void say_hello(const char* name) {
    cout << "Hello " << name << "!\n";
}

#include <boost/python.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
using namespace boost::python;


struct World
{
    World(std::string msg): msg(msg) {} // added constructor
    void set(std::string msg) { this->msg = msg; }
    std::string visitFriend(World& w) {
      return w.msg;
    }
    World(const World& w) {
      printf("Copy constructor!\n");
    }

    std::string greet() { return msg; }
    std::string msg;
};

BOOST_PYTHON_MODULE(hello) {
    def("say_hello", say_hello);

    class_<World>("World", init<std::string>())
      .def("greet", &World::greet)
      .def("set", &World::set)
      .def("visitFriend", &World::visitFriend)
      ;
}




