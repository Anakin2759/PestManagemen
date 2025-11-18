#include <string>
#include <functional>
#include <entt/entt.hpp>
#include "src/common/Common.h"
struct MetaCardInfo
{
    std::string name;
    std::string description; // 新增描述字段
    CardType type;
    std::function<void(entt::registry&, entt::entity&, entt::entity&)> onUse; // or custom signature
};

struct CardCost
{
    int mana = 0;
    int energy = 0;
};
struct CardTarget
{
    bool need_target = true;
    int max_targets = 1;
    std::function<bool(entt::entity)> filter; // 目标筛选规则
};
inline entt::entity createCard(entt::registry& reg,
                               std::string name,
                               std::string description,
                               CardType type,
                               std::function<void(entt::registry&, entt::entity&, entt::entity&)> onUse)
{
    auto e = reg.create();
    reg.emplace<MetaCardInfo>(e, MetaCardInfo{name, description, type, onUse});
    return e;
}
