#pragma once

#include "../model/user.hpp"
#include "sqlite_orm/sqlite_orm.h"
#include "user_contact.hpp"
#include <exception>
#include <iostream>

namespace service {

    template <typename  Storage>
    class user {
        private:
            Storage & storage;
        public:
            user(Storage & service) : storage(service) { }

            inline int create(const model::user & user) {

                try {
                    return storage.template insert<model::user>(std::move(user));
                } catch (const std::exception & e) {
                    std::cerr << "/user/" << __FUNCTION__ << ": " << e.what() << std::endl;
                }

                return (-1);
            }

            inline auto get_all() {
                return storage.template get_all<model::user>();
            }

            inline void update(const model::user & user) {
                storage.template update<model::user>(std::move(user));
            }

            inline bool remove(const model::user & user) {
                using namespace sqlite_orm;
                try {   
                    storage.template remove<model::user>(
                        c(&model::user::id) == user.id
                    );
                    
                    return true;
                } catch (const std::exception & e) {
                    std::cerr << "/user/" << __FUNCTION__ << ": " << e.what() << std::endl;
                }

                return false;
            }

            inline bool is_user(const model::user & user) {
                try {
                    using namespace sqlite_orm;
                    auto result = storage.template get_all<model::user>(where(
                        c(&model::user::email) == user.email and
                        c(&model::user::passwd) == user.passwd
                    ));

                    return !(result.empty());
                
                } catch (const std::exception & e) {
                    std::cerr << "/user/" << __FUNCTION__ << ": " << e.what() << std::endl;
                }

                return false;
            }
    };
}