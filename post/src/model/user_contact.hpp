#pragma once

#include "sqlite_orm/sqlite_orm.h"
#include "user.hpp"
#include <memory>
#include <string>

namespace model {

    struct user_contact {
        int id;
        std::unique_ptr<int> user_id;
        std::string contact;

        inline static auto make_table() {
            using namespace sqlite_orm;

            return sqlite_orm::make_table(
                "user_contact",
                make_column("id", &model::user_contact::id, primary_key().autoincrement()),
                make_column("user_id", &model::user_contact::user_id),
                make_column("contact", &model::user_contact::contact),
                foreign_key(&model::user_contact::user_id).references(&model::user::id)
            );
        }
    };
}