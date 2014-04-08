class Grid extends Actor
	placeable;
	
event Bump(Actor Other, PrimitiveComponent OtherComp, Vector HitNormal)
{
	local Pawn Player;
	local vector p1;
	local vector p2;
	local vector p3;
    super.Bump(Other, OtherComp, HitNormal);
	player = Pawn(Other);
    if (Player != none)
    {
		p1 = Player.Location;
		p2 = Location;
		p3.X = p2.X - (p1.X - p2.X);
		p3.Z = p1.Z;
		p3.Y = p2.Y - (p1.Y - p2.Y);
		Player.SetLocation(p3);
    }
}
 
defaultproperties
{
	Begin Object class=StaticMeshComponent Name=MyStaticMeshComponent
		StaticMesh=StaticMesh'cube'
	End Object
	CollisionComponent=MyStaticMeshComponent
 	Components.Add(MyStaticMeshComponent)
    bBlockActors=true
	bCollideActors=true
}