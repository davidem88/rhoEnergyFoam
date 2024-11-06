const bool pressArtDiff =
    runTime.controlDict().lookupOrDefault("pressArtDiff", false);

const bool convArtDiff =
    runTime.controlDict().lookupOrDefault("convArtDiff", false);


scalar sigma =
    runTime.controlDict().lookupOrDefault("sigma",1.);

scalar kp =
    runTime.controlDict().lookupOrDefault("kp",0.);

scalar ku =
    runTime.controlDict().lookupOrDefault("ku",0.);

scalar ducLevelPress =
    runTime.controlDict().lookupOrDefault("ducLevelPress",1.5);

scalar ducLevelConv =
    runTime.controlDict().lookupOrDefault("ducLevelConv",1.5);

scalar epsilon =
    runTime.controlDict().lookupOrDefault("epsilon",0.);

scalar minfty =
    runTime.controlDict().lookupOrDefault("minfty",0.);

scalar rm =
    runTime.controlDict().lookupOrDefault("rm",0.2);

scalar Tbulk_target =
    runTime.controlDict().lookupOrDefault("Tbulk_target",0.);

const bool channelCase =
    runTime.controlDict().lookupOrDefault("channelCase", false);


   
