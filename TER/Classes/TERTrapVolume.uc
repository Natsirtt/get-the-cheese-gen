class TERTrapVolume extends Volume
	placeable;

var() name triggerableName; // Le nom de l'objet à activer

var TERTrapBrush triggerable; // Référence de l'objet à activer

var bool Touched;

event simulated PostBeginPlay()
{
	local TERTrapBrush factory;
	
	super.PostBeginPlay();
	if (triggerableName != 'none')
	{
		foreach AllActors(class'TERTrapBrush', factory)
		{
			if(factory.tag == triggerableName)
			{
				triggerable = factory;
				break;
			}
		}
	}
}

event simulated Touch(Actor Other, PrimitiveComponent OtherComp, Vector Hit, Vector HitNormal)
{
	super.Touch(Other, OtherComp, Hit, HitNormal);
	`Log("Touche TrapVolume");
	if ((triggerable != none) && (!Touched))
	{
		triggerable.Activate();
	}
}


defaultproperties
{
	//triggerableName='none'
	triggerable=none
	
	Touched = false
}