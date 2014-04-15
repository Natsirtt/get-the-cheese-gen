class TERTriggerVolume extends Actor;

var bool bIsTouched;
var bool bHasBeenUnTouched; // Résoud un bug

event simulated PostBeginPlay()
{
	bIsTouched = false;
}

event simulated Touch(Actor Other, PrimitiveComponent OtherComp, Vector Hit, Vector HitNormal)
{
	bIsTouched = true;
}

event simulated UnTouch(Actor Other)
{
	bHasBeenUnTouched = true;
	bIsTouched = false;
}

function bool IsInside()
{
	return bHasBeenUnTouched && bIsTouched;
}

defaultproperties
{
	Begin Object class=CylinderComponent Name=MyCylinderComponent
		CollisionHeight = 100
		CollisionRadius = 100
		bDrawBoundingBox=false
		CollideActors=true        
        BlockActors=false
	End Object
	bBlockActors=false
	bCollideActors=true
	CollisionComponent=MyCylinderComponent
 	Components.Add(MyCylinderComponent)
	
	bIsTouched = false
	bHasBeenUnTouched = false
	bHidden = true
}