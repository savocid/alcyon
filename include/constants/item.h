#ifndef GUARD_ITEM_CONSTANTS_H
#define GUARD_ITEM_CONSTANTS_H

// These constants are used in gItemsInfo.
// Uncomment and asign values in sequence to enable pockets in your preferred order.
// NOTE: Wally's catch tutorial assumes that Items and Pokéball pockets are right next to each other,
// so manual edits to the following struct and functions is needed in order to avoid breaking the sequence:
//    - TempWallyBag
//    - PrepareBagForWallyTutorial
//    - RestoreBagAfterWallyTutorial
//    - DoWallyTutorialBagMenu

#define POCKET_ITEMS        0
#define POCKET_MEDICINE     1
#define POCKET_POKE_BALLS   2
//#define POCKET_BATTLE_ITEMS 0
#define POCKET_TM_HM        3
#define POCKET_POWER_UP     4
#define POCKET_BERRIES      5
//#define POCKET_MAIL         0
#define POCKET_TREASURES    6
//#define POCKET_MEGA_STONES  0
//#define POCKET_Z_CRYSTALS   0
#define POCKET_KEY_ITEMS    7
#define POCKETS_COUNT       8

// Default to POCKET_ITEMS if the specified pocket is disabled.
#define DEFAULT_MEDICINE_POCKET     POCKET_ITEMS
#define DEFAULT_BATTLE_ITEMS_POCKET POCKET_ITEMS
#define DEFAULT_POWER_UP_POCKET     POCKET_ITEMS
#define DEFAULT_MAIL_POCKET         POCKET_ITEMS
#define DEFAULT_TREASURES_POCKET    POCKET_ITEMS
#define DEFAULT_MEGA_STONES_POCKET  POCKET_BATTLE_ITEMS
#define DEFAULT_Z_CRYSTALS_POCKET   POCKET_BATTLE_ITEMS

#ifndef POCKET_MEDICINE
#define POCKET_MEDICINE     DEFAULT_MEDICINE_POCKET
#endif
#ifndef POCKET_BATTLE_ITEMS
#define POCKET_BATTLE_ITEMS DEFAULT_BATTLE_ITEMS_POCKET
#endif
#ifndef POCKET_POWER_UP
#define POCKET_POWER_UP     DEFAULT_POWER_UP_POCKET
#endif
#ifndef POCKET_MAIL
#define POCKET_MAIL         DEFAULT_MAIL_POCKET
#endif
#ifndef POCKET_TREASURES
#define POCKET_TREASURES    DEFAULT_TREASURES_POCKET
#endif
#ifndef POCKET_MEGA_STONES
#define POCKET_MEGA_STONES  DEFAULT_MEGA_STONES_POCKET
#endif
#ifndef POCKET_Z_CRYSTALS
#define POCKET_Z_CRYSTALS   DEFAULT_Z_CRYSTALS_POCKET
#endif

#define REPEL_LURE_MASK         (1 << 15)
#define IS_LAST_USED_LURE(var)  (var & REPEL_LURE_MASK)
#define REPEL_LURE_STEPS(var)   (var & (REPEL_LURE_MASK - 1))
#define LURE_STEP_COUNT         (IS_LAST_USED_LURE(VarGet(VAR_REPEL_STEP_COUNT)) ? REPEL_LURE_STEPS(VarGet(VAR_REPEL_STEP_COUNT)) : 0)
#define REPEL_STEP_COUNT        (!IS_LAST_USED_LURE(VarGet(VAR_REPEL_STEP_COUNT)) ? REPEL_LURE_STEPS(VarGet(VAR_REPEL_STEP_COUNT)) : 0)

#endif // GUARD_ITEM_CONSTANTS_H
