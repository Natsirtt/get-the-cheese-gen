class TERLaser extends Actor
	placeable;
	
	
var ParticleSystemComponent BeamEmitter;
var UTEmitter BeamEndpointEffect;

event simulated PostBeginPlay()
{
	super.PostBeginPlay();
}

function Tick(float dt)
{
	local actor HitActor;
	local TERPawn player;
    local vector HitLoc, HitNorm, start, end;
	local rotator LaserRotation;
	local bool hit;
	local vector baseDir;
	super.Tick(dt);
	
	hit = false;
    start = location;
	
	//baseDir = GetRotatorAxis(rotation, AXIS_Z);
	//`Log(rotator(baseDir));
	//LaserRotation = rotator(baseDir) + rotation;
	
	//LaserRotation = BeamEmitter.Rotation;
    //end = start + Vector(LaserRotation) * 32768;
	baseDir = Normal(Vector(Rotation + rot(16380, 0, 0)) /* cross vect(0, 1, 0)*/);
	end = start + baseDir * 32768;
	//`Log(Vector(LaserRotation));
	
	foreach TraceActors(class'actor', HitActor, HitLoc, HitNorm, end, start)
	{
		BeamEmitter.SetVectorParameter('LinkBeamEnd', HitLoc);
		BeamEndpointEffect.SetLocation(HitLoc);
		BeamEndpointEffect.SetRotation(rotator(HitNorm));
		BeamEndpointEffect.SetFloatParameter('Touch', 1);	
		hit = true;
		
		player = TERPawn(HitActor);
		if (player != none)
		{
			//player.TakeDamage(1, none, HitLoc, vect(0, 0, 0), class'DmgType_Fell');
			`Log("Hit someone");
			HitLoc = player.location;
			BeamEmitter.SetVectorParameter('LinkBeamEnd', player.location);
			BeamEndpointEffect.SetLocation(player.location);
			break;
		}
	}
	if (hit)
	{
		if (BeamEndpointEffect != None && !BeamEndpointEffect.bDeleteMe)
		{
			BeamEndpointEffect.SetLocation(HitLoc);
			BeamEndpointEffect.SetRotation(rotator(HitNorm));
			if (BeamEndpointEffect.ParticleSystemComponent.Template != ParticleSystem'WP_LinkGun.Effects.P_WP_Linkgun_Beam_Impact_Gold')
			{
				BeamEndpointEffect.SetTemplate(ParticleSystem'WP_LinkGun.Effects.P_WP_Linkgun_Beam_Impact_Gold', true);
			}
		}
		else
		{
			BeamEndpointEffect = Spawn(class'UTEmitter', self,, HitLoc, rotator(HitNorm));
			BeamEndpointEffect.SetTemplate(ParticleSystem'WP_LinkGun.Effects.P_WP_Linkgun_Beam_Impact_Gold', true);
			BeamEndpointEFfect.LifeSpan = 0.0;
		}
		BeamEndpointEffect.SetFloatParameter('Touch',1);
	} else
	{
		if (BeamEndpointEffect != None)
		{
			BeamEndpointEffect.SetFloatParameter('Touch', 0);
			BeamEndpointEffect.ParticleSystemComponent.DeactivateSystem();
			BeamEndpointEffect.LifeSpan = 2.0;
			BeamEndpointEffect = None;
		}
		BeamEmitter.SetVectorParameter('LinkBeamEnd', start + baseDir * 500);
	}
}

defaultproperties
{
	Begin Object class=DynamicLightEnvironmentComponent Name=MyLightEnvironment
		bEnabled=true
		bDynamic=true
	End Object
	Components.Add(MyLightEnvironment)

	Begin Object class=StaticMeshComponent Name=MyStaticMeshComponent
		StaticMesh=StaticMesh'LT_Light.SM.Mesh.S_LT_Light_SM_Light01'
		LightEnvironment=MyLightEnvironment
	End Object
	CollisionComponent=MyStaticMeshComponent
 	Components.Add(MyStaticMeshComponent)
	bBlockActors=false
	bCollideActors=true	
	
	// L'effet de particule du laser
	Begin Object Class=UTParticleSystemComponent Name=BeamEmitterComponent
		Template=ParticleSystem'WP_LinkGun.Effects.P_WP_Linkgun_Altbeam'
		bAutoActivate=true
		DepthPriorityGroup=SDPG_World
		SecondsBeforeInactive=1.0
		bUpdateComponentInTick = true
		TickGroup=TG_PostUpdateWork
		Rotation=(Pitch=16380,Yaw=0,Roll=0)
	End Object
	BeamEmitter=BeamEmitterComponent
	components.Add(BeamEmitterComponent)
}