using System;
using System.Diagnostics;
using System.IO;
using UnityEngine;

public class EngineHandler{
    private Process engineProcess;
    private StreamWriter engineInputStream;

    public void Start() {
        // Determine the correct binary path depending on the operating system
        string binaryName = "CheckersEngine.exe";
        #if UNITY_STANDALONE_LINUX || UNITY_EDITOR_LINUX
            binaryName = "CheckersEngine";
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
            engineProcess = new Process { StartInfo = startInfo };
            
            // Hook up the output reader event
            engineProcess.OutputDataReceived += new DataReceivedEventHandler(OnEngineOutput);
            engineProcess.ErrorDataReceived += new DataReceivedEventHandler(OnEngineError);

            engineProcess.Start();
            
            // Start listening asynchronously to the engine's stdout
            engineProcess.BeginOutputReadLine();
            engineProcess.BeginErrorReadLine();

            engineInputStream = engineProcess.StandardInput;

            // Handshake with your engine
            SendCommand("isready");
        }
        catch (Exception e) {
            UnityEngine.Debug.LogError($"Failed to start engine: {e.Message}");
        }
    }

    public void SendCommand(string command) {
        if (engineInputStream != null) {
            engineInputStream.WriteLine(command);
            UnityEngine.Debug.Log($"sent cmd: {command}");
            engineInputStream.Flush();
        }
    }

    public void GetMove(ulong wp, ulong bp, ulong wk, ulong bk, bool turn, int chain) {
        string positionCommand = $"position {wp} {bp} {wk} {bk} {chain} {(turn ? "w" : "b")}";
        SendCommand(positionCommand);
        SendCommand("go movetime 1000");
    }

    private void OnEngineOutput(object sender, DataReceivedEventArgs e) {
        if (!string.IsNullOrEmpty(e.Data)) {
            UnityEngine.Debug.Log($"[Engine Out]: {e.Data}");

            if (e.Data.StartsWith("bestmove")) {
                string move = e.Data.Split(' ')[1];
                UnityEngine.Debug.Log($"Engine wants to move: {move}");
                Main.Instance.ProcessEngineMove(move);
            }
        }
    }

    private void OnEngineError(object sender, DataReceivedEventArgs e) {
        if (!string.IsNullOrEmpty(e.Data)) {
            UnityEngine.Debug.LogError($"[Engine Error]: {e.Data}");
        }
    }

    public void Quit() {
        if (engineProcess != null && !engineProcess.HasExited){
            SendCommand("quit");
            engineProcess.Close();
        }
    }
}