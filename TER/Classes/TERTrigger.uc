class TERTrigger extends Trigger
	placeable;

var() name triggerableName;
var TERTriggerable triggerable;
var(CUSTOM) StaticMeshComponent CustomMesh;

event simulated PostBeginPlay()
{
	local TERTriggerable factory;
	super.PostBeginPlay();
	if (triggerableName != 'none')
	{
		foreach AllActors(class'TERTriggerable', factory)
		{
			if(factory.tag == triggerableName)
			{
				triggerable = factory;
				break;     // Ends the search
			}
		}
	}
}

event simulated Bump(Actor Other, PrimitiveComponent OtherComp, Vector HitNormal)
{
	Trigger();
}

function Trigger()
{
	if (triggerable != none)
	{
		triggerable.Trigger();
	}
}

defaultproperties
{
	triggerableName='none'
	triggerable=none
	
	Begin Object class=StaticMeshComponent Name=MyStaticMeshComponent
		StaticMesh=StaticMesh'cube'
	End Object
	bBlockActors=true
	bCollideActors=true	
	CustomMesh=MyStaticMeshComponent
	CollisionComponent=MyStaticMeshComponent
 	Components.Add(MyStaticMeshComponent)
}