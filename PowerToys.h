#pragma once

#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"

#include "version.h"
constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH);

class PowerToys : public BakkesMod::Plugin::BakkesModPlugin, public BakkesMod::Plugin::PluginSettingsWindow
{

    void RenderSettings() override;
    std::string GetPluginName() override;
    void SetImGuiContext(uintptr_t ctx) override;

public:
    virtual void onLoad();
    virtual void onUnload();

    void LoadHooks();
    void StartGame(std::string name);
    void EndGame(std::string name);
    void Reset(std::string name);
    void FAQ();

private:
    void log(std::string msg);
    int teamNumber;
    int playlistID;
    int pl;
    bool winnerset = false;
    bool pluginEnabled = false;
    bool losefreeplayEnabled = false;
    bool winfreeplayEnabled = false;
    bool queueEnabled = false;
    bool freeplayAndQueue = false;
};
