using System;
using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;


public class PluginTest : MonoBehaviour
{
    private delegate int GetNumber();
    
    private struct PluginData
    {
        public DynamicPluginsManager.PluginId id;
        public GetNumber getNumber;
    }

    private const string PluginName = @"C:\my\unity\DynamicNativePlugins\native\out\bin\Debug_x64\plugin1.dll";

    private PluginData? _plugin = null;
    
    // Use this for initialization
	void Start ()
	{
	    var idd =  DynamicPluginsManager.Register(PluginName);
        _plugin = new PluginData
        {
            id = idd,
            getNumber = DynamicPluginsManager.GetFunction<GetNumber>(idd, "get_number") as GetNumber,
        };

        Debug.LogFormat("Number: {0}", _plugin.Value.getNumber());
	}

    void OnDestroy()
    {
        Shutdown();
    }
	
	void OnPreRender () {
	}

    void OnApplicationQuit()
    {
        Shutdown();
    }

    private void Shutdown()
    {
        if (_plugin == null)
            return;

        DynamicPluginsManager.Unregister(_plugin.Value.id);
        _plugin = null;
    }
}
