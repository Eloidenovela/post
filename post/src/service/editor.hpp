#pragma once
#include "../model/user.hpp"
#include "../model/editor.hpp"
#include "sqlite_orm/sqlite_orm.h"
#include <exception>
#include <iostream>
#include <memory>
#include <vector>

namespace service {
    template <typename Storage>
    class editor {
        private:
            Storage & storage;
        public:
            editor(Storage & service) : storage(service) { }

            inline int create(const model::editor & editor) {
                try {
                    return storage.template insert<model::editor>(std::move(editor));
                } catch (const std::exception & e) {
                    std::cerr << "/editor/" << __FUNCTION__ << ": " << e.what() << std::endl;
                }

                return (-1);
            }

            inline void update(const model::editor & editor) {
                storage.template update<model::editor>(std::move(editor));
            }

            inline bool remove(const model::editor & editor) {

                try {  
                    using namespace sqlite_orm;
                    storage.template remove<model::editor>(
                        where(
                            c(&model::editor::id) == editor.id
                        )
                    );
                    return true;
                
                } catch (const std::exception & e) {
                    std::cerr << "/editor/" << __FUNCTION__ << ": " << e.what() << std::endl;
                
                }

                return false;
            }

        inline std::vector<model::user> get_all() {
            try {
                using namespace sqlite_orm;
                return storage.template get_all<model::user>(
                    where(
                        in(
                            &model::user::id,
                            select(&model::editor::user_id, 
                                where(
                                    c(&model::editor::user_id) == &model::user::id
                                )
                            )
                        )
                    )
                );
            } catch (const std::exception & e) {
                std::cerr << "/editor/" << __FUNCTION__ << ": " << e.what() << std::endl;
            }

            return { };
        }

    };
}