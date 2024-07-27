#pragma once

#include "post.hpp"
#include "sqlite_orm/sqlite_orm.h"
#include "user.hpp"
#include <memory>
#include <string>

namespace model {

    struct comment {
        int id;
        std::unique_ptr<int> user_id;
        std::unique_ptr<int> post_id;
        std::string content;
        std::string updated_at;
        std::string time;

        inline static auto make_table() {
            using namespace sqlite_orm;

            return sqlite_orm::make_table(
                "comment",
                make_column("id", &model::comment::id, primary_key().autoincrement()),
                make_column("user_id", &model::comment::user_id),
                make_column("post_id", &model::comment::post_id),
                make_column("content", &model::comment::content),
                make_column("updated_at", &model::comment::updated_at),
                make_column("time", &model::comment::time),
                foreign_key(&model::comment::user_id).references(&model::user::id),
                foreign_key(&model::comment::post_id).references(&model::post::id)
            );
        }
    };
}