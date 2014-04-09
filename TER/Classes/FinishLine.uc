class FinishLine extends Actor
	placeable;

simulated singular event Touch( Actor Other, PrimitiveComponent OtherComp, vector HitLocation, vector HitNormal )
{
	`log("Finish line touched");

    if (TERPawn(Other) != None && TERPawn(Other).Controller.bIsPlayer) //We wouldn't want potential NPCs to get coins.
    {
		`log("Finish line touched2");
        if (TERGame(WorldInfo.Game) != None)
        {
			`log("Finish line touched3");
            TERGame(WorldInfo.Game).EndGame(None,"Game Finished"); //Do the actual collecting in the game class.
        }
    }
}
defaultproperties
{
	Begin Object class=DynamicLightEnvironmentComponent Name=MyLightEnvironment
		bEnabled=true
		bDynamic=true
	End Object
	Components.Add(MyLightEnvironment)

	Begin Object class=StaticMeshComponent Name=MyStaticMeshComponent
		StaticMesh=StaticMesh'LT_Light.SM.Mesh.S_LT_Light_SM_Light01'
		LightEnvironment=MyLightEnvironment
	End Object
	CollisionComponent=MyStaticMeshComponent
 	Components.Add(MyStaticMeshComponent)
	bBlockActors=false
	bCollideActors=true	
}
