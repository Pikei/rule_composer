/**
 * \file json_utils.cpp
 * Created by Piotr Karol 2026
 */
#include <fstream>
#include <sstream>
#include <util/json_utils.hpp>

json_utils::json_utils(const logger_t& logger_) : logger { logger_ } { }

json_utils::json_utils(const std::string& file_path_, const logger_t& logger_) : default_file_path { file_path_ }, logger { logger_ }
{
}

void json_utils::set_file_path(const std::string& file_path_)
{
    this->default_file_path = file_path_;
}

void json_utils::load_file(const std::string& file_path_)
{
    validate_json_path(file_path_);

    std::ifstream file { file_path_ };
    if (!file.good() || !file.is_open())
    {
        throw std::invalid_argument { fmt::format("The file does not exist or is corrupted. Check the validity of file {}.", file_path_) };
    }

    const bool empty_file = file.peek() == std::ifstream::traits_type::eof();
    if (empty_file)
    {
        throw std::invalid_argument { fmt::format("The file at the specified path is empty. Check the contents of the file {}.", file_path_) };
    }

    file >> document;
}

void json_utils::load_file()
{
    return load_file(default_file_path);
}

void json_utils::save_file(const std::string& file_path_)
{
    validate_json_path(file_path_);

    std::ofstream file { file_path_ };

    if (!file.is_open())
    {
        throw std::runtime_error { fmt::format("Could not open file \"{}\" for writing.", file_path_) };
    }

    file << document.dump(indent);

    if (!file.good())
    {
        throw std::runtime_error { fmt::format("Failed to write JSON document to file \"{}\".", file_path_) };
    }

    logger->info("File \"{}\" saved successfully.", file_path_);
}

void json_utils::save_file()
{
    save_file(default_file_path);
}

void json_utils::print()
{
    if (document.empty())
    {
        logger->warn("The file was not loaded.");
        return;
    }

    const std::string file_contents = document.dump(indent);

    logger->info("File contents: \n{}", file_contents);
}

json* json_utils::navigate(const std::string& path)
{
    json* current = &document;
    for (const auto& field_name : split_path(path))
    {
        if (is_field_array(field_name))
        {
            current = parse_array(field_name, current);
        }
        else
        {
            if (!current->contains(field_name))
            {
                return nullptr;
            }

            current = &current->at(field_name);
        }

        if (current == nullptr)
        {
            return nullptr;
        }
    }

    return current;
}

void json_utils::validate_json_path(const std::string& file_path_)
{
    if (file_path_.empty())
    {
        throw std::invalid_argument { "The path to file is empty." };
    }

    if (file_path_.length() < ext.length())
    {
        throw std::invalid_argument { fmt::format("The path {} is too short.", file_path_) };
    }

    if (!has_json_extension(file_path_))
    {
        throw std::invalid_argument { fmt::format("The path {} does not lead to a file with the \"{}\" extension.", file_path_, ext) };
    }
}

bool json_utils::has_json_extension(const std::string& file_path_)
{
    return std::equal(ext.rbegin(), ext.rend(), file_path_.rbegin(), [](char a, char b)
                      { return std::tolower(a) == std::tolower(b); });
}

json* json_utils::parse_array(const std::string& field_name, json* current) const
{
    const size_t pos_start = field_name.find('[');
    const size_t pos_end   = field_name.find(']');
    const size_t index_len = pos_end - pos_start - 1;
    if (0 == index_len)
    {
        logger->error("Array index for \"{}\" was not specified.", field_name);
        return nullptr;
    }

    const std::string key   = field_name.substr(0, pos_start);
    const auto        index = std::stoi(field_name.substr(pos_start + 1, index_len));

    if (!current->contains(key))
    {
        logger->error("Field \"{}\" does not exist.", key);
        return nullptr;
    }

    auto& array = current->at(key);
    if ((!array.is_array()) || (array.size() <= index))
    {
        logger->error("Invalid field index: \"{}[{}]\"", field_name, index);
        return nullptr;
    }

    current = &array.at(index);
    return current;
}

std::vector<std::string> json_utils::split_path(const std::string& path)
{
    std::vector<std::string> result;
    std::istringstream       ss(path);
    std::string              field;
    while (std::getline(ss, field, '.'))
    {
        result.push_back(field);
    }
    return result;
}

bool json_utils::is_field_array(const std::string& field_name)
{
    // field_name name cannot be empty
    if (field_name.empty())
    {
        return false;
    }

    std::size_t pos_open_bracket  = field_name.rfind('[');
    std::size_t pos_close_bracket = field_name.rfind(']');

    // field_name must contain '[' and ']'
    if ((pos_open_bracket == std::string::npos) || (pos_close_bracket == std::string::npos))
    {
        return false;
    }

    // last character in field_name must be ']'
    if (field_name.back() != ']')
    {
        return false;
    }

    // '[' cannot be the first character
    if (pos_open_bracket == 0)
    {
        return false;
    }

    // There must be at least one character between '[' and ']'
    if (pos_open_bracket == field_name.size() - 1)
    {
        return false;
    }

    // All characters between '[' and ']' must be digits
    for (std::size_t i = pos_open_bracket + 1; i < field_name.size() - 1; ++i)
    {
        if (!std::isdigit(static_cast<unsigned char>(field_name[i])))
        {
            return false;
        }
    }

    return true;
}
