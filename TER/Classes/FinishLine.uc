class FinishLine extends Actor
	placeable;

simulated singular event Touch( Actor Other, PrimitiveComponent OtherComp, vector HitLocation, vector HitNormal )
{
	`log("Finish line touched");

    if (TERPawn(Other) != None && TERPawn(Other).Controller.bIsPlayer)
    {
        if (TERGame(WorldInfo.Game) != None)
        {
            TERGame(WorldInfo.Game).EndGame(PlayerController(TERPawn(Other).Controller).PlayerReplicationInfo, "Game Finished"); 
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
