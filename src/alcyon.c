#include "global.h"
#include "alcyon.h"
#include "event_data.h"
#include "overworld.h"
#include "wild_encounter.h"
#include "fieldmap.h"
#include "random.h"
#include "event_object_movement.h"
#include "pokemon.h"
#include "new_game.h"
#include "caps.h"
#include "constants/maps.h"
#include "gba/gba.h"
#include "wild_encounter.h"
#include "pokedex.h"
#include "event_object_movement.h"
#include "overworld.h"
#include "constants/event_objects.h"
#include "event_scripts.h"

static const struct SpeciesEvoData sSpeciesEvolutionStage[NUM_SPECIES + 1] =
{
    [SPECIES_NONE]                                       = { EVO_SPECIES_STAGE_0, EVO_SPECIES_STAGE_0 },

    // Generation 1
    [SPECIES_BULBASAUR]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_IVYSAUR]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_VENUSAUR]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_CHARMANDER]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_CHARMELEON]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_CHARIZARD]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_SQUIRTLE]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_WARTORTLE]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_BLASTOISE]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_CATERPIE]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_METAPOD]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_BUTTERFREE]                                 = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_WEEDLE]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_KAKUNA]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_BEEDRILL]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_PIDGEY]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_PIDGEOTTO]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_PIDGEOT]                                    = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_RATTATA]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_RATICATE]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SPEAROW]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_FEAROW]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_EKANS]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_ARBOK]                                      = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_PIKACHU]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_RAICHU]                                     = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_SANDSHREW]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SANDSLASH]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_NIDORAN_F]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_NIDORINA]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_NIDOQUEEN]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_NIDORAN_M]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_NIDORINO]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_NIDOKING]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_CLEFAIRY]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_CLEFABLE]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_VULPIX]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_NINETALES]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_JIGGLYPUFF]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_WIGGLYTUFF]                                 = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_ZUBAT]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_GOLBAT]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_ODDISH]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_GLOOM]                                      = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_VILEPLUME]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_PARAS]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_PARASECT]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_VENONAT]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_VENOMOTH]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_DIGLETT]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_DUGTRIO]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MEOWTH]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_PERSIAN]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_PSYDUCK]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_GOLDUCK]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MANKEY]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_PRIMEAPE]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_GROWLITHE]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_ARCANINE]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_POLIWAG]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_POLIWHIRL]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_POLIWRATH]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_ABRA]                                       = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_KADABRA]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_ALAKAZAM]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_MACHOP]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_MACHOKE]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_MACHAMP]                                    = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_BELLSPROUT]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_WEEPINBELL]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_VICTREEBEL]                                 = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_TENTACOOL]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_TENTACRUEL]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_GEODUDE]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_GRAVELER]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_GOLEM]                                      = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_PONYTA]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_RAPIDASH]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SLOWPOKE]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SLOWBRO]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MAGNEMITE]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_MAGNETON]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_FARFETCHD]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_DODUO]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_DODRIO]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SEEL]                                       = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_DEWGONG]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_GRIMER]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_MUK]                                        = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SHELLDER]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_CLOYSTER]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_GASTLY]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_HAUNTER]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_GENGAR]                                     = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_ONIX]                                       = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_DROWZEE]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_HYPNO]                                      = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_KRABBY]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_KINGLER]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_VOLTORB]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_ELECTRODE]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_EXEGGCUTE]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_EXEGGUTOR]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_CUBONE]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_MAROWAK]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_HITMONLEE]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_HITMONCHAN]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_LICKITUNG]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_KOFFING]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_WEEZING]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_RHYHORN]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_RHYDON]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_CHANSEY]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_TANGELA]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_KANGASKHAN]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_HORSEA]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SEADRA]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_GOLDEEN]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SEAKING]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_STARYU]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_STARMIE]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MR_MIME]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SCYTHER]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_JYNX]                                       = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ELECTABUZZ]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_MAGMAR]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_PINSIR]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_TAUROS]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MAGIKARP]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_GYARADOS]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_LAPRAS]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_DITTO]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_EEVEE]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_VAPOREON]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_JOLTEON]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_FLAREON]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_PORYGON]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_OMANYTE]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_OMASTAR]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_KABUTO]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_KABUTOPS]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_AERODACTYL]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SNORLAX]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ARTICUNO]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ZAPDOS]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MOLTRES]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_DRATINI]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_DRAGONAIR]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_DRAGONITE]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_MEWTWO]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MEW]                                        = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },

    // Generation 2
    [SPECIES_CHIKORITA]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_BAYLEEF]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_MEGANIUM]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_CYNDAQUIL]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_QUILAVA]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_TYPHLOSION]                                 = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_TOTODILE]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_CROCONAW]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_FERALIGATR]                                 = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_SENTRET]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_FURRET]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_HOOTHOOT]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_NOCTOWL]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_LEDYBA]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_LEDIAN]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SPINARAK]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_ARIADOS]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_CROBAT]                                     = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_CHINCHOU]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_LANTURN]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_PICHU]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_CLEFFA]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_IGGLYBUFF]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_TOGEPI]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_TOGETIC]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_NATU]                                       = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_XATU]                                       = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MAREEP]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_FLAAFFY]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_AMPHAROS]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_BELLOSSOM]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_MARILL]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_AZUMARILL]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_SUDOWOODO]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_POLITOED]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_HOPPIP]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SKIPLOOM]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_JUMPLUFF]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_AIPOM]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SUNKERN]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SUNFLORA]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_YANMA]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_WOOPER]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_QUAGSIRE]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ESPEON]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_UMBREON]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MURKROW]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SLOWKING]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MISDREAVUS]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_UNOWN]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_WOBBUFFET]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_GIRAFARIG]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_PINECO]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_FORRETRESS]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_DUNSPARCE]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_GLIGAR]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_STEELIX]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SNUBBULL]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_GRANBULL]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_QWILFISH]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SCIZOR]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SHUCKLE]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_HERACROSS]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SNEASEL]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_TEDDIURSA]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_URSARING]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SLUGMA]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_MAGCARGO]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SWINUB]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_PILOSWINE]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_CORSOLA]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_REMORAID]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_OCTILLERY]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_DELIBIRD]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MANTINE]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SKARMORY]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_HOUNDOUR]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_HOUNDOOM]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_KINGDRA]                                    = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_PHANPY]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_DONPHAN]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_PORYGON2]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_STANTLER]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SMEARGLE]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_TYROGUE]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_HITMONTOP]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SMOOCHUM]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_ELEKID]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_MAGBY]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_MILTANK]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_BLISSEY]                                    = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_RAIKOU]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ENTEI]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SUICUNE]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_LARVITAR]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_PUPITAR]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_TYRANITAR]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_LUGIA]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_HO_OH]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_CELEBI]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },

    // Generation 3
    [SPECIES_TREECKO]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_GROVYLE]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SCEPTILE]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_TORCHIC]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_COMBUSKEN]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_BLAZIKEN]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_MUDKIP]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_MARSHTOMP]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SWAMPERT]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_POOCHYENA]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_MIGHTYENA]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ZIGZAGOON]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_LINOONE]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_WURMPLE]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SILCOON]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_BEAUTIFLY]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_CASCOON]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_DUSTOX]                                     = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_LOTAD]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_LOMBRE]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_LUDICOLO]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_SEEDOT]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_NUZLEAF]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SHIFTRY]                                    = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_NINCADA]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_NINJASK]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SHEDINJA]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_TAILLOW]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SWELLOW]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SHROOMISH]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_BRELOOM]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SPINDA]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_WINGULL]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_PELIPPER]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SURSKIT]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_MASQUERAIN]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_WAILMER]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_WAILORD]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SKITTY]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_DELCATTY]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_KECLEON]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_BALTOY]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_CLAYDOL]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_NOSEPASS]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_TORKOAL]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SABLEYE]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_BARBOACH]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_WHISCASH]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_LUVDISC]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_CORPHISH]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_CRAWDAUNT]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_FEEBAS]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_MILOTIC]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_CARVANHA]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SHARPEDO]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_TRAPINCH]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_VIBRAVA]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_FLYGON]                                     = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_MAKUHITA]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_HARIYAMA]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ELECTRIKE]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_MANECTRIC]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_NUMEL]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_CAMERUPT]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SPHEAL]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SEALEO]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_WALREIN]                                    = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_CACNEA]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_CACTURNE]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SNORUNT]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_GLALIE]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_LUNATONE]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SOLROCK]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_AZURILL]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SPOINK]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_GRUMPIG]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_PLUSLE]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MINUN]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MAWILE]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MEDITITE]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_MEDICHAM]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SWABLU]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALTARIA]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_WYNAUT]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_DUSKULL]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_DUSCLOPS]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_ROSELIA]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SLAKOTH]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_VIGOROTH]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SLAKING]                                    = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_GULPIN]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SWALOT]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_TROPIUS]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_WHISMUR]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_LOUDRED]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_EXPLOUD]                                    = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_CLAMPERL]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_HUNTAIL]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_GOREBYSS]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ABSOL]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SHUPPET]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_BANETTE]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SEVIPER]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ZANGOOSE]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_RELICANTH]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ARON]                                       = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_LAIRON]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_AGGRON]                                     = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_CASTFORM]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_VOLBEAT]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ILLUMISE]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_LILEEP]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_CRADILY]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ANORITH]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_ARMALDO]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_RALTS]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_KIRLIA]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_GARDEVOIR]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_BAGON]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SHELGON]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SALAMENCE]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_BELDUM]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_METANG]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_METAGROSS]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_REGIROCK]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_REGICE]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_REGISTEEL]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_KYOGRE]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_GROUDON]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_RAYQUAZA]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_LATIAS]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_LATIOS]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_JIRACHI]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_DEOXYS]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_CHIMECHO]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },

    // Generation 4
    [SPECIES_TURTWIG]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_GROTLE]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_TORTERRA]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_CHIMCHAR]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_MONFERNO]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_INFERNAPE]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_PIPLUP]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_PRINPLUP]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_EMPOLEON]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_STARLY]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_STARAVIA]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_STARAPTOR]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_BIDOOF]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_BIBAREL]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_KRICKETOT]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_KRICKETUNE]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SHINX]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_LUXIO]                                      = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_LUXRAY]                                     = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_BUDEW]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_ROSERADE]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_CRANIDOS]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_RAMPARDOS]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SHIELDON]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_BASTIODON]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_BURMY]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_WORMADAM]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MOTHIM]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_COMBEE]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_VESPIQUEN]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_PACHIRISU]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_BUIZEL]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_FLOATZEL]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_CHERUBI]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_CHERRIM]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SHELLOS]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_GASTRODON]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_AMBIPOM]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_DRIFLOON]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_DRIFBLIM]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_BUNEARY]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_LOPUNNY]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MISMAGIUS]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_HONCHKROW]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_GLAMEOW]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_PURUGLY]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_CHINGLING]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_STUNKY]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SKUNTANK]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_BRONZOR]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_BRONZONG]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_BONSLY]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_MIME_JR]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 }, // ??
    [SPECIES_HAPPINY]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_CHATOT]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SPIRITOMB]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_GIBLE]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_GABITE]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_GARCHOMP]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_MUNCHLAX]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_RIOLU]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_LUCARIO]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_HIPPOPOTAS]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_HIPPOWDON]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SKORUPI]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_DRAPION]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_CROAGUNK]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_TOXICROAK]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_CARNIVINE]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_FINNEON]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_LUMINEON]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MANTYKE]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SNOVER]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_ABOMASNOW]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_WEAVILE]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MAGNEZONE]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_LICKILICKY]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_RHYPERIOR]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_TANGROWTH]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ELECTIVIRE]                                 = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_MAGMORTAR]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_TOGEKISS]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_YANMEGA]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_LEAFEON]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_GLACEON]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_GLISCOR]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MAMOSWINE]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_PORYGON_Z]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_GALLADE]                                    = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_PROBOPASS]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_DUSKNOIR]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_FROSLASS]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ROTOM]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_UXIE]                                       = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MESPRIT]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_AZELF]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_DIALGA]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_PALKIA]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_HEATRAN]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_REGIGIGAS]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_GIRATINA]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_CRESSELIA]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_PHIONE]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MANAPHY]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_DARKRAI]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SHAYMIN]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ARCEUS]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_VICTINI]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    
    // Generation 4
    [SPECIES_SNIVY]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SERVINE]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SERPERIOR]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_TEPIG]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_PIGNITE]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_EMBOAR]                                     = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_OSHAWOTT]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_DEWOTT]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SAMUROTT]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_PATRAT]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_WATCHOG]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_LILLIPUP]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_HERDIER]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_STOUTLAND]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_PURRLOIN]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_LIEPARD]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_PANSAGE]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SIMISAGE]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_PANSEAR]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SIMISEAR]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_PANPOUR]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SIMIPOUR]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MUNNA]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_MUSHARNA]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_PIDOVE]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_TRANQUILL]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_UNFEZANT]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_BLITZLE]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_ZEBSTRIKA]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ROGGENROLA]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_BOLDORE]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_GIGALITH]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_WOOBAT]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SWOOBAT]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_DRILBUR]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_EXCADRILL]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_AUDINO]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_TIMBURR]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_GURDURR]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_CONKELDURR]                                 = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_TYMPOLE]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_PALPITOAD]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SEISMITOAD]                                 = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_THROH]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SAWK]                                       = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SEWADDLE]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SWADLOON]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_LEAVANNY]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_VENIPEDE]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_WHIRLIPEDE]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SCOLIPEDE]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_COTTONEE]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_WHIMSICOTT]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_PETILIL]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_LILLIGANT]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_BASCULIN]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SANDILE]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_KROKOROK]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_KROOKODILE]                                 = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_DARUMAKA]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_DARMANITAN]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MARACTUS]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_DWEBBLE]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_CRUSTLE]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SCRAGGY]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SCRAFTY]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SIGILYPH]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_YAMASK]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_COFAGRIGUS]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_TIRTOUGA]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_CARRACOSTA]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ARCHEN]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_ARCHEOPS]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_TRUBBISH]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_GARBODOR]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ZORUA]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_ZOROARK]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MINCCINO]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_CINCCINO]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_GOTHITA]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_GOTHORITA]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_GOTHITELLE]                                 = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_SOLOSIS]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_DUOSION]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_REUNICLUS]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_DUCKLETT]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SWANNA]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_VANILLITE]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_VANILLISH]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_VANILLUXE]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_DEERLING]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SAWSBUCK]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_EMOLGA]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_KARRABLAST]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_ESCAVALIER]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_FOONGUS]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_AMOONGUSS]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_FRILLISH]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_JELLICENT]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALOMOMOLA]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_JOLTIK]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_GALVANTULA]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_FERROSEED]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_FERROTHORN]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_KLINK]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_KLANG]                                      = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_KLINKLANG]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_TYNAMO]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_EELEKTRIK]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_EELEKTROSS]                                 = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_ELGYEM]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_BEHEEYEM]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_LITWICK]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_LAMPENT]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_CHANDELURE]                                 = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_AXEW]                                       = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_FRAXURE]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_HAXORUS]                                    = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_CUBCHOO]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_BEARTIC]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_CRYOGONAL]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SHELMET]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_ACCELGOR]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_STUNFISK]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MIENFOO]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_MIENSHAO]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_DRUDDIGON]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_GOLETT]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_GOLURK]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_PAWNIARD]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_BISHARP]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_BOUFFALANT]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_RUFFLET]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_BRAVIARY]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_VULLABY]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_MANDIBUZZ]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_HEATMOR]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_DURANT]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_DEINO]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_ZWEILOUS]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_HYDREIGON]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_LARVESTA]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_VOLCARONA]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_COBALION]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_TERRAKION]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_VIRIZION]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_TORNADUS]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_THUNDURUS]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_RESHIRAM]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ZEKROM]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_LANDORUS]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_KYUREM]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_KELDEO]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MELOETTA]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_GENESECT]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },

    // Generation 6
    [SPECIES_CHESPIN]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_QUILLADIN]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_CHESNAUGHT]                                 = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_FENNEKIN]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_BRAIXEN]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_DELPHOX]                                    = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_FROAKIE]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_FROGADIER]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_GRENINJA]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_BUNNELBY]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_DIGGERSBY]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_FLETCHLING]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_FLETCHINDER]                                = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_TALONFLAME]                                 = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_SCATTERBUG]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SPEWPA]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_VIVILLON]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_LITLEO]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_PYROAR]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_FLABEBE]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_FLOETTE]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_FLORGES]                                    = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_SKIDDO]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_GOGOAT]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_PANCHAM]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_PANGORO]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_FURFROU]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ESPURR]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_MEOWSTIC]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_HONEDGE]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_DOUBLADE]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_AEGISLASH]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_SPRITZEE]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_AROMATISSE]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SWIRLIX]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SLURPUFF]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_INKAY]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_MALAMAR]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_BINACLE]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_BARBARACLE]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SKRELP]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_DRAGALGE]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_CLAUNCHER]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_CLAWITZER]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_HELIOPTILE]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_HELIOLISK]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_TYRUNT]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_TYRANTRUM]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_AMAURA]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_AURORUS]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SYLVEON]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_HAWLUCHA]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_DEDENNE]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_CARBINK]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_GOOMY]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SLIGGOO]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_GOODRA]                                     = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_KLEFKI]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_PHANTUMP]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_TREVENANT]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_PUMPKABOO]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_GOURGEIST]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_BERGMITE]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_AVALUGG]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_NOIBAT]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_NOIVERN]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_XERNEAS]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_YVELTAL]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ZYGARDE]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_DIANCIE]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_HOOPA]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_VOLCANION]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },

    // Generation 7
    [SPECIES_ROWLET]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_DARTRIX]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_DECIDUEYE]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_LITTEN]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_TORRACAT]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_INCINEROAR]                                 = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_POPPLIO]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_BRIONNE]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_PRIMARINA]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_PIKIPEK]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_TRUMBEAK]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_TOUCANNON]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_YUNGOOS]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_GUMSHOOS]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_GRUBBIN]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_CHARJABUG]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_VIKAVOLT]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_CRABRAWLER]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_CRABOMINABLE]                               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ORICORIO]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_CUTIEFLY]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_RIBOMBEE]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ROCKRUFF]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_LYCANROC]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_WISHIWASHI]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MAREANIE]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_TOXAPEX]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MUDBRAY]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_MUDSDALE]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_DEWPIDER]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_ARAQUANID]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_FOMANTIS]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_LURANTIS]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MORELULL]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SHIINOTIC]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SALANDIT]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SALAZZLE]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_STUFFUL]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_BEWEAR]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_BOUNSWEET]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_STEENEE]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_TSAREENA]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_COMFEY]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ORANGURU]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_PASSIMIAN]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_WIMPOD]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_GOLISOPOD]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SANDYGAST]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_PALOSSAND]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_PYUKUMUKU]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_TYPE_NULL]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SILVALLY]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MINIOR]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_KOMALA]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_TURTONATOR]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_TOGEDEMARU]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MIMIKYU]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_BRUXISH]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_DRAMPA]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_DHELMISE]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_JANGMO_O]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_HAKAMO_O]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_KOMMO_O]                                    = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_TAPU_KOKO]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_TAPU_LELE]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_TAPU_BULU]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_TAPU_FINI]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_COSMOG]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_COSMOEM]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SOLGALEO]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_LUNALA]                                     = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_NIHILEGO]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_BUZZWOLE]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_PHEROMOSA]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_XURKITREE]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_CELESTEELA]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_KARTANA]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_GUZZLORD]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_NECROZMA]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MAGEARNA]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MARSHADOW]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_POIPOLE]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_NAGANADEL]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_STAKATAKA]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_BLACEPHALON]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ZERAORA]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MELTAN]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MELMETAL]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },

    // Generation 8
    [SPECIES_GROOKEY]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_THWACKEY]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_RILLABOOM]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_SCORBUNNY]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_RABOOT]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_CINDERACE]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_SOBBLE]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_DRIZZILE]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_INTELEON]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_SKWOVET]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_GREEDENT]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ROOKIDEE]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_CORVISQUIRE]                                = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_CORVIKNIGHT]                                = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_BLIPBUG]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_DOTTLER]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_ORBEETLE]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_NICKIT]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_THIEVUL]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_GOSSIFLEUR]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_ELDEGOSS]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_WOOLOO]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_DUBWOOL]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_CHEWTLE]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_DREDNAW]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_YAMPER]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_BOLTUND]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ROLYCOLY]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_CARKOL]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_COALOSSAL]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_APPLIN]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 }, // ??
    [SPECIES_FLAPPLE]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 }, // ??
    [SPECIES_APPLETUN]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 }, // ??
    [SPECIES_SILICOBRA]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SANDACONDA]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_CRAMORANT]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ARROKUDA]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_BARRASKEWDA]                                = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_TOXEL]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_TOXTRICITY]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SIZZLIPEDE]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_CENTISKORCH]                                = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_CLOBBOPUS]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_GRAPPLOCT]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SINISTEA]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_POLTEAGEIST]                                = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_HATENNA]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_HATTREM]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_HATTERENE]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_IMPIDIMP]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_MORGREM]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_GRIMMSNARL]                                 = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_OBSTAGOON]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_PERRSERKER]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_CURSOLA]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SIRFETCHD]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MR_RIME]                                    = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_RUNERIGUS]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MILCERY]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_FALINKS]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_PINCURCHIN]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SNOM]                                       = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_FROSMOTH]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_STONJOURNER]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_EISCUE]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_INDEEDEE]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MORPEKO]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_CUFANT]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_COPPERAJAH]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_DRACOZOLT]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ARCTOZOLT]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_DRACOVISH]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ARCTOVISH]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_DURALUDON]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_DREEPY]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_DRAKLOAK]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_DRAGAPULT]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_ZACIAN]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ZAMAZENTA]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ETERNATUS]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_KUBFU]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_URSHIFU]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ZARUDE]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_REGIELEKI]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_REGIDRAGO]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_GLASTRIER]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SPECTRIER]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_CALYREX]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },

    // Legend Arceus
    [SPECIES_WYRDEER]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_KLEAVOR]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_URSALUNA]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_BASCULEGION_M]                              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SNEASLER]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_OVERQWIL]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ENAMORUS_INCARNATE]                         = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },

    // Mega
    /*
    [SPECIES_VENUSAUR_MEGA]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_CHARIZARD_MEGA_X]                           = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_CHARIZARD_MEGA_Y]                           = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_BLASTOISE_MEGA]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_BEEDRILL_MEGA]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_PIDGEOT_MEGA]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ALAKAZAM_MEGA]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SLOWBRO_MEGA]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_GENGAR_MEGA]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_KANGASKHAN_MEGA]                            = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_PINSIR_MEGA]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_GYARADOS_MEGA]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_AERODACTYL_MEGA]                            = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MEWTWO_MEGA_X]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MEWTWO_MEGA_Y]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_AMPHAROS_MEGA]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_STEELIX_MEGA]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SCIZOR_MEGA]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_HERACROSS_MEGA]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_HOUNDOOM_MEGA]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_TYRANITAR_MEGA]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SCEPTILE_MEGA]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_BLAZIKEN_MEGA]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SWAMPERT_MEGA]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_GARDEVOIR_MEGA]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SABLEYE_MEGA]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MAWILE_MEGA]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_AGGRON_MEGA]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MEDICHAM_MEGA]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MANECTRIC_MEGA]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SHARPEDO_MEGA]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_CAMERUPT_MEGA]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ALTARIA_MEGA]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_BANETTE_MEGA]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ABSOL_MEGA]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_GLALIE_MEGA]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SALAMENCE_MEGA]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_METAGROSS_MEGA]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_LATIAS_MEGA]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_LATIOS_MEGA]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_LOPUNNY_MEGA]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_GARCHOMP_MEGA]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_LUCARIO_MEGA]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ABOMASNOW_MEGA]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_GALLADE_MEGA]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_AUDINO_MEGA]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_DIANCIE_MEGA]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_RAYQUAZA_MEGA]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    */

    // Primal
    /*
    [SPECIES_KYOGRE_PRIMAL]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_GROUDON_PRIMAL]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    */

    // Alolan
    [SPECIES_RATTATA_ALOLA]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_RATICATE_ALOLA]                             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_RAICHU_ALOLA]                               = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_SANDSHREW_ALOLA]                            = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SANDSLASH_ALOLA]                            = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_VULPIX_ALOLA]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_NINETALES_ALOLA]                            = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_DIGLETT_ALOLA]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_DUGTRIO_ALOLA]                              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MEOWTH_ALOLA]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_PERSIAN_ALOLA]                              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_GEODUDE_ALOLA]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_GRAVELER_ALOLA]                             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_GOLEM_ALOLA]                                = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_GRIMER_ALOLA]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_MUK_ALOLA]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_EXEGGUTOR_ALOLA]                            = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MAROWAK_ALOLA]                              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },

    // Galarian
    [SPECIES_MEOWTH_GALAR]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_PONYTA_GALAR]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_RAPIDASH_GALAR]                             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SLOWPOKE_GALAR]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SLOWBRO_GALAR]                              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_FARFETCHD_GALAR]                            = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_WEEZING_GALAR]                              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MR_MIME_GALAR]                              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_ARTICUNO_GALAR]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ZAPDOS_GALAR]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MOLTRES_GALAR]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SLOWKING_GALAR]                             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_CORSOLA_GALAR]                              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ZIGZAGOON_GALAR]                            = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_LINOONE_GALAR]                              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_DARUMAKA_GALAR]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_DARMANITAN_GALAR]                           = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_YAMASK_GALAR]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_STUNFISK_GALAR]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },

    // Hisuian
    [SPECIES_GROWLITHE_HISUI]                            = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_ARCANINE_HISUI]                             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_VOLTORB_HISUI]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_ELECTRODE_HISUI]                            = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_TYPHLOSION_HISUI]                           = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_QWILFISH_HISUI]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SNEASEL_HISUI]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SAMUROTT_HISUI]                             = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_LILLIGANT_HISUI]                            = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ZORUA_HISUI]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_ZOROARK_HISUI]                              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_BRAVIARY_HISUI]                             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SLIGGOO_HISUI]                              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_GOODRA_HISUI]                               = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_AVALUGG_HISUI]                              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_DECIDUEYE_HISUI]                            = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },

    // Other Forms
    /*
    [SPECIES_PIKACHU_COSPLAY]                            = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_PIKACHU_ROCK_STAR]                          = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_PIKACHU_BELLE]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_PIKACHU_POP_STAR]                           = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_PIKACHU_PHD]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_PIKACHU_LIBRE]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_PIKACHU_ORIGINAL]                           = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_PIKACHU_HOENN]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_PIKACHU_SINNOH]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_PIKACHU_UNOVA]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_PIKACHU_KALOS]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_PIKACHU_ALOLA]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_PIKACHU_PARTNER]                            = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_PIKACHU_WORLD]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_PICHU_SPIKY_EARED]                          = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_UNOWN_B]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_UNOWN_C]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_UNOWN_D]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_UNOWN_E]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_UNOWN_F]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_UNOWN_G]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_UNOWN_H]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_UNOWN_I]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_UNOWN_J]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_UNOWN_K]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_UNOWN_L]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_UNOWN_M]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_UNOWN_N]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_UNOWN_O]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_UNOWN_P]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_UNOWN_Q]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_UNOWN_R]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_UNOWN_S]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_UNOWN_T]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_UNOWN_U]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_UNOWN_V]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_UNOWN_W]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_UNOWN_X]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_UNOWN_Y]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_UNOWN_Z]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_UNOWN_EXCLAMATION]                          = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_UNOWN_QUESTION]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_CASTFORM_SUNNY]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_CASTFORM_RAINY]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_CASTFORM_SNOWY]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_DEOXYS_ATTACK]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_DEOXYS_DEFENSE]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_DEOXYS_SPEED]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_BURMY_SANDY]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_BURMY_TRASH]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_WORMADAM_SANDY]                             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_WORMADAM_TRASH]                             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_CHERRIM_SUNSHINE]                           = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SHELLOS_EAST]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_GASTRODON_EAST]                             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ROTOM_HEAT]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ROTOM_WASH]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ROTOM_FROST]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ROTOM_FAN]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ROTOM_MOW]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_GIRATINA_ORIGIN]                            = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SHAYMIN_SKY]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ARCEUS_FIGHTING]                            = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ARCEUS_FLYING]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ARCEUS_POISON]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ARCEUS_GROUND]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ARCEUS_ROCK]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ARCEUS_BUG]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ARCEUS_GHOST]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ARCEUS_STEEL]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ARCEUS_FIRE]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ARCEUS_WATER]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ARCEUS_GRASS]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ARCEUS_ELECTRIC]                            = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ARCEUS_PSYCHIC]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ARCEUS_ICE]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ARCEUS_DRAGON]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ARCEUS_DARK]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ARCEUS_FAIRY]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_BASCULIN_BLUE_STRIPED]                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_DARMANITAN_ZEN]                             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_DARMANITAN_GALAR_ZEN]                       = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_DEERLING_SUMMER]                            = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_DEERLING_AUTUMN]                            = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_DEERLING_WINTER]                            = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SAWSBUCK_SUMMER]                            = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SAWSBUCK_AUTUMN]                            = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SAWSBUCK_WINTER]                            = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_TORNADUS_THERIAN]                           = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_THUNDURUS_THERIAN]                          = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_LANDORUS_THERIAN]                           = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_KYUREM_WHITE]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_KYUREM_BLACK]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_KELDEO_RESOLUTE]                            = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MELOETTA_PIROUETTE]                         = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_GENESECT_DOUSE]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_GENESECT_SHOCK]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_GENESECT_BURN]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_GENESECT_CHILL]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_GRENINJA_BATTLE_BOND]                       = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_GRENINJA_ASH]                               = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_VIVILLON_POLAR]                             = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_VIVILLON_TUNDRA]                            = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_VIVILLON_CONTINENTAL]                       = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_VIVILLON_GARDEN]                            = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_VIVILLON_ELEGANT]                           = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_VIVILLON_MEADOW]                            = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_VIVILLON_MODERN]                            = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_VIVILLON_MARINE]                            = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_VIVILLON_ARCHIPELAGO]                       = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_VIVILLON_HIGH_PLAINS]                       = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_VIVILLON_SANDSTORM]                         = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_VIVILLON_RIVER]                             = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_VIVILLON_MONSOON]                           = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_VIVILLON_SAVANNA]                           = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_VIVILLON_SUN]                               = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_VIVILLON_OCEAN]                             = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_VIVILLON_JUNGLE]                            = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_VIVILLON_FANCY]                             = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_VIVILLON_POKEBALL]                          = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_FLABEBE_YELLOW]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_FLABEBE_ORANGE]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_FLABEBE_BLUE]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_FLABEBE_WHITE]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_FLOETTE_YELLOW]                             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_FLOETTE_ORANGE]                             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_FLOETTE_BLUE]                               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_FLOETTE_WHITE]                              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_FLOETTE_ETERNAL]                            = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_FLORGES_YELLOW]                             = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_FLORGES_ORANGE]                             = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_FLORGES_BLUE]                               = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_FLORGES_WHITE]                              = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_FURFROU_HEART_TRIM]                         = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_FURFROU_STAR_TRIM]                          = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_FURFROU_DIAMOND_TRIM]                       = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_FURFROU_DEBUTANTE_TRIM]                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_FURFROU_MATRON_TRIM]                        = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_FURFROU_DANDY_TRIM]                         = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_FURFROU_LA_REINE_TRIM]                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_FURFROU_KABUKI_TRIM]                        = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_FURFROU_PHARAOH_TRIM]                       = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MEOWSTIC_F]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_AEGISLASH_BLADE]                            = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_PUMPKABOO_SMALL]                            = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_PUMPKABOO_LARGE]                            = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_PUMPKABOO_SUPER]                            = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_GOURGEIST_SMALL]                            = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_GOURGEIST_LARGE]                            = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_GOURGEIST_SUPER]                            = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_XERNEAS_ACTIVE]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ZYGARDE_10]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ZYGARDE_10_POWER_CONSTRUCT]                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ZYGARDE_50_POWER_CONSTRUCT]                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ZYGARDE_COMPLETE]                           = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_HOOPA_UNBOUND]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ORICORIO_POM_POM]                           = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ORICORIO_PAU]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ORICORIO_SENSU]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ROCKRUFF_OWN_TEMPO]                         = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_LYCANROC_MIDNIGHT]                          = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_LYCANROC_DUSK]                              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_WISHIWASHI_SCHOOL]                          = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SILVALLY_FIGHTING]                          = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SILVALLY_FLYING]                            = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SILVALLY_POISON]                            = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SILVALLY_GROUND]                            = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SILVALLY_ROCK]                              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SILVALLY_BUG]                               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SILVALLY_GHOST]                             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SILVALLY_STEEL]                             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SILVALLY_FIRE]                              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SILVALLY_WATER]                             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SILVALLY_GRASS]                             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SILVALLY_ELECTRIC]                          = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SILVALLY_PSYCHIC]                           = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SILVALLY_ICE]                               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SILVALLY_DRAGON]                            = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SILVALLY_DARK]                              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SILVALLY_FAIRY]                             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MINIOR_METEOR_ORANGE]                       = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MINIOR_METEOR_YELLOW]                       = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MINIOR_METEOR_GREEN]                        = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MINIOR_METEOR_BLUE]                         = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MINIOR_METEOR_INDIGO]                       = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MINIOR_METEOR_VIOLET]                       = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MINIOR_CORE_RED]                            = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MINIOR_CORE_ORANGE]                         = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MINIOR_CORE_YELLOW]                         = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MINIOR_CORE_GREEN]                          = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MINIOR_CORE_BLUE]                           = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MINIOR_CORE_INDIGO]                         = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MINIOR_CORE_VIOLET]                         = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MIMIKYU_BUSTED]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_NECROZMA_DUSK_MANE]                         = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_NECROZMA_DAWN_WINGS]                        = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_NECROZMA_ULTRA]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MAGEARNA_ORIGINAL]                          = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_CRAMORANT_GULPING]                          = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_CRAMORANT_GORGING]                          = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_TOXTRICITY_LOW_KEY]                         = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SINISTEA_ANTIQUE]                           = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_POLTEAGEIST_ANTIQUE]                        = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_STRAWBERRY_RUBY_CREAM]             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_STRAWBERRY_MATCHA_CREAM]           = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_STRAWBERRY_MINT_CREAM]             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_STRAWBERRY_LEMON_CREAM]            = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_STRAWBERRY_SALTED_CREAM]           = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_STRAWBERRY_RUBY_SWIRL]             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_STRAWBERRY_CARAMEL_SWIRL]          = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_STRAWBERRY_RAINBOW_SWIRL]          = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_BERRY_VANILLA_CREAM]               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_BERRY_RUBY_CREAM]                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_BERRY_MATCHA_CREAM]                = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_BERRY_MINT_CREAM]                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_BERRY_LEMON_CREAM]                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_BERRY_SALTED_CREAM]                = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_BERRY_RUBY_SWIRL]                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_BERRY_CARAMEL_SWIRL]               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_BERRY_RAINBOW_SWIRL]               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_LOVE_VANILLA_CREAM]                = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_LOVE_RUBY_CREAM]                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_LOVE_MATCHA_CREAM]                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_LOVE_MINT_CREAM]                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_LOVE_LEMON_CREAM]                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_LOVE_SALTED_CREAM]                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_LOVE_RUBY_SWIRL]                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_LOVE_CARAMEL_SWIRL]                = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_LOVE_RAINBOW_SWIRL]                = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_STAR_VANILLA_CREAM]                = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_STAR_RUBY_CREAM]                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_STAR_MATCHA_CREAM]                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_STAR_MINT_CREAM]                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_STAR_LEMON_CREAM]                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_STAR_SALTED_CREAM]                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_STAR_RUBY_SWIRL]                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_STAR_CARAMEL_SWIRL]                = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_STAR_RAINBOW_SWIRL]                = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_CLOVER_VANILLA_CREAM]              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_CLOVER_RUBY_CREAM]                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_CLOVER_MATCHA_CREAM]               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_CLOVER_MINT_CREAM]                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_CLOVER_LEMON_CREAM]                = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_CLOVER_SALTED_CREAM]               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_CLOVER_RUBY_SWIRL]                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_CLOVER_CARAMEL_SWIRL]              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_CLOVER_RAINBOW_SWIRL]              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_FLOWER_VANILLA_CREAM]              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_FLOWER_RUBY_CREAM]                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_FLOWER_MATCHA_CREAM]               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_FLOWER_MINT_CREAM]                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_FLOWER_LEMON_CREAM]                = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_FLOWER_SALTED_CREAM]               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_FLOWER_RUBY_SWIRL]                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_FLOWER_CARAMEL_SWIRL]              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_FLOWER_RAINBOW_SWIRL]              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_RIBBON_VANILLA_CREAM]              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_RIBBON_RUBY_CREAM]                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_RIBBON_MATCHA_CREAM]               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_RIBBON_MINT_CREAM]                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_RIBBON_LEMON_CREAM]                = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_RIBBON_SALTED_CREAM]               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_RIBBON_RUBY_SWIRL]                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_RIBBON_CARAMEL_SWIRL]              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ALCREMIE_RIBBON_RAINBOW_SWIRL]              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_EISCUE_NOICE]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_INDEEDEE_F]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MORPEKO_HANGRY]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ZACIAN_CROWNED]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ZAMAZENTA_CROWNED]                          = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ETERNATUS_ETERNAMAX]                        = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_URSHIFU_RAPID_STRIKE]                       = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ZARUDE_DADA]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_CALYREX_ICE]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_CALYREX_SHADOW]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_BASCULIN_WHITE_STRIPED]                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_LUGIA_SHADOW]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MOTHIM_SANDY]                               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MOTHIM_TRASH]                               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SCATTERBUG_POLAR]                           = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SCATTERBUG_TUNDRA]                          = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SCATTERBUG_CONTINENTAL]                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SCATTERBUG_GARDEN]                          = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SCATTERBUG_ELEGANT]                         = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SCATTERBUG_MEADOW]                          = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SCATTERBUG_MODERN]                          = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SCATTERBUG_MARINE]                          = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SCATTERBUG_ARCHIPELAGO]                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SCATTERBUG_HIGH_PLAINS]                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SCATTERBUG_SANDSTORM]                       = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SCATTERBUG_RIVER]                           = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SCATTERBUG_MONSOON]                         = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SCATTERBUG_SAVANNA]                         = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SCATTERBUG_SUN]                             = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SCATTERBUG_OCEAN]                           = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SCATTERBUG_JUNGLE]                          = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SCATTERBUG_FANCY]                           = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SCATTERBUG_POKEBALL]                        = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_SPEWPA_POLAR]                               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SPEWPA_TUNDRA]                              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SPEWPA_CONTINENTAL]                         = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SPEWPA_GARDEN]                              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SPEWPA_ELEGANT]                             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SPEWPA_MEADOW]                              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SPEWPA_MODERN]                              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SPEWPA_MARINE]                              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SPEWPA_ARCHIPELAGO]                         = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SPEWPA_HIGH_PLAINS]                         = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SPEWPA_SANDSTORM]                           = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SPEWPA_RIVER]                               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SPEWPA_MONSOON]                             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SPEWPA_SAVANNA]                             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SPEWPA_SUN]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SPEWPA_OCEAN]                               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SPEWPA_JUNGLE]                              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SPEWPA_FANCY]                               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SPEWPA_POKEBALL]                            = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_POLTCHAGEIST_ARTISAN]                       = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SINISTCHA_MASTERPIECE]                      = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_OGERPON_WELLSPRING]                         = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_OGERPON_HEARTHFLAME]                        = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_OGERPON_CORNERSTONE]                        = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_OGERPON_TEAL_TERA]                          = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_OGERPON_WELLSPRING_TERA]                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_OGERPON_HEARTHFLAME_TERA]                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_OGERPON_CORNERSTONE_TERA]                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_URSALUNA_BLOODMOON]                         = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_TERAPAGOS_TERASTAL]                         = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_TERAPAGOS_STELLAR]                          = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    */

    // Generation 9
    [SPECIES_SPRIGATITO]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_FLORAGATO]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_MEOWSCARADA]                                = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_FUECOCO]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_CROCALOR]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SKELEDIRGE]                                 = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_QUAXLY]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_QUAXWELL]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_QUAQUAVAL]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_LECHONK]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_OINKOLOGNE_M]                               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_OINKOLOGNE_F]                               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_TAROUNTULA]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SPIDOPS]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_NYMBLE]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_LOKIX]                                      = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_PAWMI]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_PAWMO]                                      = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_PAWMOT]                                     = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_TANDEMAUS]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_MAUSHOLD_THREE]                             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MAUSHOLD_FOUR]                              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_FIDOUGH]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_DACHSBUN]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SMOLIV]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_DOLLIV]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_ARBOLIVA]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_SQUAWKABILLY_GREEN]                         = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SQUAWKABILLY_BLUE]                          = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SQUAWKABILLY_YELLOW]                        = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SQUAWKABILLY_WHITE]                         = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_NACLI]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_NACLSTACK]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_GARGANACL]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_CHARCADET]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_ARMAROUGE]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_CERULEDGE]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_TADBULB]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_BELLIBOLT]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_WATTREL]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_KILOWATTREL]                                = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MASCHIFF]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_MABOSSTIFF]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SHROODLE]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_GRAFAIAI]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_BRAMBLIN]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_BRAMBLEGHAST]                               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_TOEDSCOOL]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_TOEDSCRUEL]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_KLAWF]                                      = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_CAPSAKID]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SCOVILLAIN]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_RELLOR]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_RABSCA]                                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_FLITTLE]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_ESPATHRA]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_TINKATINK]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_TINKATUFF]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_TINKATON]                                   = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_WIGLETT]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_WUGTRIO]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_BOMBIRDIER]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_FINIZEN]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_PALAFIN_ZERO]                               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_PALAFIN_HERO]                               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_VAROOM]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_REVAVROOM]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_CYCLIZAR]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ORTHWORM]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_GLIMMET]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_GLIMMORA]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_GREAVARD]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_HOUNDSTONE]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_FLAMIGO]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_CETODDLE]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_CETITAN]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_VELUZA]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_DONDOZO]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_TATSUGIRI_CURLY]                            = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_TATSUGIRI_DROOPY]                           = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_TATSUGIRI_STRETCHY]                         = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ANNIHILAPE]                                 = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_CLODSIRE]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_FARIGIRAF]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_DUDUNSPARCE_TWO_SEGMENT]                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_DUDUNSPARCE_THREE_SEGMENT]                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_KINGAMBIT]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_GREAT_TUSK]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SCREAM_TAIL]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_BRUTE_BONNET]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_FLUTTER_MANE]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SLITHER_WING]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SANDY_SHOCKS]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_IRON_TREADS]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_IRON_BUNDLE]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_IRON_HANDS]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_IRON_JUGULIS]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_IRON_MOTH]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_IRON_THORNS]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_FRIGIBAX]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_3 },
    [SPECIES_ARCTIBAX]                                   = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_BAXCALIBUR]                                 = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_GIMMIGHOUL_CHEST]                           = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_GIMMIGHOUL_ROAMING]                         = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_GHOLDENGO]                                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_WO_CHIEN]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_CHIEN_PAO]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_TING_LU]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_CHI_YU]                                     = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_ROARING_MOON]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_IRON_VALIANT]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_KORAIDON]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MIRAIDON]                                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },

    // Scarlet and Violet 1.2.0
    [SPECIES_WALKING_WAKE]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_IRON_LEAVES]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },

    // Paldean Forms
    [SPECIES_TAUROS_PALDEA_COMBAT]                       = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_TAUROS_PALDEA_BLAZE]                        = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_TAUROS_PALDEA_AQUA]                         = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_WOOPER_PALDEA]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },


    // Teal Mask
    [SPECIES_DIPPLIN]                                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 }, // ??
    [SPECIES_POLTCHAGEIST_COUNTERFEIT]                   = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_SINISTCHA_UNREMARKABLE]                     = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_OKIDOGI]                                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MUNKIDORI]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_FEZANDIPITI]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_OGERPON_TEAL]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },

    // Indigo Disk
    [SPECIES_ARCHALUDON]                                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_HYDRAPPLE]                                  = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_GOUGING_FIRE]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_RAGING_BOLT]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_IRON_BOULDER]                               = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_IRON_CROWN]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_TERAPAGOS_NORMAL]                           = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_PECHARUNT]                                  = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },

    // Totem
    /*
    [SPECIES_RATICATE_ALOLA_TOTEM]                       = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_GUMSHOOS_TOTEM]                             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_VIKAVOLT_TOTEM]                             = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_LURANTIS_TOTEM]                             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_SALAZZLE_TOTEM]                             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MIMIKYU_TOTEM_DISGUISED]                    = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_MIMIKYU_TOTEM_BUSTED]                       = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_KOMMO_O_TOTEM]                              = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_MAROWAK_ALOLA_TOTEM]                        = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_RIBOMBEE_TOTEM]                             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_ARAQUANID_TOTEM]                            = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_TOGEDEMARU_TOTEM]                           = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    */

    // Starter
    /*
    [SPECIES_PIKACHU_STARTER]                            = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_EEVEE_STARTER]                              = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    */

    // Gigantamax
    /*
    [SPECIES_VENUSAUR_GMAX]                              = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_BLASTOISE_GMAX]                             = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_CHARIZARD_GMAX]                             = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_BUTTERFREE_GMAX]                            = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_PIKACHU_GMAX]                               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_MEOWTH_GMAX]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_2 },
    [SPECIES_MACHAMP_GMAX]                               = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_GENGAR_GMAX]                                = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_KINGLER_GMAX]                               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_LAPRAS_GMAX]                                = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_EEVEE_GMAX]                                 = { EVO_SPECIES_STAGE_1, EVO_FAMILY_STAGE_1 },
    [SPECIES_SNORLAX_GMAX]                               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_GARBODOR_GMAX]                              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_MELMETAL_GMAX]                              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_RILLABOOM_GMAX]                             = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_CINDERACE_GMAX]                             = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_INTELEON_GMAX]                              = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_CORVIKNIGHT_GMAX]                           = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_ORBEETLE_GMAX]                              = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_DREDNAW_GMAX]                               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_COALOSSAL_GMAX]                             = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_FLAPPLE_GMAX]                               = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_APPLETUN_GMAX]                              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_3 },
    [SPECIES_SANDACONDA_GMAX]                            = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_TOXTRICITY_AMPED_GMAX]                      = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_TOXTRICITY_LOW_KEY_GMAX]                    = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_CENTISKORCH_GMAX]                           = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_HATTERENE_GMAX]                             = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_GRIMMSNARL_GMAX]                            = { EVO_SPECIES_STAGE_3, EVO_FAMILY_STAGE_3 },
    [SPECIES_ALCREMIE_GMAX]                              = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_COPPERAJAH_GMAX]                            = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_DURALUDON_GMAX]                             = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_URSHIFU_SINGLE_STRIKE_GMAX]                 = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    [SPECIES_URSHIFU_RAPID_STRIKE_GMAX]                  = { EVO_SPECIES_STAGE_2, EVO_FAMILY_STAGE_2 },
    */

    [SPECIES_EGG]                                        = { EVO_SPECIES_STAGE_0, EVO_FAMILY_STAGE_0 }
};



