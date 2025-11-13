#include <stdio.h>
void convertDigitsInPlace(char *arr, int length) {
    for(int i = 0; i < length; i++) {
        if (arr[i] >= '0' && arr[i] <= '9') { 
            arr[i] = arr[i] - '0'; //gibt es dann in richtig zahl from weil '0' 48 hat und '1' 49 und dann 49 - 48 = 1
        }
    }
}
const char unsigned monthCodeVal[256] = {
    [1] = 0, [2] = 3, [3] = 3, [4] = 6, [5] = 1, [6] = 4,
    [7] = 6, [8] = 2, [9] = 5, [10] = 0, [11] = 3, [12] = 0,
    //Gap Year
    [13] = 6,
    [14] = 2,
};
void weekDayName(int day){
    switch (day)
    {
        case 0:printf("Sonntag");break;
        case 1:printf("Montag");break;
        case 2:printf("Dienstag");break;
        case 3:printf("Mittwoch");break;
        case 4:printf("Donnerstag");break;
        case 5:printf("Freitag");break;
        case 6:printf("Samstag");break;   
        default:break;
    }
}
int isGap(int wholeYear){
    if(wholeYear%4 == 0){
        return 0;
    }
    return 1;
}
int validDate(char *date){
    if(date[2] != '-' || date[5] != '-'){
        return 1;
    }
    return 0;
}
int getDay(char *date){
    int day;
    day = date[0] *10 + date[1];

    return day;
}
int getMonth(char *date){
   int month;
   month = date[3] * 10 + date[4];
   
   return month;
}
int getYear(char *date){
    int year;
    year = date[8] * 10 + date[9];
    
    return year;
}
int getDecade(char *date){
    int decade;
    decade = date[6] * 10 + date[7];

    return decade;
}
int getWholeYear(char *date){
    int wholeYear;
    wholeYear = date[6] * 1000 + date[7] * 100 + date[8] * 10 + date[9];
    
    return wholeYear;
}
int yearCode(int twoDigYear){
    return (twoDigYear + twoDigYear/4) % 7;
}
int monthCode(int month, int isGap){
    int monthCodeReturn;
    if(isGap == 0){
        switch (month)
        {
        case 1:
            month = 13;
            break;
        case 2:
            month = 14;
        default:
            break;
        }
    }
    monthCodeReturn = monthCodeVal[month];
    return monthCodeReturn;
}
int decadeCode(int decade){
    int decadeCodeReturn;
    decadeCodeReturn = (6 - 2 * (decade % 4)) % 7;

    return decadeCodeReturn;
}


int calcWeekDay(char *date){
    if(validDate(date) ==1){
        return -1;
    }
    int day         = getDay(date);
    int month       = getMonth(date);
    int year        = getYear(date);
    int decade      = getDecade(date);
    int wholeYear   = getWholeYear(date);
    int gap         = isGap(wholeYear);
    int yearC       = yearCode(year);
    int monthC      = monthCode(month, gap);
    int decadeC     = decadeCode(decade);
    int weekDay     = (day + monthC + yearC + decadeC) % 7;
    weekDay         = (weekDay + 7) % 7; //falls negativ
    printf("day=%d month=%d year=%d decade=%d wholeYear=%d gap=%d yearC=%d monthC=%d decadeC=%d\n",day, month, year, decade, wholeYear, gap, yearC, monthC, decadeC);


    return weekDay;
}
int main()
{
    char date[11];
    printf("Geben Sie ein Datum im Format DD-MM-YYYY ein: ");
    scanf("%10s", date);
    convertDigitsInPlace(date, 10);
    int weekDay = calcWeekDay(date);
    if(weekDay == -1){
        printf("Falsches Format\n");
        return 0;
    }
    printf("%d\n", weekDay);
    weekDayName(weekDay);
    return 0;
}
