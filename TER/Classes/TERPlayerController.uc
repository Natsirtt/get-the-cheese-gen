class TERPlayerController extends UTPlayerController;


var bool bIsSprinting;  // sprintons nous ?

var array <TERPawn> Pawns;
var int CurrentPawnIndex;
var bool bReadyToMerge;

simulated function PostBeginPlay()
{
	super.PostBeginPlay();
	CurrentPawnIndex = 0;
	bReadyToMerge = false;
}

exec function Divide()
{
	local TERPawn p;
	
	if ((Pawns.Length == 0) || (Pawns.Find(TERPawn(Pawn)) == -1)) { // Si le Pawn actuel n'est pas dans la liste
		Pawns.AddItem(TERPawn(Pawn)); // On l'ajoute
	}
	
	p = Pawns[CurrentPawnIndex];
	p.Acceleration = vect(0, 0, 0);
	p.Velocity = vect(0, 0, 0);
	p = Spawn(class'TERPawn', , ,p.Location + vect(50, 50, 50), p.Rotation); // On crée un nouveau Pawn
	if (p != none)
	{
		Possess(p, false); // On change le Pawn actuel par le nouveau Pawn
		Pawns.AddItem(p); // On ajoute le nouveau Pawn à la liste
		CurrentPawnIndex = CurrentPawnIndex + 1;	
	}
}

exec function NextPawn()
{
	local bool ValidPlayer;
	local TERPawn OldPawn;
	`Log("Next");
	
	if (Pawns.Find(TERPawn(Pawn)) == -1)
	{
		Pawns.AddItem(TERPawn(Pawn));
		CurrentPawnIndex = Pawns.Length - 1;
	}
	
	ValidPlayer = false;
	while (ValidPlayer == false)
	{
		if (Pawns.Length > 1)
		{
			OldPawn = Pawns[CurrentPawnIndex];
			CurrentPawnIndex = (CurrentPawnIndex + 1) % Pawns.Length;
			if (Pawns[CurrentPawnIndex].IsAliveAndWell())
			{
				OldPawn.Acceleration = vect(0, 0, 0);
				OldPawn.Velocity = vect(0, 0, 0);
				UnPossess();
				
				Possess(Pawns[CurrentPawnIndex], false);
				ValidPlayer = true;
			} else {
				Pawns.RemoveItem(Pawns[CurrentPawnIndex]);
			}
		} else {
			Pawns.AddItem(TERPawn(Pawn));
			CurrentPawnIndex = 0;
		}
	}
}

exec function PreviousPawn()
{
	local bool ValidPlayer;
	local TERPawn OldPawn;
	`Log("Prev");
	if (Pawns.Find(TERPawn(Pawn)) == -1)
	{
		Pawns.AddItem(TERPawn(Pawn));
		CurrentPawnIndex = Pawns.Length - 1;
	}
	
	ValidPlayer = false;
	while (ValidPlayer == false)
	{
		if (Pawns.Length > 1)
		{
			OldPawn = Pawns[CurrentPawnIndex];
			CurrentPawnIndex = (CurrentPawnIndex - 1);
			if (CurrentPawnIndex < 0)
			{
				CurrentPawnIndex = CurrentPawnIndex + Pawns.Length;
			}
			if (Pawns[CurrentPawnIndex].IsAliveAndWell())
			{
				OldPawn.Acceleration = vect(0, 0, 0);
				OldPawn.Velocity = vect(0, 0, 0);
				UnPossess();
				Possess(Pawns[CurrentPawnIndex], false);
				ValidPlayer = true;
			} else {
				Pawns.RemoveItem(Pawns[CurrentPawnIndex]);
			}
		} else {
			Pawns.AddItem(TERPawn(Pawn));
			CurrentPawnIndex = 0;
		}
	}
}

exec function PrepareMerge()
{
	bReadyToMerge = true;
}

exec function UnPrepareMerge()
{
	bReadyToMerge = false;
}

function TryMerge(TERPawn PawnToMerge)
{
	local int ptmIndex;
	if (bReadyToMerge) {
		ptmIndex = Pawns.find(PawnToMerge);
		if ((ptmIndex != -1) && (ptmIndex != CurrentPawnIndex)) {
			if (ptmIndex < CurrentPawnIndex)
			{
				CurrentPawnIndex = CurrentPawnIndex - 1;
			}
			Pawns.RemoveItem(PawnToMerge);
			PawnToMerge.destroy();
		}
	}
}