static const MapAreaEntry sMapAreaRandomPokemonAttributes[] __attribute__((used)) = {
    {MAP_GROUP(ROUTE101), MAP_NUM(ROUTE101), OBJECTID_UNDEFINED, {
        .Active = TRUE,
        .BST_Min = BST_MIN_LEVEL_8,
        .BST_Max = BST_MAX_LEVEL_9,
        .Type_1 = { TYPE_END },
        .Type_2 = { TYPE_END },
        .Allow = { ALLOW_PSEUDO, ALLOW_END },
        .Exclusion = { SPECIES_SHEDINJA, EXCLUSION_END },
        .Evolution_Species_Stage = EVO_UNDEFINED,
        .Evolution_Family_Stage = EVO_UNDEFINED,
    }},
    {MAP_GROUP(ROUTE102), MAP_NUM(ROUTE102), OBJECTID_UNDEFINED, {
        .Active = TRUE,
        .BST_Min = BST_MIN_LEVEL_3,
        .BST_Max = BST_MAX_LEVEL_3,
        .Type_1 = { TYPE_END },
        .Type_2 = { TYPE_END },
        .Allow = { ALLOW_END },
        .Exclusion = { SPECIES_SHEDINJA, EXCLUSION_END },
        .Evolution_Species_Stage = EVO_UNDEFINED,
        .Evolution_Family_Stage = EVO_UNDEFINED,
    }},
    {MAP_GROUP(ROUTE103), MAP_NUM(ROUTE103), OBJECTID_UNDEFINED, {
        .Active = TRUE,
        .BST_Min = BST_MIN_LEVEL_4,
        .BST_Max = BST_MAX_LEVEL_4,
        .Type_1 = { TYPE_END },
        .Type_2 = { TYPE_END },
        .Exclusion = { SPECIES_SHEDINJA, EXCLUSION_END },
        .Allow = { ALLOW_END },
        .Evolution_Species_Stage = EVO_UNDEFINED,
        .Evolution_Family_Stage = EVO_UNDEFINED,
    }},

    /* // Example Usage
    {MAP_GROUP(ROUTE101), MAP_NUM(ROUTE101), OBJECTID_UNDEFINED, {
        .Active = TRUE,
        .BST_Min = BST_MIN_LEVEL_4,
        .BST_Max = BST_MAX_LEVEL_4,
        .Type_1 = { TYPE_END },
        .Type_2 = { TYPE_END },
        .Exclusion = { SPECIES_SHEDINJA, EXCLUSION_END },
        .Allow = { ALLOW_END, },
        .Evolution_Species_Stage = EVO_UNDEFINED,
        .Evolution_Family_Stage = EVO_UNDEFINED,
    }},
    */

};


