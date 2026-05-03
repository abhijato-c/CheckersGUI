using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class StatsHandler : MonoBehaviour {
    public Image TimePanel;
    public TMP_Text PlayerName;
    public TMP_Text PawnAdv;
    public TMP_Text KingAdv;
    public TMP_Text TotalAdv;
    public TMP_Text TimeCtr;
    public Color NormalColor;
    public Color RedColor;
    public Color TurnColor;
    public Color NotTurnColor;
    public bool IsWhite;

    float TimeRemaining = 600f;
    float RedZone = 60f;
    bool InRedZone = false;
    bool TimerRunning = false;
    int increment = 0;

    public void SetName(string name) {
        PlayerName.text = name;
    }

    public void SetTime(float time) {
        TimeRemaining = time * 60;
        TimeCtr.text = $"{TimeRemaining / 60:00}:{TimeRemaining % 60:00}";
    }

    public void SetIncrement(int inc) {
        increment = inc;
    }

    public void StartTimer() {
        TimerRunning = true;
        gameObject.GetComponent<Image>().color = TurnColor;
        CalcAdvantage();
    }

    public void StopTimer() {
        TimerRunning = false;
        TimeRemaining += increment;
        TimeCtr.text = $"{(int)(TimeRemaining/60) :00}:{TimeRemaining%60 :00}";
        gameObject.GetComponent<Image>().color = NotTurnColor;
        CalcAdvantage();
    }

    void CalcAdvantage() {
        Checkers board = Main.Instance.board;
        int pawnAdv = board.popcnt(board.wp) - board.popcnt(board.bp);
        int kingAdv = board.popcnt(board.wk) - board.popcnt(board.bk);
        if (!IsWhite) {
            pawnAdv = -pawnAdv;
            kingAdv = -kingAdv;
        }
        PawnAdv.text = $"{pawnAdv}x";
        KingAdv.text = $"{kingAdv}x";
        TotalAdv.text = (pawnAdv + 2 * kingAdv).ToString("+0;-#");
    }

    void Update() {
        if (TimerRunning) {
            TimeRemaining -= Time.deltaTime;
            TimeCtr.text = $"{(int)(TimeRemaining/60) :00}:{TimeRemaining%60 :00}";
            if (TimeRemaining <= 0) {
                TimeRemaining = 0;
                TimerRunning = false;
                TimeCtr.text = "00:00";
                Main.Instance.TimeOut(IsWhite);
            }
            else if (TimeRemaining <= RedZone && !InRedZone) {
                InRedZone = true;
                TimePanel.color = RedColor;
            }
            else if (TimeRemaining > RedZone && InRedZone) {
                InRedZone = false;
                TimePanel.color = NormalColor;
             }
        }
    }
}
