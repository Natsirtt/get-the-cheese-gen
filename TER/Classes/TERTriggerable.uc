class TERTriggerable extends Actor
	placeable;
	
var bool bIsActivated;
	
function Trigger()
{
	bIsActivated = !bIsActivated;
}

function bool IsActivated()
{
	return bIsActivated;
}

defaultproperties
{
	bIsActivated=false
}