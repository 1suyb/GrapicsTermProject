/*#include "Includes.h"
#include "Scene.h"
#include <glaux.h>


GLuint tex[7];   // Texture Mapping을 하기 위한 Texture 이미지의 개수를 위한 배열 변수

AUX_RGBImageRec* LoadBMP(char* Filename) {  // Bitmap 이미지를 호출한다.
    FILE* File = NULL;

    if (!Filename) return NULL;
    File = fopen(Filename, "r");
    if (File) {
        fclose(File);
        return auxDIBImageLoad(Filename);
    }

    return NULL;
}

void LoadGLTextures() {  // Bitmap 이미지 7개를 호출하여 Texture 이미지로 변환한다.
    AUX_RGBImageRec* texRec[7];
    memset(texRec, 0, sizeof(void*) * 7);

    if ((texRec[0] = LoadBMP("Data/skybox1_posz.bmp")) &&
        (texRec[1] = LoadBMP("Data/skybox1_negz.bmp")) &&
        (texRec[2] = LoadBMP("Data/skybox1_posx.bmp")) &&
        (texRec[3] = LoadBMP("Data/skybox1_negx.bmp")) &&
        (texRec[4] = LoadBMP("Data/skybox1_posy.bmp")) &&
        (texRec[5] = LoadBMP("Data/skybox1_negy.bmp")) &&
        (texRec[6] = LoadBMP("Data/Lawn2.bmp"))) {

        for (int i = 0; i < 7; i++) {
            glGenTextures(1, &tex[i]);
            glBindTexture(GL_TEXTURE_2D, tex[i]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, 3, texRec[i]->sizeX, texRec[i]->sizeY, 0,
                GL_RGB, GL_UNSIGNED_BYTE, texRec[i]->data);
        }
    }

    for (int i = 0; i < 7; i++) {
        if (texRec[i]) {
            if (texRec[i]->data) free(texRec[i]->data);
            free(texRec[i]);
        }
    }

    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}*/