class Grid extends Actor
	placeable;

var(CUSTOM) StaticMeshComponent CustomMesh;
	
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
		StaticMesh=StaticMesh'NEC_WALLS.SM.Mesh.S_NEC_Walls_SM_CAWall_STRc'
	End Object
	bBlockActors=true
	bCollideActors=true	
	CustomMesh=MyStaticMeshComponent
	CollisionComponent=MyStaticMeshComponent
 	Components.Add(MyStaticMeshComponent)

}