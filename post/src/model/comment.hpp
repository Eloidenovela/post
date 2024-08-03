#pragma once

#include "post.hpp"
#include "sqlite_orm/sqlite_orm.h"
#include "user.hpp"
#include <memory>
#include <string>
#include "../util/json.hpp"
#include "../include/json.hpp"

namespace model {
    using json = nlohmann::json;

    struct comment {
        int id;
        std::unique_ptr<int> user_id;
        std::unique_ptr<int> post_id;
        std::string content;
        std::string updated_at;
        std::string time;

        inline json to_json() const {
            return {
                {"id", id},
                {"user_id", * user_id.get()},
                {"post_id", * post_id.get()},
                {"content", content},
                {"updated_at", updated_at},
                {"time", time}
            };
        }

        inline static model::comment from_json(const json & json) {
            auto model = model::comment {
                .id = util::json::get<int>(json, "id"),
                .user_id = util::json::get<decltype(model::comment::user_id)>(json, "user_id"),
                .post_id = util::json::get<decltype(model::comment::post_id)>(json, "post_id"),
                .content = util::json::get<std::string>(json, "content"),
                .updated_at = util::json::get<std::string>(json, "updated_at"),
                .time = util::json::get<std::string>(json, "time")
            };

            return model;
        }

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