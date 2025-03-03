Eventscript_RandomPokemonGift::
# 2 "data/scripts/obtain_pokemon.pory"
	lockall
# 4 "data/scripts/obtain_pokemon.pory"
	special RandomPokemonGift_SetVar
# 6 "data/scripts/obtain_pokemon.pory"
	compare VAR_RESULT, 0
	goto_if_ne Eventscript_RandomPokemonGift_2
# 50 "data/scripts/obtain_pokemon.pory"
	msgbox Eventscript_RandomPokemonGift_Text_4
Eventscript_RandomPokemonGift_1:
# 53 "data/scripts/obtain_pokemon.pory"
	waitmessage
# 54 "data/scripts/obtain_pokemon.pory"
	releaseall
	end

Eventscript_RandomPokemonGift_2:
# 8 "data/scripts/obtain_pokemon.pory"
	showmonpic VAR_0x8005, 10, 3
# 9 "data/scripts/obtain_pokemon.pory"
	bufferspeciesname STR_VAR_1, VAR_0x8005
# 10 "data/scripts/obtain_pokemon.pory"
	msgbox Eventscript_RandomPokemonGift_Text_0, MSGBOX_YESNO
# 12 "data/scripts/obtain_pokemon.pory"
	compare VAR_RESULT, YES
	goto_if_eq Eventscript_RandomPokemonGift_5
# 45 "data/scripts/obtain_pokemon.pory"
	hidemonpic
	goto Eventscript_RandomPokemonGift_1

Eventscript_RandomPokemonGift_5:
# 14 "data/scripts/obtain_pokemon.pory"
	givemon VAR_0x8005, 15
# 16 "data/scripts/obtain_pokemon.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq Eventscript_RandomPokemonGift_8
# 27 "data/scripts/obtain_pokemon.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PC
	goto_if_eq Eventscript_RandomPokemonGift_9
# 39 "data/scripts/obtain_pokemon.pory"
	hidemonpic
# 40 "data/scripts/obtain_pokemon.pory"
	msgbox Eventscript_RandomPokemonGift_Text_3
	goto Eventscript_RandomPokemonGift_1

Eventscript_RandomPokemonGift_8:
# 17 "data/scripts/obtain_pokemon.pory"
	playfanfare MUS_OBTAIN_ITEM
# 18 "data/scripts/obtain_pokemon.pory"
	hidemonpic
# 19 "data/scripts/obtain_pokemon.pory"
	special RandomPokemonGift_RemoveObjects
# 20 "data/scripts/obtain_pokemon.pory"
	msgbox Eventscript_RandomPokemonGift_Text_1, MSGBOX_YESNO
# 21 "data/scripts/obtain_pokemon.pory"
	compare VAR_RESULT, YES
	goto_if_eq Eventscript_RandomPokemonGift_14
Eventscript_RandomPokemonGift_13:
# 25 "data/scripts/obtain_pokemon.pory"
	special SetPartyToLevelCap
	goto Eventscript_RandomPokemonGift_1

Eventscript_RandomPokemonGift_9:
# 28 "data/scripts/obtain_pokemon.pory"
	playfanfare MUS_OBTAIN_ITEM
# 29 "data/scripts/obtain_pokemon.pory"
	hidemonpic
# 30 "data/scripts/obtain_pokemon.pory"
	special RandomPokemonGift_RemoveObjects
# 31 "data/scripts/obtain_pokemon.pory"
	msgbox Eventscript_RandomPokemonGift_Text_1, MSGBOX_YESNO
# 32 "data/scripts/obtain_pokemon.pory"
	compare VAR_RESULT, YES
	goto_if_eq Eventscript_RandomPokemonGift_17
Eventscript_RandomPokemonGift_16:
# 35 "data/scripts/obtain_pokemon.pory"
	msgbox Eventscript_RandomPokemonGift_Text_2
# 36 "data/scripts/obtain_pokemon.pory"
	special SetBoxToLevelCap
	goto Eventscript_RandomPokemonGift_1

Eventscript_RandomPokemonGift_14:
# 22 "data/scripts/obtain_pokemon.pory"
	call Common_EventScript_GetGiftMonPartySlot
# 23 "data/scripts/obtain_pokemon.pory"
	call Common_EventScript_NameReceivedPartyMon
	goto Eventscript_RandomPokemonGift_13

Eventscript_RandomPokemonGift_17:
# 33 "data/scripts/obtain_pokemon.pory"
	call Common_EventScript_NameReceivedBoxMon
	goto Eventscript_RandomPokemonGift_16


Eventscript_RandomPokemonGift_Text_0:
# 10 "data/scripts/obtain_pokemon.pory"
	.string "You found a {STR_VAR_1}!\n"
	.string "Would you like to keep it?$"

Eventscript_RandomPokemonGift_Text_1:
# 20 "data/scripts/obtain_pokemon.pory"
	.string "Would you like to give {STR_VAR_1} a\n"
	.string "nickname?$"

Eventscript_RandomPokemonGift_Text_2:
# 35 "data/scripts/obtain_pokemon.pory"
	.string "{STR_VAR_1} was transferred to the\n"
	.string "PC.$"

Eventscript_RandomPokemonGift_Text_3:
# 40 "data/scripts/obtain_pokemon.pory"
	.string "Your PC is Full!$"

Eventscript_RandomPokemonGift_Text_4:
# 50 "data/scripts/obtain_pokemon.pory"
	.string "Error occurred.$"
