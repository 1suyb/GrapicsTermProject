#pragma once
#ifndef __BOX_INCLUDED__
#define __BOX_INCLUDED__
#include "Model.h"

#define NUM_PARTICLES    10000          /* Number of particles  */
#define NUM_DEBRIS       1000           /* Number of debris     */


class Box : public  Model {
public:
	bool is_spawned;

	Box() {
		is_spawned = false;
	}

	struct particleData {
		float   position[3];
		float   speed[3];
		float   color[3];
	};
	typedef struct particleData    particleData;

	struct debrisData {
		float   position[3];
		float   speed[3];
		float   orientation[3];        /* Rotation angles around x, y, and z axes */
		float   orientationSpeed[3];
		float   color[3];
		float   scale[3];
	};
	typedef struct debrisData    debrisData;

	particleData	particles[NUM_PARTICLES];
	debrisData		debris[NUM_DEBRIS];
	int             fuel = 0;                /* "fuel" of the explosion */
	int				wantNormalize = 0;   /* Speed vector normalization flag */

	void DrawCube(float size);
	void newSpeed(float dest[3]);
	void newExplosion(void); //폭발시 파티클 및 파편 생성
	void ParticleUpdate(void); //파티클 및 파편 업데이트
	void InitGL();
	void ShowParticles();
};

#endif // !__BOX_INCLUDED__

