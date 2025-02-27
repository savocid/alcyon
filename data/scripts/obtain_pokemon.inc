PokemonEncounter_Eventscript::
# 2 "data/scripts/obtain_pokemon.pory"
	lockall
# 4 "data/scripts/obtain_pokemon.pory"
	special randomPokemonGift_SetVar
# 6 "data/scripts/obtain_pokemon.pory"
	compare VAR_RESULT, 0
	goto_if_ne PokemonEncounter_Eventscript_2
# 50 "data/scripts/obtain_pokemon.pory"
	msgbox PokemonEncounter_Eventscript_Text_4
PokemonEncounter_Eventscript_1:
# 53 "data/scripts/obtain_pokemon.pory"
	waitmessage
# 54 "data/scripts/obtain_pokemon.pory"
	releaseall
	end

PokemonEncounter_Eventscript_2:
# 8 "data/scripts/obtain_pokemon.pory"
	showmonpic VAR_0x8005, 10, 3
# 9 "data/scripts/obtain_pokemon.pory"
	bufferspeciesname STR_VAR_1, VAR_0x8005
# 10 "data/scripts/obtain_pokemon.pory"
	msgbox PokemonEncounter_Eventscript_Text_0, MSGBOX_YESNO
# 12 "data/scripts/obtain_pokemon.pory"
	compare VAR_RESULT, YES
	goto_if_eq PokemonEncounter_Eventscript_6
# 43 "data/scripts/obtain_pokemon.pory"
	hidemonpic
PokemonEncounter_Eventscript_5:
# 46 "data/scripts/obtain_pokemon.pory"
	special AutomaticLevelCap
	goto PokemonEncounter_Eventscript_1

PokemonEncounter_Eventscript_6:
# 14 "data/scripts/obtain_pokemon.pory"
	givemon VAR_0x8005, 5
# 16 "data/scripts/obtain_pokemon.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq PokemonEncounter_Eventscript_9
# 26 "data/scripts/obtain_pokemon.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PC
	goto_if_eq PokemonEncounter_Eventscript_10
# 37 "data/scripts/obtain_pokemon.pory"
	hidemonpic
# 38 "data/scripts/obtain_pokemon.pory"
	msgbox PokemonEncounter_Eventscript_Text_3
	goto PokemonEncounter_Eventscript_5

PokemonEncounter_Eventscript_9:
# 17 "data/scripts/obtain_pokemon.pory"
	playfanfare MUS_OBTAIN_ITEM
# 18 "data/scripts/obtain_pokemon.pory"
	hidemonpic
# 19 "data/scripts/obtain_pokemon.pory"
	removeobject VAR_LAST_TALKED
# 20 "data/scripts/obtain_pokemon.pory"
	msgbox PokemonEncounter_Eventscript_Text_1, MSGBOX_YESNO
# 21 "data/scripts/obtain_pokemon.pory"
	compare VAR_RESULT, YES
	goto_if_eq PokemonEncounter_Eventscript_14
	goto PokemonEncounter_Eventscript_5

PokemonEncounter_Eventscript_10:
# 27 "data/scripts/obtain_pokemon.pory"
	playfanfare MUS_OBTAIN_ITEM
# 28 "data/scripts/obtain_pokemon.pory"
	hidemonpic
# 29 "data/scripts/obtain_pokemon.pory"
	removeobject VAR_LAST_TALKED
# 30 "data/scripts/obtain_pokemon.pory"
	msgbox PokemonEncounter_Eventscript_Text_1, MSGBOX_YESNO
# 31 "data/scripts/obtain_pokemon.pory"
	compare VAR_RESULT, YES
	goto_if_eq PokemonEncounter_Eventscript_17
PokemonEncounter_Eventscript_16:
# 34 "data/scripts/obtain_pokemon.pory"
	msgbox PokemonEncounter_Eventscript_Text_2
	goto PokemonEncounter_Eventscript_5

PokemonEncounter_Eventscript_14:
# 22 "data/scripts/obtain_pokemon.pory"
	call Common_EventScript_GetGiftMonPartySlot
# 23 "data/scripts/obtain_pokemon.pory"
	call Common_EventScript_NameReceivedPartyMon
	goto PokemonEncounter_Eventscript_5

PokemonEncounter_Eventscript_17:
# 32 "data/scripts/obtain_pokemon.pory"
	call Common_EventScript_NameReceivedBoxMon
	goto PokemonEncounter_Eventscript_16


PokemonEncounter_Eventscript_Text_0:
# 10 "data/scripts/obtain_pokemon.pory"
	.string "You found a {STR_VAR_1}!\n"
	.string "Would you like to keep it?$"

PokemonEncounter_Eventscript_Text_1:
# 20 "data/scripts/obtain_pokemon.pory"
	.string "Would you like to give {STR_VAR_1} a\n"
	.string "nickname?$"

PokemonEncounter_Eventscript_Text_2:
# 34 "data/scripts/obtain_pokemon.pory"
	.string "{STR_VAR_1} was transferred to the\n"
	.string "PC.$"

PokemonEncounter_Eventscript_Text_3:
# 38 "data/scripts/obtain_pokemon.pory"
	.string "Your PC is Full!$"

PokemonEncounter_Eventscript_Text_4:
# 50 "data/scripts/obtain_pokemon.pory"
	.string "Error occurred.$"
