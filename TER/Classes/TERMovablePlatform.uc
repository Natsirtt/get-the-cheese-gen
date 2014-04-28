class TERMovablePlatform extends Actor
	placeable;
	
var StaticMeshComponent CustomMesh;
var() float Size;

var() vector BaseDir;
var() float Speed;

var bool Direction; // true->va dans le sens de baseDir, false -> va dans le sens inverse

event simulated PostBeginPlay()
{
	super.PostBeginPlay();
	SetDrawScale(Size / 256);
}
	
function Tick(float dt)
{
	super.Tick(dt);
	if (Direction)
	{
		MoveSmooth(Normal(BaseDir) * Speed);
	} else 
	{
		MoveSmooth(-Normal(BaseDir) * Speed);
	}
}

event HitWall(Vector HitNormal, Actor Wall, PrimitiveComponent WallComp)
{
	Direction = !Direction;
	`Log("HitWall");
}
	
defaultproperties
{
	BaseDir = (x=1.0,y=0.0, z=0.0)
	Direction = true
	
	Begin Object class=StaticMeshComponent Name=MyStaticMeshComponent
		StaticMesh=StaticMesh'LT_Floors.SM.Mesh.S_LT_Floors_SM_TileFloorBroken_4x4'
		BlockActors=true
		CollideActors=true		
	End Object
	CustomMesh=MyStaticMeshComponent
	CollisionComponent=MyStaticMeshComponent
 	Components.Add(MyStaticMeshComponent)	
	bBlockActors=true
	bCollideActors=true
	bCollideWorld=true
	bHidden=false

	Size=256
	
	Speed = 5.0
}
