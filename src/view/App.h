#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_gpu.h>
#include <imgui.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <stdexcept>
#include <string>
#include <vector>
class App
{
public:
    App(const char* title, int width, int height) : window_(nullptr), renderer_(nullptr), running_(true)
    {
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) throw std::runtime_error(SDL_GetError());

        window_ = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE);
        if (!window_) throw std::runtime_error(SDL_GetError());

        renderer_ = SDL_CreateRenderer(window_, nullptr);
        if (!renderer_) throw std::runtime_error(SDL_GetError());

        initImGui();
    }

    ~App()
    {
        shutdownImGui();
        if (renderer_) SDL_DestroyRenderer(renderer_);
        if (window_) SDL_DestroyWindow(window_);
        SDL_Quit();
    }

    void run()
    {
        while (running_)
        {
            processEvents();
            render();
        }
    }

protected:
    virtual void onGui()
    {
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(1280, 720));

        ImGui::Begin("三国杀主界面",
                     nullptr,
                     ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
                         ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);

        // --- 获取可用区域 ---
        ImVec2 avail = ImGui::GetContentRegionAvail();
        float mainHeight = avail.y * 0.7f; // 主区域 70%
        float handHeight = avail.y * 0.3f; // 手牌区域 30%
        float sideWidth = 200.0f;          // 右下角角色贴图宽度

        // --- 主区域 ---
        ImGui::BeginChild("主区域", ImVec2(avail.x, mainHeight), true);
        {
            ImGui::Text("玩家操作区:");
            if (ImGui::Button("结束回合"))
            { /* 回合结束逻辑 */
            }

            ImGui::Text("回合: 1");
            ImGui::Text("当前玩家: 刘备");

            ImGui::Separator();

            ImGui::Text("其他游戏信息...");
        }
        ImGui::EndChild();

        // --- 手牌区域 + 右下角角色贴图 ---
        ImGui::BeginChild("底部区域", ImVec2(avail.x, handHeight), false);
        {
            // 左侧手牌区域
            ImGui::BeginChild("手牌区域", ImVec2(avail.x - sideWidth, handHeight), true);
            {
                ImGui::Text("玩家手牌:");
                ImGui::SameLine();
                for (int i = 0; i < 5; ++i)
                {
                    std::string cardName = "杀" + std::to_string(i + 1);
                    if (ImGui::Button(cardName.c_str()))
                    {
                        show_modal = true;
                    }
                    ImGui::SameLine();
                }
            }
            ImGui::EndChild();

            // 右下角角色贴图区域
            ImGui::SameLine();
            ImGui::BeginChild("角色贴图区域", ImVec2(sideWidth, handHeight), true);
            {
                ImGui::Text("刘备");
                // TODO: ImGui::Image 绘制角色贴图
            }
            ImGui::EndChild();
        }
        ImGui::EndChild();

        ImGui::End();

        // --- 模态窗口 ---
        if (show_modal) ImGui::OpenPopup("选择目标");
        if (ImGui::BeginPopupModal("选择目标", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text("请选择目标玩家:");
            static std::vector<std::string> targets = {"关羽", "张飞", "曹操"};
            for (auto& t : targets)
            {
                if (ImGui::Button(t.c_str()))
                {
                    show_modal = false;
                    ImGui::CloseCurrentPopup();
                }
            }
            ImGui::EndPopup();
        }
    }

private:
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    bool running_;

    void processEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);

            if (event.type == SDL_EVENT_QUIT)
            {
                running_ = false;
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
        SDL_SetRenderDrawColor(renderer_, 30, 30, 30, 255);
        SDL_RenderClear(renderer_);
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer_);
        SDL_RenderPresent(renderer_);
    }

    void initImGui()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGuiIO& io = ImGui::GetIO();

        // 创建字体
        ImFontConfig font_cfg;
        font_cfg.OversampleH = 3; // 水平采样，提高清晰度
        font_cfg.OversampleV = 1;
        font_cfg.PixelSnapH = true;

        // 加载中文字体
        io.Fonts->AddFontFromFileTTF(
            "C:/Windows/Fonts/msyh.ttc", 18.0f, &font_cfg, io.Fonts->GetGlyphRangesChineseFull());

        // 构建字体纹理
        ImGui_ImplSDL3_InitForSDLRenderer(window_, renderer_);
        ImGui_ImplSDLRenderer3_Init(renderer_);
    }

    void shutdownImGui()
    {
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
    }
    bool show_modal = true;
};
