#include <iostream>
#include <crow.h>
#include <memory>
#include <regex>
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
#include "service/user_contact.hpp"
#include "sqlite_orm/sqlite_orm.h"
#include "util/time.hpp"
#include "util/util.hpp"
#include "api/api.hpp"

crow::SimpleApp app;

int main(int argc, char** argv) {
    auto storage = model::get_storage();
    auto user_service = service::user{storage};
    auto contact_service = service::user_contact{storage};
    auto post_service = service::post{storage};
    auto comment_svc = service::comment{storage};
    auto editor_svc = service::editor{storage};


    auto usr_controller = controller::user{user_service, contact_service, editor_svc, post_service};

    // api::login(usr_controller);
    api::sign_up(app, usr_controller);

    app.port(8080).bindaddr("0.0.0.0").multithreaded().run();

    return 0;
}
