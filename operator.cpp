#include "operator.h"

Operator :: Operator(){type=-1; for(int i=0; i<4; i++){ver[i]=-1;}}

void Operator :: resetvertex(){for(int i=0; i<4; i++){ver[i]=-1;}}
