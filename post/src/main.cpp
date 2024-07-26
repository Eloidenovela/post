#include <iostream>
#include <crow.h>
#include <memory>
#include "model/all.hpp"
#include "model/editor.hpp"
#include "model/user.hpp"
#include "service/editor.hpp"
#include "service/user.hpp"

int main(int argc, char** argv) {
    auto storage = model::get_storage();

    service::user user_service {storage};
    service::editor editor_service {storage};

    auto user = model::user {
        .name = "Eloide",
        .nickname = "Novela",
        .email = "eloide.novela@gmail.com",
        .passwd = "1010"
    };

    // // // user_service.remove(user);
    int id = user_service.create(user);

    auto editor = model::editor {
        .user_id = std::make_unique<int>(id)
    };

    int id_ = editor_service.create(editor);
    std::cout << id_ << std::endl;


    auto users = editor_service.get_all();

    for (auto &i: users) {
        std::cout << i.name << "\t" << i.email << std::endl;
    }

    return 0;
}
