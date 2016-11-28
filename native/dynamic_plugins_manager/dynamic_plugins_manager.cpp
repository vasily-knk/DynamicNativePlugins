#include "stdafx.h"
#include <IUnityInterface.h>
#include <IUnityGraphics.h>

#include "common/dynamic_plugin.h"
#include "common/lib_wrapper.h"

namespace 
{
    
    typedef std::map<plugin_id, plugin_ptr> plugins_map_t;
    
    IUnityInterfaces* g_interfaces = nullptr;
    plugins_map_t g_plugins;

} // namespace 


extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
    UnityPluginLoad(IUnityInterfaces* unityInterfaces)
{
    g_interfaces = unityInterfaces;
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
    UnityPluginUnload()
{
    g_plugins.clear();
}


extern "C" plugin_id UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
    find_plugin(char const *name)
{
    auto it = std::find_if(g_plugins.begin(), g_plugins.end(), 
        [name](plugins_map_t::value_type const &p)
    {
        return p.second->name() == name;
    });

    if (it == g_plugins.end())
        return plugin_id_none;
                                            
    return it->first;    
}
                            
extern "C" plugin_id UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
    register_plugin(char const *name)              
{                           
    auto exisiting_id = find_plugin(name);
    if (exisiting_id != plugin_id_none)
        return plugin_id_none;

    auto rp = make_shared<plugin_t>(name, g_interfaces);
    if (!rp->valid())
        return plugin_id_none;

    auto id = rp->id();
    g_plugins.emplace(id, rp);               


    return id;                          
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
    unregister_plugin(plugin_id id)              
{
    auto it = g_plugins.find(id);       
    if (it == g_plugins.end())
        return;                    

    g_plugins.erase(it);
}

extern "C" UnityRenderingEvent UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
    get_rendering_event(plugin_id id)
{
    auto it = g_plugins.find(id);        
    if (it == g_plugins.end())             
        return nullptr;                              

    return it->second->rendering_event();
}                                     

extern "C" FARPROC UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
get_plugin_function(plugin_id id, char const *name)
{
    auto it = g_plugins.find(id);       
    if (it == g_plugins.end())
        return nullptr;                    

    return it->second->get_function(name);
}