const MapAreaAttributes* getMapAreaAttributes(s8 mapNum, s8 mapGroup, u8 objectId) {

    u16 i;
    for (i = 0; i < sizeof(sMapAreaRandomPokemonAttributes) / sizeof(MapAreaEntry); i++) {
        if (
            sMapAreaRandomPokemonAttributes[i].mapGroup == mapGroup
            && sMapAreaRandomPokemonAttributes[i].mapNum == mapNum
            && (sMapAreaRandomPokemonAttributes[i].objectId == OBJECTID_UNDEFINED || sMapAreaRandomPokemonAttributes[i].objectId == objectId)
        ) {
            return &sMapAreaRandomPokemonAttributes[i].attributes;
        }
    }
    
    return 0;
}



// ran on new game
void AlcyonInit(void)
{
    FlagSet(FLAG_RECEIVED_RUNNING_SHOES);
    FlagSet(FLAG_SYS_B_DASH);
    FlagSet(FLAG_NO_BAG_USE);
    FlagSet(FLAG_NO_CATCHING);
    //FlagSet(FLAG_SYS_POKEDEX_GET);
    EnableNationalPokedex();
    AlcyonStart();
}

// ran on game startup
void AlcyonStart(void)
{
    SetPartyToLevelCap();
    SetBoxToLevelCap();
    DisableWildEncounters(TRUE);
}


