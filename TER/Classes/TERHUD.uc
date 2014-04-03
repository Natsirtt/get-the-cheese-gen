class TERHUD extends UTHUD;

defaultproperties
{
	bHasLeaderboard=true
	bHasMap=false
	bShowFragCount=true

	WeaponBarScale=0.75
	WeaponBarY=16
	SelectedWeaponScale=1.5
	BounceWeaponScale=2.25
	SelectedWeaponAlpha=1.0
	OffWeaponAlpha=0.5
	EmptyWeaponAlpha=0.4
	WeaponBoxWidth=100.0
	WeaponBoxHeight=64.0
	WeaponScaleSpeed=10.0
	WeaponBarXOffset=70
	WeaponXOffset=60
	SelectedBoxScale=1.0
	WeaponYScale=64
	WeaponYOffset=8

	WeaponAmmoLength=48
	WeaponAmmoThickness=16
	SelectedWeaponAmmoOffsetX=110
	WeaponAmmoOffsetX=100
	WeaponAmmoOffsetY=16

	AltHudTexture=Texture2D'UI_HUD.HUD.UI_HUD_BaseA'

	HudFonts(0)=MultiFont'UI_Fonts_Final.HUD.MF_Small'
	HudFonts(1)=MultiFont'UI_Fonts_Final.HUD.MF_Medium'
	HudFonts(2)=MultiFont'UI_Fonts_Final.HUD.MF_Large'
	HudFonts(3)=MultiFont'UI_Fonts_Final.HUD.MF_Huge'

	CharPortraitMaterial=Material'UI_HUD.Materials.CharPortrait'
	CharPortraitYPerc=0.15
	CharPortraitXPerc=0.01
	CharPortraitSlideTime=2.0
	CharPortraitSlideTransitionTime=0.175
	CharPortraitSize=(X=96,Y=120)

	CurrentWeaponScale(0)=1.0
	CurrentWeaponScale(1)=1.0
	CurrentWeaponScale(2)=1.0
	CurrentWeaponScale(3)=1.0
	CurrentWeaponScale(4)=1.0
	CurrentWeaponScale(5)=1.0
	CurrentWeaponScale(6)=1.0
	CurrentWeaponScale(7)=1.0
	CurrentWeaponScale(8)=1.0
	CurrentWeaponScale(9)=1.0

	MessageOffset(0)=0.15
	MessageOffset(1)=0.242
	MessageOffset(2)=0.36
	MessageOffset(3)=0.58
	MessageOffset(4)=0.78
	MessageOffset(5)=0.83
	MessageOffset(6)=2.0

	GlowFonts(0)=font'UI_Fonts_Final.HUD.F_GlowPrimary'
	GlowFonts(1)=font'UI_Fonts_Final.HUD.F_GlowSecondary'

  	LC_White=(R=1.0,G=1.0,B=1.0,A=1.0)

	PulseDuration=0.33
	PulseSplit=0.25
	PulseMultiplier=0.5

	MaxNoOfIndicators=3
	BaseMaterial=Material'UI_HUD.HUD.M_UI_HUD_DamageDir'
	FadeTime=0.5
	PositionalParamName=DamageDirectionRotation
	FadeParamName=DamageDirectionAlpha

	HitEffectFadeTime=0.50
	HitEffectIntensity=0.25
	MaxHitEffectColor=(R=2.0,G=-1.0,B=-1.0)

	GrayColor=(R=160,G=160,B=160,A=192)
	PowerupYPos=0.75
	MaxHUDAreaMessageCount=2

	AmmoBarColor=(R=7.0,G=7.0,B=7.0,A=1.0)
	RedLinearColor=(R=3.0,G=0.0,B=0.05,A=0.8)
	BlueLinearColor=(R=0.5,G=0.8,B=10.0,A=0.8)
	DMLinearColor=(R=1.0,G=1.0,B=1.0,A=0.5)
	WhiteLinearColor=(R=1.0,G=1.0,B=1.0,A=1.0)
	GoldLinearColor=(R=1.0,G=1.0,B=0.0,A=1.0)
	SilverLinearColor=(R=0.75,G=0.75,B=0.75,A=1.0)

	MapPosition=(X=0.99,Y=0.05)
	ClockPosition=(X=0,Y=0)
	DollPosition=(X=0,Y=-1)
	AmmoPosition=(X=-1,Y=-1)
	ScoringPosition=(X=-1,Y=0)
	VehiclePosition=(X=-1,Y=-1)

    WeaponSwitchMessage=class'UTWeaponSwitchMessage'

	TalkingTexture=Texture2D'UT3GoldPatch.Talking'
	UT3GHudTexture=Texture2D'UI_GoldHud.HUDIcons'

	HealthBGCoords=(U=73,UL=143,V=111,VL=57)
	HealthOffsetX=65
	HealthBGOffsetX=65
	HealthBGOffsetY=59
	HealthIconX=80
	HealthIconY=88
	HealthTextX=185
	HealthTextY=55

	ArmorBGCoords=(U=74,UL=117,V=69,VL=42)
	ArmorBGOffsetX=65
	ArmorBGOffsetY=18
	ArmorIconX=80
	ArmorIconY=42
	ArmorTextX=160
	ArmorTextY=17

	AmmoBGCoords=(U=1,UL=162,V=368,VL=53)
	AmmoBarOffsetY=2
	AmmoTextOffsetX=125
	AmmoTextOffsetY=3

	PawnDollBGCoords=(U=9,UL=65,V=52,VL=116)
	DollOffsetX=35
	DollOffsetY=58
	DollWidth=56
	DollHeight=109
	VestX=36
	VestY=31
	VestWidth=46
	VestHeight=28
	ThighX=36
	ThighY=72
	ThighWidth=42
	ThighHeight=28
	HelmetX=36
	HelmetY=13
	HelmetWidth=22
	HelmetHeight=25
	BootX=37
	BootY=100
	BootWidth=54
	BootHeight=26


	NameplateWidth=8			//width of the left/right endcaps
	NameplateBubbleWidth=15		//width of the middle divot
	NameplateLeft=(U=224, UL=14, V=11, VL=35);
	NameplateCenter=(U=238, UL=5, V=11, VL=35);
	NameplateBubble=(U=243, UL=26, V=11, VL=35);
	NameplateRight=(U=275, UL=14, V=11, VL=35);

	BlackBackgroundColor=(R=0.7,G=0.7,B=0.7,A=0.7)

	TextRenderInfo=(bClipText=true)
}
