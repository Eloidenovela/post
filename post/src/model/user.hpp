#pragma once
#include "sqlite_orm/sqlite_orm.h"
#include <string>

namespace model {
    struct user {
        int id;
        std::string name;
        std::string nickname;
        std::string email;
        std::string passwd;

        inline static auto make_table() {
            using namespace sqlite_orm;
            return sqlite_orm::make_table(
                "user",
                make_column("id", &model::user::id, primary_key().autoincrement()),
                make_column("name", &model::user::name),
                make_column("nicknamename", &model::user::nickname),
                make_column("email", &model::user::email, unique()),
                make_column("passwd", &model::user::passwd)
            );
        }
    };
}