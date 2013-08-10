#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static convertToInt(char charToConvert);
static int calcScore(char *scoresheet);
static int calcScoreHelper( int currtotal, char *scoresheet, int frame, int allpinsflag);

int main( int argc, char **args )
{
    int totalScore = -1;
    char *scoresheet = NULL;

    if(argc < 2)
    {
        printf("ERROR: Need the scores!\n");
        exit(-1);
    }

    scoresheet = args[1];
    totalScore = calcScore(scoresheet);
    printf("Score: %d\n", totalScore);

    return;
}

static int calcScore(char *scoresheet)
{
    return calcScoreHelper(0, scoresheet, 1, 0);
}

static int calcScoreHelper( int currtotal, char *scoresheet, int frame, int allpinsflag)
{
    int first, second, allpinstmp;
    char firstchar = *scoresheet;
    *scoresheet++;
    char secondchar = *scoresheet;

    /* Base case */
    if( (firstchar == 0) || (frame > 10) )
    {
        return currtotal;
    }
    else
    {
        first = convertToInt(firstchar);
        second = convertToInt(secondchar);

        /* Check for a spare or strike on this turn */
        if( (first < 10) && (second == 10) ) // Spare
        {
            second = 10 - first;
            allpinstmp = 1;
        }
        else if( first == 10 )  // Strike
        {
            allpinstmp = 2;
        }

        /* Now check for spare/strike on last turn
         *
         * The hardcoded 10 represents the collective score from last turn (we
         * don't care what the actual numbers were).
         */
        switch( allpinsflag )
        {
            case 1:  // Spare last turn
                currtotal += 10 + (first*2) + second;
                break;
            case 2:  // Strike last turn
                currtotal += 10 + (first*2) + (second*2);
                break;
            default:  // Normal roll
                currtotal += first + second;
                break;
        }
        frame++;
        *scoresheet++;
        allpinsflag = allpinstmp;  // previous gets replaced by current

        return calcScoreHelper(currtotal, scoresheet, frame, allpinsflag);
    }

    // all else fails
    return -1;
}

static int convertToInt(char charToConvert)
{
    int tmp = -1;
    if( (charToConvert == 'X') || (charToConvert == '/') )
        tmp = 10;
    else if(charToConvert == '-')
        tmp = 0;
    else
        tmp = charToConvert - '0';
    return tmp;
}

