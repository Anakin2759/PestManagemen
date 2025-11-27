/**
 * ************************************************************************
 *
 * @file ALabel.h
 * @author AnakinLiu (azrael2759@qq.com)
 * @date 2025-11-27
 * @version 0.1
 * @brief
 *
 * ************************************************************************
 * @copyright Copyright (c) 2025 AnakinLiu
 * For study and research only, no reprinting.
 * ************************************************************************
 */

#pragma once
#include "src/view/AWidget.h"
#include <string>
// 标签组件
class ALabel : public AWidget
{
public:
    explicit ALabel(std::string text) : m_text(std::move(text)) {}

    void render(const ImVec2& position, const ImVec2& size) override
    {
        ImGui::SetCursorPos(position);
        ImGui::TextUnformatted(m_text.c_str());
    }

    ImVec2 calculateSize() override
    {
        if (isFixedSize())
        {
            return {getMinWidth(), getMinHeight()};
        }
        return ImGui::CalcTextSize(m_text.c_str());
    }

private:
    std::string m_text;
};