/*
	// CODE POUR MARCHER SUR LES MURS
var             vector OldFloor;
var input       bool bIsCrawling; // Defines if the pawn is currently crawlin
var             bool bCanCrawl;

var vector ViewX, ViewY, ViewZ;

event Possess(Pawn inPawn, bool bVehicleTransition)
{
		Super.Possess(inPawn, bVehicleTransition);
		SetBehindView(true);
}

// Console command used to start crawling
exec function Crawl()
{
		if ( bCanCrawl )
				GotoState('PlayerSpidering');
}
 
// Console ocmmand used to stop crawling
exec function UnCrawl()
{
		if ( bIsCrawling )
		{
				Pawn.SetPhysics(PHYS_Walking);
				GotoState('PlayerWalking');
		}
}
 
// Console command used to switch crawling mode on/off (better used with a key binding for example)
exec function ToggleCrawl()
{
		`log("toggle");
 
		if ( bIsCrawling )
		{
				Pawn.SetPhysics(PHYS_Walking);
				GotoState('PlayerWalking');
		}
		else if ( bCanCrawl )
				GotoState('PlayerSpidering');
}
 // Crawling state
    state PlayerSpidering
    {
    ignores SeePlayer, HearNoise, Bump;
     
        event bool NotifyHitWall(vector HitNormal, actor HitActor)
        {
                    //`log("hit wall");
     
            Pawn.SetPhysics(PHYS_Spider);
            Pawn.SetBase(HitActor, HitNormal);
            return true;
        }
     
            // Resume crawling after a jump lands on something else than a floor
        event NotifyFallingHitWall(vector HitNormal, actor HitActor)
        {
                    //`log("falling hit wall");
     
            Pawn.SetPhysics(PHYS_Spider);
            Pawn.SetBase(HitActor, HitNormal);
            }
     
        // if crawling mode, update rotation based on floor
        function UpdateRotation(float DeltaTime)
        {
            local rotator ViewRotation;
            local vector MyFloor, CrossDir, FwdDir, OldFwdDir, OldX, RealFloor;
     
            if ( (Pawn.Base == None) || (Pawn.Floor == vect(0,0,0)) )
            {
                MyFloor = vect(0,0,1);
            }
            else
            {
                MyFloor = Pawn.Floor;
            }
            if ( MyFloor != OldFloor )
            {
                // smoothly transition between floors
                RealFloor = MyFloor;
                MyFloor = Normal(6*DeltaTime * MyFloor + (1 - 6*DeltaTime) * OldFloor);
     
                if ( (RealFloor dot MyFloor) > 0.999 )
                    {
                    MyFloor = RealFloor;
                }
                else
                {
                    // translate view direction
                    CrossDir = Normal(RealFloor Cross OldFloor);
                    FwdDir = CrossDir cross MyFloor;
                    OldFwdDir = CrossDir cross OldFloor;
                    ViewX = MyFloor * (OldFloor dot ViewX) + CrossDir * (CrossDir dot ViewX) + FwdDir * (OldFwdDir dot ViewX);
                    ViewX = Normal(ViewX);
                    ViewZ = MyFloor * (OldFloor dot ViewZ) + CrossDir * (CrossDir dot ViewZ) + FwdDir * (OldFwdDir dot ViewZ);
                    ViewZ = Normal(ViewZ);
                    OldFloor = MyFloor;
                    ViewY = Normal(MyFloor cross ViewX);
     
                    Pawn.mesh.SetRotation(OrthoRotation(ViewX,ViewY,ViewZ));
                }
            }
     
            if ( (PlayerInput.aTurn != 0) || (PlayerInput.aLookUp != 0) )
            {
                // adjust Yaw based on aTurn
                if ( PlayerInput.aTurn != 0 )
                {
                    ViewX = Normal(ViewX + 2 * ViewY * Sin(0.0005*DeltaTime*PlayerInput.aTurn));
                }
     
                // adjust Pitch based on aLookUp
                if ( PlayerInput.aLookUp != 0 )
                {
                    OldX = ViewX;
                    ViewX = Normal(ViewX + 2 * ViewZ * Sin(0.0005*DeltaTime*PlayerInput.aLookUp));
                    ViewZ = Normal(ViewX Cross ViewY);
     
                    // bound max pitch
                    if ( (ViewZ dot MyFloor) < 0.1   )
                    {
                                    ViewX = OldX;
                    }
                }
     
                // calculate new Y axis
                ViewY = Normal(MyFloor cross ViewX);
            }
            ViewRotation =  OrthoRotation(ViewX,ViewY,ViewZ);
            SetRotation(ViewRotation);
            if(Pawn != None)
                    Pawn.SetRotation(ViewRotation);
     
            //SET PAWN ROTATION WITH RESPECT TO FLOOR NORMALS HERE
                    // Does not work anymore.. will need some debugging
            //Pawn.mesh.SkeletalMesh.Rotation = Pawn.Rotation;
     
        }
     
            // Resume crawling after a jump lands on a floor
        function bool NotifyLanded(vector HitNormal, Actor FloorActor)
        {
                    //`log("landed");
            Pawn.SetPhysics(PHYS_Spider);
            return bUpdating;
        }
     
            // Do not use crawling while in water
        event NotifyPhysicsVolumeChange( PhysicsVolume NewVolume )
        {
            if ( NewVolume.bWaterVolume )
            {
                GotoState(Pawn.WaterMovementState);
            }
        }
     
        function ProcessMove(float DeltaTime, vector NewAccel, eDoubleClickDir DoubleClickMove, rotator DeltaRot)
        {
                    if ( Pawn != None )
                    {
                    if ( Pawn.Acceleration != NewAccel )
                    {
                        Pawn.Acceleration = NewAccel;
                    }
           
                    if ( bPressedJump )
                    {
                        Pawn.DoJump(bUpdating);
                    }
                    }
        }
     
        function PlayerMove( float DeltaTime )
        {
            local vector NewAccel;
            local eDoubleClickDir DoubleClickMove;
            local rotator OldRotation, ViewRotation;
            local bool  bSaveJump;
     
            GroundPitch = 0;
            ViewRotation = Rotation;
     
            //Pawn.CheckBob(DeltaTime,vect(0,0,0));
     
            // Update rotation.
            SetRotation(ViewRotation);
            OldRotation = Rotation;
            UpdateRotation(DeltaTime);
     
            // Update acceleration.
            NewAccel = PlayerInput.aForward*Normal(ViewX - OldFloor * (OldFloor Dot ViewX)) + PlayerInput.aStrafe*ViewY;
     
            if ( VSize(NewAccel) < 1.0 )
            {
                NewAccel = vect(0,0,0);
            }
     
            if ( bPressedJump && Pawn.CannotJumpNow() )
            {
                bSaveJump = true;
                bPressedJump = false;
            }
            else
                bSaveJump = false;
     
            DoubleClickMove = DCLICK_None;
            ProcessMove(DeltaTime, NewAccel, DoubleClickMove, OldRotation - Rotation);
            bPressedJump = bSaveJump;
        }
     
        event BeginState(Name PreviousStateName)
        {
                    //`log("spider with roll " $ Rotation.Roll);
            OldFloor = vect(0,0,1);
            GetAxes(Rotation,ViewX,ViewY,ViewZ);
            DoubleClickDir = DCLICK_None;
            Pawn.ShouldCrouch(false);
            bPressedJump = false;
     
            if (Pawn.Physics != PHYS_Falling)
            {
                Pawn.SetPhysics(PHYS_Spider);
            }
     
            GroundPitch = 0;
            Pawn.bCrawler = true;
            bIsCrawling = true;
        }
     
        event EndState(Name NextStateName)
        {
                    //`log("unspider with roll" $ Rotation.Roll);
            GroundPitch = 0;
            if ( Pawn != None )
            {
                Pawn.ShouldCrouch(false);
                Pawn.bCrawler = Pawn.default.bCrawler;
            }
            bIsCrawling = false;
        }
    }*/

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
		/*if (Pawn.Physics == PHYS_Falling)
        {
			// CODE POUR LE WALLJUMP
			TERPawn(Pawn).DoWallJump(bUpdating);
		} else
		{*/
			Pawn.DoJump( bUpdating );
		/*}*/
		
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
	bIsSprinting=false
	 
	/*bNotifyFallingHitWall=true 
	// Crawling configuration
    bCanCrawl=true*/
}
