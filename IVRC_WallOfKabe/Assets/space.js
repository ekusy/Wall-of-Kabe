#pragma strict
var flg = false;
function Start () {

}

function Update () {
	var motion = GetComponent(Animator);
	var state : AnimatorStateInfo = motion.GetCurrentAnimatorStateInfo(0);

	if(Input.GetKeyDown("space")){
		Debug.Log("space true");
		motion.SetBool("space", true);
	}

	else if(state.IsName("Locomotion.L1")){
		if(flg==false){
			Debug.Log("space1 true");
			motion.SetBool("space1", true);
		}

	}
	else if(state.IsName("Locomotion.L2")){
		Debug.Log("space2 true");
		motion.SetBool("space2", true);
	}
	
	if(state.IsName("Locomotion.Idle2") && Input.GetKeyDown("space") ){
		motion.SetBool("space3", true);
	}
	else if(state.IsName("Locomotion.R1")){
					motion.SetBool("space4", true);
	}
	else if(state.IsName("Locomotion.R2")){
					motion.SetBool("space", false);
					motion.SetBool("space1", false);
					motion.SetBool("space2", false);
					motion.SetBool("space3", false);
					motion.SetBool("space4", false);
	}
}

public function test(){
	
}