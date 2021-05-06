#include "TextureList.h"
#include "WarpEngine.h"
#include <stdlib.h>

typedef struct TextureNode{
	TextureType type;
	int id;
	struct TextureNode* pNext;
}TextureNode;

typedef struct TextureList
{
	TextureNode* pHead;
}TextureList;

static TextureList textureList;

void TextureList_Init(void)
{
	textureList.pHead = 0;
}
void TextureList_LoadTexture(char* filename, TextureType type)
{
	TextureNode* pNode = (TextureNode*)malloc(sizeof(TextureNode));
	pNode->id = WEGraphicsLoadTexture(filename);
	pNode->type = type;
	pNode->pNext = textureList.pHead;
	textureList.pHead = pNode;
}
int TextureList_GetID(TextureType type)
{
	TextureNode* pHead = textureList.pHead;

	while (pHead)
	{
		if (pHead->type == type)
			return pHead->id;
		pHead = pHead->pNext;
	}

	return 0;
}
void TextureList_UnloadAndFree(void)
{
	TextureNode* pDelete;

	while (textureList.pHead)
	{
		pDelete = textureList.pHead;
		textureList.pHead = textureList.pHead->pNext;
		WEGraphicsUnloadTexture(pDelete->id);
		free(pDelete);
	}

	textureList.pHead = 0;
}