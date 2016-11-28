#include "stdafx.h"

#include "common/dynamic_plugin.h"
#include <fstream>
#include "wombat_skybox.h"

namespace
{
    std::ofstream g_log_file("c:\\my\\aaa.txt", std::ofstream::out | std::ofstream::app);
    IUnityGraphics *g_graphics = nullptr;
    unique_ptr<wombat_skybox> g_wombat_skybox;
}

#define EXPORTED_FUNCTION(ret_type) extern "C" ret_type UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API


void UNITY_INTERFACE_API device_event_callback(UnityGfxDeviceEventType eventType);

EXPORTED_FUNCTION(void) UnityPluginLoad(IUnityInterfaces* unityInterfaces)
{
    auto cur = boost::filesystem::current_path();
    
    g_graphics = unityInterfaces->Get<IUnityGraphics>();
    if (!g_graphics)
        return;;

    g_graphics->RegisterDeviceEventCallback(device_event_callback);
    auto renderer = g_graphics->GetRenderer();

    device_event_callback(kUnityGfxDeviceEventInitialize);

    g_log_file << "Plugin1 load" << std::endl;
}

EXPORTED_FUNCTION(void) UnityPluginUnload()
{
    if (!g_graphics)
        return;

    g_graphics->UnregisterDeviceEventCallback(device_event_callback);
    g_graphics = nullptr;

    g_log_file << "Plugin1 unload" << std::endl;
}

void UNITY_INTERFACE_API on_rendering_event(int event_id)
{
    if (g_wombat_skybox)
    {
        g_wombat_skybox->render();
    }
}


EXPORTED_FUNCTION(UnityRenderingEvent) get_rendering_event()
{
    return &on_rendering_event;    
}

EXPORTED_FUNCTION(int) get_number()
{
    return 1117;
}

EXPORTED_FUNCTION(void) process_texture(void *handle)
{

}

void UNITY_INTERFACE_API device_event_callback(UnityGfxDeviceEventType eventType)
{
    try
    {
        if (eventType == kUnityGfxDeviceEventInitialize)
        {
            g_wombat_skybox = create_wombat_skybox();
        }
        else if (eventType == kUnityGfxDeviceEventShutdown)
        {
            g_wombat_skybox.reset();
        }
    }
    catch (std::exception const &e)
    {
        int aaa = 5;         
    }
}
