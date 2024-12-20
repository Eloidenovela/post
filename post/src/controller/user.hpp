#pragma once

#include "../service/user.hpp"
#include "../service/comment.hpp"
#include "../service/contact.hpp"
#include "../service/editor.hpp"
#include "../service/post.hpp"
#include "../util/util.hpp"
#include "../util/time.hpp"
#include "../include/json.hpp"
#include <memory>
#include <regex>
#include <string>
#include <variant>

using json = nlohmann::json;

namespace controller {

    template <typename Service>
    class user {
        private:
            service::user<Service> & user_service;
            service::contact<Service> & contact_service;
            service::editor<Service> & editor_service;
            service::post<Service> & post_service;
        public:
            user(service::user<Service> & user_service, service::contact<Service> & contact_service, service::editor<Service> & editor_service, service::post<Service> & post_service) : 
                user_service(user_service), 
                contact_service(contact_service),
                editor_service(editor_service),
                post_service(post_service) 
                { }

        public:

            inline json sign_in(const model::user & user) {
                if (util::is_email(user.email)) {
                    return {
                        {"is_user", user_service.is_user(user)}
                    };
                }

                return {
                    {"error", "INVALID EMAIL"}
                };
            }

            inline json sign_up(model::user & user, std::string contact=std::string()) {
                if (util::is_email(user.email) and util::is_contact(contact)) {
                    auto id = 0;
                    if ((id = user_service.create(user)) != (-1)) {
                        
                        user.id = id;
                        auto model = model::contact {
                            .user_id = std::make_unique<int>(id),
                            .contact = contact
                        };

                        id = contact_service.create(model);

                        if (id == (-1)) {
                            user_service.remove(std::move(user));

                            return {"error", "error"};
                        }

                        return user.to_json();
                    }
                }
                
                return {"error", "INVALID_EMAIL_OR_CONTACT"};
            }

            inline json write_post(const model::user & user, model::post post) {

                if (editor_service.is_editor(user)) {

                    post.editor_id = std::make_unique<int>(user.id);
                    post.updated_at = util::time::get_date();
                    post.time = util::time::get_time();

                    if (post_service.create(post) == (-1))
                        return {"error", "post does not created"};

                    return post.to_json();
                }

                return {"error", "ACESS_DENIED: ONLY EDITORS"};
            }
    };
}
