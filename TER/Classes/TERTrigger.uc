class TERTrigger extends Trigger
	placeable;

var() name triggerableName; // Le nom de l'objet à activer

var TERTriggerable triggerable; // Référence de l'objet à activer
var(CUSTOM) StaticMeshComponent CustomMesh; // Mesh du Trigger
var() ParticleSystemComponent BlueLight; // Lumière bleue
var() ParticleSystemComponent RedLight; // Lumière rouge
var TERTriggerVolume triggerVolume; // Volume dans lequel on peut activer le trigger

event simulated PostBeginPlay()
{
	local TERTriggerable factory;
	
	triggerVolume = Spawn(class'TERTriggerVolume');
	triggerVolume.SetLocation(location);
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
	BlueLight.SetHidden(true);
	BlueLight.SetScale(BlueLight.scale * 10);
	RedLight.SetHidden(false);
	RedLight.SetScale(RedLight.scale * 10);
}

function bool UsedBy(Pawn User)
{
	local bool used;
	used = super.UsedBy(User);
	if (!used)
	{
		used = Trigger();
	}
	
	return used;
}

function bool Trigger()
{	
	if (triggerVolume.IsInside() && (triggerable != none))
	{
		triggerable.Trigger();
		if (triggerable.IsActivated())
		{
			BlueLight.SetHidden(false);
			RedLight.SetHidden(true);
		} else {
			BlueLight.SetHidden(true);
			RedLight.SetHidden(false);
		}
		return true;
	}
	return false;
}

event Tick(float DeltaTime)
{
	super.Tick(DeltaTime);
}

event TakeDamage(int DamageAmount, Controller EventInstigator, vector HitLocation, vector Momentum, class<DamageType> DamageType, optional TraceHitInfo HitInfo, optional Actor DamageCauser)
{
	if (triggerable != none)
	{
		triggerable.Trigger();
		if (triggerable.IsActivated())
		{
			BlueLight.SetHidden(false);
			RedLight.SetHidden(true);
		} else {
			BlueLight.SetHidden(true);
			RedLight.SetHidden(false);
		}
	} else {
		BlueLight.SetHidden(!BlueLight.HiddenGame);
		RedLight.SetHidden(!RedLight.HiddenGame);
	}
}

defaultproperties
{
	//triggerableName='none'
	triggerable=none

	Begin Object class=StaticMeshComponent Name=MyStaticMeshComponent
		//StaticMesh=StaticMesh'LT_Mech.SM.Mesh.S_LT_Mech_SM_Powerpole01'
		//StaticMesh=StaticMesh'Pickups.Ammo_Shock.Mesh.S_Ammo_ShockRifle'
		StaticMesh=StaticMesh'GP_Onslaught.Mesh.S_GP_Ons_Weapon_Locker'
	End Object
	bBlockActors=true
	bCollideActors=true
	bHidden=false
	CustomMesh=MyStaticMeshComponent
	CollisionComponent=MyStaticMeshComponent
 	Components.Add(MyStaticMeshComponent)
	
	Begin Object Class=ParticleSystemComponent Name=ParticleSystemComponent0
			Template=ParticleSystem'CTF_Flag_IronGuard.Effects.P_CTF_Flag_IronGuard_Idle_Blue'
			bAutoActivate=true
	End Object
	BlueLight=ParticleSystemComponent0
	Components.Add(ParticleSystemComponent0)
	Begin Object Class=ParticleSystemComponent Name=ParticleSystemComponent1
			Template=ParticleSystem'CTF_Flag_IronGuard.Effects.P_CTF_Flag_IronGuard_Idle_red'
			bAutoActivate=true
	End Object
	RedLight=ParticleSystemComponent1
	Components.Add(ParticleSystemComponent1)
}