#pragma once

#include "../include/json.hpp"
#include <string>

namespace util {
    class json {
        public:
            template <typename T>
            inline static T get(const nlohmann::json & json, const std::string & field) {
                try {
                    return (T) json[field].get<T>();
                } catch (const std::exception & e) {
                    throw std::runtime_error("expected field: " + field);
                }
            }
    };
}