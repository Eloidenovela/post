#pragma once

#include "../model/user_contact.hpp"
#include "sqlite_orm/sqlite_orm.h"
#include <algorithm>
#include <exception>
#include <iostream>
#include <vector>

namespace service {
    template <typename Storage>
    class user_contact {
        private:
            Storage & storage;
        public:
            user_contact(Storage & service) : storage(service) { }
            
            inline int create(const model::user_contact & user_contact) {
                using namespace sqlite_orm;
                return storage.template insert<model::user_contact>(std::move(user_contact));
            }

            inline auto get_all() {
                using namespace sqlite_orm;

                return storage.template get_all<model::user_contact>();
            }


            inline std::vector<model::user_contact> get_by_user(const model::user & user) {
                try {
                    using namespace sqlite_orm;

                    return storage.template get_all<model::user_contact>(
                        where(
                            c(&model::user_contact::user_id) == user.id
                        )
                    );

                } catch (const std::exception & e) {
                    std::cerr << "in " << __FUNCTION__ << ": " << e.what() << std::endl;
                }

                return { };
            }

            inline void update(const model::user_contact & user_contact) {
                storage.template update<model::user_contact>(std::move(user_contact));
            }

            inline bool remove(const model::user_contact & user_contact) {
                try {
                    using namespace sqlite_orm;
                    storage.template remove<model::user_contact>(
                        c(&model::user_contact::id) == user_contact.id
                    );

                    return true;
                
                } catch (const std::exception & e) {
                    std::cerr << "in " << __FUNCTION__ << ": " << e.what() << std::endl;
                }

                return false;
            }
    };
}