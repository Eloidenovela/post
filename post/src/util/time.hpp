#pragma once
#include <ctime>
#include <sstream>
#include <iomanip>

namespace util {
    class time {
        private:
            inline static auto get_current_date(const std::string fmt) {
                std::time_t now = std::time(nullptr);
                std::tm* local_time = std::localtime(&now);
                std::stringstream date;
                date << std::put_time(local_time, fmt.c_str());

                return date.str();
            }

        public:

            inline static const auto get_date() {  

                return util::time::get_current_date("%y-%m-%d");
            }

            inline static const auto get_time() {

                return util::time::get_current_date("%H:%M");
            }
    };
}