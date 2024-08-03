#pragma once

#include "../model/contact.hpp"
#include "sqlite_orm/sqlite_orm.h"
#include <algorithm>
#include <exception>
#include <iostream>
#include <vector>

namespace service {
    template <typename Storage>
    class contact {
        private:
            Storage & storage;
        public:
            contact(Storage & service) : storage(service) { }
            
            inline int create(const model::contact & contact) {
                using namespace sqlite_orm;
                return storage.template insert<model::contact>(std::move(contact));
            }

            inline auto get_all() {
                using namespace sqlite_orm;

                return storage.template get_all<model::contact>();
            }


            inline std::vector<model::contact> get_by_user(const model::user & user) {
                try {
                    using namespace sqlite_orm;

                    return storage.template get_all<model::contact>(
                        where(
                            c(&model::contact::user_id) == user.id
                        )
                    );

                } catch (const std::exception & e) {
                    std::cerr << "in " << __FUNCTION__ << ": " << e.what() << std::endl;
                }

                return { };
            }

            inline void update(const model::contact & contact) {
                storage.template update<model::contact>(std::move(contact));
            }

            inline bool remove(const model::contact & contact) {
                try {
                    using namespace sqlite_orm;
                    storage.template remove<model::contact>(
                        c(&model::contact::id) == contact.id
                    );

                    return true;
                
                } catch (const std::exception & e) {
                    std::cerr << "in " << __FUNCTION__ << ": " << e.what() << std::endl;
                }

                return false;
            }
    };
}