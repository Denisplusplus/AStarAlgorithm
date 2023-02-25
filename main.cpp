#include "search.h"


int main(void) {
   
    THandler handler;
    

    if (handler.readMap())
    	handler.findPath();

    return 0;
}