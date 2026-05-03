using UnityEngine;
using System.Collections.Generic;
using Unity.Mathematics;

using Move = System.Int32;
using TMPro;
using System.Linq;

public class Main : MonoBehaviour {
    public static Main Instance { get; private set; }
    public GameObject SquaresFolder;
    public GameObject PiecesFolder;
    public GameObject SelectorsFolder;
    public GameObject HighlightsFolder;
    public GameObject GameOverDialog;
    public GameObject SquarePrefab;
    public GameObject PiecePrefab;
    public GameObject SelectorPrefab;
    public GameObject CapSelectorPrefab;
    public GameObject HighlightPrefab;
    public GameObject KingPrefab;
    public GameObject MoveHistoryPrefab;
    public GameObject MoveHistoryFolder;
    public TMP_Text WhiteName;
    public TMP_Text BlackName;
    public StatsHandler WhiteStats;
    public StatsHandler BlackStats;
    public Color LightSquareColor;
    public Color DarkSquareColor;
    public float speed = 0.2f;
    public float scale = 0.8f;

    bool IsActive = true;
    bool chain = false;
    GameObject[,] Pieces = new GameObject[8,8];
    List<GameObject> Selectors = new List<GameObject>();
    List<GameObject> Highlights = new List<GameObject>();
    List<GameObject> MoveHistory = new List<GameObject>();
    public Checkers board = new Checkers();
    char[] files = {'a','b','c','d','e','f','g','h'};
    Vector2Int[] WhiteLoc = {new Vector2Int(0, 0), new Vector2Int(2, 0), new Vector2Int(4, 0), new Vector2Int(6, 0), new Vector2Int(1, 1), new Vector2Int(3, 1), new Vector2Int(5, 1), new Vector2Int(7, 1), new Vector2Int(0, 2), new Vector2Int(2, 2), new Vector2Int(4, 2), new Vector2Int(6, 2)};
    Vector2Int[] BlackLoc = {new Vector2Int(1, 7), new Vector2Int(3, 7), new Vector2Int(5, 7), new Vector2Int(7, 7), new Vector2Int(0, 6), new Vector2Int(2, 6), new Vector2Int(4, 6), new Vector2Int(6, 6), new Vector2Int(1, 5), new Vector2Int(3, 5), new Vector2Int(5, 5), new Vector2Int(7, 5)};

    public Vector3 BoardToGlobalPos(int file, int rank, int Zindex){
        return new Vector3((file- 3.5f) * scale - 1f, (rank - 3.5f) * scale, Zindex);
    }
    
    void GenerateBoard(Color LightColor, Color DarkColor) {
        for (int file = 0; file < 8; file++){
            for (int rank = 0; rank < 8; rank++){
                // Create the square
                GameObject newSquare = Instantiate(SquarePrefab, SquaresFolder.transform);
                newSquare.transform.position = BoardToGlobalPos(file, rank, 4);
                newSquare.transform.localScale = new Vector2(scale, scale);
                newSquare.name = $"Square {files[file]}{rank+1}";

                SpriteRenderer sr = newSquare.GetComponent<SpriteRenderer>();
                sr.color = ((file + rank) % 2 == 0) ? LightColor : DarkColor;
            }
        }
    }

    void ResetBoard() {
        board.ResetBoard();
        DestroySelectors();
        DestroyHighlights();
        DestroyMoveHistory();
        foreach (GameObject piece in Pieces) {
            if (piece != null) { Destroy(piece); }
        }
        foreach (Vector2Int pos in WhiteLoc) {
            GameObject pc = Instantiate(PiecePrefab, PiecesFolder.transform);
            pc.GetComponent<Piece>().Spawn(pos, true);
            Pieces[pos.y, pos.x] = pc;
        }
        foreach (Vector2Int pos in BlackLoc) {
            GameObject pc = Instantiate(PiecePrefab, PiecesFolder.transform);
            pc.GetComponent<Piece>().Spawn(pos, false);
            Pieces[pos.y, pos.x] = pc;
        }
    }

    Vector2Int IntToSquare(int i) {
        return new Vector2Int(7 - (i % 8), i / 8);
    }

    int SquareToInt(Vector2Int pos) {
        return pos.y * 8 + (7 - pos.x);
    }

    List<Vector2Int> GetValidMoves(Vector2Int pos) {
        List<Vector2Int> moves = new List<Vector2Int>();
        List<Move> PLmoves = board.GenerateMoves();
        foreach (Move move in PLmoves) {
            if ((move & 63) == SquareToInt(pos))
                moves.Add(new Vector2Int(move & 63, (move >> 6) & 63));
        }
        return moves;
    }

