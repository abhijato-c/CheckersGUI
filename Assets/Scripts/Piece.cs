using UnityEngine;
using UnityEngine.EventSystems;

public class Piece : MonoBehaviour, IPointerClickHandler {
    public Sprite WhiteTexture;
    public Sprite BlackTexture;

    bool color;
    Vector2Int pos;
    Vector3 target;
    public void Spawn(Vector2Int pos, bool color) {
        this.color = color;
        transform.position = Main.Instance.BoardToGlobalPos(pos.x, pos.y, 2);
        MoveTo(pos);
        gameObject.GetComponent<SpriteRenderer>().sprite = color ? WhiteTexture : BlackTexture;
    }
    
    public void MoveTo(Vector2Int pos) {
        this.pos = pos;
        this.target = Main.Instance.BoardToGlobalPos(pos.x, pos.y, 2);
    }

    public void OnPointerClick(PointerEventData eventData) {
        Main.Instance.PieceClicked(pos, color);
    }

    void Update() {
        if ((target - transform.position).magnitude > 0.001f)
            transform.position = Vector3.Lerp(transform.position, target, Main.Instance.speed);
    }
}
