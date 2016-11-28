using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using UnityEngine;

public class DynamicPluginsManager
{
    public struct PluginId
    {
        public readonly IntPtr Ptr;

        public PluginId(IntPtr ptr)
        {
            Ptr = ptr;
        }
    }

    public class PluginException
        : Exception
    {
        private readonly string _name;

        public PluginException(string name)
        {
            _name = name;
        }

        public override string ToString()
        {
            return string.Format("Bad plugin: {0}", _name);
        }
    }

    public class FunctionNotFoundException
        : Exception
    {
        private readonly string _name;

        public FunctionNotFoundException(string name)
        {
            _name = name;
        }

        public override string ToString()
        {
            return string.Format("Function on found: {0}", _name);
        }
    }

    
    public static PluginId? Find(string name)
    {
        var id = find_plugin(WrapName(name));
        if (!ValidId(id))
            return null;

        return new PluginId(id);
    }

    public static PluginId Register(string name)
    {
        var id = register_plugin(WrapName(name));
        if (ValidId(id))
            return new PluginId(id);

        throw new PluginException(name);
    }

    public static PluginId FindOrRegister(string name)
    {
        var id = Find(name) ?? Register(name);
        return id;
    }

    public static void Unregister(PluginId id)
    {
        unregister_plugin(id.Ptr);
    }

    public static IntPtr GetRenderingEvent(PluginId id)
    {
        return get_rendering_event(id.Ptr);
    }

    public static Delegate GetFunction<TDelegate>(PluginId id, string name) 
    {
        var ptr = get_plugin_function(id.Ptr, name);

        if (ptr == IntPtr.Zero)
            throw new FunctionNotFoundException(name);

        return Marshal.GetDelegateForFunctionPointer(ptr, typeof(TDelegate));
    }

    private static string WrapName(string name)
    {
        return string.Format("{0}/../native/out/bin/{1}_{2}/{3}.dll", Application.dataPath, "Debug", "x64", name);
        //return name;
    }

    private static bool ValidId(IntPtr id)
    {
        return id != IntPtr.Zero;
    }

    private const string LibName = "dynamic_plugins_manager";
    [DllImport(LibName)]
    private static extern IntPtr find_plugin([MarshalAs(UnmanagedType.LPStr)] string name);
    [DllImport(LibName)]
    private static extern IntPtr register_plugin([MarshalAs(UnmanagedType.LPStr)] string name);
    [DllImport(LibName)]
    private static extern void unregister_plugin(IntPtr id);
    [DllImport(LibName)]
    private static extern IntPtr get_rendering_event(IntPtr id);
    [DllImport(LibName)]
    private static extern IntPtr get_plugin_function(IntPtr id, [MarshalAs(UnmanagedType.LPStr)] string name);
}

