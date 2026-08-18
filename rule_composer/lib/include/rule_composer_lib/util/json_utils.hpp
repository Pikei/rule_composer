#ifndef RULE_COMPOSER_LIB_JSON_UTILS_HPP
#define RULE_COMPOSER_LIB_JSON_UTILS_HPP

#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

namespace rule_composer::lib::util
{
    /**
     * \brief Class providing functionality for opening, reading, and writing JSON files.
     */
    class json_utils
    {
    public:

        /**
         * \brief Constructor for the JSON functionality class
         * \param logger_ Logger used for displaying messages in the console
         */
        explicit json_utils( std::shared_ptr< spdlog::logger > logger_ );

        /**
         * \brief Constructor for the JSON functionality class
         * \param file_path_ Path to the JSON file on disk, e.g., "path/to/file.json".
         * \param logger_ Logger used for displaying messages in the console
         */
        explicit json_utils( std::string file_path_, std::shared_ptr< spdlog::logger > logger_ );

        /**
         * \brief Setter for the default JSON file path
         * \param file_path_ New default JSON file path
         */
        void set_file_path( const std::string& file_path_ );

        /**
         * \brief Loads a JSON file from the specified path
         * \param file_path_ Path to the JSON file on disk, e.g., "path/to/file.json
         * \throws std::invalid_argument If the file does not exist, is corrupted or empty
         */
        void load_file( const std::string& file_path_ );

        /**
         * \brief Calls load_file method with default file path
         */
        void load_file( );

        /**
         * \brief Saves a JSON file to the specified path
         * \param file_path_ Path to the JSON file on disk, e.g., "path/to/file.json
         * \throws std::runtime_error If could not open or or failed to write file
         */
        void save_file( const std::string& file_path_ ) const;

        /**
         * \brief Calls save_file method with default file path
         */
        void save_file( ) const;

        /**
         * \brief Prints loaded JSON file
         * \note If file is not loaded prints warning via logger
         */
        void print( ) const;

        /**
         * \brief Retrieves the value at the specified path in a JSON file.
         * \tparam T Type of returned value
         * \param path Path to value in JSON file
         * \return Retrieved value from JSON file
         * \throws std::logic_error If the file was not loaded
         * \throws std::logic_error If cannot assign a value to the specified type
         * \note For the following example JSON notation:
         * \code
         * {
         *   "object": {
         *     "list": [
         *       "param": 123
         *     ]
         *   }
         * }
         * \endcode
         * The path to the "param" field value will be "object.list[0].param"
         */
        template < typename T >
        T get_value( const std::string& path )
        {
            if ( document.empty( ) )
            {
                throw std::logic_error { "The file was not loaded." };
            }

            const auto node = navigate( path );
            if ( ( nullptr == node ) or ( node->empty( ) ) )
            {
                throw std::invalid_argument { fmt::format( "Config file does not contain value: {}", path ) };
            }
            try
            {
                return node->get< T >( );
            }
            catch ( nlohmann::json::exception& e )
            {
                throw std::logic_error { fmt::format( "Cannot assign a value to the specified type: {}", e.what( ) ) };
            }
        }

        /**
         * \brief Retrieves the optional value at the specified path in a JSON file.
         * \tparam T Type of returned value
         * \param path Path to value in JSON file
         * \return Retrieved value from JSON file or \code std::nullopt\endcode if the value does not exist.
         * \note For the following example JSON notation:
         * \code
         * {
         *   "object": {
         *     "list": [
         *       "param": 123
         *     ]
         *   }
         * }
         * \endcode
         * The path to the "param" field value will be "object.list[0].param"
         */
        template < typename T >
        std::optional< T > get_optional( const std::string& path )
        {
            const auto* node = navigate( path );

            if ( node == nullptr || node->is_null( ) )
            {
                return std::nullopt;
            }
            try
            {
                return node->get< T >( );
            }
            catch ( const nlohmann::json::exception& e )
            {
                throw std::logic_error { fmt::format( "Cannot assign a value at '{}' to the specified type: {}", path, e.what( ) ) };
            }
        }

    protected:

        /**
         * \brief Loaded JSON file
         */
        nlohmann::json document;

        /**
         * \brief Logger used for displaying messages in the console
         */
        std::shared_ptr< spdlog::logger > logger;

        /**
         * \brief Default file path
         */
        std::string default_file_path;

        /**
         * \brief Navigates the JSON file based on the provided resource path.
         * \param path Path to the resource within the JSON file.
         * \return A pointer to the JSON file fragment containing the value at the specified path, or \code nullptr\endcode if the resource was not found.
         * \note For the following example JSON notation:
         * \code
         * {
         *   "object": {
         *     "list": [
         *       "param": 123
         *     ]
         *   }
         * }
         * \endcode
         * The path to the "param" field value will be "object.list[0].param"
         */
        nlohmann::json* navigate( const std::string& path );

    private:

        /**
         * \brief Indent for printing and saving JSON file
         */
        static constexpr std::uint8_t indent = 4;

        /**
         * \brief Extension for JSON files
         */
        static constexpr std::string_view ext = ".json";

        /**
         * \brief Validates a file path to ensure it refers to a JSON file.
         * \param file_path_ Path to the JSON file on disk, e.g., "path/to/file.json"
         * \throws std::invalid_argument If the file path is empty, is shorter than the expected extension, or does not have the expected JSON extension.
         */
        static void validate_json_path( const std::string& file_path_ );

        /**
         * \brief Checks if file path refers to a JSON file.
         * \param file_path_ Path to the JSON file on disk, e.g., "path/to/file.json"
         * \return \code true\endcode if file path refers to a JSON file, \code false\endcode otherwise.
         */
        static bool has_json_extension( const std::string& file_path_ );

        /**
         * \brief Processes data stored in array format within a JSON file
         * \param field_name Field name including the index
         * \param current The currently processed fragment of the JSON file containing the array
         * \return A pointer to the current fragment of the JSON file containing the value indicated by the path, or \code nullptr\endcode if the resource was
         * not found.
         */
        nlohmann::json* parse_array( const std::string& field_name, nlohmann::json* current ) const;

        /**
         * \brief Splits a JSON navigation path into individual field names
         * \param path Path to the resource within the JSON file
         * \return A vector of keys/field names
         * \note For the following example JSON notation:
         * \code
         * {
         *   "object": {
         *     "list": [
         *       "param": 123
         *     ]
         *   }
         * }
         * \endcode
         * The path to the "param" field value would be "object.list[0].param"
         * The method will split this path into the vector
         * \code { "object", "list[0]", "param[0]" } \endcode
         */
        static std::vector< std::string > split_path( const std::string& path );

        /**
         * \brief Checks whether the specified field name refers to an array based on opening and closing square bracket.
         * \param field_name Field name
         * \return \code true\endcode if the field name refers to an array, \code false\endcode otherwise
         */
        static bool is_field_array( const std::string& field_name );
    };
} // namespace rule_composer::lib::util

#endif // RULE_COMPOSER_LIB_JSON_UTILS_HPP
