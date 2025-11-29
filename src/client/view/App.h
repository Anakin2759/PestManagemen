/**
 * ************************************************************************
 *
 * @file App.h
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

#include "src/view/ALayout.h"
#include "src/view/ALabel.h"
#include "src/view/AButton.h"
#include <entt/entt.hpp>
#include <iostream>

// 主应用类
class App
{
public:
    constexpr static int DEFAULT_WINDOW_WIDTH = 1200;
    constexpr static int DEFAULT_WINDOW_HEIGHT = 800;
    App(const char* title, int width, int height)
    {
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
        {
            std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
            throw std::runtime_error(SDL_GetError());
        }

        m_window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE);
        if (m_window == nullptr)
        {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            throw std::runtime_error(SDL_GetError());
        }
        std::cerr << "Window created: " << title << " (" << width << "x" << height << ")" << std::endl;
        m_renderer = SDL_CreateRenderer(m_window, nullptr);
        if (m_renderer == nullptr)
        {
            throw std::runtime_error(SDL_GetError());
        }

        initImGui();
        setupUI();
    }

    virtual ~App()
    {
        shutdownImGui();
        if (m_renderer == nullptr)
        {
            SDL_DestroyRenderer(m_renderer);
        }
        if (m_window == nullptr)
        {
            SDL_DestroyWindow(m_window);
        }
        SDL_Quit();
    }

    App(const App&) = delete;
    App& operator=(const App&) = delete;
    App(App&&) = delete;
    App& operator=(App&&) = delete;

    void run()
    {
        m_running = true;
        while (m_running)
        {
            processEvents();
            render();
        }
    }

    void stop() { m_running = false; }

protected:
    virtual void setupUI()
    {
        // 创建主布局
        auto mainLayout = std::make_shared<AVBoxLayout>();
        mainLayout->setSpacing(10);
        mainLayout->setMargins(10, 10, 10, 10);

        // 顶部信息栏
        auto topLayout = std::make_shared<AHBoxLayout>();
        topLayout->addWidget(std::make_shared<ALabel>("回合: 1"));
        topLayout->addWidget(std::make_shared<ALabel>("当前玩家: 刘备"));
        auto endTurnButton = std::make_shared<AButton>("结束回合");
        topLayout->addWidget(endTurnButton);

        // 主游戏区域
        auto gameAreaLayout = std::make_shared<AHBoxLayout>();
        gameAreaLayout->setSpacing(15);

        // 左侧玩家区域
        auto playerLayout = std::make_shared<AVBoxLayout>();
        playerLayout->addWidget(std::make_shared<ALabel>("玩家状态"));
        playerLayout->addWidget(std::make_shared<ALabel>("血量: 100"));

        // 右侧操作区域
        auto actionLayout = std::make_shared<AVBoxLayout>();
        actionLayout->addWidget(std::make_shared<ALabel>("可用操作"));

        auto cardLayout = std::make_shared<AHBoxLayout>();
        for (int i = 0; i < 5; ++i)
        {
            auto cardAButton = std::make_shared<AButton>("杀" + std::to_string(i + 1));
            cardLayout->addWidget(cardAButton);
        }
        actionLayout->addWidget(std::make_shared<ALabel>("手牌:"));
        actionLayout->addWidget(cardLayout);

        gameAreaLayout->addWidget(playerLayout);
        gameAreaLayout->addWidget(actionLayout);

        // 底部状态栏
        auto bottomLayout = std::make_shared<AHBoxLayout>();
        bottomLayout->addWidget(std::make_shared<ALabel>("游戏状态: 进行中"));

        // 组合所有布局
        mainLayout->addWidget(topLayout);
        mainLayout->addWidget(gameAreaLayout);
        mainLayout->addWidget(bottomLayout);

        m_rootLayout = mainLayout;
    }

    virtual void onGui()
    {
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

        ImGui::Begin("MainWindow",
                     nullptr,
                     static_cast<ImGuiWindowFlags>(static_cast<unsigned int>(ImGuiWindowFlags_NoTitleBar) |
                                                   static_cast<unsigned int>(ImGuiWindowFlags_NoResize) |
                                                   static_cast<unsigned int>(ImGuiWindowFlags_NoMove) |
                                                   static_cast<unsigned int>(ImGuiWindowFlags_NoScrollbar) |
                                                   static_cast<unsigned int>(ImGuiWindowFlags_NoCollapse)));

        if (m_rootLayout)
        {
            ImVec2 avail = ImGui::GetContentRegionAvail();
            m_rootLayout->render(ImVec2(0, 0), avail);
        }

        ImGui::End();
    }

private:
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    bool m_running = true;
    std::shared_ptr<ALayout> m_rootLayout;

    void processEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);

            if (event.type == SDL_EVENT_QUIT)
            {
                m_running = false;
            }
        }
    }

    void render()
    {
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        onGui();

        ImGui::Render();
        SDL_SetRenderDrawColor(m_renderer, 30, 30, 30, 255);
        SDL_RenderClear(m_renderer);
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_renderer);
        SDL_RenderPresent(m_renderer);
    }

    void initImGui()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        ImFontConfig fontCfg;
        fontCfg.OversampleH = 3;
        fontCfg.OversampleV = 1;
        fontCfg.PixelSnapH = true;

        io.Fonts->AddFontFromFileTTF(
            "C:/Windows/Fonts/msyh.ttc", 18.0F, &fontCfg, io.Fonts->GetGlyphRangesChineseFull());

        ImGui_ImplSDL3_InitForSDLRenderer(m_window, m_renderer);
        ImGui_ImplSDLRenderer3_Init(m_renderer);
    }

    static void shutdownImGui()
    {
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
    }
};