#pragma once

#include "sqlite_orm/sqlite_orm.h"
#include "user.hpp"
#include <memory>

namespace model {
    struct editor {
        int id;
        std::unique_ptr<int> user_id;

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