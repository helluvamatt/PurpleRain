#include "PurpleRain.h"

void CreatePurpleRain(PPurpleRain obj, int count, int screenWidth, int screenHeight, int color)
{
	if (obj == NULL) return;
	obj->Count = count;
	obj->Drops = (PDrop*)malloc(count * sizeof(PDrop));
	obj->ScreenHeight = screenHeight;
	obj->ScreenWidth = screenWidth;

	for (int i = 0; i < count; i++)
	{
		obj->Drops[i] = (PDrop)malloc(sizeof(Drop));
		CreateDrop(obj->Drops[i], screenWidth, color);
	}
}

void DestroyPurpleRain(PPurpleRain obj)
{
	if (obj == NULL) return;
	for (int i = 0; i < obj->Count; i++)
	{
		free(obj->Drops[i]);
	}
	free(obj->Drops);
}

void AnimatePurpleRain(PPurpleRain obj)
{
	if (obj == NULL) return;
	if (obj->Drops == NULL) return;
	for (int i = 0; i < obj->Count; i++)
	{
		PDrop cur = obj->Drops[i];
		if (cur != NULL)
			DropFall(cur, obj->ScreenHeight);
	}
}

PDrop GetDrop(PPurpleRain obj, int index)
{
	if (obj == NULL) return NULL;
	if (obj->Drops == NULL) return NULL;
	return obj->Drops[index];
}