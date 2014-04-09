class TEREndGame extends SequenceAction;

// Pour lancer la fin du jeu : TriggerGlobalEventClass(class'TEREndGame', pc,0);
// NB : La ligne ci-dessus est tiré du web, et était stoquée dans la fonction Died de Pawn.uc

var() bool gameFinished;

event Activated()
{
	gameFinished = true;
	// I am not sure if this log works or not (src : http://wiki.beyondunreal.com/UnrealScript_Hello_World)
	`log( "Victory !" );
}

defaultproperties
{
	bCallHandler = false
	ObjName = "Victory Trigger"
	gameFinished = false
}