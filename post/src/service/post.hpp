#pragma once

#include "../model/post.hpp"
#include "sqlite_orm/sqlite_orm.h"
#include <exception>
#include <iostream>
#include <memory>
#include <vector>

namespace service {

    template <typename Storage>
    class post {
        private:
            Storage & storage;
        public:
            post(Storage & service) : storage(service) { }

            inline int create(const model::post & post) {
                using namespace sqlite_orm;
                return storage.template insert<model::post>(std::move(post));
            }

            inline void update(const model::post & post) {
                storage.template update<model::post>(std::move(post));
            }

            inline bool remove(const model::post & post) {
                try {
                    using namespace sqlite_orm;

                    storage.template remove<model::post>(
                        where(
                            c(&model::post::id) == post.id
                        )
                    );
                    return true;
                
                } catch (const std::exception & e) {

                    std::cerr << "in " << __FUNCTION__ << ": " << e.what() << std::endl;
                }

                return false;
            }

            inline std::vector<model::post> get_all() {
                return storage.template get_all<model::post>();
            }

            inline std::vector<model::post> get_all_by_editor(const model::editor &editor) {
                try {
                    using namespace sqlite_orm;

                    return storage.template get_all(
                        where(
                            c(&model::post::editor_id) == std::make_unique<int>(editor.id)
                        )
                    );
                
                } catch (const std::exception & e) {
                    std::cerr << "in " << __FUNCTION__ << ": " << e.what() << std::endl;
                }

                return { };
            }
    };
}