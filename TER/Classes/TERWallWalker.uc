class TERWallWalker extends Volume
	placeable;
	

var() Vector WallDir;

var Vector WalkDir;

var Pawn CurrentActor;
var Vector CurrentPosition;

event simulated PostBeginPlay()
{
	WalkDir = WallDir cross vect(0, 0, 1);
}
	
simulated event Touch(Actor Other, PrimitiveComponent OtherComp, vector HitLocation, vector HitNormal )
{
	`Log("Touch");
	if (Pawn(Other) != none)
	{
		CurrentActor = Pawn(Other);
		CurrentPosition = Other.Location;
		
		if (wallDir.X > 0) 
		{
			Other.setRotation(rot(0, 16383, 0));
		} else if (wallDir.X < 0) 
		{
			Other.setRotation(rot(0, -16383, 0));
		} else if (wallDir.Y > 0) 
		{
			Other.setRotation(rot(16383, 0, 0));
		} else if (wallDir.Y < 0) 
		{
			Other.setRotation(rot(-16383, 0, 0));
		}
		Other.Velocity = vect(0, 0, 0);
		Other.Acceleration = vect(0, 0, 0);
		Other.SetPhysics(PHYS_Spider);
	}
}

simulated event UnTouch(Actor Other)
{
	if (Other == CurrentActor)
	{
		//Other.setRotation(Other.Rotation + rotator(WallDir));
		Other.SetPhysics(PHYS_Falling);
		CurrentActor.Acceleration = vect(0,0,0);
		CurrentActor.Velocity = vect(0,0,0);
		CurrentActor = none;
	}
}

function Tick(float dt)
{
	Local Vector NewPos;
	
	if (CurrentActor != none)
	{
		NewPos.x = CurrentActor.Location.X;
		NewPos.y = CurrentActor.Location.Y;
		NewPos.z = CurrentPosition.Z;
		CurrentActor.setLocation(NewPos);
		//CurrentActor.setRotation(CurrentActor.Rotation + rotator(-WallDir));
		CurrentActor.Acceleration.Z = 0;
		CurrentActor.Acceleration.X = WallDir.X * GetGravityZ() * 50;
		CurrentActor.Acceleration.Y = WallDir.Y * GetGravityZ() * 50;
		if (wallDir.X > 0) 
		{
			CurrentActor.setRotation(rot(0, 16383, 0));
		} else if (wallDir.X < 0) 
		{
			CurrentActor.setRotation(rot(0, -16383, 0));
		} else if (wallDir.Y > 0) 
		{
			CurrentActor.setRotation(rot(16383, 0, 0));
		} else if (wallDir.Y < 0) 
		{
			CurrentActor.setRotation(rot(-16383, 0, 0));
		}
	}
}
	
defaultproperties
{
	WallDir = (X=0,Y=1,Z=0)
	bStatic=false
	//TickGroup=TG_PostUpdateWork
}