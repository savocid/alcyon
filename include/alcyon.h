#ifndef GUARD_ALCYON_H
#define GUARD_ALCYON_H

#define MAX_RANDOM_LIST_SIZE 100
#define MAX_EXCLUSION_LIST_SIZE 100

#define OBJECTID_UNDEFINED 0xFF

#define BST_UNDEFINED 0xFFF
#define EVO_UNDEFINED 0xFF

#define TYPE_END 0xFF
#define EXCLUSION_END 0xFF
#define ALLOW_END 0xFF

#define ALLOW_ALL 0
#define ALLOW_LEGENDARY 1
#define ALLOW_MYTHICAL 2
#define ALLOW_PSEUDO 3
#define ALLOW_BANNED 4
#define ALLOW_MEGA 5
#define ALLOW_PRIMAL 6
#define ALLOW_ULTRABEAST 7
#define ALLOW_TOTEM 8
#define ALLOW_PARADOX 9
#define ALLOW_GIGANTAMAX 10
#define ALLOW_TERA 11
#define ALLOW_REGIONAL 12
#define ALLOW_COUNT 13

#define EVO_SPECIES_STAGE_0 0
#define EVO_SPECIES_STAGE_1 1
#define EVO_SPECIES_STAGE_2 2
#define EVO_SPECIES_STAGE_3 3

#define EVO_FAMILY_STAGE_0 0
#define EVO_FAMILY_STAGE_1 1
#define EVO_FAMILY_STAGE_2 2
#define EVO_FAMILY_STAGE_3 3

#define BST_MIN_LEVEL_1 0
#define BST_MAX_LEVEL_1 299

#define BST_MIN_LEVEL_2 300
#define BST_MAX_LEVEL_2 359

#define BST_MIN_LEVEL_3 360
#define BST_MAX_LEVEL_3 419

#define BST_MIN_LEVEL_4 420
#define BST_MAX_LEVEL_4 459

#define BST_MIN_LEVEL_5 460
#define BST_MAX_LEVEL_5 499

#define BST_MIN_LEVEL_6 500
#define BST_MAX_LEVEL_6 529

#define BST_MIN_LEVEL_7 530
#define BST_MAX_LEVEL_7 559

#define BST_MIN_LEVEL_8 560
#define BST_MAX_LEVEL_8 599

#define BST_MIN_LEVEL_9 600
#define BST_MAX_LEVEL_9 BST_UNDEFINED

typedef struct {
    bool8 Active;
    u16 BST_Min;
    u16 BST_Max;
    u8 Type_1[NUMBER_OF_MON_TYPES+1];
    u8 Type_2[NUMBER_OF_MON_TYPES+1];
    u16 Exclusion[MAX_EXCLUSION_LIST_SIZE];
    u8 Evolution_Species_Stage;
    u8 Evolution_Family_Stage;
    u8 Allow[ALLOW_COUNT+1];
    u16 Object_Flag;
} MapAreaAttributes;

typedef struct {
    s8 mapGroup;
    s8 mapNum;
    u8 objectId;
    MapAreaAttributes attributes;
} MapAreaEntry;


struct SpeciesEvoData {
    u8 evo_species_stage;
    u8 evo_family_stage;
};

struct RandomList
{
    u16 id;
    u16 bst;
    u8 type_1;
    u8 type_2;
};

void AlcyonInit(void);
void AlcyonStart(void);
void RandomPokemonGift_SetVar(void);
void RandomPokemonGift_RemoveObjects(void);
//void RandomPokemonGift_SetSprites();
u16 getRandomPokemonByArea(s8 mapNum, s8 mapGroup, u8 objectId);

#endif // GUARD_ALCYON_H