#ifndef TEXTURELIST_H
#define TEXTURELIST_H

typedef enum TextureType{
	TX_PLAYER_MAINBODY,
	TX_PLAYER_UPPERBODY,
	TX_BULLET,
	TX_ENEMY_BULLET,
	TX_BOSS,
	TX_BOSS_EYE,
	TX_BOSS_BAR,
	TX_CIRCLE,
	TX_PS_TEST,
	TX_TILE_ONEWAY,
	TX_TILE_SOLID
}TextureType;

void TextureList_Init(void);
void TextureList_LoadTexture(char* filename, TextureType type);
int TextureList_GetID(TextureType type);
void TextureList_UnloadAndFree(void);

#endif//TEXTURELIST_H