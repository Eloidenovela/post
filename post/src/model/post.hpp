#pragma once

#include "editor.hpp"
#include "sqlite_orm/sqlite_orm.h"
#include <cstddef>
#include <memory>

namespace model {

    struct post {
        int id;
        std::unique_ptr<int> editor_id;
        std::string content;
        std::string updated_at;
        std::string time;
        size_t likes;

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