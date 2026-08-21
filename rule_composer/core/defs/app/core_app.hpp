/**
 * \file core_app.hpp
 * Created by Piotr Karol 2026
 */

#ifndef RULE_COMPOSER_APPLICATION_HPP
#define RULE_COMPOSER_APPLICATION_HPP

#include <app/rule_engine.hpp>
#include <rule_composer_lib/app/application.hpp>
#include <util/config_parser.hpp>

#include "comm/communication_hub.hpp"

namespace rule_composer::core::app
{
    class core_app : public lib::app::application
    {
    public:

        explicit core_app( const cxxopts::ParseResult& args );

    protected:

        void before_run( ) override;

        util::config_parser            parser;
        dto::configuration_dto         config_dto;
        std::unique_ptr< rule_engine > engine;
        std::unique_ptr< comm::communication_hub > comm_hub;
    };
} // namespace rule_composer::core::app

#endif // RULE_COMPOSER_APPLICATION_HPP
