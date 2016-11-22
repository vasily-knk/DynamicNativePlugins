#pragma once

#include "common/lib_wrapper.h"


typedef HMODULE plugin_id;
const auto plugin_id_none = nullptr;

struct plugin_t
{
    explicit plugin_t(char const *name, IUnityInterfaces* interfaces)
        : name_(name)
        , lib_(name)
    {
        if (!lib_.valid())
            return;

        typedef void (UNITY_INTERFACE_API *pfn_t)(IUnityInterfaces* unityInterfaces);
        
        if (auto fn = lib_.get_function<pfn_t>("UnityPluginLoad"))
            fn(interfaces);
    }

    ~plugin_t()
    {
        if (!lib_.valid())
            return;

        typedef void (UNITY_INTERFACE_API *pfn_t)();

        if (auto fn = lib_.get_function<pfn_t>("UnityPluginUnload"))
            fn();
    }

    UnityRenderingEvent rendering_event() const
    {
        if (!lib_.valid())
            return nullptr;
        
        typedef UnityRenderingEvent (UNITY_INTERFACE_API *plugin_rendering_event_pfn)();

        auto fn = lib_.get_function<plugin_rendering_event_pfn>("get_rendering_event");
        if (!fn)
            return nullptr;

        return fn();
    }

    FARPROC get_function(char const *name) const
    {
        if (!lib_.valid())
            return nullptr;

        return lib_.get_function<FARPROC>(name);
    }

    string const &name() const
    {
        return name_;
    }

    bool valid() const
    {
        return lib_.valid();
    }

    plugin_id id() const
    {
        if (!valid())
            return plugin_id_none;

        return lib_.lib();
    }

private:
    string name_;
    lib_wrapper lib_;
};

typedef shared_ptr<plugin_t> plugin_ptr;
