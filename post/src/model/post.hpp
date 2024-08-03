#pragma once

#include "editor.hpp"
#include "sqlite_orm/sqlite_orm.h"
#include <cstddef>
#include <cstdint>
#include <memory>
#include "../util/json.hpp"
#include "../include/json.hpp"

namespace model {
    using json = nlohmann::json;

    struct post {
        int id;
        std::unique_ptr<int> editor_id;
        std::string content;
        std::string updated_at;
        std::string time;
        size_t likes;

        inline json to_json() const {
            return {
                {"id", id},
                {"editor_id", * editor_id.get()},
                {"content", content},
                {"updated_at", updated_at},
                {"time", time},
                {"likes", likes}
            };
        }

        inline static model::post from_json(const json & json) {
            auto model = model::post {
                .id = util::json::get<int>(json, "id"),
                .editor_id = util::json::get<decltype(model::post::editor_id)>(json, "editor_id"),
                .content = util::json::get<std::string>(json, "content"),
                .updated_at = util::json::get<std::string>(json, "updated_at"),
                .time = util::json::get<decltype(model::post::time)>(json, "time"),
                .likes = util::json::get<decltype(model::post::likes)>(json, "likes")
            };

            return model;
        }

        inline static auto make_table() {
            using namespace sqlite_orm;

            return sqlite_orm::make_table(
                "post",
                make_column("id", &model::post::id, primary_key().autoincrement()),
                make_column("editor_id", &model::post::editor_id),
                make_column("content", &model::post::content),
                make_column("updated_at", &model::post::updated_at),
                make_column("time", &model::post::time),
                make_column("likes", &model::post::likes),
                foreign_key(&model::post::editor_id).references(&model::editor::id)
            );
        }
    };
}