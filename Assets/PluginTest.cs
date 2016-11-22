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


    private PluginData? _plugin = null;
    
    // Use this for initialization
	void Start ()
	{
        var pluginName = string.Format("{0}/../native/out/bin/{1}_{2}/plugin1.dll", Application.dataPath, "Debug", "x64");
        Debug.Log(pluginName);
	    var idd =  DynamicPluginsManager.Register(pluginName);
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
