#pragma once
#include <exception>
#include <iostream>
#include <string>
#include <regex>

namespace util {

    typedef std::string error;
    inline bool is_email(const std::string & email) {
        const std::string domain_patterns[] = {
            ".*(@gmail).*",
            ".*(@outlook).*",
            ".*(@icloud).*",
            ".*(@yahoo).*",
            ".*(@hotmail).*"
        };

        try {
            for (auto & pattern: domain_patterns) {
                auto regex = std::regex(pattern);

                if (std::regex_match(email, regex)) 
                    return true;
            }
        } catch (const std::exception & e) {
            std::cerr << "util/" << __FUNCTION__ << ": " << e.what() << std::endl;
        }

        return false;
    }

    inline bool is_contact(std::string contact) {
        std::regex pattern("\\+2588[2-7]\\d{7}"); // mazambican pattern

        return std::regex_match(contact, pattern);
    }


}