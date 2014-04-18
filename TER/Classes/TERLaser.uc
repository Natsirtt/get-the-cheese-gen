class TERLaser extends Actor
	placeable;
	
	
var ParticleSystemComponent BeamEmitter; // L'effet de particule du laser
var UTEmitter BeamEndpointEffect; // L'effet au bout du laser lorsque le laser touche quelque chose
var() int LaserMaxLength; // La longueur maximale du laser

function Tick(float dt)
{
	local Actor HitActor;
	local Actor nearestActor;
	local int nearestDistance;
	local vector NearestHitLoc, NearestHitNorm;
	local TERPawn player;
    local vector HitLoc, HitNorm, start, end;
	local vector projDir;
	super.Tick(dt);
	
    start = location;
	
	// On fait une rotation pour que la direction de la projection soit la même que celle du laser
	projDir = QuatRotateVector(QuatFromRotator(Rotation), vect(0, 0, 1));
	end = start + projDir * LaserMaxLength;
	
	// On teste tous les acteurs dans la direction
	/**
	 * A optimiser avec Trace : http://wiki.beyondunreal.com/UE3:Actor_native_functions_%28UDK%29#Trace
	 */
	foreach TraceActors(class'actor', HitActor, HitLoc, HitNorm, end, start)
	{
		if ((nearestActor == none) || (nearestDistance > VSize(start - HitLoc)))
		{
			nearestActor = HitActor;
			nearestDistance = VSize(start - HitLoc);
			NearestHitLoc = HitLoc;
			NearestHitNorm = HitNorm;
		}
	}
	
	if (nearestActor != none) // Si le laser a touché quelque chose (Un mur ou un joueur par exemple)
	{
		player = TERPawn(nearestActor);
		if (player != none) // Si l'Actor est un joueur
		{
			player.TakeDamage(1, none, NearestHitLoc, vect(0, 0, 0), class'DmgType_Fell');
			NearestHitLoc = player.location;
		}
		// On modifie le point d'arrivée du laser 
		BeamEmitter.SetVectorParameter('LinkBeamEnd', NearestHitLoc);
		if (BeamEndpointEffect != None && !BeamEndpointEffect.bDeleteMe) // Si l'effet de particule n'a pas été recyclé
		{
			if (BeamEndpointEffect.ParticleSystemComponent.Template != ParticleSystem'WP_LinkGun.Effects.P_WP_Linkgun_Beam_Impact_Gold')
			{
				BeamEndpointEffect.SetTemplate(ParticleSystem'WP_LinkGun.Effects.P_WP_Linkgun_Beam_Impact_Gold', true);
			}
		} else // Sinon on le recrée
		{
			BeamEndpointEffect = Spawn(class'UTEmitter', self,, NearestHitLoc, rotator(NearestHitNorm));
			BeamEndpointEffect.SetTemplate(ParticleSystem'WP_LinkGun.Effects.P_WP_Linkgun_Beam_Impact_Gold', true);
			BeamEndpointEFfect.LifeSpan = 0.0;
		}
		BeamEndpointEffect.SetLocation(NearestHitLoc);
		BeamEndpointEffect.SetRotation(rotator(NearestHitNorm));
		BeamEndpointEffect.SetFloatParameter('Touch',1);
	} else // Aucune colision
	{
		// On supprime l'effet en bout de laser
		if (BeamEndpointEffect != None)
		{
			BeamEndpointEffect.SetFloatParameter('Touch', 0);
			BeamEndpointEffect.ParticleSystemComponent.DeactivateSystem();
			BeamEndpointEffect.LifeSpan = 2.0;
			BeamEndpointEffect = None;
		}
		// On change le point d'arrivé du laser
		BeamEmitter.SetVectorParameter('LinkBeamEnd', start + projDir * LaserMaxLength);
	}
}

defaultproperties
{
	// La base du laser
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
	
	LaserMaxLength = 32768
}