    public void PieceClicked(Vector2Int pos, bool color) {
        if (color != board.turn || !IsActive) return;
        DestroySelectors();
        List<Vector2Int> moves = GetValidMoves(pos);
        foreach (Vector2Int move in moves) {
            Vector2Int From = IntToSquare(move.x);
            Vector2Int To = IntToSquare(move.y);

            GameObject selector = Instantiate(IsCaptureMove(From, To) ? CapSelectorPrefab : SelectorPrefab, SelectorsFolder.transform);
            selector.GetComponent<Selector>().Spawn(From, To);
            Selectors.Add(selector);
        }
    }

    void DestroySelectors() {
        foreach (GameObject selector in Selectors) Destroy(selector);
        Selectors.Clear();
    }

    void DestroyHighlights() {
        foreach (GameObject highlight in Highlights) Destroy(highlight);
        Highlights.Clear();
    }

    void DestroyMoveHistory() {
        foreach (GameObject entry in MoveHistory) Destroy(entry);
        MoveHistory.Clear();
    }

    public void SelectorClicked(Vector2Int from, Vector2Int to, bool isCapture) {
        DestroySelectors();
        DestroyHighlights();
        Move move = (isCapture ? (1 << 12) : 0) | (SquareToInt(to) << 6) | SquareToInt(from);
        Pieces[to.y, to.x] = Pieces[from.y, from.x];
        Pieces[from.y, from.x] = null;
        Pieces[to.y, to.x].GetComponent<Piece>().MoveTo(to);

        // Check for captures
        if (isCapture) {
            Vector2Int capturedPos = new Vector2Int((from.x + to.x) / 2, (from.y + to.y) / 2);
            Destroy(Pieces[capturedPos.y, capturedPos.x]);
        }

        // Check for promotion
        if ((to.y == 7 && board.turn) || (to.y == 0 && !board.turn)) {
            GameObject king = Instantiate(KingPrefab, Pieces[to.y, to.x].transform);
        }

        bool PrevTurn = board.turn;
        board.MakeMove(move);

        // Highlight forced captures
        List<Move> PLmoves = board.GenerateMoves();
        foreach (Move CapMove in PLmoves) {
            if ((CapMove >> 12) != 0) {
                Vector2Int CapFrom = IntToSquare(CapMove & 63);
                GameObject highlight = Instantiate(HighlightPrefab, HighlightsFolder.transform);
                highlight.transform.position = BoardToGlobalPos(CapFrom.x, CapFrom.y, 3);
                Highlights.Add(highlight);
            }
        }

        if (board.IsGameOver()) {
            bool winner = board.GetWinner();
            OpenGameOverDialog(true, winner);
        }

        // Move History
        if (!chain) {
            GameObject entry = Instantiate(MoveHistoryPrefab, MoveHistoryFolder.transform);
            entry.GetComponentInChildren<TextMeshProUGUI>().text = $"{from.y * 8 + from.x + 1}-{to.y * 8 + to.x + 1}";
            MoveHistory.Add(entry);
        }
        else {
            MoveHistory.Last().GetComponentInChildren<TextMeshProUGUI>().text += $"-{to.y * 8 + to.x + 1}";
            chain = false;
        }

        if (PrevTurn != board.turn) {
            if (board.turn) {
                WhiteStats.StartTimer();
                BlackStats.StopTimer();
            } 
            else {
                BlackStats.StartTimer();
                WhiteStats.StopTimer();
            }
        }
        else { chain = true; }
    }

    public bool IsCaptureMove(Vector2Int from, Vector2Int to) {
        if (math.abs((from - to).x) == 2)
            return true;
        return false;
    }

    public void OpenGameOverDialog(bool result, bool winner) {
        IsActive = false;
        WhiteStats.StopTimer();
        BlackStats.StopTimer();
        GameOverDialog.SetActive(true);
        GameOverDialog.transform.Find("Result").GetComponent<TMP_Text>().text = result ? "Win/Loss" : "Draw";
        GameOverDialog.transform.Find("Winner").GetComponent<TMP_Text>().text = result ? (winner ? "White" : "Black") : "-";
    }

    public void NewGame(string p1Name, string p2Name, int time, int increment, bool opponentIsPlayer){
        ResetBoard();
        IsActive = true;

        WhiteStats.StopTimer();
        BlackStats.StopTimer();

        WhiteName.text = p1Name;
        BlackName.text = p2Name;

        WhiteStats.SetName(p1Name);
        BlackStats.SetName(p2Name);
        WhiteStats.SetTime(time);
        BlackStats.SetTime(time);
        WhiteStats.SetIncrement(increment);
        BlackStats.SetIncrement(increment);
        WhiteStats.StartTimer();
    }

    public void TimeOut(bool isWhite) {
        OpenGameOverDialog(true, !isWhite);
    }

    void Awake() {
        if (Instance == null) Instance = this;
        else Destroy(gameObject);
    }
    
    void Start() {
        GenerateBoard(LightSquareColor, DarkSquareColor);
        ResetBoard();
    }
}