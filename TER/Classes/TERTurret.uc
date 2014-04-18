class TERTurret extends Actor
	placeable;
	
var() float radialSpeed; // Vitesse de rotation en degrés/second
var() float detectionRadius; // Le rayon de détection
var() StaticMeshComponent CustomMesh; // Le mesh représentant la tourelle

var TERPawn target;

function Tick(float dt)
{
	local TERPawn player;
	local TERPawn nearestPlayer;
	local int nearestDistance;
	local Rotator targetRotation;
		
	foreach VisibleActors(class'TERPawn', player, detectionRadius)
	{
		if ((nearestPlayer == none) || (nearestDistance > VSize(Location - player.Location)))
		{
			nearestPlayer = player;
			nearestDistance = VSize(Location - player.Location);
		}
	}
	if (nearestPlayer != none)
	{
		target = nearestPlayer;
	}
	if (target != none) {
		targetRotation = Rotator(target.Location - Location);
		targetRotation = RInterpTo(Rotation, targetRotation, dt, radialSpeed, false);
		targetRotation.pitch = 0;
		targetRotation.roll = 0;
		setRotation(targetRotation);
	}
}

defaultproperties
{
	radialSpeed = 1.0
	detectionRadius = 1000
	
	Begin Object class=StaticMeshComponent Name=MyStaticMeshComponent
		StaticMesh=StaticMesh'NEC_Deco.SM.Mesh.S_NEC_Deco_SM_Cuchulainn_Pose3'
		Rotation=(Pitch=0,Yaw=49140,Roll=0)
	End Object
	CollisionComponent=MyStaticMeshComponent
 	Components.Add(MyStaticMeshComponent)
	CustomMesh = MyStaticMeshComponent
	bBlockActors=true
	bCollideActors=true	
}