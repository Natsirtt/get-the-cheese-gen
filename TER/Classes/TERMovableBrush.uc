class TERMovableBrush extends Brush
	placeable;
	
var() vector BaseDir;
var() float Speed;

var bool Direction; // true->va dans le sens de baseDir, false -> va dans le sens inverse
var vector Target;
var Actor TargetActor;

event simulated PostBeginPlay()
{
	super.PostBeginPlay();
	SetTickIsDisabled(false);
	`Log("Je suis vivant !!!");
	CalcNewTarget();
}
	
function Tick(float dt)
{
	Local vector NewLocation;
	super.Tick(dt);
	`Log("Tick");
	if (Target != Location)
	{
		`Log("J'ai une cible !!!");
		`Log(TargetActor);
		NewLocation = VInterpTo(Location, Target, dt, Speed);
		setLocation(NewLocation);
	}
}

event Bump(Actor Other, PrimitiveComponent OtherComp, Vector HitNormal)
{
	super.Bump(Other, OtherComp, HitNormal);
	
	if (Other == TargetActor) {
		Direction = !Direction;
		CalcNewTarget();
	}
}

function CalcNewTarget()
{
	Local vector start, end, HitLoc, HitNorm;
	Local Actor HitActor;
	start = Location;
	if (Direction) 
	{
		end = start + BaseDir * 30000;
	} else
	{
		end = start - BaseDir * 30000;
	}
	HitActor = Trace(HitLoc, HitNorm, end, start, true);
	if (HitActor != none) 
	{	
		TargetActor = HitActor;
		Target = HitLoc;
	} else {
		Target = Location;
		TargetActor = none;
	}
}
	
defaultproperties
{
	BaseDir = (x=1.0,y=0.0, z=0.0)
	Direction = true
	
	Begin Object Name=BrushComponent0
		bAcceptsLights=true
		LightingChannels=(Dynamic=TRUE,bInitialized=TRUE)
		BlockActors=true
		BlockRigidBody=true
		/*AlwaysLoadOnClient=True
		AlwaysLoadOnServer=True*/
	End Object

	bCollideActors=True
	bStatic=false
	bHidden=false
	bMovable=true
	Speed = 10.0
}
