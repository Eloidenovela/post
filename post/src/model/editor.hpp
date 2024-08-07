#pragma once

#include "sqlite_orm/sqlite_orm.h"
#include "user.hpp"
#include <memory>
#include "../util/json.hpp"
#include "../include/json.hpp"

namespace model {
    using json = nlohmann::json;
    
    struct editor {
        int id;
        std::unique_ptr<int> user_id;

        inline json to_json() const {
            return {
                {"id", id},
                {"user_id", * user_id.get()}
            };
        }

        inline static model::editor from_json(const json & json) {
            auto model = model::editor {
                .id = util::json::get<int>(json, "id"),
                .user_id = std::make_unique<int>(util::json::get<int>(json, "user_id"))
            };

            return model;
        }

        inline static auto make_table() {
            using namespace sqlite_orm;
            return sqlite_orm::make_table(
                "editor",
                make_column("id", &model::editor::id, primary_key().autoincrement()),
                make_column("user_id", &model::editor::user_id),
                foreign_key(&model::editor::user_id).references(&model::user::id)
            );
        }
    };
}