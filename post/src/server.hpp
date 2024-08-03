#pragma once

#include <crow.h>
#include "api/api.hpp"
#include "controller/user.hpp"
#include "crow/app.h"
#include "model/all.hpp"
#include "model/editor.hpp"
#include "model/user.hpp"
#include "service/comment.hpp"
#include "service/editor.hpp"
#include "service/post.hpp"
#include "service/user.hpp"
#include "service/contact.hpp"
#include "sqlite_orm/sqlite_orm.h"
#include "util/time.hpp"
#include "util/util.hpp"
#include "api/api.hpp"

namespace server {
    inline void run() {
        auto app = crow::SimpleApp();

        auto storage = model::get_storage();

        auto user_service = service::user{storage};
        auto contact_service = service::contact{storage};
        auto post_service = service::post{storage};
        auto comment_svc = service::comment{storage};
        auto editor_svc = service::editor{storage};

        auto usr_controller = controller::user{user_service, contact_service, editor_svc, post_service};

        api::sign_in(app, usr_controller);
        api::sign_up(app, usr_controller);


        app.port(8080)
            .server_name("post")
            .bindaddr("0.0.0.0")
            .multithreaded()
            .run();
    }
}