u8 getTypeCount(const u8 *types) {
    u8 count = 0;
    for (u8 i = 0; i < NUMBER_OF_MON_TYPES+1; i++) {
        if (types[i] == TYPE_END)
            break;
        count++;
    }
    return count;
}


bool8 IsSpeciesExcluded(u16 species, const u16 *exclusion)
{
    for (u16 i = 0; i < MAX_EXCLUSION_LIST_SIZE+1; i++)
    {
        if (exclusion[i] == EXCLUSION_END)
            break;

        if (species == exclusion[i])
            return TRUE;
    }
    return FALSE;
}

bool8 IsSpeciesAllowed(u8 condition, const u8 *allow)
{
    for (u16 i = 0; i < MAX_EXCLUSION_LIST_SIZE+1; i++)
    {
        if (allow[i] == ALLOW_END)
            break;

        if (condition == allow[i])
            return TRUE;
    }
    return FALSE;
}





/*void RandomPokemonGift_SetSprites(void)
{
    u16 t, i;
    for (t = 0; t < sizeof(sMapAreaRandomPokemonAttributes) / sizeof(MapAreaEntry); t++)
    {
        s8 mapNum = sMapAreaRandomPokemonAttributes[t].mapNum;
        s8 mapGroup = sMapAreaRandomPokemonAttributes[t].mapGroup;
        u8 objectId = sMapAreaRandomPokemonAttributes[t].objectId;

        if (mapNum != gSaveBlock1Ptr->location.mapNum || mapGroup != gSaveBlock1Ptr->location.mapGroup)
            continue;
    
        struct ObjectEventTemplate *savObjTemplates = gSaveBlock1Ptr->objectEventTemplates;
        for (i = 0; i < OBJECT_EVENT_TEMPLATES_COUNT; i++)
        {
            struct ObjectEventTemplate *objectEventTemplate = &savObjTemplates[i];

            if (objectId != OBJECTID_UNDEFINED && objectId != objectEventTemplate->localId)
                continue;

            if (objectEventTemplate->graphicsId == OBJ_EVENT_GFX_VAR_0)
            {
                const u32 species = getRandomPokemonByArea(mapNum, mapGroup, objectEventTemplate->localId);
                const u16 graphicsId = GetGraphicsIdForMon(species, 0, 0);
                objectEventTemplate->graphicsId = graphicsId != SPECIES_NONE ? graphicsId : OBJ_EVENT_GFX_MOVING_BOX;
            }
        }
    }
}*/


