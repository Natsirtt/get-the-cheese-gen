class TERTurret extends Actor
	placeable;
	
var() float radialSpeed; // Vitesse de rotation en degrés/second
var() float detectionRadius; // Le rayon de détection
var() StaticMeshComponent CustomMesh; // Le mesh représentant la tourelle

var ParticleSystemComponent BeamEmitter; // L'effet de particule du laser
var UTEmitter BeamEndpointEffect; // L'effet au bout du laser lorsque le laser touche quelque chose

function Tick(float dt)
{
	local TERPawn player;
	local TERPawn nearestPlayer;
	local int nearestDistance;
	local Rotator targetRotation;
	
	local TERPawn HitPawn;
    local vector HitLoc, HitNorm, start, end;
	
	super.Tick(dt);
		
	foreach VisibleActors(class'TERPawn', player, detectionRadius, Location + vect(0, 0, 50))
	{
		if ((nearestPlayer == none) || (nearestDistance > VSize(Location - player.Location)))
		{
			nearestPlayer = player;
			nearestDistance = VSize(Location - player.Location);
		}
	}
	if (nearestPlayer != none)
	{
		targetRotation = Rotator(nearestPlayer.Location - Location);
		targetRotation = RInterpTo(Rotation, targetRotation, dt, radialSpeed, false);
		targetRotation.pitch = 0;
		targetRotation.roll = 0;
		setRotation(targetRotation);
	} 
	
	start = Location + vect(0, 0, 50);
	end = start + Vector(Rotation) * detectionRadius;
	HitPawn = TERPawn(Trace(HitLoc, HitNorm, end, start, true));

	if (HitPawn != none) {
		HitPawn.TakeDamage(1, none, HitPawn.Location, vect(0, 0, 0), class'DmgType_Fell');
		// On modifie le point d'arrivée du laser 
		BeamEmitter.SetVectorParameter('LinkBeamEnd', HitPawn.Location);
		BeamEmitter.ActivateSystem();
		if (BeamEndpointEffect != None && !BeamEndpointEffect.bDeleteMe) // Si l'effet de particule n'a pas été recyclé
		{
			if (BeamEndpointEffect.ParticleSystemComponent.Template != ParticleSystem'WP_LinkGun.Effects.P_WP_Linkgun_Beam_Impact_Gold')
			{
				BeamEndpointEffect.SetTemplate(ParticleSystem'WP_LinkGun.Effects.P_WP_Linkgun_Beam_Impact_Gold', true);
			}
		} else // Sinon on le recrée
		{
			BeamEndpointEffect = Spawn(class'UTEmitter', self,, HitPawn.Location, rotator(HitNorm));
			BeamEndpointEffect.SetTemplate(ParticleSystem'WP_LinkGun.Effects.P_WP_Linkgun_Beam_Impact_Gold', true);
			BeamEndpointEFfect.LifeSpan = 0.0;
		}
		BeamEndpointEffect.SetLocation(HitPawn.Location);
		BeamEndpointEffect.SetRotation(rotator(HitNorm));
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
		BeamEmitter.DeactivateSystem();
	}
}

defaultproperties
{
	radialSpeed = 10.0
	detectionRadius = 1000
	
	Begin Object class=StaticMeshComponent Name=MyStaticMeshComponent
		StaticMesh=StaticMesh'NEC_Deco.SM.Mesh.S_NEC_Deco_SM_Cuchulainn_Pose3'
		Rotation=(Pitch=0,Yaw=49140,Roll=0)
		bAcceptsLights=true
		LightingChannels=(Dynamic=TRUE,bInitialized=TRUE)
	End Object
	CollisionComponent=MyStaticMeshComponent
 	Components.Add(MyStaticMeshComponent)
	CustomMesh = MyStaticMeshComponent
	bBlockActors=true
	bCollideActors=true	
	
	// L'effet de particule du laser
	Begin Object Class=UTParticleSystemComponent Name=BeamEmitterComponent
		Template=ParticleSystem'WP_LinkGun.Effects.P_WP_Linkgun_Altbeam'
		bAutoActivate=true
		DepthPriorityGroup=SDPG_World
		SecondsBeforeInactive=1.0
		bUpdateComponentInTick = true
		TickGroup=TG_PostUpdateWork
	End Object
	BeamEmitter=BeamEmitterComponent
	components.Add(BeamEmitterComponent)
	
}