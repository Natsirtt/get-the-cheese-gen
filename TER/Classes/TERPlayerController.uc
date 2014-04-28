class TERPlayerController extends UTPlayerController ;


var bool bIsSprinting;  // sprintons nous ?

simulated function PostBeginPlay()
{
    super.PostBeginPlay();
    bNoCrosshair = true; 
}



/* CheckJumpOrDuck()
Called by ProcessMove()
handle jump and duck buttons which are pressed
*/
function CheckJumpOrDuck()
{
	if ( Pawn == None )
	{
		return;
	}



	if ( bDoubleJump && (bUpdating || ((UTPawn(Pawn) != None) && UTPawn(Pawn).CanDoubleJump())) )
	{
		UTPawn(Pawn).DoDoubleJump( bUpdating );
	}
    else if ( bPressedJump )
	{
		Pawn.DoJump( bUpdating );
	}
	if ( Pawn.Physics != PHYS_Falling && Pawn.bCanCrouch )
	{
		// crouch if pressing duck
		Pawn.ShouldCrouch(bDuck != 0);
	}
}

event PlayerTick( float DeltaTime )
{
    Super.PlayerTick(DeltaTime);

    if(bIsSprinting && PlayerInput.aForward<=0)
    {
		SetPreviousSpeed();//vitesse précédente ou actuelle selon si on a sprinté ou non
    }
    if( PlayerInput.aForward>0)//si on avace
    {
		if(bIsSprinting)//si on sprinte
		{
			SetSprintSpeed();//on sprint donc vitesse de sprint
			//tempsDeRepos=tempsDeRepos+DeltaTime;
		}
    }
}


state PlayerWalking
{
ignores SeePlayer, HearNoise, Bump;

   function ProcessMove(float DeltaTime, vector NewAccel, eDoubleClickDir DoubleClickMove, rotator DeltaRot)
   {
      if( Pawn == None )
      {
         return;
      }

      if (Role == ROLE_Authority)
      {
         // Update ViewPitch for remote clients
         Pawn.SetRemoteViewPitch( Rotation.Pitch );
      }

      Pawn.Acceleration = NewAccel;

      CheckJumpOrDuck();
   }
}

function UpdateRotation( float DeltaTime )
{
   local Rotator   DeltaRot, newRotation, ViewRotation;

   ViewRotation = Rotation;
   if (Pawn!=none)
   {
      Pawn.SetDesiredRotation(ViewRotation);
   }

   // Calculate Delta to be applied on ViewRotation
   DeltaRot.Yaw   = PlayerInput.aTurn;
   DeltaRot.Pitch   = PlayerInput.aLookUp;

   ProcessViewRotation( DeltaTime, ViewRotation, DeltaRot );
   SetRotation(ViewRotation);

   NewRotation = ViewRotation;
   NewRotation.Roll = Rotation.Roll;

   if ( Pawn != None )
      Pawn.FaceRotation(NewRotation, deltatime);
}

exec function Sprint()  // permet de sprinter
{
    if(TERPawn(Pawn) != none)  // si nous avons bien un pion et qu'il lui reste de l'energie
    {
        //calculate coef
        bIsSprinting = true;
    }
}

exec function StopSprint()  // arrete le sprint
{
	SetPreviousSpeed();
	bIsSprinting = false;
}

function SetSprintSpeed()
{
    if(TERPawn(Pawn) != none)
    {
        TERPawn(Pawn).GroundSpeed = TERPawn(pawn).sprintSpeed;
        //il est possible de remplacer cette ligne par " LePawn(Pawn).GroundSpeed=640"
    }
}

function SetPreviousSpeed()
{
	if(TERPawn(Pawn) != none)
	{
		TERPawn(Pawn).GroundSpeed = TERPawn(Pawn).normalSpeed;
    }
}

exec function ExitGame()
{
	QuitToMainMenu();
}

function GetTriggerUseList(float interactDistanceToCheck, float crosshairDist, float minDot, bool bUsuableOnly, out array<Trigger> out_useList)
{
    //local int Idx;
    local vector cameraLoc;
    local rotator cameraRot;
    local TERTrigger checkTrigger;
    //local SeqEvent_Used UseSeq;
 
    if (Pawn != None)
    {
        // grab camera location/rotation for checking crosshairDist
        GetPlayerViewPoint(cameraLoc, cameraRot);
        // search of nearby actors that have use events
        foreach Pawn.CollidingActors(class'TERTrigger', checkTrigger, interactDistanceToCheck)
        {
            //8<------
            //Code from the parent function. I've snipped it, but you have to put it in
            //or you'll basically break Use events in Kismet.
            //8<------
 
            //If it's a usable actor and it hasn't already been added to the list, let's add it.
            if (((out_useList.Length == 0) || (out_useList[out_useList.Length-1] != checkTrigger)))
            {
                out_useList[out_useList.Length] = checkTrigger;
            }
        }
    }
}

defaultproperties
{
	DesiredFOV=90.000000
	DefaultFOV=90.000000
	FOVAngle=90.000
	CameraClass=None
	CheatClass=class'UTCheatManager'
	InputClass=class'UTGame.UTPlayerInput'
	LastKickWarningTime=-1000.0
	bForceBehindview=true
	DamageCameraAnim=CameraAnim'FX_HitEffects.DamageViewShake'
	MatineeCameraClass=class'Engine.Camera'
	bCheckSoundOcclusion=true
	ZoomRotationModifier=0.5
	VehicleCheckRadiusScaling=1.0
	bRotateMiniMap=false

	PulseTimer=5.0;

	MinRespawnDelay=1.5
	IdentifiedTeam=255
	OldMessageTime=-100.0
	LastTeamChangeTime=-1000.0

	Begin Object Class=ForceFeedbackWaveform Name=ForceFeedbackWaveform7
		Samples(0)=(LeftAmplitude=60,RightAmplitude=50,LeftFunction=WF_LinearDecreasing,RightFunction=WF_LinearDecreasing,Duration=0.200)
	End Object
	CameraShakeShortWaveForm=ForceFeedbackWaveform7

	Begin Object Class=ForceFeedbackWaveform Name=ForceFeedbackWaveform8
		Samples(0)=(LeftAmplitude=60,RightAmplitude=50,LeftFunction=WF_LinearDecreasing,RightFunction=WF_LinearDecreasing,Duration=0.400)
	End Object
	CameraShakeLongWaveForm=ForceFeedbackWaveform8

	AchievementHandlerClass=Class'UTAchievements'


	//Ajouts TER
<<<<<<< HEAD
	 bIsSprinting=false
=======
	bIsSprinting=false
	 
	bNotifyFallingHitWall=true 
	// Crawling configuration
    /*bCanCrawl=true*/
>>>>>>> 55ad14d4d81ee1ae240d18aee2a9cd3c43391f40
}
