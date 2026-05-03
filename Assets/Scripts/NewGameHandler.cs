using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class NewGameHandler : MonoBehaviour {
    public GameObject OppPlayerBtn;
    public GameObject OppCompBtn;
    public GameObject StartBtn;
    public TMP_Text TimeText;
    public TMP_Text IncrementText;
    public TMP_Text P1NameText;
    public TMP_Text P2NameText;
    public TMP_InputField P1NameInp;
    public TMP_InputField P2NameInp;
    public Slider TimeSlider;
    public Slider IncrementSlider;
    
    int[] times = {1, 2, 3, 4, 5, 10, 15, 20, 25, 30, 60};
    int[] increments = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    bool OpponentIsPlayer = true;
    int time = 0;
    int increment = 0;
    
    public void Spawn() {
        PlayerClicked();
        TimeSlider.value = 5;
        IncrementSlider.value = 0;
        TimeChanged(5);
        IncrementChanged(0);
        gameObject.SetActive(true);
    }

    public void PlayerClicked() {
        OppPlayerBtn.GetComponent<Image>().color = new Color32(50, 160, 90, 255);
        OppCompBtn.GetComponent<Image>().color = new Color32(255, 255, 255, 255);
        OpponentIsPlayer = true;
        P1NameText.text = "Player 1 Name";
        P2NameText.text = "Player 2 Name";
        P1NameInp.text = "Player 1";
        P2NameInp.text = "Player 2";
    }
    public void CompClicked() {
        OppCompBtn.GetComponent<Image>().color = new Color32(50, 160, 90, 255);
        OppPlayerBtn.GetComponent<Image>().color = new Color32(255, 255, 255, 255);
        OpponentIsPlayer = false;
        P1NameText.text = "Player Name";
        P2NameText.text = "Computer Name";
        P1NameInp.text = "Player";
        P2NameInp.text = "Computer";
    }
    public void TimeChanged(float index) {
        time = times[(int) index];
        TimeText.text = $"{time} min";
    }
    public void IncrementChanged(float index) {
        increment = increments[(int) index];
        IncrementText.text = $"{increment} sec";
    }
    public void StartPressed() {
        string P1Name = P1NameInp.text;
        string P2Name = P2NameInp.text;
        if (P1Name == "") { P1Name = "Player 1"; }
        if (P2Name == "") { P2Name = OpponentIsPlayer ? "Player 2" : "Computer"; }
        Main.Instance.NewGame(P1Name, P2Name, time, increment, OpponentIsPlayer);
        gameObject.SetActive(false);
    }
}