void RandomPokemonGift_SetVar(void)
{
    VarSet(VAR_RESULT, 1);

    u8 objectId = VarGet(VAR_LAST_TALKED);
    if (!objectId)
    {
        VarSet(VAR_RESULT, 0);
        return;
    }

    u16 species_var = getRandomPokemonByArea(gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup, objectId);
    if (!species_var)
    {
        VarSet(VAR_RESULT, 0);
        return;
    }
    VarSet(VAR_0x8005, species_var);


    u16 object_flag = GetObjectEventFlagIdByLocalIdAndMap(objectId,gSaveBlock1Ptr->location.mapNum,gSaveBlock1Ptr->location.mapGroup);
    VarSet(VAR_0x8006, object_flag);
}

void RandomPokemonGift_RemoveObjects(void)
{
    s8 mapNum = gSaveBlock1Ptr->location.mapNum;
    s8 mapGroup = gSaveBlock1Ptr->location.mapGroup;
    u8 objectId = VarGet(VAR_LAST_TALKED);
    u16 flagId = GetObjectEventFlagIdByLocalIdAndMap(objectId,mapNum,mapGroup);

    
    const struct ObjectEventTemplate *templates = gSaveBlock1Ptr->objectEventTemplates;
    u8 count = gMapHeader.events->objectEventCount;

    for (u8 i = 0; i < count; i++)
    {
        if (templates[i].flagId == flagId)
            RemoveObjectEventByLocalIdAndMap(templates[i].localId, mapNum, mapGroup);
    }
}



