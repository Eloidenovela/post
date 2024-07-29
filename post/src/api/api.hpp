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

using json = nlohmann::json;

namespace api {
    template <typename S>
    inline void login(crow::SimpleApp &app, controller::user<S> & user_controller)  {
       CROW_ROUTE(app, "/post/login").methods("GET"_method, "POST"_method)
            ([&](const crow::request & req){

            try {
                if (!(req.body.empty())) {
                    auto user = json::parse(req);

                    auto u = model::user {
                        .name = user["name"].get<std::string>(),
                        .nickname = user["nickname"].get<std::string>(),
                        .email = user["email"].get<std::string>(),
                        .passwd = user["passwd"].get<std::string>()
                    };
                    
                    return crow::response(user_controller.sign_in(u).dump(4));
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
                    auto sig_up_data = json::parse(req.body);
                    auto user_data = model::user {
                        .name = sig_up_data["name"].get<std::string>(),
                        .nickname = sig_up_data["nickname"].get<std::string>(),
                        .email = sig_up_data["email"].get<std::string>(),
                        .passwd = sig_up_data["passwd"].get<std::string>()
                    };

                    auto contact = sig_up_data["contact"].get<std::string>();

                    return crow::response(user_controller.sign_up(user_data, contact).dump(4));
                }
            } catch (const std::exception & e) {
                std::cerr << "api/" << __FUNCTION__ << ": " << e.what() << std::endl;
            }

            return crow::response("BAD");
        });
    }
}