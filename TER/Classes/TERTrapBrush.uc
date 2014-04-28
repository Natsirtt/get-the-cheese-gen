class TERTrapBrush extends Actor
	placeable;
	
var StaticMeshComponent CustomMesh;
var() float Size;
var() float TimeToDestroy; // Temps avant que le piege se déclenche

event simulated PostBeginPlay()
{
	super.PostBeginPlay();
	SetDrawScale(Size / 256);
}

function Activate()
{
	SetTimer(TimeToDestroy);
}

function Timer()
{    
	setHidden(true);
	destroy();
}

defaultproperties
{
	Begin Object class=StaticMeshComponent Name=MyStaticMeshComponent
		StaticMesh=StaticMesh'LT_Floors.SM.Mesh.S_LT_Floors_SM_TileFloorBroken_4x4'
	End Object
	bBlockActors=true
	bCollideActors=true
	bHidden=false
	CustomMesh=MyStaticMeshComponent
	CollisionComponent=MyStaticMeshComponent
 	Components.Add(MyStaticMeshComponent)

	Size=256
	TimeToDestroy = 0.5
}
