#pragma once

#include "comment.hpp"
#include "editor.hpp"
#include "post.hpp"
#include "sqlite_orm/sqlite_orm.h"
#include "user.hpp"
#include "contact.hpp"
#include <iostream>

namespace model {
    inline auto get_storage() {
        using namespace sqlite_orm;

        static bool did_sync = false;

        static auto storage = sqlite_orm::make_storage(
            "post.sqlite",
            model::user::make_table(),
            model::editor::make_table(),
            model::post::make_table(),
            model::comment::make_table(),
            model::contact::make_table()
        );

        if(not did_sync){
            for(const auto & [name, result] : storage.sync_schema()){
                std::cout << "[sync " << name << ": " << result <<"]" << std::endl;
            }
            did_sync = true;
        }
        return storage;
    }
}