u16 getRandomPokemonByArea(s8 mapNum, s8 mapGroup, u8 objectId)
{
    u16 random_list_count = 0;
    struct RandomList random_list[MAX_RANDOM_LIST_SIZE];

    const MapAreaAttributes *attributes = getMapAreaAttributes(mapNum, mapGroup, objectId);

    if (!attributes || !attributes->Active)
    {
        return SPECIES_NONE;
    }

    u16 bst_min = attributes->BST_Min;
    u16 bst_max = attributes->BST_Max;
    const u8 *type_1 = attributes->Type_1;
    const u8 *type_2 = attributes->Type_2;
    u8 type_1_count = getTypeCount(type_1);
    u8 type_2_count = getTypeCount(type_2);
    const u16 *exclusion = attributes->Exclusion;
    u8 evo_species_stage = attributes->Evolution_Species_Stage;
    u8 evo_family_stage = attributes->Evolution_Family_Stage;
    const u8 *allow = attributes->Allow;

    

    for (u16 i = 0; i < NUM_SPECIES; i++)
    {
        if (
            !IsSpeciesEnabled(i) ||
            IsSpeciesExcluded(i, exclusion) ||
            gSpeciesInfo[i].natDexNum == NATIONAL_DEX_NONE ||
            GetSetPokedexFlag(gSpeciesInfo[i].natDexNum, FLAG_GET_CAUGHT)
        )
        {
            continue;
        }

        u16 mon_bst = gSpeciesInfo[i].baseHP
        + gSpeciesInfo[i].baseAttack
        + gSpeciesInfo[i].baseDefense
        + gSpeciesInfo[i].baseSpeed
        + gSpeciesInfo[i].baseSpAttack
        + gSpeciesInfo[i].baseSpDefense;

        const bool8 isPseudoLegendary = mon_bst == 600 && sSpeciesEvolutionStage[i].evo_family_stage == EVO_FAMILY_STAGE_3 && sSpeciesEvolutionStage[i].evo_species_stage == EVO_SPECIES_STAGE_3 && gSpeciesInfo[i].growthRate == GROWTH_SLOW;

        if (
            !IsSpeciesAllowed(ALLOW_ALL, allow) &&
            ((gSpeciesInfo[i].isLegendary
                && !IsSpeciesAllowed(ALLOW_LEGENDARY, allow)) ||
            (gSpeciesInfo[i].isMythical
                && !IsSpeciesAllowed(ALLOW_MYTHICAL, allow)) ||
            (isPseudoLegendary
                && !IsSpeciesAllowed(ALLOW_PSEUDO, allow)) ||
            (gSpeciesInfo[i].isFrontierBanned
                && !IsSpeciesAllowed(ALLOW_BANNED, allow)) ||
            (gSpeciesInfo[i].isMegaEvolution
                && !IsSpeciesAllowed(ALLOW_MEGA, allow)) ||
            (gSpeciesInfo[i].isPrimalReversion
                && !IsSpeciesAllowed(ALLOW_PRIMAL, allow)) ||
            (gSpeciesInfo[i].isUltraBeast
                && !IsSpeciesAllowed(ALLOW_ULTRABEAST, allow)) ||
            (gSpeciesInfo[i].isTotem
                && !IsSpeciesAllowed(ALLOW_TOTEM, allow)) ||
            (gSpeciesInfo[i].isGigantamax
                && !IsSpeciesAllowed(ALLOW_GIGANTAMAX, allow)) ||
            (gSpeciesInfo[i].isParadox
                && !IsSpeciesAllowed(ALLOW_PARADOX, allow)) ||
            (gSpeciesInfo[i].isTeraForm
                && !IsSpeciesAllowed(ALLOW_TERA, allow)) ||
            ((gSpeciesInfo[i].isAlolanForm || gSpeciesInfo[i].isGalarianForm || gSpeciesInfo[i].isHisuianForm || gSpeciesInfo[i].isPaldeanForm)
                && !IsSpeciesAllowed(ALLOW_REGIONAL, allow)))
        )
        {
            continue;
        }


        u8 mon_type_1 = gSpeciesInfo[i].types[0];
        u8 mon_type_2 = gSpeciesInfo[i].types[1];

        bool8 bst_min_valid = (bst_min == BST_UNDEFINED || mon_bst >= bst_min);
        bool8 bst_max_valid = (bst_max == BST_UNDEFINED || mon_bst <= bst_max);

        bool8 type_1_valid = (type_1_count == 0);
        for (u8 j = 0; j < type_1_count; j++)
        {
            if (mon_type_1 == type_1[j])
            {
                type_1_valid = TRUE;
                break;
            }
        }

        bool8 type_2_valid = (type_2_count == 0);
        for (u8 j = 0; j < type_2_count; j++)
        {
            if (mon_type_2 == type_2[j])
            {
                type_2_valid = TRUE;
                break;
            }
        }

        bool8 evo_species_valid = evo_species_stage == EVO_UNDEFINED ? TRUE : sSpeciesEvolutionStage[i].evo_species_stage == evo_species_stage ? TRUE : FALSE;
        bool8 evo_family_valid = evo_family_stage == EVO_UNDEFINED ? TRUE : sSpeciesEvolutionStage[i].evo_family_stage == evo_family_stage ? TRUE : FALSE;

        if (bst_min_valid && bst_max_valid && type_1_valid && type_2_valid && random_list_count <= MAX_RANDOM_LIST_SIZE && evo_species_valid && evo_family_valid)
        {
            random_list[random_list_count].id = i;
            random_list[random_list_count].bst = mon_bst;
            random_list[random_list_count].type_1 = mon_type_1;
            random_list[random_list_count].type_2 = mon_type_2;
            random_list_count++;
        }
    }

    if (random_list_count == 0)
    {
        return SPECIES_NONE;
    }

    u32 trainerId = GetTrainerId(gSaveBlock2Ptr->playerTrainerId);
    u32 seed = ISO_RANDOMIZE1(trainerId+(mapGroup*trainerId)+(mapNum*trainerId)+(objectId*trainerId));
    u32 index = seed % random_list_count;

    //struct RandomList result = random_list[Random() % random_list_count];
    struct RandomList result = random_list[index];

    if (!result.id)
    {
        return SPECIES_NONE;
    }

    return result.id;
}

