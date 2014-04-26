class TERPawn extends UTPawn;

var int normalSpeed;
var int sprintSpeed;

var float WallJumpBoostXY;
var float WallJumpBoostZ;

//override to make player mesh visible by default
simulated event BecomeViewTarget( PlayerController PC )
{
   local UTPlayerController UTPC;

   Super.BecomeViewTarget(PC);

   if (LocalPlayer(PC.Player) != None)
   {
      UTPC = UTPlayerController(PC);
      if (UTPC != None)
      {
         //set player controller to behind view and make mesh visible
         UTPC.SetBehindView(true);
         SetMeshVisibility(UTPC.bBehindView);
      }
   }
}

simulated function bool CalcCamera( float fDeltaTime, out vector out_CamLoc, out rotator out_CamRot, out float out_FOV )
{
   local vector CamStart, HitLocation, HitNormal, CamDirX, CamDirY, CamDirZ, CurrentCamOffset;
   local float DesiredCameraZOffset;

   CamStart = Location;
   CurrentCamOffset = CamOffset;

   DesiredCameraZOffset = (Health > 0) ? 1.9 * GetCollisionHeight() + Mesh.Translation.Z : 0.f; // ici 1.2
   CameraZOffset = (fDeltaTime < 0.2) ? DesiredCameraZOffset * 5 * fDeltaTime + (1 - 5*fDeltaTime) * CameraZOffset : DesiredCameraZOffset;

   if ( Health <= 0 )
   {
      CurrentCamOffset = vect(0,0,0);
      CurrentCamOffset.X = GetCollisionRadius();
   }

   CamStart.Z += CameraZOffset;
   GetAxes(out_CamRot, CamDirX, CamDirY, CamDirZ);
   CamDirX *= CurrentCameraScale*3.5;//ici pas de *

   if ( (Health <= 0) || bFeigningDeath )
   {
      // adjust camera position to make sure it's not clipping into world
      // @todo fixmesteve.  Note that you can still get clipping if FindSpot fails (happens rarely)
      FindSpot(GetCollisionExtent(),CamStart);
   }
   if (CurrentCameraScale < CameraScale)
   {
      CurrentCameraScale = FMin(CameraScale, CurrentCameraScale + 5 * FMax(CameraScale - CurrentCameraScale, 0.3)*fDeltaTime);
   }
   else if (CurrentCameraScale > CameraScale)
   {
      CurrentCameraScale = FMax(CameraScale, CurrentCameraScale - 5 * FMax(CameraScale - CurrentCameraScale, 0.3)*fDeltaTime);
   }

   if (CamDirX.Z > GetCollisionHeight())
   {
      CamDirX *= square(cos(out_CamRot.Pitch * 0.0000958738)); // 0.0000958738 = 2*PI/65536
   }

   out_CamLoc = CamStart - CamDirX*CurrentCamOffset.X + CurrentCamOffset.Y*CamDirY + CurrentCamOffset.Z*CamDirZ;

   if (Trace(HitLocation, HitNormal, out_CamLoc, CamStart, false, vect(12,12,12)) != None)
   {
      out_CamLoc = HitLocation;
   }

   return true;
}

function bool DoWallJump( bool bUpdating )
{
    local Vector HitLocation, HitNormal, End, Start;
    local Actor HitActor;
     
    //Perform trace
    Start = Location + (Vector(Rotation) * GetCollisionRadius()/2);
    End = Start + (vector(Rotation) * GetCollisionRadius() * 2.5);
    HitActor = Trace(HitLocation, HitNormal, End, Start, true,);
    `Log("Player try to jump on " @ HitActor);
     
    //check on what we want to jump, we jump only on world surfaces
    if (HitActor == WorldInfo || HitActor.isA('StaticMeshActor'))
    {
        `Log("-Player jump on the wall !");
         
        FaceRotation(rotator(HitNormal), 0);
        Controller.SetRotation( rotator(HitNormal) );
         
		if (HitNormal.X != 0)
		{
			Velocity.X = HitNormal.X * WallJumpBoostXY;
		}
		 
		if (HitNormal.Y != 0)
		{
			Velocity.Y = HitNormal.Y * WallJumpBoostXY;
		}
         
        //PlayerController(Controller).PlaySound(playerSoundWallJump, false, true);
 
        Velocity.Z = JumpZ + WallJumpBoostZ;
 
        return true;
    }
     
    return false;
}

