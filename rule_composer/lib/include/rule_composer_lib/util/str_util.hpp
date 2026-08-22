/**
 * \file str_util.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_STR_UTIL_HPP
#define RULE_COMPOSER_STR_UTIL_HPP

#include <string>
#include <vector>

namespace rule_composer::lib::util
{

    class str_util
    {
    public:

        static std::vector< std::string > str_to_vector( const std::string& str, const char delimiter );
    };

} // namespace rule_composer::lib::util

#endif // RULE_COMPOSER_STR_UTIL_HPP
