

#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_gpu.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
class AWidget
{
public:
    AWidget() = default;
    virtual ~AWidget() = default;
    AWidget(const AWidget&) = default;
    AWidget& operator=(const AWidget&) = default;
    AWidget(AWidget&&) = default;
    AWidget& operator=(AWidget&&) = default;

    void setFixedSize(float width, float height)
    {
        m_fixedWidth = width;
        m_fixedHeight = height;
        m_useFixedSize = true;
    }

    void setMinimumSize(float width, float height)
    {
        m_minWidth = width;
        m_minHeight = height;
    }

    void setMaximumSize(float width, float height)
    {
        m_maxWidth = width;
        m_maxHeight = height;
    }

    virtual void render(const ImVec2& position, const ImVec2& size) = 0;
    virtual ImVec2 calculateSize() = 0;

    [[nodiscard]] float getMinWidth() const { return m_minWidth; }
    [[nodiscard]] float getMinHeight() const { return m_minHeight; }
    [[nodiscard]] float getMaxWidth() const { return m_maxWidth; }
    [[nodiscard]] float getMaxHeight() const { return m_maxHeight; }
    [[nodiscard]] bool isFixedSize() const { return m_useFixedSize; }

private:
    bool m_useFixedSize = false;
    float m_fixedWidth = 0, m_fixedHeight = 0;
    float m_minWidth = 0, m_minHeight = 0;
    float m_maxWidth = FLT_MAX, m_maxHeight = FLT_MAX;
};