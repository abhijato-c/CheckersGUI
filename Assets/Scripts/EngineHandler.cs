using System;
using System.Diagnostics;
using System.IO;
using UnityEngine;

public class EngineHandler{
    private Process Engine;
    private StreamWriter Input;
    private StreamReader Output;

    public void Start() {
        // Determine the correct binary path depending on the operating system
        string binaryName = "Checkers.exe";
        #if UNITY_STANDALONE_LINUX || UNITY_EDITOR_LINUX
            binaryName = "Checkers";
        #endif
        string binaryPath = Path.Combine(Application.streamingAssetsPath, binaryName);

        // Configure the process start settings
        ProcessStartInfo startInfo = new ProcessStartInfo
        {
            FileName = binaryPath,
            UseShellExecute = false,
            RedirectStandardInput = true,
            RedirectStandardOutput = true,
            RedirectStandardError = true,
            CreateNoWindow = true
        };

        try {
            Engine = new Process { StartInfo = startInfo };
            Engine.Start();
            Input = Engine.StandardInput;
            Output = Engine.StandardOutput;

            SendCommand("isready");
        }
        catch (Exception e) {
            Engine = null;
            Input = null;
            Output = null;
            UnityEngine.Debug.LogError($"Failed to start engine: {e.Message}");
        }
    }

    private void SendCommand(string command) {
        if (Input != null) {
            Input.WriteLine(command);
            Input.Flush();
        } 
        else {
            UnityEngine.Debug.LogError("Engine input stream is not initialized.");
        }
    }

    public void GetMove(ulong wp, ulong bp, ulong wk, ulong bk, bool turn, int chain) {
        if (Input == null) {
            UnityEngine.Debug.LogError("Engine input stream is not initialized.");
            return;
        }
        string positionCommand = $"position {wp} {wk} {bp} {bk} {chain} {(turn ? "w" : "b")}";
        SendCommand(positionCommand);
        SendCommand("go movetime 1000");

        string line;
        
        while ((line = Output.ReadLine()) != null){
            if (line.StartsWith("bestmove")) {
                string move = line.Split(' ')[1];
                UnityEngine.Debug.Log($"Engine wants to move: {move}");
                Main.Instance.ProcessEngineMove(move);
                break;
            }
        }
    }

    public void Kill(){
        if (Engine == null || Engine.HasExited) return;
        try{
            Input.WriteLine("quit");
            Input.Flush();
            if (!Engine.WaitForExit(100)) Engine.Kill();
        }
        catch (Exception e){
            UnityEngine.Debug.LogWarning($"Error while killing engine: {e.Message}");
        }
        finally{
            Engine.Dispose();
            Engine = null;
            Input = null;
            Output = null;
            UnityEngine.Debug.Log("Engine killed.");
        }
    }
}