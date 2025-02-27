PokemonEncounter_Eventscript::
# 2 "data/scripts/obtain_pokemon.pory"
	lockall
# 4 "data/scripts/obtain_pokemon.pory"
	special randomPokemonGift_SetVar
# 6 "data/scripts/obtain_pokemon.pory"
	compare VAR_RESULT, 0
	goto_if_ne PokemonEncounter_Eventscript_2
# 58 "data/scripts/obtain_pokemon.pory"
	msgbox PokemonEncounter_Eventscript_Text_4
PokemonEncounter_Eventscript_1:
# 61 "data/scripts/obtain_pokemon.pory"
	waitmessage
# 62 "data/scripts/obtain_pokemon.pory"
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
# 51 "data/scripts/obtain_pokemon.pory"
	hidemonpic
PokemonEncounter_Eventscript_5:
# 54 "data/scripts/obtain_pokemon.pory"
	special AutomaticLevelCap
	goto PokemonEncounter_Eventscript_1

PokemonEncounter_Eventscript_6:
# 14 "data/scripts/obtain_pokemon.pory"
	random 5
# 15 "data/scripts/obtain_pokemon.pory"
	switch VAR_RESULT
# 16 "data/scripts/obtain_pokemon.pory"
	case 0, PokemonEncounter_Eventscript_11
# 17 "data/scripts/obtain_pokemon.pory"
	case 2, PokemonEncounter_Eventscript_12
# 18 "data/scripts/obtain_pokemon.pory"
	case 3, PokemonEncounter_Eventscript_13
# 19 "data/scripts/obtain_pokemon.pory"
	case 4, PokemonEncounter_Eventscript_14
# 20 "data/scripts/obtain_pokemon.pory"
	case 5, PokemonEncounter_Eventscript_15
PokemonEncounter_Eventscript_9:
# 24 "data/scripts/obtain_pokemon.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq PokemonEncounter_Eventscript_16
# 34 "data/scripts/obtain_pokemon.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PC
	goto_if_eq PokemonEncounter_Eventscript_17
# 45 "data/scripts/obtain_pokemon.pory"
	hidemonpic
# 46 "data/scripts/obtain_pokemon.pory"
	msgbox PokemonEncounter_Eventscript_Text_3
	goto PokemonEncounter_Eventscript_5

PokemonEncounter_Eventscript_11:
# 16 "data/scripts/obtain_pokemon.pory"
	givemon VAR_0x8005, 15, , , , 1
	goto PokemonEncounter_Eventscript_9

PokemonEncounter_Eventscript_12:
# 17 "data/scripts/obtain_pokemon.pory"
	givemon VAR_0x8005, 15, , , , 1
	goto PokemonEncounter_Eventscript_9

PokemonEncounter_Eventscript_13:
# 18 "data/scripts/obtain_pokemon.pory"
	givemon VAR_0x8005, 15, , , , 2
	goto PokemonEncounter_Eventscript_9

PokemonEncounter_Eventscript_14:
# 19 "data/scripts/obtain_pokemon.pory"
	givemon VAR_0x8005, 15, , , , 2
	goto PokemonEncounter_Eventscript_9

PokemonEncounter_Eventscript_15:
# 20 "data/scripts/obtain_pokemon.pory"
	givemon VAR_0x8005, 15, , , , 3
	goto PokemonEncounter_Eventscript_9

PokemonEncounter_Eventscript_16:
# 25 "data/scripts/obtain_pokemon.pory"
	playfanfare MUS_OBTAIN_ITEM
# 26 "data/scripts/obtain_pokemon.pory"
	hidemonpic
# 27 "data/scripts/obtain_pokemon.pory"
	removeobject VAR_LAST_TALKED
# 28 "data/scripts/obtain_pokemon.pory"
	msgbox PokemonEncounter_Eventscript_Text_1, MSGBOX_YESNO
# 29 "data/scripts/obtain_pokemon.pory"
	compare VAR_RESULT, YES
	goto_if_eq PokemonEncounter_Eventscript_21
	goto PokemonEncounter_Eventscript_5

PokemonEncounter_Eventscript_17:
# 35 "data/scripts/obtain_pokemon.pory"
	playfanfare MUS_OBTAIN_ITEM
# 36 "data/scripts/obtain_pokemon.pory"
	hidemonpic
# 37 "data/scripts/obtain_pokemon.pory"
	removeobject VAR_LAST_TALKED
# 38 "data/scripts/obtain_pokemon.pory"
	msgbox PokemonEncounter_Eventscript_Text_1, MSGBOX_YESNO
# 39 "data/scripts/obtain_pokemon.pory"
	compare VAR_RESULT, YES
	goto_if_eq PokemonEncounter_Eventscript_24
PokemonEncounter_Eventscript_23:
# 42 "data/scripts/obtain_pokemon.pory"
	msgbox PokemonEncounter_Eventscript_Text_2
	goto PokemonEncounter_Eventscript_5

PokemonEncounter_Eventscript_21:
# 30 "data/scripts/obtain_pokemon.pory"
	call Common_EventScript_GetGiftMonPartySlot
# 31 "data/scripts/obtain_pokemon.pory"
	call Common_EventScript_NameReceivedPartyMon
	goto PokemonEncounter_Eventscript_5

PokemonEncounter_Eventscript_24:
# 40 "data/scripts/obtain_pokemon.pory"
	call Common_EventScript_NameReceivedBoxMon
	goto PokemonEncounter_Eventscript_23


PokemonEncounter_Eventscript_Text_0:
# 10 "data/scripts/obtain_pokemon.pory"
	.string "You found a {STR_VAR_1}!\n"
	.string "Would you like to keep it?$"

PokemonEncounter_Eventscript_Text_1:
# 28 "data/scripts/obtain_pokemon.pory"
	.string "Would you like to give {STR_VAR_1} a\n"
	.string "nickname?$"

PokemonEncounter_Eventscript_Text_2:
# 42 "data/scripts/obtain_pokemon.pory"
	.string "{STR_VAR_1} was transferred to the\n"
	.string "PC.$"

PokemonEncounter_Eventscript_Text_3:
# 46 "data/scripts/obtain_pokemon.pory"
	.string "Your PC is Full!$"

PokemonEncounter_Eventscript_Text_4:
# 58 "data/scripts/obtain_pokemon.pory"
	.string "Error occurred.$"
