#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "caps.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"


u32 GetCurrentLevelCap(void)
{
    static const u32 sLevelCapFlagMap[][2] =
    {
        {FLAG_BADGE01_GET, 15},
        {FLAG_BADGE02_GET, 19},
        {FLAG_BADGE03_GET, 24},
        {FLAG_BADGE04_GET, 29},
        {FLAG_BADGE05_GET, 31},
        {FLAG_BADGE06_GET, 33},
        {FLAG_BADGE07_GET, 42},
        {FLAG_BADGE08_GET, 46},
        {FLAG_IS_CHAMPION, 58},
    };

    u32 i;

    if (B_LEVEL_CAP_TYPE == LEVEL_CAP_FLAG_LIST)
    {
        for (i = 0; i < ARRAY_COUNT(sLevelCapFlagMap); i++)
        {
            if (!FlagGet(sLevelCapFlagMap[i][0]))
                return sLevelCapFlagMap[i][1];
        }
    }
    else if (B_LEVEL_CAP_TYPE == LEVEL_CAP_VARIABLE)
    {
        return VarGet(B_LEVEL_CAP_VARIABLE);
    }

    return MAX_LEVEL;
}

u32 GetSoftLevelCapExpValue(u32 level, u32 expValue)
{
    static const u32 sExpScalingDown[5] = { 4, 8, 16, 32, 64 };
    static const u32 sExpScalingUp[5]   = { 16, 8, 4, 2, 1 };

    u32 levelDifference;
    u32 currentLevelCap = GetCurrentLevelCap();

    if (B_EXP_CAP_TYPE == EXP_CAP_NONE)
        return expValue;

    if (level < currentLevelCap)
    {
        if (B_LEVEL_CAP_EXP_UP)
        {
            levelDifference = currentLevelCap - level;
            if (levelDifference > ARRAY_COUNT(sExpScalingUp) - 1)
                return expValue + (expValue / sExpScalingUp[ARRAY_COUNT(sExpScalingUp) - 1]);
            else
                return expValue + (expValue / sExpScalingUp[levelDifference]);
        }
        else
        {
            return expValue;
        }
    }
    else if (B_EXP_CAP_TYPE == EXP_CAP_HARD)
    {
        return 0;
    }
    else if (B_EXP_CAP_TYPE == EXP_CAP_SOFT)
    {
        levelDifference = level - currentLevelCap;
        if (levelDifference > ARRAY_COUNT(sExpScalingDown) - 1)
            return expValue / sExpScalingDown[ARRAY_COUNT(sExpScalingDown) - 1];
        else
            return expValue / sExpScalingDown[levelDifference];
    }
    else
    {
       return expValue;
    }
}

u32 GetCurrentEVCap(void)
{

    static const u16 sEvCapFlagMap[][2] = {
        // Define EV caps for each milestone
        {FLAG_BADGE01_GET, 30},
        {FLAG_BADGE02_GET, 90},
        {FLAG_BADGE03_GET, 150},
        {FLAG_BADGE04_GET, 210},
        {FLAG_BADGE05_GET, 270},
        {FLAG_BADGE06_GET, 330},
        {FLAG_BADGE07_GET, 390},
        {FLAG_BADGE08_GET, 450},
        {FLAG_IS_CHAMPION, MAX_TOTAL_EVS},
    };

    if (B_EV_CAP_TYPE == EV_CAP_FLAG_LIST)
    {
        for (u32 evCap = 0; evCap < ARRAY_COUNT(sEvCapFlagMap); evCap++)
        {
            if (!FlagGet(sEvCapFlagMap[evCap][0]))
                return sEvCapFlagMap[evCap][1];
        }
    }
    else if (B_EV_CAP_TYPE == EV_CAP_VARIABLE)
    {
        return VarGet(B_EV_CAP_VARIABLE);
    }
    else if (B_EV_CAP_TYPE == EV_CAP_NO_GAIN)
    {
        return 0;
    }

    return MAX_TOTAL_EVS;
}


void AutomaticLevelCap(void)
{
    u8 levelCap = GetCurrentLevelCap();

    for (u8 i = 0; i < PARTY_SIZE; i++)
    {
        u16 species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, NULL);
        u32 expToGive = gExperienceTables[gSpeciesInfo[species].growthRate][levelCap];

        SetMonData(&gPlayerParty[i], MON_DATA_EXP, &expToGive);
        CalculateMonStats(&gPlayerParty[i]);

        //TeachLevelUpMovesUntilMax(&gPlayerParty[i]);
    }



    for (u8 boxId = 0; boxId < TOTAL_BOXES_COUNT; boxId++)
    {
        for (u8 boxPosition = 0; boxPosition < IN_BOX_COUNT; boxPosition++)
        {
            u16 species = GetBoxMonData(&gPokemonStoragePtr->boxes[boxId][boxPosition], MON_DATA_SPECIES, NULL);
            u32 expToGive = gExperienceTables[gSpeciesInfo[species].growthRate][levelCap];
    
            SetBoxMonData(&gPokemonStoragePtr->boxes[boxId][boxPosition], MON_DATA_EXP, &expToGive);
        }
    }

}


void TeachLevelUpMovesUntilMax(struct Pokemon *mon)
{
    u16 species = GetMonData(mon, MON_DATA_SPECIES);
    const struct LevelUpMove *learnset = GetSpeciesLevelUpLearnset(species);
    u8 currentLevel = GetMonData(mon, MON_DATA_LEVEL);
    u8 move_1 = GetMonData(mon, MON_DATA_MOVE1);
    u8 move_2 = GetMonData(mon, MON_DATA_MOVE2);
    u8 move_3 = GetMonData(mon, MON_DATA_MOVE3);
    u8 move_4 = GetMonData(mon, MON_DATA_MOVE4);

    u16 currentMoves[MAX_MON_MOVES] = {move_1, move_2, move_3, move_4};

    for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
    {
        if (learnset[i].level > currentLevel)
            continue;
        if (currentMoves[MAX_MON_MOVES-1] != MOVE_NONE)
            break;

        bool8 alreadyKnowsMove = FALSE;
        for (u8 j = 0; j < MAX_MON_MOVES; j++)
        {
            if (currentMoves[j] == learnset[i].move)
            {
                alreadyKnowsMove = TRUE;
                break;
            }
        }

       if (!alreadyKnowsMove)
       {
           for (u8 j = 0; j < MAX_MON_MOVES; j++)
           {
               if (currentMoves[j] == MOVE_NONE)
               {
                   GiveMoveToMon(mon, learnset[i].move);
                   currentMoves[j] = learnset[i].move;
                   break;
               }
           }
       }

    }
}