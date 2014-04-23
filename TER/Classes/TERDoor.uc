class TERDoor extends TERTriggerable
	placeable;
	
var(CUSTOM) StaticMeshComponent CustomMesh; // Le Mesh de la porte
	
function Trigger()
{
	super.Trigger();
	
	CustomMesh.SetActorCollision(!IsActivated(), !IsActivated());
	SetHidden(IsActivated());
}

defaultproperties
{
	Begin Object class=StaticMeshComponent Name=MyStaticMeshComponent
		bAcceptsLights=true
		LightingChannels=(Dynamic=TRUE,bInitialized=TRUE)
		StaticMesh=StaticMesh'NEC_WALLS.SM.Mesh.S_NEC_Walls_SM_CAWall_STRc'
	End Object
	bBlockActors=true
	bCollideActors=true
	CustomMesh=MyStaticMeshComponent
	CollisionComponent=MyStaticMeshComponent
 	Components.Add(MyStaticMeshComponent)
}