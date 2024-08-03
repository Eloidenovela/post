#pragma once

#include "crow.h"
#include "crow/app.h"
#include "crow/common.h"
#include "../include/json.hpp"
#include "crow/http_request.h"
#include "../controller/user.hpp"
#include "crow/http_response.h"
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
            
            return crow::response("BAD");
        });
    }

    template <typename S>
    inline void  sign_up(crow::SimpleApp & app, controller::user<S> & user_controller) {
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

            return crow::response("BAD");
        });
    }
}