#pragma once
#include "../service/editor.hpp"
#include "../service/user.hpp"
#include <memory>

namespace controller {
template <typename S> 
    class admin {
        service::user<S> &user_service;
        service::editor<S> &editor_service;

    public:
        admin(service::editor<S> editor_service, service::user<S> user_service)
            : user_service(user_service), editor_service(editor_service) {}

        inline int create_editor(const model::user &admin, model::user &user) {
          if (user_service.is_admin(admin)) {
            auto editor = model::editor{.user_id = std::make_unique<int>(user.id)};

            return editor_service.create(editor);
          }

          return (-1);
        }
    };
} // namespace controller