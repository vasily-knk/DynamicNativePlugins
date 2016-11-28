using System;
using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;
using UnityEditor;


public class PluginTest : MonoBehaviour
{
    private Vector3 _oldPos;

    // Use this for initialization
	void Start ()
	{
        Debug.LogFormat("Number: {0}", Plugin1.Instance.GetNumber());
	    var tex = Resources.Load<Texture2D>("grass");
        Plugin1.Instance.ProcessTexture(tex.GetNativeTexturePtr());
	}

    void Update()
    {
        var pos = gameObject.transform.position;
        if (pos != _oldPos)
        {
            Debug.LogFormat("Postion: {0}", pos);
            _oldPos = pos;
        }
    }

	void OnPreRender () {
        GL.IssuePluginEvent(Plugin1.Instance.GetRenderingEvent(), 117);
	}

    void OnApplicationQuit()
    {
        Plugin1.Shutdown();
    }
}
