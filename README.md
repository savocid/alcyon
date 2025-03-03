**Features**
- Updated options menu with (TEXT SPEED / FRAME / ALWAYS RUN / GENERATE NEW SEED / SET TIME / SAVE) menu actions. Save only temporary saves the options selection not the game.

  ![13](https://github.com/user-attachments/assets/18977841-cf89-4d24-a95c-112f12487362)
  ![14](https://github.com/user-attachments/assets/07a9b0ce-a8c9-46d5-b27b-b99135c69f01)

- Updated start menu with PC / Fly aswell as reordering of options, also improved the code so you can more easily disable/enable menu items for debugging / preference.
- Faster PC initialization.

  ![1](https://github.com/user-attachments/assets/4f448940-4b01-4a0d-adda-6fd8f57c8f24)
  ![2](https://github.com/user-attachments/assets/b72269a5-fd0e-4b55-838d-2742e0b7de07)
- Additional Bag Pockets (ITEMS / **MEDICINE** / POKé BALLS / TMs & HMs / **POWER UP** / BERRIES / **TREASURES** / KEY ITEMS)

  ![3](https://github.com/user-attachments/assets/dc76a879-fb2f-4781-8dc9-8714c1095a38)
- Bag sort option.

  ![10](https://github.com/user-attachments/assets/255ca3b3-dc63-4dc5-bb9d-59b0a87ae90d)
- Updated Party screen (modified gen-4 style).

  ![12](https://github.com/user-attachments/assets/17b45658-a0dd-4d5a-8f19-6ec29938f15f)
- Relearn Moves in party screen.

  ![7](https://github.com/user-attachments/assets/793e3972-9d2b-4290-872e-16f7e4323595)
- Relearn Egg moves (option to only learn at a specific level or to disable it).
- Move item in party screen (instead of having to open bag, also can be activated with SELECT).

  ![6](https://github.com/user-attachments/assets/73b36aa6-3e08-473f-9bb4-91ec5375c41b)
- Automatic Level Cap (can be called when received a badge for example or when receiving a pokémon. It runs when the game starts).
- Level Up Evolution via party screen (with a indicator to show that a pokémon can evolve via Level Up).

  ![5](https://github.com/user-attachments/assets/7d5946ce-43b9-4901-9157-7758fbc1373f)
- "Random Gift Pokémon" script.

  ![11](https://github.com/user-attachments/assets/915c03a7-9752-4720-8955-ea18cf2eac92)
- Options include:
  - 'Minimum Base Stats' / 'Maximum Base Stats' (The Pokémon has to have a base stat value between these values. Can be unset).
  - 'Type 1' / 'Type 2' (The Pokémon has to have one of these types. Can be unset).
  - 'Allow' (Allow or prohibit for example all Legendary, Ultra Beast, or Regional Forms etc.. If unset all of these examples are allowed).
  - 'Exclusion' (Excludes a specific Pokémon, for example Shedinja. Can be unset).
  - 'Evolution Species Stage' (The Pokémon has to be a specific evolution stage, meaning if set to 2 then Pokémon like Ivysaur, Wartortle, Charmeleon, and Snorlax could be selected. Can be unset.).
  - 'Evolution Family Stage' (The Pokémon has to be part of a specific family evolution stage, meaning if set to 2 then Pokémon like Munchlax, Snorlax, Seel, Dewgong could be selected. Can be unset.).
  - Setup: Simply set the script 'RandomPokemonGift_Eventscript' to an object and adjust the parameters in 'src/alcyon.c' > 'sMapAreaRandomPokemonAttributes' for the current map (examples in the file).
  - Randomization generated by Trainer ID, so same Trainer ID will always generate same pokémon if the parameters are the same (takes into account the map/objectid aswell). Randomization (Trainer ID) can be regenerated in the options menu.

    ![11](https://github.com/user-attachments/assets/77f21652-35d7-40fd-b984-f46cde2642e4)
- Animation skip for HM Field effects (the popup only) and overall faster initialization (no dialog etc)
- Can always use HM Field effects in the overworld (Surf / Strength / Cut / Waterfall / Dive / Rock Smash).

  ![15](https://github.com/user-attachments/assets/cb88f712-743a-46ff-9d89-fb9e06f480f5)
  ![17](https://github.com/user-attachments/assets/bda77521-285d-46c4-94e7-59ec48025f8d)
  ![18](https://github.com/user-attachments/assets/28801eb8-4ed0-473a-af25-cd10a9c69586)
  ![19](https://github.com/user-attachments/assets/e54dc8e4-397e-4a98-a6bc-5c2d7b8a5807)
  ![21](https://github.com/user-attachments/assets/2e258197-e591-4075-b402-f5ef07c88cdf)
  ![22](https://github.com/user-attachments/assets/49c6b723-7b85-4873-97e1-812e20e8d55b)

- Surf rush with B press.

  ![16](https://github.com/user-attachments/assets/d78fa68c-814a-4b1c-bdf4-615cb2d8aa8a)
