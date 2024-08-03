#pragma once

#include "sqlite_orm/sqlite_orm.h"
#include "user.hpp"
#include <memory>
#include <string>
#include "../util/json.hpp"
#include "../include/json.hpp"

namespace model {
    using json = nlohmann::json;

    struct contact {
        int id;
        std::unique_ptr<int> user_id;
        std::string contact;

        inline json to_json() const {
            return {
                {"id", id},
                {"user_id", * user_id.get()},
                {"contact", contact}
            };
        }

        inline static model::contact from_json(const json & json) {
            auto model = model::contact {
                .id = util::json::get<int>(json, "id"),
                .user_id = util::json::get<decltype(model::contact::user_id)>(json, "user_id"),
                .contact = util::json::get<std::string>(json, "contact")
            };

            return model;
        }
        
        inline static auto make_table() {
            using namespace sqlite_orm;

            return sqlite_orm::make_table(
                "contact",
                make_column("id", &model::contact::id, primary_key().autoincrement()),
                make_column("user_id", &model::contact::user_id),
                make_column("contact", &model::contact::contact),
                foreign_key(&model::contact::user_id).references(&model::user::id)
            );
        }
    };
}