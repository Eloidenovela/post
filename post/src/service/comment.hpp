#pragma once
#include "../model/comment.hpp"
#include "sqlite_orm/sqlite_orm.h"
#include <exception>
#include <iostream>
#include <memory>
#include <vector>

namespace service {
    template <typename Storage>
    class comment {
        private:
            Storage & storage;
        public:
            comment(Storage & service) : storage(service) { }

            inline int create(const model::comment & comment) {

                return storage.template insert<model::comment>(std::move(comment));
            }

            inline void update(const model::comment & comment) {
                storage.template update<model::comment>(std::move(comment));
            }

            inline bool remove(const model::comment & comment) {
                try {
                    using namespace sqlite_orm;
                    storage.template remove<model::comment>(
                        where(
                            c(&model::comment::id) == comment.id
                        )
                    );
                    return true;
                
                } catch (const std::exception & e) {
                    std::cerr << "/comment/" << __FUNCTION__ << ": " << e.what() << std::endl;
                }

                return true;
            }

            inline std::vector<model::comment> get_all() {
                return storage.template get_all<model::comment>();
            }

            inline std::vector<model::comment> get_all_by_user(const model::user & user) {
                try {
                    using namespace sqlite_orm;

                    return storage.template get_all<model::comment>(
                        where(
                            c(&model::comment::user_id) == std::make_unique<int>(user.id)
                        )
                    );
                
                } catch (const std::exception & e) {
                    std::cerr << "/comment/" << __FUNCTION__ << ": " << e.what() << std::endl;
                }

                return { };
            }

            inline std::vector<model::comment> get_all_by_post(const model::post & post) {
                try {
                    using namespace sqlite_orm;

                    return storage.template get_all<model::comment>(
                        where(
                            c(&model::comment::post_id) == std::make_unique<int>(post.id)
                        )
                    );
                } catch (const std::exception & e) {
                    std::cerr << "/comment/" << __FUNCTION__ << ": " << e.what() << std::endl;
                }

                return { };
            }
    };
}