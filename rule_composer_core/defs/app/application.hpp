/**
 * \file application.hpp
 * Created by Piotr Karol 2026
 */

#ifndef RULE_COMPOSER_APPLICATION_HPP
#define RULE_COMPOSER_APPLICATION_HPP

#include <app/abstract_application.hpp>
#include <rule_engine/rule_engine.hpp>
#include <util/config_parser.hpp>

class application : public abstract_application
{
public:
    explicit application(const cxxopts::ParseResult& args);

protected:
    void before_run() override;

    config_parser                parser;
    configuration_dto            config_dto;
    std::unique_ptr<rule_engine> engine;
};

#endif // RULE_COMPOSER_APPLICATION_HPP
