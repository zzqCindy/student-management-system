#include "admin.h"

Admin::Admin()
{
}

Admin::Admin(char u[10],char pw[20]){
    setId(u);
    setPassword(pw);
}
