#pragma once

#include "crow.h"
#include "crow/app.h"
#include "crow/common.h"
#include "../include/json.hpp"
#include "crow/http_request.h"
#include "../controller/user.hpp"
#include "../controller/post.hpp"
#include "crow/http_response.h"
#include "crow/json.h"
#include <exception>
#include <iostream>
#include <string>

namespace api {
    using json = nlohmann::json;
    
    template <typename S>
    inline void sign_in(crow::SimpleApp &app, controller::user<S> & user_controller)  {
       CROW_ROUTE(app, "/post/login").methods("GET"_method, "POST"_method)
            ([&](const crow::request & req){

            try {
                if (!(req.body.empty())) {
                    auto json = json::parse(req.body);

                    auto user = model::user::from_json(json);
                    
                    return crow::response(user_controller.sign_in(user).dump(4));
                }

            } catch (const std::exception & e) {
                std::cerr << "api/" << __FUNCTION__ << ": " << e.what() << std::endl;
            }
            
            return crow::response(crow::BAD_REQUEST);
        });
    }

    template <typename S>
    inline void sign_up(crow::SimpleApp & app, controller::user<S> & user_controller) {
        CROW_ROUTE(app, "/post/sign-in").
        methods("POST"_method, "GET"_method)([&](const crow::request & req) {

            try {

                if (!(req.body.empty())) {
                    auto body = json::parse(req.body);
                    auto user = model::user::from_json(body);
                    std::string contact = body["contact"].get<std::string>();

                    return crow::response(user_controller.sign_up(user, contact).dump(4));
                }
            } catch (const std::exception & e) {
                std::cerr << "api/" << __FUNCTION__ << ": " << e.what() << std::endl;
            }

            return crow::response(crow::BAD_REQUEST);
        });
    }

    template <typename S>
    inline void wpost(crow::SimpleApp & app, controller::user<S> & user_controller) {
        CROW_ROUTE(app, "/post/wpost").
        methods(crow::HTTPMethod::POST, crow::HTTPMethod::GET)
        ([&](const crow::request & req) {

            if (!(req.body.empty())) {
                auto json = json::parse(req.body);
                auto user = model::user();
                auto post = user_controller.write_post(user, model::post::from_json(json));

                return crow::response(post.dump(4));
            }

            return crow::response(crow::BAD_REQUEST);
        });
    }

    template <typename S>
    inline void rpost(crow::SimpleApp & app, controller::post<S> & post_controller) {
        CROW_ROUTE(app, "/post/rpost").methods(crow::HTTPMethod::GET)([&](const crow::request & req){
            return crow::response(post_controller.post_get_all().dump(4));
        });
    }
}