/**
 * ************************************************************************
 *
 * @file DeckSystem.h
 * @author AnakinLiu (azrael2759@qq.com)
 * @date 2025-11-27
 * @version 0.1
 * @brief 牌堆管理系统，负责管理发牌/洗牌/检索
 *
 * ************************************************************************
 * @copyright Copyright (c) 2025 AnakinLiu
 * For study and research only, no reprinting.
 * ************************************************************************
 */
#pragma once
#include <entt/entt.hpp>
#include "entt/entity/fwd.hpp"
#include "src/context/GameContext.h"
#include "src/components/Deck.h"
#include "src/components/Events.h"
#include "src/components/Character.h"
#include "src/components/Card.h"
#include <algorithm>
#include <random>

class DeckSystem
{
public:
    explicit DeckSystem(GameContext& context) : m_context(&context) { m_context->logger->info("DeckSystem 初始化"); }

    // Disable copy and move operations due to reference member
    DeckSystem(const DeckSystem&) = default;
    DeckSystem& operator=(const DeckSystem&) = delete;
    DeckSystem(DeckSystem&&) = default;
    DeckSystem& operator=(DeckSystem&& other) = delete;
    ~DeckSystem() = default;
    void registerEvents() {

    };
    void unregisterEvents() {

    };

private:
    void onInitDeck()
    {
        // 初始化牌堆

        // 洗牌
        onShuffleDeck({});
    }
    void onCardDiscarded(events::CardDiscarded event)
    {
        auto& [player, cards, count] = event;

        auto& handCards = m_context->registry.try_get<HandCards>(player)->handCards;
        auto* equipments = m_context->registry.try_get<Equipments>(player);
        auto& [weapon, armor, attackhorse, defensehorse] = *equipments;
        // 用 unordered_set 提升查找效率
        std::unordered_set<entt::entity> cardSet(cards.begin(), cards.end());

        // 移除手牌
        auto newEnd = std::ranges::remove_if(handCards, [&](entt::entity card) { return cardSet.contains(card); });
        handCards.erase(newEnd.begin(), newEnd.end());

        auto checkDiscarded = [](entt::entity& equipments, std::unordered_set<entt::entity>& cardSet)
        {
            if (equipments != entt::null && cardSet.contains(equipments))
            {
                equipments = entt::null;
            }
        };
        checkDiscarded(weapon, cardSet);
        checkDiscarded(armor, cardSet);
        checkDiscarded(attackhorse, cardSet);
        checkDiscarded(defensehorse, cardSet);

        m_Deck.processingArea.insert(m_Deck.processingArea.end(), cards.begin(), cards.end());
    }

    void onProcessFinished()
    {
        m_Deck.discardPile.insert(m_Deck.discardPile.end(), m_Deck.processingArea.begin(), m_Deck.processingArea.end());
        m_Deck.processingArea.clear();
    }

    void onShuffleDeck(events::ShuffleDeck event)
    {
        std::random_device rdd;
        std::mt19937 gen(rdd());
        std::shuffle(m_Deck.discardPile.begin(), m_Deck.discardPile.end(), gen);
        m_Deck.drawPile.insert(m_Deck.drawPile.end(), m_Deck.discardPile.begin(), m_Deck.discardPile.end());
        m_Deck.discardPile.clear();
    }

    void onDealCards(events::DealCards event)
    {
        auto& [player, count] = event;
        auto& handCards = m_context->registry.get<HandCards>(player).handCards;

        if (m_Deck.drawPile.empty() or m_Deck.drawPile.size() < count)
        {
            // 如果摸牌堆为空，触发洗牌事件
            m_context->dispatcher.trigger<events::ShuffleDeck>();
        }
        if (!m_Deck.drawPile.empty())
        {
            handCards.insert(handCards.end(), m_Deck.drawPile.begin(), m_Deck.drawPile.begin() + count);
            m_Deck.drawPile.erase(m_Deck.drawPile.begin(), m_Deck.drawPile.begin() + count);
            m_context->dispatcher.trigger<events::CardDrawn>(
                {.player = player,
                 .cards = std::span<entt::entity>(handCards.end() - count, handCards.end()),
                 .count = count});
        }
        else
        {
            m_context->logger->warn("无法发牌，摸牌堆和弃牌堆均为空");
            m_context->dispatcher.trigger<events::GameEnd>({"无法发牌，游戏结束"});
        }
    }

    void onFindCardInDrawPile(events::FindCardInDrawPile event)
    {
        m_findCard = entt::null;
        auto& [cardName, suitType, rank] = event;
        {
            auto it1 = std::ranges::find_if(m_Deck.drawPile.begin(),
                                            m_Deck.drawPile.end(),
                                            [&](entt::entity card)
                                            {
                                                auto& meta = m_context->registry.get<MetaCardInfo>(card);
                                                return meta.name == cardName;
                                            });
            if (it1 != m_Deck.drawPile.end())
            {
                m_findCard = *it1;
                return;
            }
        }
    }
    GameContext* m_context;
    Deck m_Deck;
    entt::entity m_findCard{entt::null};
};