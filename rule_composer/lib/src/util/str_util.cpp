/**
 * \file str_util.cpp
 * Created by Piotr Karol 2026
 */

#include <rule_composer_lib/util/str_util.hpp>

namespace rule_composer::lib::util
{
    std::vector< std::string > str_util::str_to_vector( const std::string& str, const char delimiter )
    {
        std::vector< std::string > result;
        std::size_t                pos_start = 0;
        std::size_t                pos_end   = str.find_first_of( delimiter, pos_start );
        while ( pos_end != std::string::npos )
        {
            result.push_back( str.substr( pos_start, pos_end - pos_start ) );
            pos_start = pos_end + 1;
            pos_end   = str.find_first_of( delimiter, pos_start );
        }
        return result;
    }
} // namespace rule_composer::lib::util
