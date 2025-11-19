#pragma once
#include <cstdint>
// 回合的阶段
enum class TurnPhase : uint8_t
{
    GAME_START,
    START,   // 回合开始阶段
    JUDGE,   // 判定阶段
    DRAW,    // 摸牌阶段
    PLAY,    // 出牌阶段
    DISCARD, // 弃牌阶段
    END,     // 回合结束阶段
    GAME_OVER
};

enum class GameMode : uint8_t
{
    CLASSIC_FIVE,
    CLASSIC_EIGHT,
    TEAM_BATTLE,
    CHANLLENGE_PEST
};

enum class GenderType : uint8_t
{
    FEMALE,
    MALE,
    OTHER
};

enum class IdentityType : uint8_t
{
    MEMBER,
    OWNER,
    ADMIN,
    ROGUE,
    PESTMAN
};
enum class FactionType : uint8_t
{
    VIRGIN,
    PLAYMAN,
    BOOMER
};

enum class SkillType : uint8_t
{
    PASSIVE,  // 被动技能
    ACTIVE,   // 主动技能
    REACTIVE, // 反应技能
    LOCKED,
    PHASELIMITED,
    AWAKENING // 觉醒
};

enum class CardType : uint8_t
{
    BASIC,
    TRICK,
    EQUIPMENT
};

enum class StatusType : uint8_t
{
    HORIZONTAL_PLACEMENT, // 横置
    STUNNED,
    SHIELDED
};

enum class Suit : uint8_t
{
    HEARTS,   // 红桃
    DIAMONDS, // 方块
    CLUBS,    // 梅花
    SPADES,   // 黑桃
    JOKER     // 小王或大王
};