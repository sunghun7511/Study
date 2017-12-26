# include "DSMBAMBOO.h"

int main(int argc, char * argv[]){
    DSMBAMBOO *bamboo;
    bamboo = (DSMBAMBOO *)malloc(sizeof(DSMBAMBOO));
    
    bamboo->제보하기 = "http://dsmbamboo.lapio.kr/";
    bamboo->페이스북 = "https://www.facebook.com/DSMBAMBOO/";

    bamboo->관리자지원 = "Messenger";
    
    bamboo->message = "많은 이용 부탁드립니다.";
    
    free(bamboo);

    return 0;
}