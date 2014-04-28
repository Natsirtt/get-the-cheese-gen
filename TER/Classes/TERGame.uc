class TERGame extends UTGame;

var int gameTime;
var() bool gameStarted;
var() bool gameFinished;

var float StartTime;

function bool CheckModifiedEndGame(PlayerReplicationInfo Winner, string Reason)
{
	return false;
}

function simulated Timer()
{
	super.Timer();
	gameTime++;
}

event simulated PostBeginPlay()
{
	super.PostBeginPlay();
	SetTimer( 1, true);
	gameTime = 0;
	StartTime = 0;
}

function EndGame(PlayerReplicationInfo Winner, string Reason )
{
	super.EndGame(Winner, Reason);
	gameTime = WorldInfo.TimeSeconds - StartTime;
	bGameEnded = true;
	if ((Reason == "Game Finished"))
	{
		if ( bGameEnded )
		{
			ConsoleCommand("Disconnect");
			//GotoState('MatchOver');
			//setTimer(1);
		}
	}
}

function int GetGameTime()
{
	return 0;
}
	
state MatchInProgress
{
	function int GetGameTime()
	{
		return WorldInfo.TimeSeconds - StartTime;
	}
	
	function BeginState(Name PreviousStateName)
	{
		super.BeginState(PreviousStateName);
		StartTime = WorldInfo.TimeSeconds;
	}
}

State MatchOver
{
	function int GetGameTime()
	{
		return gameTime;
	}
}
static event class<GameInfo> SetGameType(string MapName, string Options, string Portal)
{
	return class'TERGame';
}
/*
function string GetNextMap()
{
	return "";
}
*/
static function bool AllowMutator( string MutatorClassName )
{
	return false;
}

exec function AddBots(int Num)
{
	// RIEN
}
function UTBot AddBot(optional string BotName, optional bool bUseTeamIndex, optional int TeamIndex)
{
	return none;
}
defaultproperties
{
	bUseClassicHUD = true;
	HUDType=class'TER.TERHUD'
	PlayerControllerClass=class'TER.TERPlayerController'
	ConsolePlayerControllerClass=class'UTGame.UTConsolePlayerController'
	DefaultPawnClass=class'TERPawn'
	PlayerReplicationInfoClass=class'TER.TERPlayerReplicationInfo'
	GameReplicationInfoClass=class'UTGame.UTGameReplicationInfo'
	DeathMessageClass=class'UTDeathMessage'
	/*PopulationManagerClass=class'UTPopulationManager'
	BotClass=class'UTBot'*/

	bAllowKeyboardAndMouse=true
	bRestartLevel=False
	bDelayedStart=True
	bTeamScoreRounds=false
	bUseSeamlessTravel=true
	bWeaponStay=true

	bAutoNumBots=false
	CountDown=4
	bPauseable=true
	EndMessageWait=1
	DefaultMaxLives=0

	Acronym="???"

	DefaultInventory(0)=class'UTWeap_LinkGun'

	VictoryMessageClass=class'UTGame.UTVictoryMessage'

	// Voice is only transmitted when the player is actively pressing a key
	bRequiresPushToTalk=true

	bExportMenuData=true

	SpawnProtectionTime=+2.0

	SpeechRecognitionData=SpeechRecognition'SpeechRecognition.Alphabet'
	LastEncouragementTime=-20
	MidgameScorePanelTag=DMPanel
	bMidGameHasMap=false

	MaxPlayersAllowed=64

	bGivePhysicsGun=true

	SpreeStatEvents.Add(SPREE_KILLINGSPREE)
	SpreeStatEvents.Add(SPREE_RAMPAGE)
	SpreeStatEvents.Add(SPREE_DOMINATING)
	SpreeStatEvents.Add(SPREE_UNSTOPPABLE)
	SpreeStatEvents.Add(SPREE_GODLIKE)
	SpreeStatEvents.Add(SPREE_MASSACRE)
	
	bPlayersVsBots=false

	//TER
	gameTime=0.0
	gameStarted=false
	gameFinished=false
}
