#pragma once

#if DISPLAY_TYPE > 0
    #if SUPPORT_POINTS_OF_INTEREST == 1
struct PointOfInterest {
    const char *pDisplay;
    byte hourRA;
    byte minRA;
    byte secRA;
    int degreeDEC;
    byte minDEC;
    byte secDEC;
};

// Points of interest are sorted by DEC
// Note that you cannot add any points of interest between 0 and -1 degree Declination (don't ask).
    PointOfInterest pointOfInterest[] = {
        // Name (15chars)    RA (hms)     DEC (dms)
        //0123456789012345
        {">Polaris", POLARIS_RA_HOUR, POLARIS_RA_MINUTE, POLARIS_RA_SECOND, 89, 21, 6},
        // added for SH
        {">Small Magellanic Cloud", 0, 53, 26, -72, 40, 35},
        {">Large Magellanic Cloud", 5, 23, 23, -69, 44, 03},
        {">Eagle Nebula", 18, 20, 05, -13, 47, 52},
        {">Crux", 12, 27, 52, -63, 13, 29},    
        {">Alpha Centauri", 14, 29, 35, -62, 40, 20},
        {">Omega Centauri ", 13, 26, 47, -47, 28, 46},
        {">47 Tucanae", 0, 24, 05, -72, 04, 53},
        {">Wishing Well Cluster", 11, 05, 39, -58, 45, 10},
        {">Hamburger Galaxy", 13, 25, 27, -43, 1, 8},
        {">Sculptor Galaxy", 00, 47, 33, -25, 17, 19},
        {">Carina Nebula", 10, 45, 8, -59, 52, 4},
        {">Tau Canis Majoris", 07, 18, 0, -24, 57, 0},
        {">Eight-Burst Nebula", 10, 07, 1, -40, 26, 11},
        {">M83 Southern Pinwheel", 13, 37, 0, -29, 51, 57},
        {">M42 Orion Nbula", 5, 36, 18, -5, 22, 44},
    
        // Add new items above here, not below.
        {">Home", 0, 0, 0, 90, 0, 0},
        {">Unpark", 0, 0, 0, 90, 0, 0},
        {">Park", 0, 0, 0, 90, 0, 0},
        // And definitely don't add here.
    };

int currentPOI = 0;
int parkPOI    = sizeof(pointOfInterest) / sizeof(pointOfInterest[0]) - 1;
int unparkPOI  = sizeof(pointOfInterest) / sizeof(pointOfInterest[0]) - 2;
byte homePOI   = sizeof(pointOfInterest) / sizeof(pointOfInterest[0]) - 3;

bool processPOIKeys()
{
    lcdButton_t key;
    bool waitForRelease = false;
    if (lcdButtons.keyChanged(&key))
    {
        waitForRelease = true;
        switch (key)
        {
            case btnSELECT:
                {
                    mount.stopSlewing(ALL_DIRECTIONS);
                    if (currentPOI == homePOI)
                    {
                        mount.startSlewingToHome();
                    }
                    else if (currentPOI == parkPOI)
                    {
                        mount.park();
                    }
                    else if (currentPOI == unparkPOI)
                    {
                        mount.startSlewing(TRACKING);
                    }
                    else
                    {
                        PointOfInterest *poi = &pointOfInterest[currentPOI];
                        LOG(DEBUG_INFO, "[POI]: Selected %s.  RA: %d %d %d", poi->pDisplay, poi->hourRA, poi->minRA, poi->secRA);
                        LOG(DEBUG_INFO, "[POI]: Selected %s. DEC: %d %d %d", poi->pDisplay, poi->degreeDEC, poi->minDEC, poi->secDEC);
                        long targetSeconds = (60L * abs(poi->degreeDEC) + poi->minDEC) * 60L + poi->secDEC;
                        targetSeconds *= (poi->degreeDEC < 0 ? -1 : 1);
                        mount.targetRA().set(poi->hourRA, poi->minRA, poi->secRA);
                        mount.targetDEC() = Declination::FromSeconds(targetSeconds);
                        LOG(DEBUG_INFO, "[POI]: Target RA  is %s. %ls", mount.targetRA().ToString(), targetSeconds);
                        LOG(DEBUG_INFO,
                            "[POI]: mount target DEC is %s. %ls",
                            mount.targetDEC().ToString(),
                            mount.targetDEC().getTotalSeconds());
                        mount.startSlewingToTarget();
                    }
                }
                break;

            case btnLEFT:
            case btnDOWN:
                {
                    currentPOI = adjustWrap(currentPOI, 1, 0, parkPOI);
                }
                break;

            case btnUP:
                {
                    currentPOI = adjustWrap(currentPOI, -1, 0, parkPOI);
                }
                break;

            case btnRIGHT:
                {
                    lcdMenu.setNextActive();
                }
                break;

            default:
                break;
        }
    }

    return waitForRelease;
}

void printPOISubmenu()
{
    if (mount.isSlewingIdle())
    {
        lcdMenu.printMenu(pointOfInterest[currentPOI].pDisplay);
    }
}
    #endif
#endif
