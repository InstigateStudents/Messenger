#include "client.hpp"
#include "server.hpp"

int main() {
try{
    Server serv;
    sleep(10);
    Client cl("Gev");
    }
    catch(...) {
        std::cout << "exception is catched" <<std::endl;
    }
    while (true);

    std::cout << "return 0" << std::endl;
    return 0;
}
