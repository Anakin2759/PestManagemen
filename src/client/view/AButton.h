

#pragma once
#include "src/view/AWidget.h"
#include <string>
#include <functional>
// 按钮组件

class AButton : public AWidget
{
public:
    explicit AButton(std::string text, std::function<void()> onClick = nullptr)
        : m_text(std::move(text)), m_onClick(std::move(onClick))
    {
    }

    void render(const ImVec2& position, const ImVec2& size) override
    {
        ImGui::SetCursorPos(position);
        if (ImGui::Button(m_text.c_str(), size))
        {
            if (m_onClick)
            {
                m_onClick();
            }
        }
    }

    ImVec2 calculateSize() override
    {
        if (isFixedSize())
        {
            return ImVec2(getMinWidth(), getMinHeight());
        }
        ImVec2 textSize = ImGui::CalcTextSize(m_text.c_str());
        return ImVec2(textSize.x + 20, textSize.y + 10); // 加上padding
    }

private:
    std::string m_text;
    std::function<void()> m_onClick;
};