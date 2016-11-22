#include "stdafx.h"

#include "common/dynamic_plugin.h"
#include <fstream>

namespace
{
    std::ofstream g_log_file("c:\\my\\aaa.txt", std::ofstream::out | std::ofstream::app);
}

#define EXPORTED_FUNCTION(ret_type) extern "C" ret_type UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API


EXPORTED_FUNCTION(void) UnityPluginLoad(IUnityInterfaces* unityInterfaces)
{
    g_log_file << "Plugin1 load" << std::endl;
}

EXPORTED_FUNCTION(void) UnityPluginUnload()
{
    g_log_file << "Plugin1 unload" << std::endl;
}

void UNITY_INTERFACE_API on_rendering_event(int event_id)
{
    g_log_file << "Plugin1 rendering event: " << event_id << std::endl;       
}


EXPORTED_FUNCTION(UnityRenderingEvent) get_rendering_event()
{
    return &on_rendering_event;    
}

EXPORTED_FUNCTION(int) get_number()
{
    return 239;
}
