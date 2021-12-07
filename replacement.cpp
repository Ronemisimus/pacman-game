#include "iofunctions.h"

// bad exit codes
#define NOT_STARTED_FROM_TERMINAL 1
#define BAD_STDIN_READ 2

// This function moves the cursor to the line y and column x.
// (0,0) is the upper left corner of the screen.
// This function is adjusted for non canonial output mode
void gotoxy( short x, short y ) 
{
    char result[40];
	sprintf(result,"\x1b[%d;%df", y + 1, x + 1);
    write(STDOUT_FILENO, result, strlen(result));
}

/**************************
 * this function sets the terminal
 * to process input charater by character
 * instead of line by line
 * saved - path to save the current terminal options
 *************************/
void setTerminalInputMode(struct termios *saved)
{
    struct termios attr;

    // make sure the input is a tty meaning a terminal
    if(!isatty(STDIN_FILENO))
    {
        fprintf(stderr,"not a terminal\n");
        exit(NOT_STARTED_FROM_TERMINAL);
    }

    // save current terminal mode
    tcgetattr(STDIN_FILENO, saved);
    
    // get current mode and change the flags we need
    tcgetattr (STDIN_FILENO, &attr);
    attr.c_lflag &= ~(ICANON|ECHO); /* Clear ICANON and ECHO. */
    attr.c_cc[VMIN] = 1;
    attr.c_cc[VTIME] = 0;
    // apply the changed flags
    tcsetattr (STDIN_FILENO, TCSAFLUSH, &attr);
}

/*************************************
 * return the original terminal params
 ************************************/
void resetTerminalInputMode(struct termios saved)
{
    tcsetattr(STDIN_FILENO,TCSANOW, &saved);
}

/**
 * repalces windows kbhit
**/
int _kbhit()
{
    
    int bytesWaiting = 0;
    ioctl(STDIN_FILENO, FIONREAD, &bytesWaiting);

    return bytesWaiting;
}

/**
 * replaces windows _getch
**/
int _getch()
{
    int bytesWaiting;
    ioctl(STDIN_FILENO, FIONREAD, &bytesWaiting);
    
    int c = 0;
    if(-1!=read(STDIN_FILENO, &c, bytesWaiting))// check an error happand
    {
        return c;
    }
    else
    {
        exit(BAD_STDIN_READ);
    }
}

/**
 * sleep for miliseconds
**/
void Sleep(long miliSeconds)
{
    usleep(miliSeconds*1000);
}

/**
 * not needed in linux
**/
void _flushall()
{
    
}