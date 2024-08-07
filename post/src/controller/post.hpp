#pragma once

#include "../service/user.hpp"
#include "../service/comment.hpp"
#include "../service/contact.hpp"
#include "../service/editor.hpp"
#include "../service/post.hpp"
#include "../include/json.hpp"

namespace controller {
    using json = nlohmann::json;
    template <typename S>
    class post {
        service::post<S> post_service;
        public:
            post(service::post<S> & service) : post_service(service) { }
            
            inline json post_get_all() const {
                auto posts = post_service.get_all();
                auto json = json::array_t();

                for (auto & post: posts) 
                    json.push_back(post.to_json());

                return (nlohmann::json) json;
            }
    };
}