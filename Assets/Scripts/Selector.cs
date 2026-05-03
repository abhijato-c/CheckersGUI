using UnityEngine;
using UnityEngine.EventSystems;

public class Selector : MonoBehaviour, IPointerClickHandler {
    public Vector2Int From;
    public Vector2Int To;
    public bool isCapture;

    public void Spawn(Vector2Int from, Vector2Int to) {
        this.From = from;
        this.To = to;
        transform.position = Main.Instance.BoardToGlobalPos(to.x, to.y, 1);
    }

    public void OnPointerClick(PointerEventData eventData) {
        Main.Instance.SelectorClicked(From, To, isCapture);
    }
}
