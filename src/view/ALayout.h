/**
 * ************************************************************************
 *
 * @file ALayout.h
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
#include <memory>
#include <vector>
#include "src/view/AWidget.h"
#include <sys/stat.h>

// 模拟 Qt 的布局方向
enum class LayoutDirection : uint8_t
{
    HORIZONTAL,
    VERTICAL
};

// 基础组件类（模拟 QWidget）

// 布局容器（模拟 QLayout）
class ALayout : public AWidget
{
public:
    void addWidget(const std::shared_ptr<AWidget>& widget) { m_widgets.push_back(widget); }

    void setDirection(LayoutDirection direction) { m_direction = direction; }

    void setSpacing(float spacing) { m_spacing = spacing; }

    void setMargins(float left, float top, float right, float bottom) { m_margins = ImVec4(left, top, right, bottom); }

    [[nodiscard]] const std::vector<std::shared_ptr<AWidget>>& getWidgets() const { return m_widgets; }
    [[nodiscard]] const ImVec4& getMargins() const { return m_margins; }
    [[nodiscard]] float getSpacing() const { return m_spacing; }

private:
    std::vector<std::shared_ptr<AWidget>> m_widgets;
    LayoutDirection m_direction = LayoutDirection::HORIZONTAL;
    float m_spacing = 5.0F;
    ImVec4 m_margins = ImVec4(0, 0, 0, 0); // left, top, right, bottom
};

// 水平布局（模拟 QAHBoxLayout）
class AHBoxLayout : public ALayout
{
public:
    AHBoxLayout() { setDirection(LayoutDirection::HORIZONTAL); }

    void render(const ImVec2& position, const ImVec2& size) override
    {
        ImVec2 currentPos = ImVec2(position.x + getMargins().x, position.y + getMargins().y);
        float availableWidth = size.x - getMargins().x - getMargins().z;
        float availableHeight = size.y - getMargins().y - getMargins().w;

        // 计算每个widget的宽度
        int stretchCount = 0;
        std::vector<float> widths;
        for (const auto& widget : getWidgets())
        {
            ImVec2 widgetSize = widget->calculateSize();
            if (widget->isFixedSize())
            {
                widths.push_back(widget->getMinWidth());
            }
            else
            {
                widths.push_back(widgetSize.x);
                stretchCount++;
            }
        }

        // 分配剩余空间
        if (stretchCount > 0)
        {
            float totalFixedWidth = 0;
            for (size_t i = 0; i < getWidgets().size(); ++i)
            {
                if (!getWidgets()[i]->isFixedSize())
                {
                    continue;
                }
                totalFixedWidth += widths[i];
            }

            float remainingWidth =
                availableWidth - totalFixedWidth - (getSpacing() * static_cast<float>(getWidgets().size() - 1));
            float stretchWidth = remainingWidth / static_cast<float>(stretchCount);

            for (size_t i = 0; i < getWidgets().size(); ++i)
            {
                if (!getWidgets()[i]->isFixedSize())
                {
                    widths[i] = stretchWidth;
                }
            }
        }

        // 渲染widgets
        for (size_t i = 0; i < getWidgets().size(); ++i)
        {
            getWidgets()[i]->render(currentPos, ImVec2(widths[i], availableHeight));
            currentPos.x += widths[i] + getSpacing();
        }
    }

    ImVec2 calculateSize() override
    {
        float totalWidth = getMargins().x + getMargins().z;
        float totalHeight = 0;

        for (const auto& widget : getWidgets())
        {
            ImVec2 size = widget->calculateSize();
            totalWidth += size.x;
            totalHeight = std::max(totalHeight, size.y);
        }

        totalWidth += getSpacing() * static_cast<float>(getWidgets().size() - 1);
        totalHeight += getMargins().y + getMargins().w;

        return {totalWidth, totalHeight};
    }
};

// 垂直布局（模拟 QAVBoxLayout）
class AVBoxLayout : public ALayout
{
public:
    AVBoxLayout() { setDirection(LayoutDirection::VERTICAL); }

    void render(const ImVec2& position, const ImVec2& size) override
    {
        ImVec2 currentPos = ImVec2(position.x + getMargins().x, position.y + getMargins().y);
        float availableWidth = size.x - getMargins().x - getMargins().z;
        float availableHeight = size.y - getMargins().y - getMargins().w;

        // 计算每个widget的高度
        int stretchCount = 0;
        std::vector<float> heights;
        for (const auto& widget : getWidgets())
        {
            ImVec2 widgetSize = widget->calculateSize();
            if (widget->isFixedSize())
            {
                heights.push_back(widget->getMaxHeight());
            }
            else
            {
                heights.push_back(widgetSize.y);
                stretchCount++;
            }
        }

        // 分配剩余空间
        if (stretchCount > 0)
        {
            float totalFixedHeight = 0;
            for (size_t i = 0; i < getWidgets().size(); ++i)
            {
                if (!getWidgets()[i]->isFixedSize())
                {
                    continue;
                }
                totalFixedHeight += heights[i];
            }

            float remainingHeight =
                availableHeight - totalFixedHeight - (getSpacing() * static_cast<float>(getWidgets().size() - 1));
            float stretchHeight = remainingHeight / static_cast<float>(stretchCount);

            for (size_t i = 0; i < getWidgets().size(); ++i)
            {
                if (!getWidgets()[i]->isFixedSize())
                {
                    heights[i] = stretchHeight;
                }
            }
        }

        // 渲染widgets
        for (size_t i = 0; i < getWidgets().size(); ++i)
        {
            getWidgets()[i]->render(currentPos, ImVec2(availableWidth, heights[i]));
            currentPos.y += heights[i] + getSpacing();
        }
    }

    ImVec2 calculateSize() override
    {
        float totalWidth = 0;
        float totalHeight = getMargins().y + getMargins().w;

        for (const auto& widget : getWidgets())
        {
            ImVec2 size = widget->calculateSize();
            totalWidth = std::max(totalWidth, size.x);
            totalHeight += size.y;
        }

        totalWidth += getMargins().x + getMargins().z;
        totalHeight += getSpacing() * static_cast<float>(getWidgets().size() - 1);

        return {totalWidth, totalHeight};
    }
};