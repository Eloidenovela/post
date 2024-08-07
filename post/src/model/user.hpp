#pragma once
#include "crow/json.h"
#include "sqlite_orm/sqlite_orm.h"
#include <string>
#include <crow.h>
#include "../include/json.hpp"
#include "../util/json.hpp"


namespace model {

    using json = nlohmann::json;

    struct user {
        int id;
        std::string name;
        std::string nickname;
        std::string email;
        std::string passwd;
        bool is_admin;

        inline json to_json() const {
            return {
                {"id", id},
                {"name", name},
                {"nickname", nickname},
                {"email", email},
                {"passwd", passwd},
                {"is_admin", is_admin}
            };
        }

        inline static model::user from_json(const json & json) {
            auto to_model = model::user {
                // .id = util::json::get<int>(json, "id"),
                .name = util::json::get<std::string>(json, "name"),
                .nickname = util::json::get<std::string>(json, "nickname"),
                .email = util::json::get<std::string>(json, "email"),
                .passwd = util::json::get<std::string>(json, "passwd"),
                .is_admin = util::json::get<bool>(json, "is_admin")
            };

            return to_model;
        }

        inline static auto make_table() {
            using namespace sqlite_orm;
            return sqlite_orm::make_table(
                "user",
                make_column("id", &model::user::id, primary_key().autoincrement()),
                make_column("name", &model::user::name),
                make_column("nicknamename", &model::user::nickname),
                make_column("email", &model::user::email, unique()),
                make_column("passwd", &model::user::passwd),
                make_column("is_admin", &model::user::is_admin)
            );
        }
    };
}