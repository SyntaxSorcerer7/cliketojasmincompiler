/* main.c */

#include "global.hpp"
#include <iostream>

int main(void)
{
    try{
        init();
        parse();
        exit(0);    /*  successful termination  */
    }  catch (const std::exception& ex) {
        std::cout << "***  Exception caught: " << ex.what() << std::endl;
        
    } catch (const std::string& ex) {
        std::cout << "***  Exception caught: " << ex << std::endl;
    // ...
    } catch (...) {
        std::cout << "*** Unkown Exception caught: " << std::endl;

    // ...
    }

}
