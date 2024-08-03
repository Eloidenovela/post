#include "server.hpp"

int main(int argc, char** argv) {
    try {
        server::run();
    } catch (const std::exception & e) {
        CROW_LOG_ERROR << e.what();    
    }
                                                                 
    return 0;
}
