#include "pch.h"
#include "Generator.h"

using namespace std;

// Consts
const string ResourceFolder = "Resources";
const string PlacesFilename = "places.txt";
const string TitlesFilename = "titles.txt";
const string AnimalsFilename = "animals.txt";
const int HashingIterations = 6091;
const char LowercaseAlphabet[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
const char CapitalAlphabet[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
const char Numbers[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
const char SpecialCharacters[] = { '?', '_', '-', '!', '@', '$', '#', '&' };
// Headers
void beginDecryptFile();
int chooseOption();
string decryptFile(string fileFullPath, string encryptionKey);
void encryptFile(string fileFullPath, string password, string key);
bool flipACoin();
void generateWordKey();
void generateCharacterKey();
string getEncryptionKey();
string getFilePath();
int getRandomIntUpTo(int range);
string getRandomStringFromFile(string filename);
wstring s2ws(string& s);

string ExecutablePath;

void Generator::run(char executablePath[])
{
    ExecutablePath = executablePath;

    int key;
    do
    {
        key = chooseOption();
        switch (key)
        {
            case '1':
                generateWordKey();
                break;
            case '2':
                //generateCharacterKey();
                cout << "\nThis feature not yet implemented.";
                break;
            case '3':
                beginDecryptFile();
                break;
        }
    } while (key != 'q');
}

void beginDecryptFile()
{
    cout << "\nPlease enter the full path to the file: ";
    string fileFullPath;
    getline(cin, fileFullPath);
    string encryptionKey = getEncryptionKey();
    string decryptedPassword = decryptFile(fileFullPath, encryptionKey);
    cout << "\n\nThe file has been decrypted successfully!";
    cout << "\nYour password is: " + decryptedPassword + "\n\n";
}

int chooseOption()
{
    // a bool to store if the loop has run once already
    bool afterFirst = false;
    // stores last key press
    int key;

    do
    {
        key = NULL;
        if (afterFirst)
            std::cout << endl << endl << "Invalid selection. Please choose a valid option." << endl << endl;

        std::cout << "(1) Generate a word key" << endl;
        std::cout << "(2) Generate a character key" << endl;
        std::cout << "(3) Decrypt file" << endl;
        std::cout << endl << "(Q) Quit Application";
        std::cout << endl << endl << "Your selection: ";
        string input;
        getline(cin, input);
        key = input[0];
        afterFirst = true;
    } while (key != '1' && key != '2' && key != '3' && key != 'q');

    return key;
}

string decryptFile(string fileFullPath, string encryptionKey)
{
    fstream fileStream(fileFullPath, fstream::in);
    if (!fileStream)
    {
        cout << "Error opening file: '" << fileFullPath << "'.";
        cout << "\nPress any key to exit.";
        _getch();
        exit(1);
    }
    fileStream.close();
    string encryptedPassword = "";
    fileStream.open(fileFullPath, fstream::in | fstream::out);
    fileStream >> encryptedPassword;
    fileStream.close();
    // Get the character count of the encryption key
    int keyCount = 0;
    for (size_t i = 0; i < encryptionKey.length(); i++)
        keyCount += encryptionKey[i];
    // Remove the encryption
    string decryptedPassword = encryptedPassword;
    for (size_t i = 0; i < encryptedPassword.length(); i++)
        decryptedPassword[i] = encryptedPassword[i] - keyCount;

    return decryptedPassword;
}

void encryptFile(string fileFullPath, string password, string encryptionKey)
{
    // Get the character count of the encryption key
    int keyCount = 0;
    for (size_t i = 0; i < encryptionKey.length(); i++)
        keyCount += encryptionKey[i];
    // Add the key count to each ASCII character
    string encryptedPass = password;
    for (size_t i = 0; i < password.length(); i++)
        encryptedPass[i] = password[i] + keyCount;

    fstream fileStream(fileFullPath, fstream::out);
    if (!fileStream)
    {
        cout << "Error opening file: '" << fileFullPath << "'.";
        cout << "\nPress any key to exit.";
        _getch();
        exit(1);
    }
    fileStream.close();
    // Write password to file
    fileStream.open(fileFullPath, fstream::in | fstream::out);
    fileStream << encryptedPass;
    fileStream.close();
}

bool flipACoin()
{
    return rand() % 101 < 50 ? true : false;
}

void generateWordKey()
{
    bool firstOrSecond = false;
    string generatedPassword = "";
    string uniqueTitle = getRandomStringFromFile(TitlesFilename);
    string uniquePlace = getRandomStringFromFile(PlacesFilename);
    string thirdString = getRandomStringFromFile(AnimalsFilename);

    char numberForPassword = Numbers[getRandomIntUpTo(sizeof(Numbers) - 1)];
    firstOrSecond = flipACoin();

    cout << "\nYour new password is:\t";
    generatedPassword = uniqueTitle
        + ((firstOrSecond) ? "" : "_")
        + uniquePlace
        + ((firstOrSecond) ? "_" : "")
        + thirdString
        + numberForPassword;
    cout << generatedPassword;

    //string masterPassword = "";
    string fileFullPath = getFilePath();
    string encryptionKey = getEncryptionKey();
    encryptFile(fileFullPath, generatedPassword, encryptionKey);
    cout << "\nYour password file has been encrypted successfully.\n\n";
}

void generateCharacterKey()
{

}

string getFilePath()
{
    string fileFullPath = "";
    try
    {
        cout << "\nPlease enter the full path with filename and extension: ";
        getline(cin, fileFullPath);
        if (fileFullPath == "")
        {
            cout << "\nFile path is empty.";
            return getFilePath();
        }
        return fileFullPath;
    }
    catch (int e)
    {
        cout << printf("\n%c\n", e);
    }
    catch (...)
    {
        cout << "An unknown error has occurred.";
    }
    return fileFullPath;
}

string getEncryptionKey()
{
    const char star = '*';
    char key;
    string encryptionKey = "";
    do
    {
        cout << "Please enter a password for this file: ";
        while (true)
        {
            key = _getch();
            if (key == '\r')
                break;
            else if (key == '\b')
            {
                if (encryptionKey.length() > 0)
                {
                    encryptionKey = encryptionKey.substr(0, encryptionKey.length() - 1);
                    cout << "\b \b"; // write a backspace character, deleting the last char in the string
                }
            }
            else if (isalnum(key))
            {
                encryptionKey += key;
                cout << star;
            }
        }
    } while (encryptionKey == "");

    return encryptionKey;
}

int getRandomIntUpTo(int range)
{
    return rand() % (range + 1);
}

string getRandomStringFromFile(string filename)
{
    string randomString;
    fstream fileStream;
    fileStream.open(ExecutablePath + "\\..\\" + ResourceFolder + "\\" + filename);
    if (!fileStream)
    {
        cout << "Error opening a resource file: '" + filename + "'.";
        cout << "\nPress any key to exit.";
        _getch();
        exit(1);
    }
    vector <string> values;
    string tempString;
    while (!fileStream.eof())
    {
        getline(fileStream, tempString);
        bool isAlpha = true;
        for (size_t i = 0; i < tempString.length(); i++)
        {
            if (!isalpha(tempString[i]))
            {
                isAlpha = false;
                break;
            }
        }
        if (isAlpha)
            values.push_back(tempString);
    }
    int randIndex = getRandomIntUpTo(values.size());
    return values[randIndex];
}

// Source: https://stackoverflow.com/a/27296
wstring s2ws(string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    wstring r(buf);
    delete[] buf;
    return r;
}
