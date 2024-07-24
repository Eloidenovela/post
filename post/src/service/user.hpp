#pragma once

#include "../model/user.hpp"
#include "sqlite_orm/sqlite_orm.h"
#include <exception>
#include <iostream>

namespace service {
    template <typename  Storage>
    class user {
        private:
            Storage & storage;
        public:
            user(Storage & service) : storage(service) {}

            inline int create(const model::user & user) {
                return storage.template insert<model::user>(std::move(user));
            }

            inline auto get_all() {
                return storage.template get_all<model::user>();
            }

            inline void update(const model::user & user) {
                storage.template update<model::user>(std::move(user));
            }

            inline bool remove(const model::user & user) {
                try {   
                    storage.template remove<model::user>(std::move(user));
                    return true;
                } catch (const std::exception &e) {
                    std::cerr << "in " << __FUNCTION__ << ": " << e.what() << std::endl;
                }

                return false;
            }
    };
}