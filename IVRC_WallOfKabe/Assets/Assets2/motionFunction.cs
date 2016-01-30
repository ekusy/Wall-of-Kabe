using UnityEngine;
using System.Collections;

public class motionFunction : MonoBehaviour {
	public Animator motion;
	public AnimatorStateInfo state;
	int st=0;
	bool flg = false;
	// Use this for initialization
	void Start () {
		motion = GetComponent<Animator>();
		state = motion.GetCurrentAnimatorStateInfo(0);
	}

	// Update is called once per frame
	void Update () {
		Debug.Log ("st="+st);
		if(Input.GetKeyDown("space") && st==0){
			st++;
			Debug.Log("space true,"+st);
			motion.SetBool("space", true);
		}

		else if(st==1){//state.IsName("Locomotion.L1")){
			if(flg==false){
				Debug.Log("space1 true,"+st);
				st++;
				motion.SetBool("space1", true);
			}
			/*
		else{
			flg=false;
			Debug.Log("space false");
			motion.SetBool("space", false);
		}
		*/
		}
		else if(st==2){//state.IsName("Locomotion.L2")){
			Debug.Log("space2 true,"+st);
			st++;
			motion.SetBool("space2", true);
		}
		
		if (st==3 && Input.GetKeyDown("space")){//state.IsName ("Locomotion.Idle2") && Input.GetKeyDown ("space")) {
			motion.SetBool ("space3", true);
			st++;
		} 
		else if (st==4){//state.IsName ("Locomotion.R1")) {
			st++;
			motion.SetBool ("space4", true);
		}
		else if (st==5){//state.IsName ("Locomotion.R2")) {
			motion.SetBool ("space", false);
			motion.SetBool ("space1", false);
			motion.SetBool ("space2", false);
			motion.SetBool ("space3", false);
			motion.SetBool ("space4", false);
			st=0;
		}
	}
}
