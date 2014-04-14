class TERTriggerVolume extends Actor;

var bool bIsTouched;

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
	bIsTouched = false;
}

function bool IsInside()
{
	return bIsTouched;
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
	bHidden = true
}