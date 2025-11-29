#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <entt/entt.hpp>

struct UseCardMessage
{
    entt::entity player;
    entt::entity card;
    std::vector<entt::entity> targets;

    static constexpr const char* type = "UseCard";

    [[nodiscard]] nlohmann::json toJson() const
    {
        return {{"type", type}, {"player", player}, {"card", card}, {"targets", targets}};
    }

    static UseCardMessage fromJson(const nlohmann::json& json)
    {
        return {.player = json.at("player").get<entt::entity>(),
                .card = json.at("card").get<entt::entity>(),
                .targets = json.at("targets").get<std::vector<entt::entity>>()};
    }
};