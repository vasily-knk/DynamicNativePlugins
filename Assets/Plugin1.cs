using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

sealed class Plugin1
{
    private static Plugin1 _instance;

    private delegate int GetNumberDelegate();
    private delegate void ProcessTextureDelegate(IntPtr handle);

    private readonly DynamicPluginsManager.PluginId _id;
    private GetNumberDelegate _getNumberDelegate;
    private ProcessTextureDelegate _processTextureDelegate;
    
    private Plugin1()
    {
        _id = DynamicPluginsManager.FindOrRegister("plugin1");
    }

    public int GetNumber()
    {
        if (_getNumberDelegate == null)
            _getNumberDelegate = DynamicPluginsManager.GetFunction<GetNumberDelegate>(_id, "get_number") as GetNumberDelegate;

        return _getNumberDelegate.Invoke();
    }

    public void ProcessTexture(IntPtr handle)
    {
        if (_processTextureDelegate == null)
            _processTextureDelegate = DynamicPluginsManager.GetFunction<ProcessTextureDelegate>(_id, "process_texture") as ProcessTextureDelegate;

        _processTextureDelegate.Invoke(handle);
    }

    public IntPtr GetRenderingEvent()
    {
        return DynamicPluginsManager.GetRenderingEvent(_id);
    }

    public static Plugin1 Instance
    {
        get { return _instance ?? (_instance = new Plugin1()); }
    }

    public static void Shutdown()
    {
        if (_instance == null) 
            return;

        DynamicPluginsManager.Unregister(_instance._id);
        _instance = null;
    }
}

