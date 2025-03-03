**Features**
- Updated options menu with (TEXT SPEED / FRAME / ALWAYS RUN / GENERATE NEW SEED / SET TIME / SAVE) menu actions. Save only temporary saves the options selection not the game.
- Updated start menu with PC / Fly aswell as reordering of options, also improved the code so you can more easily disable/enable menu items for debugging / preference.
- Faster PC initialization.
- Additional Bag Pockets (ITEMS / *MEDICINE* / POKé BALLS / TMs & HMs / *POWER UP* / BERRIES / *TREASURES* / KEY ITEMS)
- Bag sort option.
- Updated Party screen (modified gen-4 style).
- Relearn Moves in party screen.
- Relearn Egg moves (option to only learn at a specific level or to disable it).
- Move item in party screen (instead of having to open bag, also can be activated with SELECT).
- Automatic Level Cap (can be called when received a badge for example or when receiving a pokémon. It runs when the game starts).
- Level Up Evolution via party screen (with a indicator to show that a pokémon can evolve via Level Up).
- "Random Gift Pokémon" script with options like:
  - 'Minimum Base Stats' / 'Maximum Base Stats' (The Pokémon has to have a base stat value between these values. Can be unset).
  - 'Type 1' / 'Type 2' (The Pokémon has to have one of these types. Can be unset).
  - 'Allow' (Allow or prohibit for example all Legendary, Ultra Beast, or Regional Forms etc.. If unset all of these examples are allowed).
  - 'Exclusion' (Excludes a specific Pokémon, for example Shedinja. Can be unset).
  - 'Evolution Species Stage' (The Pokémon has to be a specific evolution stage, meaning if set to 2 then Pokémon like Ivysaur, Wartortle, Charmeleon, and Snorlax could be selected. Can be unset.).
  - 'Evolution Family Stage' (The Pokémon has to be part of a specific family evolution stage, meaning if set to 2 then Pokémon like Munchlax, Snorlax, Seel, Dewgong could be selected. Can be unset.).
  - Setup: Simply set the script 'RandomPokemonGift_Eventscript' to an object and adjust the parameters in 'src/alcyon.c' > 'sMapAreaRandomPokemonAttributes' for the current map (examples in the file).
- Can always use HM Field effects in the overworld (Surf / Strength / Cut / Waterfall / Dive).
- Animation skip for HM Field effects (the popup only) and overall faster initialization (no dialog etc).

https://github.com/user-attachments/assets/1c72ec69-c1e8-448e-9b93-e1596557c27b

