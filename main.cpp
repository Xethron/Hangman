/*
 * =====================================================================================
 *
 *       Filename:  hangman.cpp
 *
 *    Description:  Hangman Game. User guesses needs to guess the letters to a word.
 *                      The user has 10 tries in which to guess the letters.
 *
 *        Version:  0.4.1.3
 *        Created:  8 March 2012
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Bernhard Breytenbach
 *   Organization:  Unforged
 *
 * =====================================================================================
 */

#include <iostream> //Command Prompt Input output
#include <fstream> //Usage of Files
#include <curses.h>

using namespace std;

string alphabet="a b c d e f g h i j k l m n o p q r s t u v w x y z"; //used for validation
string line, guessed, word, display;
int numlines=0,inttries=0;
ifstream myfile("words.txt"); //File containing all the words

/*******************************
** Create all the Underscores **
*******************************/
void makeDisplay ()
{
    display = "";
    for (int k=0;k<string(word).size();k++)
        display=display+"_"; //Add one underscore for every letter in the word
    guessed="_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _";
}

/******************************************************
** ASCII MAN!!! d-_-b One for every number of tries! **
******************************************************/
string makeMan ()
{
    switch ( inttries )
    {
        case 10:return "\n  ================|\n //               |\n ||               |\n ||               |\n ||              _^_\n ||             / ..\\\n ||            [  _  ]\n ||             \\___/\n ||\n ||               ||    - *Snap!!!*\n ||              /||\\\n ||             //||\\\\\n ||            // || \\\\\n ||            *  ||  *\n ||              //\\\\\n ||             //  \\\\\n /\\            //    \\\\\n//\\\\         ***      ***\n/||\\\\\n_||_\\\\\n";
        case 9:return "\n  ================|\n //               |\n ||               |\n ||               |\n ||              _^_\n ||             / ..\\\n ||            [  _  ]\n ||             \\___/\n ||               ||\n ||              /||\\\n ||             //||\\\\\n ||            // || \\\\\n ||            *  ||  *\n ||              //\n ||             //\n ||            //\n /\\          ***\n//\\\\ \n/||\\\\ \n_||_\\\\\n";
        case 8:return "\n  ================|\n //               |\n ||               |\n ||               |\n ||              _^_\n ||             / ..\\\n ||            [  _  ]\n ||             \\___/\n ||               ||\n ||              /||\\\n ||             //||\\\\\n ||            // || \\\\\n ||            *  ||  *\n ||\n ||\n ||\n /\\\n//\\\\\n/||\\\\\n_||_\\\\\n";
        case 7:return "\n  ================|\n //               |\n ||               |\n ||               |\n ||              _^_\n ||             / ..\\\n ||            [  _  ]\n ||             \\___/\n ||               ||\n ||              /||\n ||             //||\n ||            // ||\n ||            *  ||\n ||\n ||\n ||\n /\\\n//\\\\\n/||\\\\\n_||_\\\\\n";
        case 6:return "\n  ================|\n //               |\n ||               |\n ||               |\n ||              _^_\n ||             / ..\\\n ||            [  _  ]\n ||             \\___/\n ||               ||\n ||               ||\n ||               ||\n ||               ||\n ||               ||\n ||\n ||\n ||\n /\\\n//\\\\\n/||\\\\\n_||_\\\\\n";
        case 5:return "\n  ================|\n //               |\n ||               |\n ||               |\n ||              _^_\n ||             / ..\\\n ||            [  _  ]\n ||             \\___/\n ||               ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n /\\\n//\\\\\n/||\\\\\n_||_\\\\\n";
        case 4:return "\n  ================|\n //               |\n ||               |\n ||               |\n ||              _^_\n ||             / ..\\\n ||            [  _  ]\n ||             \\___/\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n /\\\n//\\\\\n/||\\\\\n_||_\\\\\n";
        case 3:return "\n  ================|\n //               |\n ||               |\n ||               |\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n /\\\n//\\\\\n/||\\\\\n_||_\\\\\n";
        case 2:return "\n  ================\n //\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n /\\\n//\\\\\n/||\\\\\n_||_\\\\\n";
        case 1:return "\n\n\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n /\\\n//\\\\\n/||\\\\\n_||_\\\\\n";
        case 0:return "\n\n\nCreated By Bernhard Breytenbach for educational purposes. 2008 - 1012\n\nPress * anytime to quit!\n\n\n\n\n\n\n\n\n\n\n\n /\\\n//\\\\\n/||\\\\\n_||_\\\\\n";
    }
}

/****************************************
** Check the guessed letter and add it **
****************************************/
void guesslet (char a)
{
    int correct=0,tried=0,validlet=0,k=0;

    for (k = 0; k < 51; k+=2) //Alphabetic Checks
        if (alphabet[k]==a) //Check if letter is in alphabet
        {
            validlet=1; //Confirm valid entery
            if (guessed[k]!=a) //Check to see if the letter has been tried before
                guessed[k]=a; //Save letter in String
                    else
                        tried=1; //Letter has been tried before
        }
    
    if ((tried!=1) && (validlet==1)) //Check if letter is valid and hasn't been tried before
    {
        for (k=0;k<string(word).size();k++)
            if (word[k]==a) //Check if the letter is in the word
            {
                display[k]=a; //Change the underscore to the letter
                correct=1; //Yes, there is at least one correct letter
            }
        if (correct!=1)
           inttries++; //If the letter isn't in the word, increase tries
    }
}

/************************************************
** Select a random word from the text document **
************************************************/
int selectRandLine ()
{
    int randline=0, wordlength=0, k=0;
    string newword;
    //Generate random line
    randline = (rand()%numlines)+1;
    //Reset curser to first line
    myfile.clear();    
    myfile.seekg(0, ios::beg);
    //Grab line from file
    for (int lineno = 0; getline (myfile,newword) && lineno < randline; lineno++);
    wordlength=string(newword).size();
    word="";
    for (int i = 0; wordlength>i; i++)
    {
        for (k = 0; k < 51; k+=2) //Alphabetic Checks
            if (alphabet[k]==newword[i]) //Check if letter is in alphabet
                word=word+newword[i];
    }
}

/*******************
** The main class **
*******************/
int main ()
{
    initscr();
    char a; //Guessing letter
    srand((unsigned)time(0)); //Seed RNG
    while (std::getline(myfile, line)) ++numlines; //Open the word list and count how many words are present.
    
    while (a!='*') //Continuous loop with exit number 2.
    {
        selectRandLine (); //Select a random word from the file
        makeDisplay(); //Make the correct number of underscores
        inttries = 0; //Reset number of tries
        while (display!=word) //Exit loop when word is guessed correctly.
        {
            cout << makeMan (); //Draw ASCII Man d-_-b
            cout << "Please guess a letter!\nWord: " << display << "\nGuessed: " << guessed << "\nTries left:" << 10-inttries << "\n";
            cin >> a; //Read user input
            guesslet(a); //Check if letter is valid and in word
            if (a=='*') inttries=10; //Check for quit character
            if (inttries>=10) display=word; //Meet condition to exit loop when tries expire
        }
        cout << makeMan (); //Draw ASCII Man d-_-b
        //Message when user loses.
        if (inttries>=10) cout << "\nYou lost! The word was \"" << word << "\".\nPress any key to play again, or * to quit.\n\n";
        //Message when user wins!
        if (inttries<10) cout << "\nYou won! The word is \"" << word << "\"!\nPress any key to play again, or * to quit.\n\n";
        cin >> a; //Read user input
    }

    return 0;
}
