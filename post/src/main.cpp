#include <iostream>
#include <crow.h>
#include "model/all.hpp"
#include "service/user.hpp"

int main(int argc, char** argv) {
    auto storage = model::get_storage();

    service::user user_service {storage};

    return 0;
}
