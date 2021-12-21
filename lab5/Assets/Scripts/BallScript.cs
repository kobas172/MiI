using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BallScript : MonoBehaviour
{
    public int balls = 3;
    public int score = 0;
    public bool ready = true;
    public float launchForce = 500.0f;
    public float bumpForce = 500.0f;

    public void Launch()
    {
        if (ready && balls > 0)
        {
            GetComponent<Rigidbody>().AddForce(0, launchForce, 0);
        }
    }
}
