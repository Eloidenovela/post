#include <iostream>
#include <crow.h>
#include <memory>
#include <regex>
#include "model/all.hpp"
#include "model/editor.hpp"
#include "model/user.hpp"
#include "service/editor.hpp"
#include "service/user.hpp"
#include "sqlite_orm/sqlite_orm.h"
#include "util/time.hpp"
#include "util/util.hpp"

int main(int argc, char** argv) {
    auto storage = model::get_storage();

    std::cout << util::time::get_time() << std::endl; 

    return 0;
}
