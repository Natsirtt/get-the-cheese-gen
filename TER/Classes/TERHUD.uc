class TERHUD extends UTHUD;

event simulated PostBeginPlay()
{
	super.PostBeginPlay();
}

function DrawHUD()
{
	//Local int gameTime;
	super.DrawHUD();

	Canvas.Font = class'Engine'.static.GetLargeFont();
	Canvas.SetDrawColor(0, 255, 0); // Green
	Canvas.SetPos(sizeX / 2, 20);

	Canvas.DrawText(TERGame(PlayerOwner.WorldInfo.game).GetGameTime()$" secondes");

	Canvas.SetPos(200, 15);
}



defaultproperties
{
    bHasLeaderboard=false
	bHasMap=false
	bShowFragCount=false
}
