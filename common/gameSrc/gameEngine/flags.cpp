#include <stdio.h>

typedef enum {
	FLAG_PHYSICAL = 1 << 0, // 00000001
	FLAG_CONTROL = 1 << 1,  // 00000010
	FLAG_RENDER = 1 << 2,   // 00000100
	FLAG_VELOCITY = 1 << 3, // 00001000
} components_flags_e;

typedef enum {
	FLAG_PHYSICS = 42       // 00001001
} systems_flags_e;


// Entity ent                       (signature = 000000000)
// ent.addComponent(Physical)       (signature = 000000001)
// ent.addComponent(Render)         (signature = 000000101)
// ent.addComponent(Velocity)       (signature = 000001101)

// systemPhysics (flag = 00001001)
//


bool hasFlag(unsigned int signature, unsigned int flag)
{
	return ((signature & flag) != 0);
}

int main()
{
	unsigned int signature = 0;

	signature = FLAG_PHYSICAL | FLAG_CONTROL; // 00000011
	printf("%u\n", hasFlag(signature, FLAG_RENDER));
	return 0;
}