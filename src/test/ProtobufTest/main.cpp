#include <iostream>
#include <unistd.h>
#include <example/example.pb.h>

int main() {

    raptor::protobuf::Person person;
    person.set_name("tesasasat");
    person.set_id(111);
    person.set_email("john.doe@example.com");
    std::string serialized;
    person.SerializeToString(&serialized);

    std::cout << "Serialized Message: " << serialized << std::endl;

    return 0;
}