defaultproperties
{
	//Components.Remove(Sprite)

	Components.Add(MyLightEnvironment)
	LightEnvironment=MyLightEnvironment

	Mesh=WPawnSkeletalMeshComponent
	Components.Add(WPawnSkeletalMeshComponent)

	DefaultMeshScale=1.075
	BaseTranslationOffset=6.0

	OverlayMesh=OverlayMeshComponent0

	ArmsMesh[0]=FirstPersonArms

	ArmsMesh[1]=FirstPersonArms2

	CylinderComponent=CollisionCylinder

	PawnAmbientSound=AmbientSoundComponent
	Components.Add(AmbientSoundComponent)

	WeaponAmbientSound=AmbientSoundComponent2
	Components.Add(AmbientSoundComponent2)

	ViewPitchMin=-18000
	ViewPitchMax=18000

	WalkingPct=+0.4
	CrouchedPct=+0.4
	BaseEyeHeight=38.0
	EyeHeight=38.0

	GroundSpeed=440.0
	normalSpeed=440.0
	sprintSpeed=880.0

	AirSpeed=330.0 //ici 440
	WaterSpeed=220.0
	DodgeSpeed=500.0 // ici 600
	DodgeSpeedZ=295.0
	AccelRate=2048.0
	JumpZ=700.0 //ici 322.0
	CrouchHeight=29.0
	CrouchRadius=21.0
	WalkableFloorZ=0.78

	AlwaysRelevantDistanceSquared=+1960000.0
	InventoryManagerClass=class'UTInventoryManager'

	MeleeRange=+20.0
	bMuffledHearing=true

	Buoyancy=+000.99000000
	UnderWaterTime=+00020.000000
	bCanStrafe=True
	bCanSwim=true
	RotationRate=(Pitch=20000,Yaw=20000,Roll=20000)
	MaxLeanRoll=2048
	AirControl=+0.35
	DefaultAirControl=+0.35
	bCanCrouch=true
	bCanClimbLadders=True
	bCanPickupInventory=True
	bCanDoubleJump=true
	SightRadius=+12000.0

	MaxMultiJump=1
	MultiJumpRemaining=1
	MultiJumpBoost=-45.0

	SoundGroupClass=class'UTGame.UTPawnSoundGroup'

	TransInEffects(0)=class'UTEmit_TransLocateOutRed'
	TransInEffects(1)=class'UTEmit_TransLocateOut'

	MaxStepHeight=26.0
	MaxJumpHeight=50.0// ici 49
	MaxDoubleJumpHeight=100.0 // ici 87.0
	DoubleJumpEyeHeight=87.0 // ici 43.0

	HeadRadius=+9.0
	HeadHeight=5.0
	HeadScale=+1.0
	HeadOffset=32

	SpawnProtectionColor=(R=40,G=40)
	TranslocateColor[0]=(R=20)
	TranslocateColor[1]=(B=20)
	DamageParameterName=DamageOverlay
	SaturationParameterName=Char_DistSatRangeMultiplier

	TeamBeaconMaxDist=3000.f
	TeamBeaconPlayerInfoMaxDist=3000.f
	RagdollLifespan=18.0

	bPhysRigidBodyOutOfWorldCheck=TRUE
	bRunPhysicsWithNoController=true

	ControllerClass=class'UTGame.UTBot'

	CurrentCameraScale=1.0
	CameraScale=15.0
	CameraScaleMin=3.0
	CameraScaleMax=40.0

	LeftFootControlName=LeftFootControl
	RightFootControlName=RightFootControl
	bEnableFootPlacement=true
	MaxFootPlacementDistSquared=56250000.0 // 7500 squared

	SlopeBoostFriction=0.2
	bStopOnDoubleLanding=true
	DoubleJumpThreshold=500.0//ici 160
	FireRateMultiplier=1.0

	ArmorHitSound=SoundCue'A_Gameplay.Gameplay.A_Gameplay_ArmorHitCue'
	SpawnSound=SoundCue'A_Gameplay.A_Gameplay_PlayerSpawn01Cue'
	TeleportSound=SoundCue'A_Weapon_Translocator.Translocator.A_Weapon_Translocator_Teleport_Cue'

	MaxFallSpeed=+1800.0//ici +1250
	AIMaxFallSpeedFactor=1.1 // so bots will accept a little falling damage for shorter routes
	LastPainSound=-1000.0

	FeignDeathBodyAtRestSpeed=12.0
	bReplicateRigidBodyLocation=true

	MinHoverboardInterval=0.7
	HoverboardClass=class'UTVehicle_Hoverboard'

	FeignDeathPhysicsBlendOutSpeed=2.0
	TakeHitPhysicsBlendOutSpeed=0.5

	TorsoBoneName=b_Spine2
	FallImpactSound=SoundCue'A_Character_BodyImpacts.BodyImpacts.A_Character_BodyImpact_BodyFall_Cue'
	FallSpeedThreshold=125.0

	SuperHealthMax=199

	// moving here for now until we can fix up the code to have it pass in the armor object
	ShieldBeltMaterialInstance=Material'Pickups.Armor_ShieldBelt.M_ShieldBelt_Overlay'
	ShieldBeltTeamMaterialInstances(0)=Material'Pickups.Armor_ShieldBelt.M_ShieldBelt_Red'
	ShieldBeltTeamMaterialInstances(1)=Material'Pickups.Armor_ShieldBelt.M_ShieldBelt_Blue'
	ShieldBeltTeamMaterialInstances(2)=Material'Pickups.Armor_ShieldBelt.M_ShieldBelt_Red'
	ShieldBeltTeamMaterialInstances(3)=Material'Pickups.Armor_ShieldBelt.M_ShieldBelt_Blue'

	HeroCameraPitch=6000
	HeroCameraScale=6.0

	//@TEXTURECHANGEFIXME - Needs actual UV's for the Player Icon
	IconCoords=(U=657,V=129,UL=68,VL=58)
	MapSize=1.0

	// default bone names
	WeaponSocket=WeaponPoint
	WeaponSocket2=DualWeaponPoint
	HeadBone=b_Head
	PawnEffectSockets[0]=L_JB
	PawnEffectSockets[1]=R_JB


	MinTimeBetweenEmotes=1.0

	DeathHipLinSpring=10000.0
	DeathHipLinDamp=500.0
	DeathHipAngSpring=10000.0
	DeathHipAngDamp=500.0

	bWeaponAttachmentVisible=true

	TransCameraAnim[0]=CameraAnim'Envy_Effects.Camera_Shakes.C_Res_IN_Red'
	TransCameraAnim[1]=CameraAnim'Envy_Effects.Camera_Shakes.C_Res_IN_Blue'
	TransCameraAnim[2]=CameraAnim'Envy_Effects.Camera_Shakes.C_Res_IN'

	MaxFootstepDistSq=9000000.0
	MaxJumpSoundDistSq=16000000.0

	SwimmingZOffset=-30.0
	SwimmingZOffsetSpeed=45.0

	TauntNames(0)=TauntA
	TauntNames(1)=TauntB
	TauntNames(2)=TauntC
	TauntNames(3)=TauntD
	TauntNames(4)=TauntE
	TauntNames(5)=TauntF

	Begin Object Class=ForceFeedbackWaveform Name=ForceFeedbackWaveformFall
		Samples(0)=(LeftAmplitude=50,RightAmplitude=40,LeftFunction=WF_Sin90to180,RightFunction=WF_Sin90to180,Duration=0.200)
	End Object
	FallingDamageWaveForm=ForceFeedbackWaveformFall

	CamOffset=(X=4.0,Y=16.0,Z=-13.0)
	
	WallJumpBoostXY=100.0
	WallJumpBoostZ=10.0
	bDirectHitWall=true
}
